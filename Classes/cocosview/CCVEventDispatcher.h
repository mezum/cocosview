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

#ifndef cocosview_CCVEvent_h
#define cocosview_CCVEvent_h

#include <memory>
#include <functional>
#include <vector>
#include "CCVMacros.h"
#include "CCVEventDetail.h"
#include "CCVEventListener.h"

NS_CCV_BEG
/**
 * event dispatcher class.
 */
class EventDispatcher
{
	public:
		/** add event listener */
		void addListener(EventListener::Pointer listener, bool useWeakReference = false);
	
		/** remove event listener */
		void removeListener(EventListener::Pointer listener);
	
		/** indicate whether the listener list contains this listener */
		bool hasListener(EventListener::Pointer listener) const;
	
		/**
		 * dispatch event.
		 * @return true if the dispatching is not cancelled, otherwise false.
		 */
		bool dispatch();
		bool dispatch(EventDetail &detail);
	
	private:
		std::vector<EventListener::WeakPointer> _listeners;
		std::vector<EventListener::Pointer> _referenceKeeper;
};
NS_CCV_END

#endif
