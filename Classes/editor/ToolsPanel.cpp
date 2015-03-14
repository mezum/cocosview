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

#include "ToolsPanel.h"
#include "Tool.h"
#include "Resources.h"
#include "PanelSize.h"

USING_NS_CC;

NS_CCV_BEG

ToolsPanel::ToolsPanel(std::shared_ptr<Operator> op)
: PanelBox(std::move(op))
{
	
}

bool ToolsPanel::init()
{
	if (!Box::init()) return false;
	
	setBackgroundColor(Color3B(0x66, 0x66, 0x77));
	setBackgroundOpacity(0xA0);
	
	setPosition(BoxPosition{
		CoordValue{CoordType::PIXEL, 0.0f},
		CoordValue{CoordType::PIXEL, 0.0f}
	});
	
	setSize(BoxSize{
		CoordValue{CoordType::PIXEL, PanelSize::TOOLPANEL_WIDTH},
		CoordValue{CoordType::PARENT_HEIGHT, 1.0f}
	});
	
	// top aligner
	_top = Box::create(Node::create());
	_top->setPosition(BoxPosition{
		CoordValue{CoordType::PARENT_WIDTH, 0.5f},
		CoordValue{CoordType::PARENT_HEIGHT, 1.0f}
	});
	addChild(_top);
	
	// tool icons
	auto *eventDispatcher = Director::getInstance()->getEventDispatcher();
	int i = 0;
	for (auto type : Tool::Type()) {
		auto &toolInfo = Tool::getInfo(type);
		std::string path = Resources::getPath("icon", toolInfo.getIconFileName());
		auto sprite = SpriteBox::create(Sprite::create(path));
		sprite->setPosition(BoxPosition{
			CoordValue{CoordType::PIXEL, 0.0f},
			CoordValue{CoordType::PIXEL, -50.0f * i - 25.0f}
		});
		sprite->setSize(BoxSize{
			CoordValue{CoordType::SCALE, 1.0f},
			CoordValue{CoordType::SCALE, 1.0f}
		});
		_top->addChild(sprite);
		
		auto *touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = [](Touch *touch, Event *event) -> bool
		{
			auto *node = event->getCurrentTarget();
			return node->getBoundingBox().containsPoint(node->getParent()->convertTouchToNodeSpace(touch));
		};
		touchListener->onTouchEnded = [this, type](Touch *touch, Event *event)
		{
			auto *node = event->getCurrentTarget();
			if (node->getBoundingBox().containsPoint(node->getParent()->convertTouchToNodeSpace(touch))) {
				getOperator()->setCurrentTool(type);
			}
		};
		// NOTE: the event listener will be removed from event dispatcher by sprite destructor
		eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite->getView());
		i++;
	}
	
	return true;
}

NS_CCV_END
