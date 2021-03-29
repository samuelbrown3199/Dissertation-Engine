#pragma once
#ifndef PERFORMANCESTATS_H_
#define PERFORMANCESTATS_H_

#include <iostream>

#include "Application.h"

namespace NobleEngine
{
	/**
	*Stores engine performance stats.
	*/
	struct PerformanceStats
	{
		friend class NobleEngine::Application;

	private:
		Uint32 frameStart, renderStart, updateStart, physicsStart;
		double fps = 0;
		double deltaT = 0;

		const int avgFrameRateCount = 60;
		std::vector<int> framerateList;
		int currentFrameCount = 0;

		/**
		*Resets the performance stats. Done every frame by the engine.
		*/
		void ResetPerformanceStats();
		/**
		*Updates the performance stats. Done every frame by the engine.
		*/
		void UpdatePerformanceStats();

	public:
		static double avgFPS;
		static double frameTime;
		static double updateTime;
		static double renderTime;
		static double physicsTime;

		/**
		*Prints out perfomance information for the current frame.
		*/
		static void PrintOutPerformanceStats();
	};
}

#endif