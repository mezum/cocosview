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

#ifndef cocosview_CCVSpriteBox_h
#define cocosview_CCVSpriteBox_h

#include <memory>
#include "cocos2d.h"
#include "CCVBox.h"
#include "CCVCreateHelper.h"

NS_CCV_BEG
class SpriteBox : public Box,
                  CreateHelper<SpriteBox>
{
	public:
		/** the pointer type of this class. */
		using Pointer = std::shared_ptr<SpriteBox>;
	
		/**
		 * create a instance.
		 * @param sprite target sprite
		 * @return a instance.
		 */
		using CreateHelper<SpriteBox>::create;
	
	protected:
		void applySize(const cocos2d::Size &size) override;
	
	CCV_CONSTRUCTOR_ACCESS:
		SpriteBox(cocos2d::Sprite *sprite);
};
NS_CCV_END

#endif
