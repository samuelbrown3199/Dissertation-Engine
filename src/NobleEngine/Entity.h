#include <memory>
#include <vector>
#include <string>
#pragma once

#include "Component.h"
namespace NobleEngine
{
	/**
	*Entities are containers for use in storing game data.
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
		std::shared_ptr<T> AddComponent()
		{
			std::shared_ptr<T> component = std::make_shared<T>();
			entityComponents.push_back(component);
			T::componentList.push_back(component);

			return component;
		}

		int GetEntityComponentSize()
		{
			return entityComponents.size();
		}

	private:

		/**
		*Stores the entity's components.
		*/
		std::vector<std::shared_ptr<ComponentBase>> entityComponents;
	};
}