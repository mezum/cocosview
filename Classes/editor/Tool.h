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

#ifndef cocosview_Tool_h
#define cocosview_Tool_h

#include <string>
#include <map>
#include "cocosview/cocosview.h"

NS_CCV_BEG

/**
 * tool information
 */
class Tool
{
	public:
		/** tool type enum */
		enum class Type
		{
			SELECT,
			SPRITE,
			LABEL,
			BUTTON,
			LAYER,
			NODE,
			ALL
		};
	
		/** tool type */
		Type getType() const;
	
		/** icon file name */
		std::string getIconFileName() const;
	
		/** get information by type */
		static const Tool& getInfo(Type type);
	
	private:
		Tool(Type type, std::string iconFileName);
	
		static std::map<Type, Tool> _infoMap;
		const Type _type;
		const std::string _iconFileName;
};

inline Tool::Type begin(Tool::Type) { return Tool::Type::SELECT; }
inline Tool::Type end(Tool::Type) { return Tool::Type::ALL; }

NS_CCV_END

inline NS_CCV::Tool::Type operator *(const NS_CCV::Tool::Type &type) { return type; }
inline NS_CCV::Tool::Type operator ++(NS_CCV::Tool::Type &type)
{
	using EnumEntryType = std::underlying_type<NS_CCV::Tool::Type>::type;
	EnumEntryType index = EnumEntryType(type);
	type = static_cast<NS_CCV::Tool::Type>(index + 1);
	return static_cast<NS_CCV::Tool::Type>(index);
}

inline NS_CCV::Tool::Type operator ++(const NS_CCV::Tool::Type &type, int)
{
	using EnumEntryType = std::underlying_type<NS_CCV::Tool::Type>::type;
	EnumEntryType index = EnumEntryType(type);
	return static_cast<NS_CCV::Tool::Type>(index + 1);
}

#endif
