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

#ifndef cocosview_CCVEventDetail_h
#define cocosview_CCVEventDetail_h

#include "CCVMacros.h"

NS_CCV_BEG
class EventDetail
{
	public:
		/** indicate whether the event is able to cancel to call next listeners. */
		bool isCancelable() const { return _isCancelable; }
	
		/** indicate whether the event cancelled. */
		bool isCancelled() const { return _isCancelled; }
	
		/** constructor */
		EventDetail(bool isCancelable = true);
	
		/**
		 * cancel to call next listeners.
		 * If the event is not able to cancel, the method do nothing.
		 */
		void stopImmediately();
	
		/** destructor. */
		virtual ~EventDetail() = default;
	
	private:
		const bool _isCancelable;
		bool _isCancelled;
};
NS_CCV_END

#endif
