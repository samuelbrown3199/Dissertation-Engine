#pragma once

#include <memory>

#include "Component.h"

struct Entity
{
	std::vector<std::shared_ptr<Component>> entityComponents;

	template<typename T>
	void AddComponent(std::vector<std::shared_ptr<T>> list)
	{
		std::shared_ptr<T> comp = std::make_shared<T>();
		entityComponents.push_back(comp);
		list.push_back(comp);
	}
};