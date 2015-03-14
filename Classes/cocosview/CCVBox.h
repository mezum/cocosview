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

#ifndef cocosview_Box_h
#define cocosview_Box_h

#include <memory>
#include <unordered_set>
#include "cocos2d.h"
#include "CCVMacros.h"
#include "CCVCoord.h"
#include "CCVSizeCalculator.h"
#include "CCVEventDispatcher.h"
#include "CCVCreateHelper.h"

NS_CCV_BEG

/**
 * basic box class.
 *
 * the box placement model is like this figure:
 *     +---------------- screen ----------------+
 *     |                                        |
 *     | +-------------- parent --------------+ |
 *     | |                                    | |
 *     | | +------ margin of this box ------+ | |
 *     | | |                                | | |
 *     | | | +--------- this box ---------+ | | |
 *     | | | |                            | | | |
 *     | | | | +---- margin of child ---+ | | | |
 *     | | | | |                        | | | | |
 *     | | | | | +---- child box -----+ | | | | |
 *     | | | | | |                    | | | | | |
 *     | | | | | +--------------------+ | | | | |
 *     | | | | +------------------------| | | | |
 *     | | | +----------------------------+ | | |
 *     | | +--------------------------------+ | |
 *     | +------------------------------------+ |
 *     +----------------------------------------+
 */
class Box : public std::enable_shared_from_this<Box>,
            CreateHelper<Box>
{
	public:
		/** the pointer type of this class. */
		using Pointer = std::shared_ptr<Box>;
		using ConstPointer = const std::shared_ptr<const Box>;
		using WeakPointer = std::weak_ptr<Box>;
	
		/** on resized event */
		EventDispatcher onResized;
	
		/** on enter event */
		EventDispatcher onEnter;
	
		/** on enter event */
		EventDispatcher onExit;
	
		/**
		 * create a instance.
		 * @param view target node
		 * @return a instance.
		 */
		using CreateHelper::create;
	
		/**
		 * destructor.
		 */
		virtual ~Box();
	
		/**
		 * get parent box.
		 */
		Box::Pointer getParent() const;
	
		/**
		 * get root box.
		 */
		virtual Box::ConstPointer getRoot() const;
		virtual Box::Pointer getRoot();
	
		/**
		 * get real graphic node of this box.
		 */
		cocos2d::Node* getView() const;
	
		/**
		 * get anchor point.
		 */
		const cocos2d::Vec2& getAnchorPoint() const;
	
		/**
		 * set anchor point.
		 */
		void setAnchorPoint(const cocos2d::Vec2 &anchor);
	
		/**
		 * get logical size.
		 */
		const BoxSize& getSize() const;
	
		/**
		 * set logical size.
		 */
		void setSize(const BoxSize &size);
	
		/**
		 * get logical position.
		 */
		const BoxPosition& getPosition() const;
	
		/**
		 * set logical size.
		 */
		void setPosition(const BoxPosition &position);
	
		/**
		 * get margin.
		 */
		const BoxMargin& getMargin() const;
	
		/**
		 * set margin.
		 */
		void setMargin(const BoxMargin &margin);
	
		/**
		 * add child box.
		 */
		void addChild(Box::Pointer child);
	
		/**
		 * remove child box.
		 */
		void removeChild(Box::Pointer child);
	
		/**
		 * force layout.
		 */
		void doLayout();
	
	protected:
		/**
		 * set parent box.
		 */
		void setParent(Box::Pointer box);
	
		/**
		 * implement to apply new size
		 */
		virtual void applySize(const cocos2d::Size &size);
	
	CCV_CONSTRUCTOR_ACCESS:
		/**
		 * construct with rootNode flag.
		 * @param view       real graphic node
		 * @param isRootNode true, if the instance is root node, otherwise false.
		 */
		Box(cocos2d::Node *view, bool isRootNode = false);
	
		/**
		 * initialize.
		 * @return true if the object succeeded in initializing, otherwise false.
		 */
		virtual bool init();
	
	private:
		/**
		 * receive that a parent of the box was resized.
		 */
		void onParentSizeChanged(const SizeCalculator &calc);
	
		/**
		 * apply new size.
		 * if the box contains children,
		 * the box notify its children that the parent was resized by calling its method onParentSizeChanged.
		 */
		void updateSize(const SizeCalculator &calc);
	
		/**
		 * apply new position.
		 */
		void updatePosition(const SizeCalculator &calc);
	
		cocos2d::Node *_view;
		bool _joined;
	
		Box::WeakPointer _parent;
		std::unordered_set<Box::Pointer> _children;
		
		BoxSize _size;
		BoxPosition _position;
		BoxMargin _margin;
};
NS_CCV_END

#endif
