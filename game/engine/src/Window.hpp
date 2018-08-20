//
// Created by massimo on 28/07/18.
//

#ifndef CULT_WINDOW_HPP
#define CULT_WINDOW_HPP
#include <functional>
#include <string>

#include "Renderer.hpp"

struct GLFWwindow;

namespace engine
{
	class Window
	{
		public:
		Window(
				int xSize, int ySize, const std::string &name, Window *share = nullptr);
		~Window();
		Window(const Window &other) = delete;
		Window &operator=(const Window &other) = delete;
		Window(Window &&other) noexcept;
		void update();
		bool shouldClose() const;
		void makeCurrentContext();
		void setShouldClose(bool shouldClose);

		private:
		GLFWwindow *window;
		Renderer renderer;
		void keyCallback(int key, int scanCode, int action, int mods);
		static void staticKeyCallback(
				GLFWwindow *window, int key, int scanCode, int action, int mods);
	};
}	// namespace engine

#endif	// CULT_WINDOW_HPP
