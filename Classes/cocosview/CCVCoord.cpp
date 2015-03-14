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

#include "CCVCoord.h"

USING_NS_CC;

NS_CCV_BEG

CoordValue::CoordValue()
: type(CoordType::PIXEL), value(0.0f)
{
	
}

CoordValue::CoordValue(CoordType type, float value)
: type(type), value(value)
{
	
}

float CoordValue::toFloat(const Size &parentSize) const
{
	return toFloat(parentSize, Director::getInstance()->getOpenGLView()->getDesignResolutionSize());
}

float CoordValue::toFloat(const Size &parentSize, const Size &screenSize) const
{
	switch (type) {
		case CoordType::PIXEL: return value;
		case CoordType::PARENT_WIDTH: return parentSize.width * value;
		case CoordType::PARENT_HEIGHT: return parentSize.height * value;
		case CoordType::SCREEN_WIDTH: return screenSize.width * value;
		case CoordType::SCREEN_HEIGHT: return screenSize.height * value;
		case CoordType::SCALE: return value;
	}
	return 0.0f;
}

CoordValue CoordValue::applyScale(const CoordValue &base) const
{
	if (type != CoordType::SCALE) return *this;
	return CoordValue{base.type, base.value * value};
}

Vec2 BoxPosition::toVec2(const Size &parentSize) const
{
	return toVec2(parentSize, Director::getInstance()->getOpenGLView()->getDesignResolutionSize());
}

Vec2 BoxPosition::toVec2(const Size &parentSize, const Size &screenSize) const
{
	return Vec2(
		x.toFloat(parentSize, screenSize),
		y.toFloat(parentSize, screenSize)
	);
}

Size BoxSize::toSize(const Size &parentSize) const
{
	return toSize(parentSize, Director::getInstance()->getOpenGLView()->getDesignResolutionSize());
}

Size BoxSize::toSize(const Size &parentSize, const Size &screenSize) const
{
	return Size(
		width.toFloat(parentSize, screenSize),
		height.toFloat(parentSize, screenSize)
	);
}

Rect BoxMargin::toRect(const Size &parentSize) const
{
	return toRect(parentSize, Director::getInstance()->getOpenGLView()->getDesignResolutionSize());
}

Rect BoxMargin::toRect(const Size &parentSize, const Size &screenSize) const
{
	Rect rect;
	rect.origin.x = left.toFloat(parentSize, screenSize);
	rect.origin.y = bottom.toFloat(parentSize, screenSize);
	rect.size.width = parentSize.width - rect.origin.x - right.toFloat(parentSize, screenSize);
	rect.size.height = parentSize.height - rect.origin.y - top.toFloat(parentSize, screenSize);
	return std::move(rect);
}

NS_CCV_END