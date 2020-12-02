#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <memory>

namespace NobleEngine
{
	/**
	*The base class that components inherit from.
	*/
	struct ComponentBase
	{
		/**
		*Contains the entity ID the component is linked to.
		*/
		int entityID;

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
	};
}

#endif