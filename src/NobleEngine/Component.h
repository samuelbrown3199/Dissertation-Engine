#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <memory>

namespace NobleEngine
{
	struct ComponentBase
	{
		/**
		*Contains the entity ID the component is linked to.
		*/
		int entityID;
	};

	template<typename T>
	struct Component : public ComponentBase
	{
		static std::vector<std::shared_ptr<T>> componentList;
	};
}

#endif