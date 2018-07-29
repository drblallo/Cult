//
// Created by massimo on 29/07/18.
//

#ifndef CULT_CONSUMERTHREAD_HPP
#define CULT_CONSUMERTHREAD_HPP

#include "SafeQueue.hpp"
namespace utils {

  class ConsumerThread {

   public:
    ConsumerThread();
    virtual ~ConsumerThread();
    ConsumerThread(const ConsumerThread& other) = delete;
    ConsumerThread(ConsumerThread&& other) = delete;
    ConsumerThread& operator=(const ConsumerThread& other) = delete;
    void start(bool detachThread);
    void stop();
    bool isRunning() const {return running;}
    bool wasStarted() const {return started;}

   private:
    void run();
    void processAll();
    bool started;
    bool running;
    SafeQueue<std::function<void()> > actionQueue;

   protected:
    virtual void onStop() {};
    void append(std::function<void()> operation) {actionQueue.offer(std::move(operation));}

  };
} // namespace utils

#endif //CULT_CONSUMERTHREAD_HPP
