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

#ifndef cocosview_EditorScene_h
#define cocosview_EditorScene_h

#include <memory>
#include "cocos2d.h"
#include "cocosview/cocosview.h"
#include "PreviewPanel.h"
#include "PropertiesPanel.h"
#include "ToolsPanel.h"

NS_CCV_BEG
class EditorScene : public cocos2d::Scene
{
	public:
		CREATE_FUNC(EditorScene);
		void onEnter() override;
		void update(float delta) override;
	
	CCV_CONSTRUCTOR_ACCESS:
		EditorScene() = default;
		bool init() override;
	
	private:
		cocos2d::Size _prevScreenSize;
		RootBox::Pointer _root;
		PreviewPanel::Pointer _previewPanel;
		PropertiesPanel::Pointer _propertiesPanel;
		ToolsPanel::Pointer _toolsPanel;
};
NS_CCV_END

#endif
