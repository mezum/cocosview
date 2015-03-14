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

#include "PreviewPanel.h"
#include <limits>
#include "PanelSize.h"

USING_NS_CC;

NS_CCV_BEG

PreviewPanel::PreviewPanel(std::shared_ptr<Operator> op)
: PanelBox(std::move(op))
{
	
}

bool PreviewPanel::init()
{
	if (!Box::init()) return false;
	
	setBackgroundOpacity(0);
	
	setPosition(BoxPosition{
		CoordValue{CoordType::PIXEL, 0.0f},
		CoordValue{CoordType::PIXEL, 0.0f}
	});
	
	setSize(BoxSize{
		CoordValue{CoordType::PARENT_WIDTH, 1.0f},
		CoordValue{CoordType::PARENT_HEIGHT, 1.0f}
	});
	
	setMargin(BoxMargin{
		CoordValue{CoordType::PIXEL, PanelSize::TOOLPANEL_WIDTH},
		CoordValue{CoordType::PIXEL, PanelSize::PROPERTIESPANEL_WIDTH},
		CoordValue{CoordType::PIXEL, 0.0f},
		CoordValue{CoordType::PIXEL, 0.0f}
	});
	
	// scroller
	_scroller = ScrollBox::create();
	_scroller->setAnchorPoint(Vec2(0.5f, 0.5f));
	_scroller->setPosition(BoxPosition{
		CoordValue{CoordType::PARENT_WIDTH, 0.5f},
		CoordValue{CoordType::PARENT_HEIGHT, 0.5f}
	});
	_scroller->setSize(BoxSize{
		CoordValue{CoordType::PARENT_WIDTH, 1.0f},
		CoordValue{CoordType::PARENT_HEIGHT, 1.0f}
	});
	_scroller->setClippingEnabled(false);
	_scroller->enableAutoFitScrollArea(false);
	addChild(_scroller);
	
	// screen node
	_screen = Box::create(LayerColor::create(Color4B(0, 0, 0, 255)));
	_screen->getView()->ignoreAnchorPointForPosition(false);
	_screen->getView()->setAnchorPoint(Vec2(0.5f, 0.5f));
	_screen->setSize(BoxSize{
		CoordValue{CoordType::PIXEL,  640},
		CoordValue{CoordType::PIXEL, 1136}
	});
	_screen->setPosition(BoxPosition{
		CoordValue{CoordType::PIXEL, 0.0f},
		CoordValue{CoordType::PIXEL, 0.0f}
	});
	_scroller->setContent(_screen);
	
	EventListener::Function onEnterFunc = std::bind(&PreviewPanel::onEnterListener, std::ref(*this), std::placeholders::_1);
	_onEnterListener = EventListener::create(onEnterFunc);
	onEnter.addListener(_onEnterListener, true);
	
	return true;
}

void PreviewPanel::onEnterListener(EventDetail &detail)
{
	_scroller->fitScrollArea();
	_scroller->jumpTo(LayoutGravity::Vertical::MIDDLE);
	_scroller->jumpTo(LayoutGravity::Horizontal::CENTER);
	_scroller->getInertiaX()->setMin(-std::numeric_limits<float>::max());
	_scroller->getInertiaX()->setMax(+std::numeric_limits<float>::max());
	_scroller->getInertiaY()->setMin(-std::numeric_limits<float>::max());
	_scroller->getInertiaY()->setMax(+std::numeric_limits<float>::max());
}

NS_CCV_END
