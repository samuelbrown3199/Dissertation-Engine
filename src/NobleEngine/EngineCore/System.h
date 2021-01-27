#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <math.h>
#include <thread>
#include <mutex>

#include "ThreadingManager.h"

#define SetupComponentList(T) std::vector<std::shared_ptr<T>> Component<T>::componentList;

namespace NobleEngine
{
	class Application;

	/**
	*Stores performance information for systems.
	*/
	struct SystemPerformanceStats
	{
		double updateTime, renderTime;
		int componentListSize;
	};

	struct SystemBase
	{
	protected:

		SystemPerformanceStats performanceStats;
		std::vector<std::shared_ptr<std::thread>> workerThreads;
	public:
		/**
		*Stores a weak pointer back to the application core.
		*/
		std::weak_ptr<Application> application;
		/**
		*Tells the system whether or not it should use a seperated thread or not.
		*/
		bool useThreading = false;
		/**
		*Tells the system whether or not it should use a update or not.
		*/
		bool useUpdate = true;
		/**
		*Tells the system whether or not it should use a render or not.
		*/
		bool useRender = true;
		/**
		*Determines how many components a thread should handle.
		*/
		int maxComponentsPerThread = 1024;
		/**
		*Sets the amount of components a worker thread should handle, and enables system threading.
		*/
		void SetThreadingUse(int componentsPerThread)
		{
			useThreading = true;
			maxComponentsPerThread = componentsPerThread;
		}
		/**
		*Returns the application as a shared pointer.
		*/
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
		/**
		*Returns performance information from the system.
		*/
		SystemPerformanceStats GetPerformanceStats()
		{
			return performanceStats;
		}
	};

	/**
	*System struct that component systems can inherit from. Systems handle game functionality.
	*/
	template<typename T>
	struct System : public SystemBase
	{
	private:
		/**
		*Update is called every frame.
		*/
		void Update()
		{
			performanceStats.componentListSize = T::componentList.size();

			if (useUpdate)
			{
				Uint32 updateStart = SDL_GetTicks();
				PreUpdate();

				if (!useThreading)
				{
					for (size_t co = 0; co < T::componentList.size(); co++)
					{
						OnUpdate(T::componentList.at(co));
					}
				}
				else
				{
					int amountOfThreads = ceil(T::componentList.size() / maxComponentsPerThread)+1;
					for (int i = 0; i < amountOfThreads; i++)
					{
						int buffer = maxComponentsPerThread * i;						
						workerThreads.emplace_back(ThreadingManager::CreateThread(&System<T>::ThreadUpdate, this, maxComponentsPerThread, buffer));
					}

					for (int i = workerThreads.size()-1; i >= 0; i--)
					{
						ThreadingManager::JoinThread(workerThreads.at(i));
						workerThreads.pop_back();
					}
				}

				performanceStats.updateTime = SDL_GetTicks() - updateStart;
			}
		}
		/**
		*Used to generate the functionality of a worker update thread.
		*/
		void ThreadUpdate(int amount, int buffer)
		{
			int maxCap = buffer + amount;
			for (size_t co = buffer; co < maxCap; co++)
			{
				if (co >= T::componentList.size())
					continue;
				if (T::componentList.at(co))
				{
					OnUpdate(T::componentList.at(co));
				}
			}
		}
		/**
		*Render is called every frame.
		*/
		void Render()
		{
			if (useRender)
			{
				Uint32 renderStart = SDL_GetTicks();
				PreRender();

				if (!useThreading)
				{
					for (size_t co = 0; co < T::componentList.size(); co++)
					{
						OnRender(T::componentList.at(co));
					}
				}
				else
				{
					int amountOfThreads = ceil(T::componentList.size() / maxComponentsPerThread)+1;
					std::cout << "Amount required for " << T::componentList.size() << " components is " << amountOfThreads << " thread(s) with each thread handling " << maxComponentsPerThread << " components." << std::endl;
					for (int i = 0; i < amountOfThreads; i++)
					{
						int buffer = maxComponentsPerThread * i;
						workerThreads.emplace_back(ThreadingManager::CreateThread(&System<T>::ThreadRender, this, maxComponentsPerThread, buffer));
					}

					for (size_t i = workerThreads.size(); i > 0; i--)
					{
						ThreadingManager::JoinThread(workerThreads.at(i));
						workerThreads.pop_back();
					}
				}

				performanceStats.renderTime = SDL_GetTicks() - renderStart;
			}
		}
		/**
		*Used to generate the functionality of a worker render thread.
		*/
		void ThreadRender(int amount, int buffer)
		{
			int maxCap = buffer + amount;
			for (size_t co = buffer; co < maxCap; co++)
			{
				if (co >= T::componentList.size())
					continue;
				if (T::componentList.at(co))
				{
					OnRender(T::componentList.at(co));
				}
			}
		}
	public:
		/**
		*Function is called before update loops over every component.
		*/
		virtual void PreUpdate() {};
		/**
		*Function is called before render loops over every component.
		*/
		virtual void PreRender() {};
		/**
		*Inherited classes can implement this function with a parameter taking in a shared pointer of the type. Functionality can then be called on that pointer.
		*/
		virtual void OnUpdate(std::shared_ptr<T> comp) {};
		/**
		*Inherited classes can implement this function with a parameter taking in a shared pointer of the type. Functionality can then be called on that pointer.
		*/
		virtual void OnRender(std::shared_ptr<T> comp) {};
		/**
		*Sets the system to use each feature, such as threading, update & rendering.
		*/
		void SetSystemUse(bool update, bool render)
		{
			useUpdate = update;
			useRender = render;
		}
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