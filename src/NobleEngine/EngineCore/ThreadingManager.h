#pragma once
#ifndef THREADINGMANAGER_H_
#define THREADINGMANAGER_H_

#include <vector>
#include <memory>
#include <algorithm>
#include <thread>

namespace NobleEngine
{
	struct ThreadingManager
	{
		static int maxAmountOfThreads;
		static std::vector<std::shared_ptr<std::thread>> threads;

		static void SetupMaxThreads();
		static void CleanupLooseThreads();

		template<typename ... Args>
		/**
		*Creates a thread and adds it to a list. Returns a shared pointer to the thread. Arguments must be passed as if created a std::thread as normal.
		*/
		static std::shared_ptr<std::thread> CreateThread(Args&&... args)
		{
			std::shared_ptr<std::thread> thread = std::make_shared<std::thread>(std::forward<Args>(args)...);
			threads.emplace_back(thread);

			return thread;
		}
		/**
		*Joins the thread back. Removes it from the list of current threads.
		*/
		static void JoinThread(std::shared_ptr<std::thread> thread);
	};
}

#endif