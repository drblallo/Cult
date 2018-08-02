//
// Created by massimo on 28/07/18.
//

#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <g3log/g3log.hpp>

namespace GEngine
{
	std::function<void(int, int, int, int)> Window::inputCallback(nullptr);

	Window::Window(int xSize, int ySize, const std::string &name)
	{
		window = glfwCreateWindow(xSize, ySize, name.c_str(), nullptr, nullptr);
		glfwSetKeyCallback(window, Window::underlyingCallback);
		if (!window)
		{
			LOG(FATAL) << "Could not create Window" << std::endl;
			return;
		}
	}

	Window::~Window()
	{
		if (window)
		{
			LOG(INFO) << "Closing Window" << std::endl;
			glfwDestroyWindow(window);
		}
	}

	Window::Window(Window &&other) noexcept: window(other.window)
	{
		glfwSetKeyCallback(window, Window::underlyingCallback);
		other.inputCallback = nullptr;
		other.window				= nullptr;
	}

	void Window::swapBuffer() { glfwSwapBuffers(window); }

	bool Window::shouldClose() const
	{
		return static_cast<bool>(glfwWindowShouldClose(window));
	}

	void Window::makeCurrentContext() { glfwMakeContextCurrent(window); }

	void Window::setInputCallback(
			std::function<void(int, int, int, int)> callback)
	{
		inputCallback = std::move(callback);
	}

	void Window::underlyingCallback(
			GLFWwindow *, int key, int scanCode, int action, int mods)
	{
		if (inputCallback)
			inputCallback(key, scanCode, action, mods);
	}

	void Window::setShouldClose(bool shouldClose)
	{
		glfwSetWindowShouldClose(window, shouldClose);
	}

}	// namespace GEngine
