#include "ResourceManager.h"

#include "Material.h"

namespace NobleEngine
{
	std::shared_ptr<ResourceManager> ResourceManager::instance;

	std::shared_ptr<Material> ResourceManager::LoadMaterial(std::string diffusePath, std::string specularPath)
	{
		std::shared_ptr<Material> mat = std::make_shared<Material>();

		if (diffusePath != "")
		{
			mat->diffuseTexture = LoadResource<Texture>(diffusePath);
		}
		if (specularPath != "")
		{
			mat->specularTexture = LoadResource<Texture>(specularPath);
		}

		return mat;
	}

	void ResourceManager::UnloadUnusedResources()
	{
		for (size_t re = 0; re < resources.size(); re++)
		{
			if (resources.at(re).use_count() == 1)
			{
				resources.erase(resources.begin() + re);
			}
		}
	}
}