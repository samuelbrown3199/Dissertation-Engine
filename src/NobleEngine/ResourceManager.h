#include <vector>
#include <memory>
#include <string>

#include "Resource.h"

namespace NobleEngine
{
	struct Material;

	struct ResourceManager
	{
		static std::shared_ptr<ResourceManager> instance;

		/**
		*Stores all loaded resources.
		*/
		std::vector<std::shared_ptr<Resource>> resources;
		std::vector<std::shared_ptr<Material>> materials;

		/**
		*Loads a resource of the passed type with the file directory.
		*/
		template<typename T>
		std::shared_ptr<T> LoadResource(std::string fileDirectory)
		{
			for (size_t re = 0; re < resources.size(); re++)
			{
				if (resources.at(re)->resourcePath == fileDirectory)
				{
					std::shared_ptr<T> resource = std::dynamic_pointer_cast<T>(resources.at(re));
					if (resource)
					{
						return resource;
					}
				}
			}

			std::shared_ptr<T> newResource = std::make_shared<T>();
			newResource->resourcePath = fileDirectory;
			newResource->OnLoad();
			resources.push_back(newResource);
			return newResource;
		}

		std::shared_ptr<Material> LoadMaterial(std::string diffusePath, std::string specularPath);

		/**
		*Unloads resources whose use count is currently 1. This means that un-used resources are no longer kept in memory.
		*/
		void UnloadUnusedResources();
	};
}