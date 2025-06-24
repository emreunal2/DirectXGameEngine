

#include <DX3D/Resource/ResourceManager.h>
#include <DX3D/Resource/Mesh.h>
#include <DX3D/Resource/Texture.h>
#include <DX3D/Resource/Material.h>
#include <DX3D/Resource/Font.h>
#include <filesystem>


ResourceManager::ResourceManager(Game* game):m_game(game)
{
}


ResourceManager::~ResourceManager() = default;

Game* ResourceManager::getGame()
{
	return m_game;
}

ResourcePtr ResourceManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	auto it = m_map_resources.find(file_path);

	if (it != m_map_resources.end())
	{
		auto mat = std::dynamic_pointer_cast<Material>(it->second);
		if (mat) return std::make_shared<Material>(mat, this);
		return it->second;
	}

	std::filesystem::path resourcePath = file_path;

	if (!std::filesystem::exists(resourcePath)) return ResourcePtr();

	ResourcePtr resPtr;
	auto ext = resourcePath.extension();
	if (!ext.compare(L".obj"))
		resPtr = std::make_shared<Mesh>(resourcePath.c_str(), this);
	else if (!ext.compare(L".jpg") || !ext.compare(L".png") || !ext.compare(L".bmp"))
		resPtr = std::make_shared<Texture>(resourcePath.c_str(), this);
	else if (!ext.compare(L".hlsl") || !ext.compare(L".fx"))
		resPtr = std::make_shared<Material>(resourcePath.c_str(), this);
	else if (!ext.compare(L".font"))
		resPtr = std::make_shared<Font>(resourcePath.c_str(), this);

	if (resPtr)
	{
		m_map_resources.emplace(file_path, resPtr);
		return resPtr;
	}

	return nullptr;
}

