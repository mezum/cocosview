/*
 Copyright (c) 2015 RyujuOrchestra.
 This software is released under the MIT License.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#include "CCVBox.h"
#include "CCVRootBox.h"
#include "CCVBoxEventDetail.h"

USING_NS_CC;

NS_CCV_BEG

Box::Box(Node *view, bool isRootNode)
: _view(view), _joined(isRootNode)
{
	view->retain();
}

bool Box::init()
{
	return true;
}

Box::~Box()
{
	_view->release();
}

Box::ConstPointer Box::getRoot() const
{
	return _parent.expired() ? nullptr : _parent.lock()->getParent();
}

Box::Pointer Box::getRoot()
{
	return _parent.expired() ? nullptr : _parent.lock()->getParent();
}

Box::Pointer Box::getParent() const
{
	return _parent.expired() ? nullptr : _parent.lock();
}

void Box::setParent(Box::Pointer box)
{
	_parent = std::move(box);
	_joined = !_parent.expired();
	if (_joined) onEnter.dispatch();
	else         onExit.dispatch();
}

Node* Box::getView() const
{
	return _view;
}

const Vec2& Box::getAnchorPoint() const
{
	return getView()->isIgnoreAnchorPointForPosition() ? Vec2::ZERO : getView()->getAnchorPoint();
}

void Box::setAnchorPoint(const Vec2 &anchor)
{
	getView()->setAnchorPoint(anchor);
}

const BoxSize& Box::getSize() const
{
	return _size;
}

void Box::setSize(const cocosview::BoxSize &size)
{
	_size = size;
	if (_joined) {
		auto &calc = dynamic_pointer_cast<RootBox>(getRoot())->getSizeCalculator();
		updateSize(calc);
		updatePosition(calc);
	}
}

const BoxPosition& Box::getPosition() const
{
	return _position;
}

void Box::setPosition(const BoxPosition &position)
{
	_position = position;
	if (_joined) {
		auto &calc = dynamic_pointer_cast<RootBox>(getRoot())->getSizeCalculator();
		updatePosition(calc);
	}
}

const BoxMargin& Box::getMargin() const
{
	return _margin;
}

void Box::setMargin(const BoxMargin &margin)
{
	_margin = margin;
	if (_joined) {
		auto &calc = dynamic_pointer_cast<RootBox>(getRoot())->getSizeCalculator();
		updateSize(calc);
		updatePosition(calc);
	}
}

void Box::addChild(Box::Pointer child)
{
	getView()->addChild(child->getView());
	child->setParent(shared_from_this());
	_children.insert(child);
	child->doLayout();
}

void Box::removeChild(Box::Pointer child)
{
	_children.erase(child);
	child->setParent(nullptr);
	getView()->removeChild(child->getView());
}

void Box::doLayout()
{
	auto &calc = dynamic_pointer_cast<RootBox>(getRoot())->getSizeCalculator();
	updateSize(calc);
	updatePosition(calc);
}

void Box::onParentSizeChanged(const SizeCalculator &calc)
{
	updateSize(calc);
	updatePosition(calc);
}

void Box::updateSize(const SizeCalculator &calc)
{
	auto parent = getParent();
	const Size &parentSize = parent ? parent->getView()->getContentSize() : calc.getScreenSize();
	
	Size oldSize = getView()->getContentSize();
	Size newSize = calc.calcSize(_size, _margin, parentSize);
	if (newSize.width == oldSize.width && newSize.height == oldSize.height) return;
	
	applySize(newSize);
	for (auto &child : _children) child->onParentSizeChanged(calc);
	
	BoxEventDetail eventDetail{shared_from_this(), false};
	onResized.dispatch(eventDetail);
}

void Box::updatePosition(const SizeCalculator &calc)
{
	auto parent = getParent();
	const Size &parentSize = parent ? parent->getView()->getContentSize() : calc.getScreenSize();
	Vec2 position = calc.calcPosition(_position, _margin, parentSize);
	
	getView()->setPosition(position);
}

void Box::applySize(const cocos2d::Size &size)
{
	getView()->setContentSize(size);
}

NS_CCV_END

