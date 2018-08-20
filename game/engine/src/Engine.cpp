//
// Created by blallo on 27/07/18.
//

#include "Engine.hpp"

#include <GLFW/glfw3.h>
#include <g3log/g3log.hpp>

#include "Engine_Internal.hpp"
#include "Window.hpp"

namespace engine
{
	std::atomic<bool> initialized;
	std::mutex initLock;
	Engine_Internal engine;

	void Engine::init()
	{
		std::lock_guard<std::mutex> g(initLock);
		if (initialized.load())
			return;

		LOG(INFO) << "Starting Engine";

		if (!glfwInit())
		{
			LOG(FATAL) << "Could not start Engine" << std::endl;
			return;
		}

		glfwSetErrorCallback(logError);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		initialized.store(true);
	}

	void Engine::terminate()
	{
		std::lock_guard<std::mutex> g(initLock);
		if (!initialized.load())
			return;

		initialized.store(false);
		glfwTerminate();
	}

	void Engine::start()
	{
		init();
		engine.start();
	}

	void Engine::blockingStart()
	{
		init();
		engine.blockingStart();
	}

	void Engine::stop() { engine.stop(); }

	void Engine::logError(int, const char *description)
	{
		LOG(WARNING) << description << std::endl;
	}

	bool Engine::isRunning() { return engine.isRunning(); }

}	// namespace engine
