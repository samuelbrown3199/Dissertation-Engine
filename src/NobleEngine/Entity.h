#include <memory>
#include <vector>
#include <string>

#include "Component.h"
namespace NobleEngine
{
	/**
	*Entities will be containers for use in storing game data.
	*/
	struct Entity
	{
	public:
		/**
		*The entity's unique ID.
		*/
		int entityID;
		/**
		*The entity's tag.
		*/
		std::string tag;

		/**
		*Adds the component to the entity with the passed list type.
		*/
		template <typename T>
		void AddComponent(std::vector <std::shared_ptr<T>> componentList)
		{
			std::shared_ptr<T> component = std::make_shared();
			componentList.push_back(component);
			entityComponents.push_back(component);
		}

	private:

		/**
		*Stores the entity's components.
		*/
		std::vector<std::shared_ptr<Component>> entityComponents;
	};
}