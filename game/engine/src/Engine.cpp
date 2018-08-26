//
// Created by blallo on 27/07/18.
//

#include "Engine.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <g3log/g3log.hpp>
//#include <glad/glad.h>

#include "Window.hpp"

namespace engine
{
	std::atomic<bool> initialized;
	std::atomic<unsigned> openWindows;
	std::mutex initLock;

	void logError(int, const char *description)
	{
		LOG(WARNING) << description << std::endl;
	}

	void init()
	{
		std::lock_guard<std::mutex> g(initLock);
		if (initialized.load())
			return;

		LOG(INFO) << "Starting Engine";

		if (!glfwInit())
		{
			LOG(FATAL) << "Could not start Engine";
			return;
		}

		glfwSetErrorCallback(logError);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		initialized.store(true);
	}

	void terminate()
	{
		std::lock_guard<std::mutex> g(initLock);
		if (!initialized.load() || openWindows.load() != 0)
			return;

		initialized.store(false);
		glfwTerminate();
	}

	Engine::Engine(): window(nullptr), thread() {}
	Engine::~Engine() { thread.blockingStop(); }

	bool Engine::isInitialized() { return initialized.load(); }

	void Engine::start()
	{
		thread.start([this] { onStart(); }, [this] { onStop(); });
	}

	void Engine::runLater(std::function<void()> function)
	{
		thread.runLater(function);
	}

	void Engine::blockingStart()
	{
		thread.blockingStart([this] { onStart(); }, [this] { onStop(); });
	}

	void Engine::stop() { thread.stop(); }

	void Engine::update()
	{
		window->update();
		glfwPollEvents();

		if (window->shouldClose())
			stop();
		else
			thread.runLater([this]() { update(); });
	}

	void Engine::onStop()
	{
		LOG(INFO) << "Tearing down Engine";

		window.reset(nullptr);
		openWindows--;
		terminate();
	}

	void Engine::onStart()
	{
		openWindows++;
		init();
		window = std::make_unique<Window>(640, 480, "Main Window");

		window->makeCurrentContext();
		glfwSwapInterval(1);

		thread.runLater([this]() { update(); });
	}

}	// namespace engine
