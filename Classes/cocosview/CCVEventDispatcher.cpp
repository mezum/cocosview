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

#include "CCVEventDispatcher.h"
#include <algorithm>

NS_CCV_BEG

void EventDispatcher::addListener(EventListener::Pointer listener, bool useWeakReference)
{
	_listeners.emplace_back(listener);
	if (useWeakReference) _referenceKeeper.emplace_back();
	else                  _referenceKeeper.emplace_back(listener);
}

void EventDispatcher::removeListener(EventListener::Pointer listener)
{
	for (auto it = std::begin(_listeners); it != std::end(_listeners);) {
		if (it->expired()) {
			auto index = std::distance(std::begin(_listeners), it);
			it = _listeners.erase(it);
			_referenceKeeper.erase(std::begin(_referenceKeeper) + index);
			continue;
		}
		
		if (it->lock() == listener) {
			auto index = std::distance(std::begin(_listeners), it);
			_listeners.erase(it);
			_referenceKeeper.erase(std::begin(_referenceKeeper) + index);
			break;
		}
		++it;
	}
}

bool EventDispatcher::hasListener(EventListener::Pointer listener) const
{
	for (auto it = std::begin(_listeners); it != std::end(_listeners);) {
		if (it->expired()) continue;
		if (it->lock() == listener) return true;
	}
	return false;
}

bool EventDispatcher::dispatch()
{
	EventDetail detail;
	dispatch(detail);
}

bool EventDispatcher::dispatch(EventDetail &detail)
{
	for (auto it = std::begin(_listeners); it != std::end(_listeners);) {
		if (it->expired()) {
			auto index = std::distance(std::begin(_listeners), it);
			it = _listeners.erase(it);
			_referenceKeeper.erase(std::begin(_referenceKeeper) + index);
			continue;
		}
		
		it->lock()->func(detail);
		if (detail.isCancelled()) return false;
		++it;
	}
	return true;
}

NS_CCV_END
