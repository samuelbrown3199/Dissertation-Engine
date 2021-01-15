#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <memory>

#include "Application.h"

namespace NobleEngine
{
	struct Entity;

	/**
	*The base class that components inherit from.
	*/
	struct ComponentBase
	{
		/**
		*Contains the entity ID the component is linked to.
		*/
		int entityID;
		/**
		*Used to determine whether the component is marked for deletion.
		*/
		bool markedForDeletion = false;
		/**
		*Returns the components entity.
		*/
		std::shared_ptr<Entity> GetEntity()
		{
			return Application::GetEntity(entityID);
		}
		virtual ~ComponentBase() {}
	};

	/**
	*The component struct that is used for user define components.
	*/
	template<typename T>
	struct Component : public ComponentBase
	{
		/**
		*Stores the list of the component type passed in through the template.
		*/
		static std::vector<std::shared_ptr<T>> componentList;

		virtual ~Component() {}
		virtual void OnInitialize() {};
	};
}

#endif