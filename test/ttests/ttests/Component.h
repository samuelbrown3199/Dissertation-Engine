#pragma once

#include <iostream>
#include <vector>
#include <memory>

struct Component;
static std::vector<std::shared_ptr<Component>> components;

struct Component : public std::enable_shared_from_this<Component>
{
	int entityID = 0;

	Component()
	{
		entityID = 0;
	}
};