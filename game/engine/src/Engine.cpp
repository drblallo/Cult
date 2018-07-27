//
// Created by blallo on 27/07/18.
//

#include "../include/Engine.hpp"
#include <GLFW/glfw3.h>
#include <g3log/g3log.hpp>

namespace GEngine {

  void Engine::start() {
    LOG(INFO) << "Starting Engine" << std::endl;

    if (!glfwInit()) {
      LOG(FATAL) << "Could not start Engine" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  void Engine::stop() {
    glfwTerminate();
    LOG(INFO) << "Tearing down Engine" << std::endl;
  }
}

