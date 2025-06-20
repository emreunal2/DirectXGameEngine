

#pragma once
#include <DX3D/Prerequisites.h>
#include <set>
#include <list>

class GraphicsEngine
{
public:
	//Initialize the GraphicsEngine and DirectX 11 Device
	explicit GraphicsEngine(Game* game);
	//Release all the resources loaded
	~GraphicsEngine();

	GraphicsEngine(const GraphicsEngine&) = delete;
	GraphicsEngine& operator=(const GraphicsEngine&) = delete;
	void update();
public:
	RenderSystem * getRenderSystem();

	void addComponent(Component* component);
	void removeComponent(Component* component);


private:
	std::unique_ptr<RenderSystem> m_render_system = nullptr;
	Game* m_game = nullptr;


	std::set<MeshComponent*> m_meshes;
	std::set<CameraComponent*> m_cameras;
	std::set<LightComponent*> m_lights;
	std::set<TerrainComponent*> m_terrains;
	std::set<WaterComponent*> m_waterComps;
	std::set<FogComponent*> m_fogs;

	std::list<Component*> m_uiComponents;
	//std::set<ImageComponent*> m_images;
};

