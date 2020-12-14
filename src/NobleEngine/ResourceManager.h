#include <vector>
#include <memory>
#include <string>

#include "Resource.h"

namespace NobleEngine
{
	struct ResourceManager
	{
		/**
		*Stores all loaded resources.
		*/
		std::vector<std::shared_ptr<Resource>> resources;

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

		void UnloadUnusedResources();
	};
}