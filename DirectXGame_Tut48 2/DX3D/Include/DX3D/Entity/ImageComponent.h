

#pragma once
#include <DX3D/Entity/Component.h>
#include <DX3D/Math/Rect.h>

class ImageComponent: public Component
{
public:
	ImageComponent();
	virtual ~ImageComponent();
	ImageComponent(const ImageComponent&) = delete;
	ImageComponent& operator=(const ImageComponent&) = delete;
	void setImage(const TexturePtr& image);
	const TexturePtr& getImage();

	void setSize(const Rect& size);
	const Rect& getSize() const;

protected:
	virtual void onCreateInternal() override;

private:
	TexturePtr m_image;
	Rect m_size;
};

