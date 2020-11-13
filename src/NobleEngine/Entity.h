#include <memory>
#include <vector>
#include <string>

#include "Component.h"
namespace NobleEngine
{
	struct Entity
	{
	public:
		int entityID;
		std::string tag;

		template <typename T>
		void AddComponent(std::vector <std::shared_ptr<T>> componentList)
		{
			std::shared_ptr<T> component = std::make_shared();
			componentList.push_back(component);
			entityComponents.push_back(component);
		}

	private:
		std::vector<std::shared_ptr<Component>> entityComponents;
	};
}