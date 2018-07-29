//
// Created by blallo on 27/07/18.
//

#include "../include/Engine.hpp"
#include <g3log/g3log.hpp>
#include <GLFW/glfw3.h>
#include "Window.hpp"

namespace GEngine {

  Engine* Engine::engine(new Engine());

  void Engine::init() {
    LOG(INFO) << "Starting Engine" << std::endl;

    if (!glfwInit()) {
      LOG(FATAL) << "Could not start Engine" << std::endl;
      return;
    }

    glfwSetErrorCallback(logError);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    initialized = true;
  }

  void Engine::start() {
    if (!initialized) {
      LOG(FATAL) << "Engine was not initialized" << std::endl;
      return;
    }

    window = std::make_unique<Window>(Window(640, 480, "Main Window"));

    window->setInputCallback(
        [this](int a, int b, int c, int d){inputCallback(a, b, c, d);});

    window->makeCurrentContext();
    glfwSwapInterval(1);

    while (!window->shouldClose()) {
      window->swapBuffer();
      glfwPollEvents();
    }

    LOG(INFO) << "Closing Window" << std::endl;
    window.reset(nullptr);
  }

  void Engine::terminate() {
    if (!initialized) {
      LOG(FATAL) << "Engine was not initialized" << std::endl;
      return;
    }
    LOG(INFO) << "Tearing down Engine" << std::endl;

    glfwTerminate();
    initialized = false;
  }

  void Engine::logError(int, const char *description) {
    LOG(WARNING) << description << std::endl;
  }

  void Engine::inputCallback(int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      window->setShouldClose(true);
  }
}  //  namespace GEngine

