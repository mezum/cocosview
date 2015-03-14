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

#ifndef cocosview_PanelBox_h
#define cocosview_PanelBox_h

#include <memory>
#include "cocosview/cocosview.h"
#include "Operator.h"

NS_CCV_BEG
class PanelBox : public Box
{
	public:
		PanelBox(std::shared_ptr<Operator> op);
	
		const cocos2d::Color3B& getBackgroundColor() const;
		void setBackgroundColor(const cocos2d::Color3B &color);
	
		GLbyte getBackgroundOpacity() const;
		void setBackgroundOpacity(GLbyte opacity);
	
		std::shared_ptr<Operator> getOperator() const;
	
	private:
		std::shared_ptr<Operator> _op;
};
NS_CCV_END

#endif
