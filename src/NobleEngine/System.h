#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H

#include <memory>
#include <vector>
#include <string>

#define SetupComponentList(T) std::vector<std::shared_ptr<T>> Component<T>::componentList;

namespace NobleEngine
{
	class Application;

	struct SystemBase
	{
		/**
		*Stores the tags that the system targets. Makes it possible to target specific entities with certain tags.
		*/
		std::vector<std::string> targetTags;

		/**
		*Stores a weak pointer back to the application core.
		*/
		std::weak_ptr<Application> application;

		std::shared_ptr<Application> GetApplication()
		{
			return application.lock();
		}

		/**
		*Update is called every frame.
		*/
		virtual void Update() {};
		/**
		*Render is called every frame.
		*/
		virtual void Render() {};

		/**
		*Used in the inherited System struct.
		*/
		virtual void ClearUnneededComponents() {};
	};

	/**
	*System struct that component systems can inherit from. Systems handle game functionality.
	*/
	template<typename T>
	struct System : public SystemBase
	{
		/**
		*Update is called every frame.
		*/
		virtual void Update() {};
		/**
		*Render is called every frame.
		*/
		virtual void Render() {};
		
		/**
		*Clears the list of component data that is marked for deletion. Handles the passed type through the template.
		*/
		void ClearUnneededComponents()
		{
			for (size_t co = 0; co < T::componentList.size(); co++)
			{
				if (T::componentList.at(co)->markedForDeletion)
				{
					T::componentList.erase(T::componentList.begin() + co);
				}
			}
		}
	};
}
#endif