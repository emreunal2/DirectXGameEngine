

#pragma once
#include <DX3D/Entity/Component.h>
#include <DX3D/Math/Rect.h>

class ImageComponent: public Component
{
public:
	ImageComponent();
	virtual ~ImageComponent();

	void setImage(const TexturePtr& image);
	const TexturePtr& getImage();

	void setSize(const Rect& size);
	Rect getSize();

protected:
	virtual void onCreateInternal();

private:
	TexturePtr m_image;
	Rect m_size;
};

