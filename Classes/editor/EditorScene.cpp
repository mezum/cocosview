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

#include "EditorScene.h"
#include "Operator.h"

USING_NS_CC;

NS_CCV_BEG

bool EditorScene::init()
{
	if (!Scene::init()) return false;
	
	scheduleUpdate();
	return true;
}

void EditorScene::onEnter()
{
	Scene::onEnter();
	
	Director::getInstance()->setClearColor(Color4F(0x33 / 255.0f, 0x33 / 255.0f, 0x44 / 255.0f, 1.0f));
	
	auto op = Operator::create();
	_previewPanel = PreviewPanel::create(op);
	_propertiesPanel = PropertiesPanel::create(op);
	_toolsPanel = ToolsPanel::create(op);
	
	_root = RootBox::create(this);
	_root->addChild(_previewPanel);
	_root->addChild(_propertiesPanel);
	_root->addChild(_toolsPanel);
}

void EditorScene::update(float delta)
{
	auto *gl = Director::getInstance()->getOpenGLView();
	const Size &size = gl->getFrameSize();
	if (size.width == _prevScreenSize.width && size.height == _prevScreenSize.height) return;
	_prevScreenSize = size;
	
	gl->setDesignResolutionSize(size.width, size.height, ResolutionPolicy::EXACT_FIT);
	_root->setSize(BoxSize{
		CoordValue{CoordType::PIXEL, size.width},
		CoordValue{CoordType::PIXEL, size.height}
	});
}

NS_CCV_END
