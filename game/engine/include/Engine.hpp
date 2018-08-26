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
		Engine();
		~Engine();
		void start();
		void blockingStart();
		void stop();
		bool isRunning() const { return thread.isRunning(); }
		static bool isInitialized();
		void runLater(std::function<void()> function);

		private:
		std::unique_ptr<Window> window;
		utils::ConsumerThread thread;

		void onStart();
		void onStop();
		void update();
	};
}	// namespace engine

#endif	// CULT_ENGINE_HPP
