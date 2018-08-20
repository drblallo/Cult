//
// Created by blallo on 27/07/18.
//

#ifndef CULT_ENGINE_HPP
#define CULT_ENGINE_HPP

#include <memory>

#include "ConsumerThread.hpp"

namespace engine
{
	class Window;

	class Engine
	{
		public:
		static void start();
		static void blockingStart();
		static void stop();
		static void terminate();
		static bool isRunning();

		private:
		static void init();
		static void logError(int error, const char* description);
	};
}	// namespace engine

#endif	// CULT_ENGINE_HPP
