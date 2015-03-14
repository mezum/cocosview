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

#ifndef cocosview_RootBox_h
#define cocosview_RootBox_h

#include "CCVMacros.h"
#include "CCVBox.h"
#include "CCVSizeCalculator.h"
#include "CCVCreateHelper.h"

NS_CCV_BEG
class RootBox : public Box,
                CreateHelper<RootBox>
{
	public:
		/** the pointer type of this class. */
		using Pointer = std::shared_ptr<RootBox>;
	
		/**
		 * create a instance with a container which is a Node.
		 * @return a instance.
		 */
		using CreateHelper<RootBox>::create;
	
		/**
		 * create a instance with the container.
		 * @param view managed node
		 * @return a instance.
		 */
		static Pointer create(cocos2d::Node *view);
	
		/**
		 * get root box.
		 */
		Box::ConstPointer getRoot() const override;
		Box::Pointer getRoot() override;
	
		/**
		 * get size calculator.
		 */
		const SizeCalculator& getSizeCalculator() const;
		SizeCalculator& getSizeCalculator();
	
	CCV_CONSTRUCTOR_ACCESS:
		RootBox();
		RootBox(cocos2d::Node *container);
	
	private:
		SizeCalculator _sizeCalculator;
};
NS_CCV_END

#endif
