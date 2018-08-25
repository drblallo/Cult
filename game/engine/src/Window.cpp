//
// Created by massimo on 28/07/18.
//

#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <g3log/g3log.hpp>

namespace engine
{
	Window::Window(int xSize, int ySize, const std::string &name, Window *share)
			: renderer(xSize, ySize)
	{
		GLFWwindow *shrWindow(nullptr);
		if (share)
			shrWindow = share->window;

		window = glfwCreateWindow(xSize, ySize, name.c_str(), nullptr, shrWindow);

		glfwSetWindowUserPointer(window, this);
		glfwSetKeyCallback(window, Window::staticKeyCallback);
		glfwSetWindowSizeCallback(window, Window::staticSizeCallback);
		if (!window)
		{
			LOG(FATAL) << "Could not create Window";
			return;
		}
	}

	Window::~Window()
	{
		if (window)
		{
			LOG(INFO) << "Closing Window";
			glfwDestroyWindow(window);
		}
	}

	Window::Window(Window &&other) noexcept
			: window(other.window), renderer(std::move(other.renderer))
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

	void Window::staticSizeCallback(GLFWwindow *window, int width, int height)
	{
		Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
		if (w)
			w->setSize(width, height);
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

	void Window::setSize(int width, int height)
	{
		LOG(DEBUG) << "resizing window";
		renderer.getCamera().setWidth(width);
		renderer.getCamera().setHeight(height);
	}

}	// namespace engine
