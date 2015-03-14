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

#include "Tool.h"

NS_CCV_BEG

std::map<Tool::Type, Tool> Tool::_infoMap{
	{Type::SELECT, Tool{Type::SELECT, "select.png"}},
	{Type::SPRITE, Tool{Type::SPRITE, "sprite.png"}},
	{Type::LABEL,  Tool{Type::LABEL,  "label.png"}},
	{Type::BUTTON, Tool{Type::BUTTON, "button.png"}},
	{Type::LAYER,  Tool{Type::LAYER,  "layer.png"}},
	{Type::NODE,   Tool{Type::NODE,   "node.png"}}
};

const Tool& Tool::getInfo(Type type)
{
	return _infoMap.at(type);
}

Tool::Type Tool::getType() const
{
	return _type;
}

std::string Tool::getIconFileName() const
{
	return _iconFileName;
}

Tool::Tool(Type type, std::string iconFileName)
: _type(type), _iconFileName(iconFileName)
{
	
}

NS_CCV_END
