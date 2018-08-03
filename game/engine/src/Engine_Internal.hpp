//
// Created by massimo on 03/08/18.
//

#ifndef CULT_ENGINE_INTERNAL_HPP
#define CULT_ENGINE_INTERNAL_HPP

#include <memory>

#include "ConsumerThread.hpp"

namespace GEngine
{
	class Window;
	class Engine_Internal
	{
		public:
		Engine_Internal();
		~Engine_Internal();
		void start();
		void blockingStart();
		void stop();
		bool isRunning() const { return thread.isRunning(); }

		private:
		std::unique_ptr<Window> window;
		utils::ConsumerThread thread;

		void update();
		void onStart();
		void onStop();
	};
}	// namespace GEngine

#endif	// CULT_ENGINE_INTERNAL_HPP
