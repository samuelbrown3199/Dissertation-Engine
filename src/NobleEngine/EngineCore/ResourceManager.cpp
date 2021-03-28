#include "ResourceManager.h"

#include "../ResourceManagement/Material.h"
#include "../ResourceManagement/Font.h"
#include "../ResourceManagement/ShaderProgram.h"

namespace NobleEngine
{
	std::vector<std::shared_ptr<Resource>> ResourceManager::resources;
	std::vector <std::shared_ptr<ShaderProgram>> ResourceManager::shaderPrograms;

	std::shared_ptr<Material> ResourceManager::LoadMaterial(std::string diffusePath)
	{
		for (size_t ma = 0; ma < resources.size(); ma++)
		{
			//will need to add checking other variables of materials match later on.
			bool diffuseMatch = false;
			std::shared_ptr<Material> matToCheck = std::dynamic_pointer_cast<Material>(resources.at(ma));

			if (matToCheck)
			{
				if (diffusePath != "")
				{
					if (matToCheck->diffuseTexture)
					{
						if (matToCheck->diffuseTexture->resourcePath == diffusePath)
						{
							diffuseMatch = true;
						}
					}
				}
				else
				{
					diffuseMatch = true;
				}
	
				if (diffuseMatch)
				{
					return matToCheck;
				}
			}
		}

		std::shared_ptr<Material> mat = std::make_shared<Material>();
		if (diffusePath != "")
		{
			mat->diffuseTexture = LoadResource<Texture>(diffusePath);
		}

		return mat;
	}

	std::shared_ptr<Material> ResourceManager::LoadMaterial(std::string diffusePath, std::string specularPath)
	{
		for (size_t ma = 0; ma < resources.size(); ma++)
		{
			//will need to add checking other variables of materials match later on.
			bool diffuseMatch = false, specularMatch = false;
			std::shared_ptr<Material> matToCheck = std::dynamic_pointer_cast<Material>(resources.at(ma));

			if (matToCheck)
			{
				if (diffusePath != "")
				{
					if (matToCheck->diffuseTexture)
					{
						if (matToCheck->diffuseTexture->resourcePath == diffusePath)
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
					if (matToCheck->specularTexture)
					{
						if (matToCheck->specularTexture->resourcePath == specularPath)
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
					return matToCheck;
				}
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
		resources.push_back(mat);
		return mat;
	}


	std::shared_ptr<Font> ResourceManager::LoadFont(std::string fontPath, int fontPixelSize)
	{
		for (size_t re = 0; re < resources.size(); re++)
		{
			if (resources.at(re)->resourcePath == fontPath)
			{
				std::shared_ptr<Font> resource = std::dynamic_pointer_cast<Font>(resources.at(re));
				if (resource)
				{
					if (resource->fontPixelSize == fontPixelSize)
					{
						return resource;
					}
				}
			}
		}

		std::shared_ptr<Font> newResource = std::make_shared<Font>(fontPixelSize);
		newResource->resourcePath = fontPath;
		newResource->OnLoad();
		resources.push_back(newResource);
		return newResource;
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

		for (size_t sha = 0; sha < shaderPrograms.size(); sha++)
		{
			if (shaderPrograms.at(sha).use_count() == 1)
			{
				shaderPrograms.erase(shaderPrograms.begin() + sha);
			}
		}
	}
}