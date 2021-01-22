#include "ThreadingManager.h"

namespace NobleEngine
{
	int ThreadingManager::maxAmountOfThreads = 0;
	std::vector<std::shared_ptr<std::thread>> ThreadingManager::threads;

	void ThreadingManager::SetupMaxThreads()
	{
		maxAmountOfThreads = std::thread::hardware_concurrency();
		maxAmountOfThreads--;
	}

	void ThreadingManager::CleanupLooseThreads()
	{
		for (size_t i = 0; i < threads.size(); i++)
		{
			threads.at(i)->join();
		}

		threads.clear();
	}

	void ThreadingManager::JoinThread(std::shared_ptr<std::thread> thread)
	{
		std::vector<std::shared_ptr<std::thread>>::iterator itr = std::find(threads.begin(), threads.end(), thread);
		threads.erase(itr);

		thread->join();
	}
}