//
// Created by blallo on 27/07/18.
//

#ifndef CULT_ENGINE_HPP
#define CULT_ENGINE_HPP

#include <memory>
#include "ConsumerThread.hpp"

class GLFWwindow;

namespace GEngine {
class Window;

class Engine : public utils::ConsumerThread {

 public:
  Engine();
  static Engine& getEngine();

 protected:
  virtual void onStart();
  virtual void onStop();

 private:
  std::unique_ptr<Window> window;
  static bool initialized;

  static void init();
  static void terminate();

  void update();

  static void logError(int error, const char* description);
  static Engine engine;
  void inputCallback(int key, int scanCode, int action, int mods);
};
}  // namespace GEngine

#endif //CULT_ENGINE_HPP
