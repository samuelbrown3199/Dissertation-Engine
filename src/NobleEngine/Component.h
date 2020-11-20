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
	};

	/**
	*The component struct that is used for user define components.
	*/
	template<typename T>
	struct Component : public ComponentBase
	{
		static std::vector<std::shared_ptr<T>> componentList;
	};
}

#endif