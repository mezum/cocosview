/*
 CopyY_AXIS (c) 2015 RyujuOrchestra.
 This software is released under the MIT License.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the Y_AXISs
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyY_AXIS notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYY_AXIS HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#include <limits>
#include "CCVScrollBox.h"
#include "CCVDefaultScrollInertia.h"

USING_NS_CC;

static constexpr EventKeyboard::KeyCode KEY_ZOOM = EventKeyboard::KeyCode::KEY_ALT;

#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
static constexpr EventKeyboard::KeyCode KEY_SWAP = EventKeyboard::KeyCode::KEY_HYPER;
#else
static constexpr EventKeyboard::KeyCode KEY_SWAP = EventKeyboard::KeyCode::KEY_CTRL;
#endif

static constexpr int X_AXIS = 0;
static constexpr int Y_AXIS = 1;

static const std::string UPDATE_FUNC_ID = "ScrollBox::update";

NS_CCV_BEG

ScrollBox::ScrollBox()
: Box(ClippingRectangleNode::create()),
  _scrollableDirection(ScrollableDirection::BOTH),
  _isZoomingEnabled(true),
  _isZoomingKeyPressed(false),
  _isSwappingKeyPressed(false),
  _contentScale(1.0f),
  _isAutoFitScrollAreaEnabled(true)
{
	auto *view = reinterpret_cast<ClippingRectangleNode*>(getView());
	view->setClippingEnabled(true);
	
	view->setOnEnterCallback([this] {
		auto *view = reinterpret_cast<ClippingRectangleNode*>(getView());
		
		auto mouseListener = EventListenerMouse::create();
		mouseListener->onMouseScroll = CC_CALLBACK_1(ScrollBox::onMouseScroll, this);
		
		auto keyListener = EventListenerKeyboard::create();
		keyListener->onKeyPressed = CC_CALLBACK_2(ScrollBox::onKeyPressed, this);
		keyListener->onKeyReleased = CC_CALLBACK_2(ScrollBox::onKeyReleased, this);
		
		auto *dispatcher = Director::getInstance()->getEventDispatcher();
		dispatcher->addEventListenerWithSceneGraphPriority(mouseListener, view);
		dispatcher->addEventListenerWithSceneGraphPriority(keyListener, view);
	});
	
	_inertias[X_AXIS] = std::unique_ptr<DefaultScrollInertia>( new DefaultScrollInertia() );
	_inertias[X_AXIS]->setMin(-std::numeric_limits<float>::max());
	_inertias[X_AXIS]->setMax(std::numeric_limits<float>::max());
	
	_inertias[Y_AXIS] = std::unique_ptr<DefaultScrollInertia>( new DefaultScrollInertia() );
	_inertias[Y_AXIS]->setMin(-std::numeric_limits<float>::max());
	_inertias[Y_AXIS]->setMax(std::numeric_limits<float>::max());
	
	std::function<void(float)> updateFunc = std::bind(&ScrollBox::update, std::ref(*this), std::placeholders::_1);
	getView()->schedule(updateFunc, UPDATE_FUNC_ID);
	
	EventListener::Function onResizedFunc = std::bind(&ScrollBox::onResizedHandler, std::ref(*this), std::placeholders::_1);
	_onResizeListener = EventListener::create(onResizedFunc);
	onResized.addListener(_onResizeListener, true);
}

Box::ConstPointer ScrollBox::getContent() const
{
	return _content;
}

Box::Pointer ScrollBox::getContent()
{
	return _content;
}

void ScrollBox::setContent(Box::Pointer content)
{
	if (_content) removeChild(_content);
	_content = content;
	if (_isAutoFitScrollAreaEnabled) {
		fitScrollArea();
		updateContentPosition();
	}
	else {
		_content->setPosition(_contentBoxPosition);
	}
	
	_content->getView()->setScale(_contentScale);
	addChild(_content);
}

bool ScrollBox::isClippingEnabled() const
{
	return reinterpret_cast<ClippingRectangleNode*>(getView())->isClippingEnabled();
}

void ScrollBox::setClippingEnabled(bool enabled)
{
	reinterpret_cast<ClippingRectangleNode*>(getView())->setClippingEnabled(enabled);
}

bool ScrollBox::isZoomingEnabled() const
{
	return _isZoomingEnabled;
}

void ScrollBox::setZoomingEnabled(bool enabled)
{
	_isZoomingEnabled = enabled;
}

ScrollableDirection ScrollBox::getScrollableDirection() const
{
	return _scrollableDirection;
}

void ScrollBox::setScrolableDirection(ScrollableDirection direction)
{
	_scrollableDirection = direction;
}

const LayoutGravity& ScrollBox::getLayoutGravity() const
{
	return _layoutGravity;
}

void ScrollBox::setHorizontalLayoutGravity(LayoutGravity::Horizontal gravity)
{
	if (_layoutGravity.horizontal != gravity) {
		_layoutGravity.horizontal = std::move(gravity);
		if (_isAutoFitScrollAreaEnabled) updateScrollDomain(X_AXIS);
	}
}

void ScrollBox::setVerticalLayoutGravity(LayoutGravity::Vertical gravity)
{
	if (_layoutGravity.vertical != gravity) {
		_layoutGravity.vertical = std::move(gravity);
		if (_isAutoFitScrollAreaEnabled) updateScrollDomain(Y_AXIS);
	}
}

const std::unique_ptr<ScrollInertia>& ScrollBox::getInertiaX() const
{
	return _inertias[X_AXIS];
}

void ScrollBox::setInertiaX(std::unique_ptr<ScrollInertia> inertia)
{
	float current = _inertias[X_AXIS]->getCurrent();
	_inertias[X_AXIS] = std::move(inertia);
	_inertias[X_AXIS]->moveTo(current);
	if (_isAutoFitScrollAreaEnabled) updateScrollDomain(X_AXIS);
}

const std::unique_ptr<ScrollInertia>& ScrollBox::getInertiaY() const
{
	return _inertias[Y_AXIS];
}

void ScrollBox::setInertiaY(std::unique_ptr<ScrollInertia> inertia)
{
	float current = _inertias[Y_AXIS]->getCurrent();
	_inertias[Y_AXIS] = std::move(inertia);
	_inertias[Y_AXIS]->moveTo(current);
	if (_isAutoFitScrollAreaEnabled) updateScrollDomain(X_AXIS);
}

bool ScrollBox::isAutoFitScrollAreaEnabled() const
{
	return _isAutoFitScrollAreaEnabled;
}

void ScrollBox::enableAutoFitScrollArea(bool enabled)
{
	_isAutoFitScrollAreaEnabled = enabled;
	if (enabled) fitScrollArea();
}

void ScrollBox::fitScrollArea()
{
	updateScrollDomain(X_AXIS);
	updateScrollDomain(Y_AXIS);
}

void ScrollBox::jumpTo(LayoutGravity::Vertical target)
{
	auto &inertia = _inertias[X_AXIS];
	switch (target) {
		case LayoutGravity::Vertical::TOP:
			inertia->moveTo(inertia->getMax());
			break;
		case LayoutGravity::Vertical::MIDDLE:
			inertia->moveTo((inertia->getMax() + inertia->getMin()) / 2);
			break;
		case LayoutGravity::Vertical::BOTTOM:
			inertia->moveTo(inertia->getMin());
			break;
	}
}

void ScrollBox::jumpTo(LayoutGravity::Horizontal target)
{
	auto &inertia = _inertias[Y_AXIS];
	switch (target) {
		case LayoutGravity::Horizontal::LEFT:
			inertia->moveTo(inertia->getMin());
			break;
		case LayoutGravity::Horizontal::CENTER:
			inertia->moveTo((inertia->getMax() + inertia->getMin()) / 2);
			break;
		case LayoutGravity::Horizontal::RIGHT:
			inertia->moveTo(inertia->getMax());
			break;
	}
}

void ScrollBox::onMouseScroll(Event *event)
{
	if (!_content) return;
	
	auto *mouseEvent = reinterpret_cast<EventMouse*>(event);
	
	auto *view = getView();
	auto &size = view->getContentSize();
	Rect area{0, 0, size.width, size.height};
	
	// check cursor area
	if (!area.containsPoint(view->convertToNodeSpace(mouseEvent->getLocation()))) {
		return;
	}
	
	// zoom in/out
	if (_isZoomingKeyPressed) {
		if (!_isZoomingEnabled) return;
		
		_contentScale += (mouseEvent->getScrollX() + mouseEvent->getScrollY()) * 0.01f;
		_content->getView()->setScale(_contentScale);
		if (_isAutoFitScrollAreaEnabled) fitScrollArea();
	}
	// scroll
	else {
		if (_scrollableDirection == ScrollableDirection::NONE) return;
		float scrollX = mouseEvent->getScrollX() * 5.0f;
		float scrollY = mouseEvent->getScrollY() * 5.0f;
		if (_isSwappingKeyPressed) {
			float temp = scrollY;
			scrollY = scrollX;
			scrollX = temp;
		}
		
		if (_scrollableDirection == ScrollableDirection::VERTICAL) scrollX = 0.0f;
		if (_scrollableDirection == ScrollableDirection::HORIZONTAL) scrollY = 0.0f;
		
		_inertias[X_AXIS]->drag(scrollX);
		_inertias[Y_AXIS]->drag(scrollY);
	}
}

void ScrollBox::onKeyPressed(EventKeyboard::KeyCode code, Event *event)
{
	switch (code) {
		case KEY_ZOOM:
			_isZoomingKeyPressed = true;
			break;
		case KEY_SWAP:
			_isSwappingKeyPressed = true;
			break;
		default:
			break;
	}
}

void ScrollBox::onKeyReleased(EventKeyboard::KeyCode code, Event *event)
{
	switch (code) {
		case KEY_ZOOM:
			_isZoomingKeyPressed = false;
			break;
		case KEY_SWAP:
			_isSwappingKeyPressed = false;
			break;
		default:
			break;
	}
}

void ScrollBox::onResizedHandler(EventDetail &detail)
{
	if (_content && _isAutoFitScrollAreaEnabled) {
		fitScrollArea();
	}
}

void ScrollBox::update(float delta)
{
	_inertias[X_AXIS]->update(delta);
	_inertias[Y_AXIS]->update(delta);
	updateContentPosition();
}

void ScrollBox::updateContentPosition()
{
	_contentBoxPosition.x.value = _inertias[X_AXIS]->getCurrent();
	_contentBoxPosition.y.value = _inertias[Y_AXIS]->getCurrent();
	_content->setPosition(_contentBoxPosition);
}

void ScrollBox::updateScrollDomain(int axis)
{
	float containerSize;
	float contentSize;
	float anchorOffset;
	if (axis == X_AXIS) {
		containerSize = getView()->getContentSize().width;
		contentSize = _content->getView()->getContentSize().width * _contentScale;
		anchorOffset = contentSize * _content->getAnchorPoint().x;
	}
	else {
		containerSize = getView()->getContentSize().height;
		contentSize = _content->getView()->getContentSize().height * _contentScale;
		anchorOffset = contentSize * _content->getAnchorPoint().y;
	}
	
	if (contentSize >= containerSize) {
		float rest = contentSize - containerSize;
		_inertias[axis]->setMin(-rest + anchorOffset);
		_inertias[axis]->setMax(-0.0f + anchorOffset);
	}
	else {
		float pos = 0.0f;
		if (axis == X_AXIS) {
			switch (_layoutGravity.horizontal) {
				case LayoutGravity::Horizontal::LEFT:
					pos = 0.0f + anchorOffset;
					break;
				case LayoutGravity::Horizontal::CENTER:
					pos = (containerSize - contentSize) / 2 + anchorOffset;
					break;
				case LayoutGravity::Horizontal::RIGHT:
					pos = (containerSize - contentSize) + anchorOffset;
					break;
			}
		}
		else {
			switch (_layoutGravity.vertical) {
				case LayoutGravity::Vertical::TOP:
					pos = (containerSize - contentSize) + anchorOffset;
					break;
				case LayoutGravity::Vertical::MIDDLE:
					pos = (containerSize - contentSize) / 2 + anchorOffset;
					break;
				case LayoutGravity::Vertical::BOTTOM:
					pos = 0.0f + anchorOffset;
					break;
			}
		}
		_inertias[axis]->setMin(pos);
		_inertias[axis]->setMax(pos);
	}
}

NS_CCV_END
