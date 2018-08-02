//
// Created by blallo on 27/07/18.
//

#ifndef CULT_ENGINE_HPP
#define CULT_ENGINE_HPP

#include <memory>
#include "ConsumerThread.hpp"

class GLFWwindow;

namespace GEngine
{
class Window;

class Engine
{
  public:
  Engine();
  ~Engine();
  static Engine& getEngine();
  static void init();
  static void terminate();

  void start();
  void blockingStart();
  void stop();
  bool isRunning() const { return thread.isRunning(); }

  private:
  std::unique_ptr<Window> window;
  utils::ConsumerThread thread;

  static std::atomic<bool> initialized;
  static std::mutex initLock;

  void update();
  void onStart();
  void onStop();

  static void logError(int error, const char* description);
  static Engine engine;
  void inputCallback(int key, int scanCode, int action, int mods);
};
}  // namespace GEngine

#endif  // CULT_ENGINE_HPP
