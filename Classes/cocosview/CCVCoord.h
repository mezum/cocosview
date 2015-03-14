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

#ifndef cocosview_Coord_h
#define cocosview_Coord_h

#include "cocos2d.h"
#include "CCVMacros.h"

NS_CCV_BEG

enum class CoordType
{
	PIXEL,
	SCREEN_WIDTH,
	SCREEN_HEIGHT,
	PARENT_WIDTH,
	PARENT_HEIGHT,
	SCALE
};

struct CoordValue
{
	/** coord type */
	CoordType type = CoordType::PIXEL;
	/** coord value */
	float value = 0.0f;
	
	CoordValue();
	CoordValue(CoordType type, float value);
	
	/** translate to float by real parent size */
	float toFloat(const cocos2d::Size &parentSize) const;
	
	/** translate to float by real parent and screen size */
	float toFloat(const cocos2d::Size &parentSize, const cocos2d::Size &screenSize) const;
	
	/**
	 * apply scale.
	 * @return a coord value applied scale to base value if this coord type is SCALE, otherwise return this coord.
	 */
	CoordValue applyScale(const CoordValue &base) const;
};

struct BoxPosition
{
	CoordValue x;
	CoordValue y;
	
	cocos2d::Vec2 toVec2(const cocos2d::Size &parentSize) const;
	cocos2d::Vec2 toVec2(const cocos2d::Size &parentSize, const cocos2d::Size &screenSize) const;
};

struct BoxSize
{
	CoordValue width;
	CoordValue height;
	
	cocos2d::Size toSize(const cocos2d::Size &parentSize) const;
	cocos2d::Size toSize(const cocos2d::Size &parentSize, const cocos2d::Size &screenSize) const;
};

struct BoxMargin
{
	CoordValue left;
	CoordValue right;
	CoordValue top;
	CoordValue bottom;
	
	cocos2d::Rect toRect(const cocos2d::Size &parentSize) const;
	cocos2d::Rect toRect(const cocos2d::Size &parentSize, const cocos2d::Size &screenSize) const;
};

NS_CCV_END

#endif
