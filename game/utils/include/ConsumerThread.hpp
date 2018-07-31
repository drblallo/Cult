//
// Created by massimo on 29/07/18.
//

#ifndef CULT_CONSUMERTHREAD_HPP
#define CULT_CONSUMERTHREAD_HPP

#include <atomic>
#include <thread>
#include "SafeQueue.hpp"

namespace utils {

  class ConsumerThread {
   public:
    //creates a new consumer thread not yet started
    ConsumerThread();
    ConsumerThread(std::function<void()> onStart, std::function<void()> onEnd);
    //Cannot be called from inside the spawned thread, will terminate the thread, will wait for him to end
    ~ConsumerThread();
    ConsumerThread(const ConsumerThread& other) = delete;
    ConsumerThread(ConsumerThread&& other) = delete;
    ConsumerThread& operator=(const ConsumerThread& other) = delete;

    //spawn a new thread that will consume every operation inserted with run later.
    //cannot be called if running == true
    //sets running to ture
    void start();
    //stops the thread and does not wait for him to end
    void stop();
    //stops the thread and waits for him to end
    void blockingStop();
    //return true if the thread is processing instructions
    bool isRunning() const {return running.load();}
    //runs a function in the thread
    void runLater(std::function<void()> operation) {actionQueue.offer(std::move(operation));}

   private:
    //keeps evaluating the action queue until running becomes false.
    void run();
    //evalue all the actions until the queue is empty
    void processAll();
    std::atomic<bool> running;
    std::atomic<bool> terminate;
    std::thread::id workerThreadID;
    SafeQueue<std::function<void()> > actionQueue;
    std::function<void()> onStart;
    std::function<void()> onEnd;

  };
} // namespace utils

#endif //CULT_CONSUMERTHREAD_HPP
