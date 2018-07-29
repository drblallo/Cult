//
// Created by blallo on 27/07/18.
//

#ifndef CULT_ENGINE_HPP
#define CULT_ENGINE_HPP

#include <memory>

class GLFWwindow;

namespace GEngine {
class Window;

class Engine {
 public:
  void init();
  void start();
  void terminate();
  static inline Engine &getEngine() { return *engine; }

 private:
  static Engine *engine;
  bool initialized;
  std::unique_ptr<Window> window;

  static void logError(int error, const char* description);
  void inputCallback(int key, int scanCode, int action, int mods);
};
}  // namespace GEngine

#endif //CULT_ENGINE_HPP
