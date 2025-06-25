

#pragma once
#include <DX3D/Entity/Component.h>
#include <DX3D/Math/Vector4D.h>




class FogComponent: public Component
{
public:
	FogComponent();
	FogComponent(const FogComponent&) = delete;
	FogComponent& operator=(const FogComponent&) = delete;
	virtual ~FogComponent();

	void setData(const Vector4D& color, f32 start, f32 end);


	const Vector4D& getColor() const;
	f32 getStart();
	f32 getEnd();

protected:
	virtual void onCreateInternal();

private:
	Vector4D m_color = Vector4D(0.5f,0.5f,0.5f,1.0f);
	f32 m_start = 50;
	f32 m_end = 300;
};

