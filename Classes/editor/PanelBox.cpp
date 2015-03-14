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

#include "PanelBox.h"

USING_NS_CC;

NS_CCV_BEG

PanelBox::PanelBox(std::shared_ptr<Operator> op)
: Box(LayerColor::create()), _op(std::move(op))
{
	Node *view = getView();
	view->ignoreAnchorPointForPosition(false);
	view->setAnchorPoint(Vec2(0.0f, 0.0f));
}

const Color3B& PanelBox::getBackgroundColor() const
{
	return getView()->getColor();
}

void PanelBox::setBackgroundColor(const cocos2d::Color3B &color)
{
	getView()->setColor(color);
}

GLbyte PanelBox::getBackgroundOpacity() const
{
	return getView()->getOpacity();
}

void PanelBox::setBackgroundOpacity(GLbyte opacity)
{
	getView()->setOpacity(opacity);
}

std::shared_ptr<Operator> PanelBox::getOperator() const
{
	return _op;
}

NS_CCV_END
