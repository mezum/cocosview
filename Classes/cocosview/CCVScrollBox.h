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

#ifndef cocosview_CCVScrollBox_h
#define cocosview_CCVScrollBox_h

#include <memory>
#include <array>
#include "CCVMacros.h"
#include "CCVCreateHelper.h"
#include "CCVBox.h"
#include "CCVScrollableDirection.h"
#include "CCVLayoutGravity.h"
#include "CCVScrollInertia.h"

NS_CCV_BEG

/**
 * the box contains scrollable child.
 */
class ScrollBox : public Box,
                  CreateHelper<ScrollBox>
{
	public:
		/** the pointer type of this class. */
		using Pointer = std::shared_ptr<ScrollBox>;
	
		/** create a instance. */
		using CreateHelper<ScrollBox>::create;
	
		/** get inner content. */
		Box::ConstPointer getContent() const;
		Box::Pointer getContent();
	
		/** set inner content. */
		void setContent(Box::Pointer content);
	
		/**
		 * indicate whether enabled or disabled clipping.
		 * default value is true (enabled).
		 */
		bool isClippingEnabled() const;
	
		/** enable or disable clippling. */
		void setClippingEnabled(bool enabled);

		/**
		 * indicate whether enabled or disabled zooming in/out.
		 * default value is true (enabled).
		 */
		bool isZoomingEnabled() const;
	
		/** enable or disable zooming in/out. */
		void setZoomingEnabled(bool enabled);
	
		/**
		 * get scrollable direction of this ScrollBox.
		 * default value is BOTH.
		 */
		ScrollableDirection getScrollableDirection() const;
	
		/** set scrollable direction of this ScrollBox. */
		void setScrolableDirection(ScrollableDirection direction);
	
		/** get layout gravity. */
		const LayoutGravity& getLayoutGravity() const;
	
		/** set horizontal layout gravity. */
		void setHorizontalLayoutGravity(LayoutGravity::Horizontal gravity);
	
		/** set vertical layout gravity */
		void setVerticalLayoutGravity(LayoutGravity::Vertical gravity);
	
		/** x axis inertia object. */
		const std::unique_ptr<ScrollInertia>& getInertiaX() const;
		void setInertiaX(std::unique_ptr<ScrollInertia> inertia);
	
		/** y axis inertia object. */
		const std::unique_ptr<ScrollInertia>& getInertiaY() const;
		void setInertiaY(std::unique_ptr<ScrollInertia> inertia);
	
		/**
		 * indicate whether enabled or disabled auto-fit scroll area when resize the ScrollBox and change inertia.
		 * default value is true (enabled).
		 */
		bool isAutoFitScrollAreaEnabled() const;
	
		/** set flag of auto-fit scroll area. */
		void enableAutoFitScrollArea(bool enabled);
	
		/** fit scroll area. */
		void fitScrollArea();
	
		/** scroll immediately without animation. */
		void jumpTo(LayoutGravity::Vertical target);
		void jumpTo(LayoutGravity::Horizontal target);
	
	CCV_CONSTRUCTOR_ACCESS:
		ScrollBox();
	
	private:
		void onMouseScroll(cocos2d::Event *event);
		void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event);
		void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event);
	
		void onResizedHandler(EventDetail &detail);
	
		void update(float delta);
		void updateContentPosition();
		void updateScrollDomain(int axis);
	
		Box::Pointer _content;
		float _contentScale;
		BoxPosition _contentBoxPosition;
		std::array<std::unique_ptr<ScrollInertia>, 2> _inertias;
		LayoutGravity _layoutGravity;
	
		bool _isAutoFitScrollAreaEnabled;
		EventListener::Pointer _onResizeListener;
	
		bool _isZoomingEnabled;
		ScrollableDirection _scrollableDirection;
	
		bool _isZoomingKeyPressed;
		bool _isSwappingKeyPressed;
	
};
NS_CCV_END

#endif
