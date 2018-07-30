//
// Created by massimo on 28/07/18.
//

#ifndef CULT_WINDOW_HPP
#define CULT_WINDOW_HPP
#include <string>
#include <functional>

class GLFWwindow;

namespace GEngine {

  class Window {
   public:
    Window(int xSize, int ySize, const std::string& name);
    ~Window();
    Window(const Window& other) = delete;
    Window& operator=(const Window& other) = delete;
    Window(Window&& other) noexcept;
    void swapBuffer();
    bool shouldClose() const;
    void makeCurrentContext();
    void setShouldClose(bool shouldClose);
    static void setInputCallback(std::function<void(int key, int scanCode, int action, int mods)> callback);

   private:
    GLFWwindow* window;
    static std::function<void(int key, int scanCode, int action, int mods)> inputCallback;
    static void underlyingCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
    void nextFrame();
  };
}

#endif //CULT_WINDOW_HPP
