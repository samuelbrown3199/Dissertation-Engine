#include "ResourceManager.h"

#include "../ResourceManagement/Material.h"

namespace NobleEngine
{
	std::vector<std::shared_ptr<Resource>> ResourceManager::resources;
	std::vector<std::shared_ptr<Material>> ResourceManager::materials;

	std::shared_ptr<Material> ResourceManager::LoadMaterial(std::string diffusePath, std::string specularPath)
	{
		for (size_t ma = 0; ma < materials.size(); ma++)
		{
			//will need to add checking other variables of materials match later on.
			bool diffuseMatch = false, specularMatch = false;
			if (diffusePath != "")
			{
				if (materials.at(ma)->diffuseTexture)
				{
					if (materials.at(ma)->diffuseTexture->resourcePath == diffusePath)
					{
						diffuseMatch = true;
					}
				}
			}
			else
			{
				diffuseMatch = true;
			}
			if (specularPath != "")
			{
				if (materials.at(ma)->specularTexture)
				{
					if (materials.at(ma)->specularTexture->resourcePath == specularPath)
					{
						specularMatch = true;
					}
				}
			}
			else
			{
				specularMatch = true;
			}

			if (diffuseMatch && specularMatch)
			{
				return materials.at(ma);
			}
		}

		std::shared_ptr<Material> mat = std::make_shared<Material>();
		if (diffusePath != "")
		{
			mat->diffuseTexture = LoadResource<Texture>(diffusePath);
		}
		if (specularPath != "")
		{
			mat->specularTexture = LoadResource<Texture>(specularPath);
		}
		materials.push_back(mat);
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

		for (size_t ma = 0; ma < materials.size(); ma++)
		{
			if (materials.at(ma).use_count() == 1)
			{
				materials.erase(materials.begin() + ma);
			}
		}
	}
}