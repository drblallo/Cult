//
// Created by massimo on 28/07/18.
//

#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <g3log/g3log.hpp>

namespace GEngine
{
	Window::Window(int xSize, int ySize, const std::string &name, Window *share)
	{
		GLFWwindow *shrWindow(nullptr);
		if (share)
			shrWindow = share->window;

		window = glfwCreateWindow(xSize, ySize, name.c_str(), nullptr, shrWindow);

		glfwSetWindowUserPointer(window, this);
		glfwSetKeyCallback(window, Window::staticKeyCallback);
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
		glfwSetKeyCallback(window, Window::staticKeyCallback);
		other.window = nullptr;
		glfwSetWindowUserPointer(window, this);
	}

	void Window::update()
	{
		renderer.render();
		glfwSwapBuffers(window);
	}

	bool Window::shouldClose() const
	{
		return static_cast<bool>(glfwWindowShouldClose(window));
	}

	void Window::makeCurrentContext() { glfwMakeContextCurrent(window); }

	void Window::staticKeyCallback(
			GLFWwindow *window, int key, int scanCode, int action, int mods)
	{
		Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
		if (w)
			w->keyCallback(key, scanCode, action, mods);
	}

	void Window::setShouldClose(bool shouldClose)
	{
		glfwSetWindowShouldClose(window, shouldClose);
	}

	void Window::keyCallback(int key, int, int action, int)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			setShouldClose(true);
	}

}	// namespace GEngine
