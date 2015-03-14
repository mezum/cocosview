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

#ifndef cocosview_CCVInertia_h
#define cocosview_CCVInertia_h

#include "CCVMacros.h"

NS_CCV_BEG

/**
 * Inertia simulator interface for scroll.
 */
class Inertia
{
	public:
		/** notify the inertia that user begin to move this. */
		virtual void touch() = 0;
	
		/** notify the inertia that user end to move this. */
		virtual void release() = 0;
	
		/** drag value. (relative) */
		virtual void drag(float amount) = 0;
	
		/** set new value. (absolute) */
		virtual void moveTo(float value) = 0;
	
		/** update value */
		virtual void update(float delta) = 0;
	
		/** get current value. */
		float getCurrent() const { return _current; }
	
		/** destructor */
		virtual ~Inertia() = default;
	
	protected:
		/** set value */
		void setCurrent(float value) { _current = value; }
	
	private:
		float _current = 0.0f;
};

NS_CCV_END

#endif
