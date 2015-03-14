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

#include "CCVSizeCalculator.h"

NS_CCV_BEG

const cocos2d::Size& SizeCalculator::getScreenSize() const
{
	return _screenSize;
}

void SizeCalculator::setScreenSize(const cocos2d::Size &screenSize)
{
	_screenSize = screenSize;
}


cocos2d::Size SizeCalculator::calcSize(const BoxSize &logicalSize, const BoxMargin &margin, const cocos2d::Size &parentSize) const
{
	const cocos2d::Rect area = margin.toRect(parentSize, _screenSize);
	return logicalSize.toSize(area.size, _screenSize);
}

cocos2d::Vec2 SizeCalculator::calcPosition(const BoxPosition &logicalPosition, const BoxMargin &margin, const cocos2d::Size &parentSize) const
{
	const cocos2d::Rect area = margin.toRect(parentSize, _screenSize);
	return logicalPosition.toVec2(area.size, _screenSize) + cocos2d::Vec2(area.origin.x, area.origin.y);
}

NS_CCV_END
