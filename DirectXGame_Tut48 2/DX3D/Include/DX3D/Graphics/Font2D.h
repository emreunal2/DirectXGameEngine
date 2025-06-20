

#pragma once
#include <DX3D/Prerequisites.h>
#include <DX3D/Math/Rect.h>
#include <SpriteFont.h>



class Font2D
{
public:
	Font2D(const wchar_t* fullPath, RenderSystem* system);
	Font2D(const Font2D&) = delete;
	Font2D& operator=(const Font2D&) = delete;
	Rect getBounds(const wchar_t* text);
private:
	std::unique_ptr<DirectX::DX11::SpriteFont> m_font = nullptr;
	std::unique_ptr<DirectX::DX11::SpriteBatch> m_batch = nullptr;

	RenderSystem* m_system = nullptr;

	friend class GraphicsEngine;
};

