#pragma once
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <exception>

namespace NobleEngine
{
	/**
	*A struct that other types of resources inherit from, e.g textures and models.
	*/
	struct Resource
	{
		/**
		*Stores the path of the resource. This is used to check if the resource is already loaded.
		*/
		std::string resourcePath;

		/**
		*Loads the resource.
		*/
		virtual void OnLoad() {};
	};
}
#endif