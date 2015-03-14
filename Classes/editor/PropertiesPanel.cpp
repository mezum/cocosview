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

#include "PropertiesPanel.h"
#include "PanelSize.h"

USING_NS_CC;

NS_CCV_BEG

PropertiesPanel::PropertiesPanel(std::shared_ptr<Operator> op)
: PanelBox(std::move(op))
{
	
}

bool PropertiesPanel::init()
{
	if (!Box::init()) return false;
	
	setBackgroundColor(Color3B(0x66, 0x66, 0x77));
	setBackgroundOpacity(0xA0);
	
	setPosition(BoxPosition{
		CoordValue{CoordType::PARENT_WIDTH, 1.0f},
		CoordValue{CoordType::PIXEL, 0.0f}
	});
	
	setSize(BoxSize{
		CoordValue{CoordType::PIXEL, PanelSize::PROPERTIESPANEL_WIDTH},
		CoordValue{CoordType::PARENT_HEIGHT, 1.0f}
	});
	
	setAnchorPoint(Vec2(1.0f, 0.0f));
	
	return true;
}

NS_CCV_END
