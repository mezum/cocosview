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

#ifndef cocosview_CCVCreateHelper_h
#define cocosview_CCVCreateHelper_h

#include <type_traits>
#include "CCVMacros.h"
#include "CCVTypeTraits.h"

NS_CCV_BEG
template <class T>
class CreateHelper
{
	private:
		struct TempClass : public T
		{
			template <typename... Args>
			explicit TempClass(Args&&... args) : T(std::forward<Args>(args)...) { }
			
			bool init()
			{
				return T::init();
			}
		};
	
	public:
		template <typename... Args>
		static std::shared_ptr<T> create(Args&&... args)
		{
			auto ptr = std::make_shared<TempClass>(std::forward<Args>(args)...);
			if (!ptr->init()) return nullptr;
			return std::move(ptr);
		}
};
NS_CCV_END

#endif
