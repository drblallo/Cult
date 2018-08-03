//
// Created by massimo on 03/08/18.
//

#include "Engine_Internal.hpp"

#include <GLFW/glfw3.h>
#include <g3log/g3log.hpp>

#include "Window.hpp"

namespace GEngine
{
	Engine_Internal::Engine_Internal(): window(nullptr), thread() {}
	Engine_Internal::~Engine_Internal() { thread.blockingStop(); }

	void Engine_Internal::start()
	{
		thread.start([this]() { onStart(); }, [this] { onStop(); });
	}

	void Engine_Internal::blockingStart()
	{
		thread.blockingStart([this]() { onStart(); }, [this] { onStop(); });
	}

	void Engine_Internal::stop() { thread.stop(); }

	void Engine_Internal::update()
	{
		window->update();
		glfwPollEvents();

		if (window->shouldClose())
			stop();
		else
			thread.runLater([this]() { update(); });
	}

	void Engine_Internal::onStop()
	{
		thread.stop();
		LOG(INFO) << "Tearing down Engine" << std::endl;

		window.reset(nullptr);
	}

	void Engine_Internal::onStart()
	{
		window = std::make_unique<Window>(640, 480, "Main Window");

		window->makeCurrentContext();
		glfwSwapInterval(1);

		thread.runLater([this]() { update(); });
	}

}	// namespace GEngine
