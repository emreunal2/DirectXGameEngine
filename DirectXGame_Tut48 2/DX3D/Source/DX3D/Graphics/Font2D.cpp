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


#include <DX3D/Graphics/Font2D.h>
#include <DX3D/Graphics/RenderSystem.h>

Font2D::Font2D(const wchar_t* fullPath, RenderSystem* system)
{
	m_font = std::make_unique<DirectX::DX11::SpriteFont>(system->m_d3d_device.Get(), fullPath);
	if (!m_font)
		DX3DError("Creation of Font2D failed");

	auto context = system->m_imm_context.Get();
	m_batch = std::make_unique<DirectX::DX11::SpriteBatch>(context);
	if (!m_batch)
		DX3DError("Creation of Font2D failed");
}

Rect Font2D::getBounds(const wchar_t* text)
{
	auto rc = m_font->MeasureDrawBounds(text, DirectX::XMFLOAT2(0, 0));
	return Rect(rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top);
}
