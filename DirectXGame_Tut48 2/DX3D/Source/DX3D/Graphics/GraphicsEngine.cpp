

#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/Font2D.h>

#include <DX3D/Resource/ResourceManager.h>
#include <DX3D/Resource/Mesh.h>
#include <DX3D/Resource/Texture.h>
#include <DX3D/Resource/Material.h>
#include <DX3D/Resource/Font.h>

#include <DX3D/Game/Game.h>
#include <DX3D/Game/Display.h>

#include <DX3D/Math/Matrix4x4.h>
#include <DX3D/Math/Vector4D.h>

#include <DX3D/Entity/TransformComponent.h>
#include <DX3D/Entity/MeshComponent.h>
#include <DX3D/Entity/CameraComponent.h>
#include <DX3D/Entity/LightComponent.h>
#include <DX3D/Entity/TerrainComponent.h>
#include <DX3D/Entity/WaterComponent.h>
#include <DX3D/Entity/FogComponent.h>
#include <DX3D/Entity/TextComponent.h>
#include <DX3D/Entity/ImageComponent.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <DX3D/Entity/Entity.h>


__declspec(align(16))
struct CameraData
{
	Matrix4x4 view;
	Matrix4x4 proj;
	Vector4D position;
};


__declspec(align(16))
struct LightData
{
	Vector4D color;
	Vector4D direction;
};

__declspec(align(16))
struct TerrainData
{
	Vector4D size;
	f32 heightMapSize = 0.0f;
};

__declspec(align(16))
struct WaterData
{
	Vector4D size;
	f32 heightMapSize = 0.0f;
};

__declspec(align(16))
struct FogData
{
	Vector4D color;
	f32 start;
	f32 end;
	f32 enable;
};


__declspec(align(16))
struct ConstantData
{
	Matrix4x4 world;
	float time;
	CameraData camera;
	LightData light;
	TerrainData terrain;
	WaterData water;
	FogData fog;
};


GraphicsEngine::GraphicsEngine(Game* game): m_game(game)
{
	m_render_system = std::make_unique<RenderSystem>();
	//create imgui

}

void GraphicsEngine::update()
{

	auto swapChain = m_game->m_display->m_swapChain;
	auto context = m_render_system->getImmediateDeviceContext();
	m_render_system->clearState();
	
	ConstantData constData = {};
	constData.time = m_game->m_totalTime;


	Vector4D fogColor = Vector4D(0, 0, 0, 0);

	for (auto f : m_fogs)
	{
		constData.fog.enable = true;
		fogColor = f->getColor();
		constData.fog.color = fogColor;
		constData.fog.start = f->getStart();
		constData.fog.end = f->getEnd();
	}

	context->clearRenderTargetColor(swapChain, backgroundRed, backgroundGreen, backgroundBlue, 1);
	auto winSize = m_game->m_display->getClientSize();
	context->setViewportSize(winSize.width, winSize.height);





	for (auto c : m_cameras)
	{
		auto t = c->getEntity()->getTransform();
		constData.camera.position = t->getPosition();
		c->setScreenArea(winSize);
		c->getViewMatrix(constData.camera.view);
		c->getProjectionMatrix(constData.camera.proj);
	}


	for (auto l : m_lights)
	{
		auto t = l->getEntity()->getTransform();
		Matrix4x4 w;
		t->getWorldMatrix(w);
		constData.light.direction = w.getZDirection();
		constData.light.color = l->getColor();
	}

	for (auto m : m_meshes)
	{
		auto transform = m->getEntity()->getTransform();
		transform->getWorldMatrix(constData.world);

		auto mesh = m->getMesh().get();
		const auto materials = m->getMaterials();


		context->setVertexBuffer(mesh->m_vertex_buffer);
		context->setIndexBuffer(mesh->m_index_buffer);


		for (auto i = 0; i < mesh->getNumMaterialSlots(); i++)
		{
			if (i >= materials.size()) break;
			auto mat = materials[i].get();

			m_render_system->setCullMode(mat->getCullMode());

			mat->setData(&constData, sizeof(ConstantData));
			context->setConstantBuffer(mat->m_constant_buffer);

			context->setVertexShader(mat->m_vertex_shader);
			context->setPixelShader(mat->m_pixel_shader);

			context->setTexture(&mat->m_vec_textures[0], (unsigned int)mat->m_vec_textures.size());

			auto slot = mesh->getMaterialSlot(i);
			context->drawIndexedTriangleList((unsigned int)slot.num_indices, (unsigned int)slot.start_index, 0);
		}
	}

	for (auto t : m_terrains)
	{
		auto transform = t->getEntity()->getTransform();
		transform->getWorldMatrix(constData.world);
		constData.terrain.size = t->getSize();
		constData.terrain.heightMapSize = (f32)t->getHeightMap()->getTexture()->getSize().width;

		context->setVertexBuffer(t->m_meshVb);
		context->setIndexBuffer(t->m_meshIb);

		m_render_system->setCullMode(CullMode::Back);
		t->updateData(&constData, sizeof(constData));
		context->setConstantBuffer(t->m_cb);


		context->setVertexShader(t->m_vertexShader);
		context->setPixelShader(t->m_pixelShader);

		Texture2DPtr terrainTextures[3];
		terrainTextures[0] = t->getHeightMap()->getTexture();
		terrainTextures[1] = t->getGroundMap()->getTexture();
		terrainTextures[2] = t->getCliffMap()->getTexture();

		context->setTexture(terrainTextures, 3);

		context->drawIndexedTriangleList((ui32)t->m_meshIb->getSizeIndexList(), 0, 0);
	}


	for (auto w : m_waterComps)
	{
		auto transform = w->getEntity()->getTransform();
		transform->getWorldMatrix(constData.world);
		constData.water.size = w->getSize();
		constData.water.heightMapSize = (f32)w->getWaveHeightMap()->getTexture()->getSize().width;

		context->setVertexBuffer(w->m_meshVb);
		context->setIndexBuffer(w->m_meshIb);

		m_render_system->setCullMode(CullMode::Back);
		w->updateData(&constData, sizeof(constData));
		context->setConstantBuffer(w->m_cb);


		context->setVertexShader(w->m_vertexShader);
		context->setPixelShader(w->m_pixelShader);

		Texture2DPtr waterTextures[1];
		waterTextures[0] = w->getWaveHeightMap()->getTexture();

		context->setTexture(waterTextures, 1);

		context->drawIndexedTriangleList((ui32)w->m_meshIb->getSizeIndexList(), 0, 0);
	}


	//RENDERING UI COMPONENTS
	//----------------------------


	for (auto c : m_uiComponents)
	{
		if (auto t = dynamic_cast<TextComponent*>(c))
		{
			auto transform = t->getEntity()->getTransform();
			auto pos = transform->getPosition();

			auto font = t->getFont()->getFont();

			font->m_batch->Begin();
			font->m_font->DrawString(font->m_batch.get(), t->getText(), DirectX::XMFLOAT2(pos.x, pos.y));
			font->m_batch->End();
		}
		else if (auto i = dynamic_cast<ImageComponent*>(c))
		{
			auto transform = i->getEntity()->getTransform();
			auto pos = transform->getPosition();

			auto texture = i->getImage()->getTexture();
			auto size = i->getSize();
			m_render_system->drawImage(texture, { (i32)pos.x,(i32)pos.y,size.width,size.height });
		}
	}
	
	/*for (auto i : m_images)
	{
		auto transform = i->getEntity()->getTransform();
		auto pos = transform->getPosition();

		auto texture = i->getImage()->getTexture();
		auto size = i->getSize();
		m_render_system->drawImage(texture, {(i32)pos.x,(i32)pos.y,size.width,size.height});
	}*/
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Time Scale:"))
		{
			ImGui::Text("TimeScale: %.2f", m_game->m_timeScale);
			if (ImGui::MenuItem("TimeScaleDown"))
			{
				m_game->setTimeScale(m_game->m_timeScale - 0.1f);
			}
			if (ImGui::MenuItem("TimeScaleUp"))
			{
				m_game->setTimeScale(m_game->m_timeScale + 0.1f);
			}
			if(ImGui::MenuItem("Pause/Play"))
			{
				if (m_game->m_timeScale != 0) {
					m_game->setTimeScale(0);
				}
				else
				{
					m_game->setTimeScale(1);
				}
			}
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("Background Color"))
		{
			ImGui::ColorEdit3("Background Color", (float*)&backgroundRed);
			ImGui::EndMenu();
		}

	}

	ImGui::EndMainMenuBar();
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	swapChain->present(true);
}

RenderSystem * GraphicsEngine::getRenderSystem()
{
	return m_render_system.get();
}

void GraphicsEngine::addComponent(Component* component)
{
	if (auto c = dynamic_cast<MeshComponent*>(component))
		m_meshes.emplace(c);
	else if (auto c = dynamic_cast<CameraComponent*>(component))
	{
		if (!m_cameras.size()) m_cameras.emplace(c);
	}
	else if (auto c = dynamic_cast<LightComponent*>(component))
	{
		if (!m_lights.size()) m_lights.emplace(c);
	}
	else if (auto c = dynamic_cast<TerrainComponent*>(component))
	{
		if (!m_terrains.size()) m_terrains.emplace(c);
	}
	else if (auto c = dynamic_cast<WaterComponent*>(component))
	{
		if (!m_waterComps.size()) m_waterComps.emplace(c);
	}
	else if (auto c = dynamic_cast<FogComponent*>(component))
	{
		if (!m_fogs.size()) m_fogs.emplace(c);
	}
	else if (auto c = dynamic_cast<TextComponent*>(component))
	{
		m_uiComponents.push_back(c);
	}
	else if (auto c = dynamic_cast<ImageComponent*>(component))
	{
		m_uiComponents.push_back(c);
	}

}

void GraphicsEngine::removeComponent(Component* component)
{
	if (auto c = dynamic_cast<MeshComponent*>(component))
		m_meshes.erase(c);
	else if (auto c = dynamic_cast<CameraComponent*>(component))
		m_cameras.erase(c);
	else if (auto c = dynamic_cast<LightComponent*>(component))
		m_lights.erase(c);
	else if (auto c = dynamic_cast<TerrainComponent*>(component))
		m_terrains.erase(c);
	else if (auto c = dynamic_cast<WaterComponent*>(component))
		m_waterComps.erase(c);
	else if (auto c = dynamic_cast<FogComponent*>(component))
		m_fogs.erase(c);
	else if (auto c = dynamic_cast<TextComponent*>(component))
		m_uiComponents.remove(c);
	else if (auto c = dynamic_cast<ImageComponent*>(component))
		m_uiComponents.remove(c);
}

GraphicsEngine::~GraphicsEngine()
{
}
