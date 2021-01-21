#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H

#include <memory>
#include <vector>
#include <string>
#include <math.h>
#include <thread>
#include <mutex>

#define SetupComponentList(T) std::vector<std::shared_ptr<T>> Component<T>::componentList;

namespace NobleEngine
{
	class Application;

	struct SystemBase
	{
	protected:
		std::vector<std::thread> workerThreads;
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
			if (useUpdate)
			{
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
					std::cout << "Amount required for " << T::componentList.size() << " components is " << amountOfThreads << " thread(s) with each thread handling " << maxComponentsPerThread << " components." << std::endl;
					for (int i = 0; i < amountOfThreads; i++)
					{
						int buffer = maxComponentsPerThread * i;						
						workerThreads.emplace_back(std::thread(&System<T>::ThreadUpdate, this, maxComponentsPerThread, buffer));
					}

					for (int i = workerThreads.size(); i > 0; i--)
					{
						workerThreads.at(i).join();
						workerThreads.pop_back();
					}
				}
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
						workerThreads.emplace_back(std::thread(&System<T>::ThreadRender, this, maxComponentsPerThread, buffer));
					}

					for (int i = workerThreads.size(); i > 0; i--)
					{
						workerThreads.at(i).join();
						workerThreads.pop_back();
					}
				}
			}
		}
		/**
		*Used to generate the functionality of a worker render thread.
		*/
		void ThreadRender(int amount, int buffer)
		{
			std::cout << "Render Thread" << std::endl;

			int maxCap = buffer + amount;
			for (size_t co = buffer; co < maxCap; co++)
			{
				if (T::componentList.at(co))
				{
					OnRender(T::componentList.at(co));
				}
			}
		}
	public:
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
		void SetSystemUse(bool threading, bool update, bool render)
		{
			useThreading = threading;
			useThreading = false; //temp
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