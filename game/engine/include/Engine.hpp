//
// Created by blallo on 27/07/18.
//

#ifndef CULT_ENGINE_HPP
#define CULT_ENGINE_HPP

namespace GEngine {
class Engine {
 private:
  static inline Engine &getEngine() { return *engine; }
  static Engine *engine;
  void start();
  void stop();
};
}  // namespace GEngine

#endif //CULT_ENGINE_HPP
