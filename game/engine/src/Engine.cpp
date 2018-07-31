//
// Created by blallo on 27/07/18.
//

#include "Engine.hpp"
#include <g3log/g3log.hpp>
#include <GLFW/glfw3.h>
#include "Window.hpp"

namespace GEngine {

  Engine Engine::engine;
  std::atomic<bool> Engine::initialized;
  std::mutex Engine::initLock;

  Engine::Engine() :
    window(nullptr),
    thread([this]() {onStart();}, [this] {onStop();}) {}
  Engine::~Engine() {thread.blockingStop();}

  Engine& Engine::getEngine() {
    return engine;
  }

  void Engine::init() {
    std::lock_guard<std::mutex> g(initLock);
    if (initialized.load())
      return;

    LOG(INFO) << "Starting Engine" << std::endl;

    if (!glfwInit()) {
      LOG(FATAL) << "Could not start Engine" << std::endl;
      return;
    }

    glfwSetErrorCallback(logError);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    initialized.store(true);
  }

  void Engine::terminate() {
    std::lock_guard<std::mutex> g(initLock);
    if (!initialized.load())
      return;

    initialized.store(false);
    glfwTerminate();
  }

  void Engine::update() {
    window->swapBuffer();
    glfwPollEvents();

    if (window->shouldClose())
      stop();
    else
      thread.runLater([this]() { update(); });
  }

  void Engine::onStop() {
    thread.stop();
    LOG(INFO) << "Tearing down Engine" << std::endl;

    window.reset(nullptr);
  }

  void Engine::start() {
     thread.start();
  }

  void Engine::stop() {
    thread.stop();
  }

  void Engine::onStart() {

    init();
    window = std::make_unique<Window>(Window(640, 480, "Main Window"));

    Window::setInputCallback(
        [this](int a, int b, int c, int d){inputCallback(a, b, c, d);});

    window->makeCurrentContext();
    glfwSwapInterval(1);

    thread.runLater([this]() { update(); });
  }

  void Engine::logError(int, const char *description) {
    LOG(WARNING) << description << std::endl;
  }

  void Engine::inputCallback(int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      window->setShouldClose(true);
  }
}  //  namespace GEngine

