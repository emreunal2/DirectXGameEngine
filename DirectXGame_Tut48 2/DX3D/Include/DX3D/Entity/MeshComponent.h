

#pragma once
#include <DX3D/Prerequisites.h>
#include <DX3D/Entity/Component.h>
#include <vector>

class MeshComponent: public Component
{
public:
	MeshComponent();
	virtual ~MeshComponent();
	MeshComponent(const MeshComponent&) = delete;
	MeshComponent& operator=(const MeshComponent&) = delete;
	void setMesh(const MeshPtr& mesh);
	const MeshPtr& getMesh();

	void addMaterial(const MaterialPtr& material);
	void removeMaterial(ui32 index);
	const std::vector<MaterialPtr>& getMaterials();
protected:
	virtual void onCreateInternal() override;
private:
	MeshPtr m_mesh;
	std::vector<MaterialPtr> m_materials;
};

