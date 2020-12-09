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
		*A weak pointer to this entity. Used for passing this into other functions.
		*/
		std::weak_ptr<Entity> self;
		/**
		*Adds the component to the entity with the passed template type and automatically adds it to the component type list. This also returns a shared pointer of the component.
		*/
		template <typename T>
		std::shared_ptr<T> AddComponent()
		{
			std::shared_ptr<T> component = std::make_shared<T>();
			component->entityID = entityID;
			entityComponents.push_back(component);
			T::componentList.push_back(component);

			return component;
		}

		/**
		*Removes a component of the passed type.
		*/
		template<typename T>
		void RemoveComponent()
		{
			std::shared_ptr<T> comp;
			for (size_t i = 0; i < entityComponents.size(); i++)
			{
				comp = std::dynamic_pointer_cast<T>(entityComponents.at(i));
				if(comp)
				{
					//delete component data
					for (int i = 0; i < T::componentList.size(); i++)
					{
						if (T::componentList[i] == comp)
						{
							T::componentList.erase(T::componentList.begin() + i);
						}
					}
					entityComponents.erase(entityComponents.begin() + i);
				}
				else
				{
					std::cout << "Entity of ID: " << entityID << " does not contain component to remove." << std::endl;
				}
			}
		}

		/**
		*Removes all components from an entity.
		*/
		void RemoveAllComponents()
		{
			for (int co = 0; co < entityComponents.size(); co++)
			{
				entityComponents.at(co)->markedForDeletion = true;
			}
		}
		/**
		*Returns a shared pointer of the component of the passed type if it exists.
		*/
		template<typename T>
		std::shared_ptr<T> GetComponent() //currently bugged when trying to use.
		{
			std::shared_ptr<T> comp;
			for (size_t i = 0; i < entityComponents.size(); i++)
			{
				comp = std::dynamic_pointer_cast<T>(entityComponents.at(i));
				if (!comp) continue;

				return comp;
			}

			std::cout << "Could not find component on entity " << entityID << std::endl;
			throw std::exception();
		}
		/**
		*Returns the size of the entity component list.
		*/
		int GetEntityComponentSize();
		/**
		*Tells the engine to destroy this entity at the end of the current frame.
		*/
		void Destroy();

	private:
		/**
		*Stores the entity's components.
		*/
		std::vector<std::shared_ptr<ComponentBase>> entityComponents;
	};
}