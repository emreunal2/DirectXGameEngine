/*MIT License

C++ 3D Game Tutorial Series (https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)

Copyright (c) 2019-2023, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/


#include <DX3D/Resource/Font.h>
#include <DX3D/Resource/ResourceManager.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <sstream>
#include <regex>
#include <filesystem>

Font::Font(const wchar_t* fullPath, ResourceManager* manager): Resource(fullPath, manager)
{
	m_font = manager->getGame()->getGraphicsEngine()->getRenderSystem()->createFont(fullPath);
}

const Font2DPtr& Font::getFont()
{
	return m_font;
}

bool FontUtility::createFont(const wchar_t* fontName, f32 fontSize, const wchar_t* outputPath)
{
	std::wstringstream p;
	std::wstring s = std::regex_replace(fontName, std::wregex(L"\\s+"), L"");
	p << outputPath << s << ".font";

	if (!std::filesystem::exists(p.str()))
	{
		std::wstringstream command;
		command << "DX3D\\Vendor\\DirectXTK\\bin\\MakeSpriteFont ";
		command << "\"" << fontName << "\" ";
		command << p.str() << " ";
		command << "/FontSize:" << fontSize;

		if (_wsystem(command.str().c_str()) != 0)
			DX3DError("Creation of the font " << fontName << " failed");

		return true;
	}

	return true;
}
