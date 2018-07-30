//
// Created by massimo on 29/07/18.
//

#ifndef CULT_CONSUMERTHREAD_HPP
#define CULT_CONSUMERTHREAD_HPP

#include <atomic>
#include "SafeQueue.hpp"

namespace utils {

  class ConsumerThread {

   public:
    //creates a new consumer thread not yet started
    ConsumerThread();
    //stops the thread, waits for to end, deletes it and returns, a thread can't suicide itselft, it will leak
    virtual ~ConsumerThread();
    ConsumerThread(const ConsumerThread& other) = delete;
    ConsumerThread(ConsumerThread&& other) = delete;
    ConsumerThread& operator=(const ConsumerThread& other) = delete;

    //spawn a new thread that will consume every operation inserted with run later.
    //will set keep alive to true
    //cannot be called if keep alive == true
    //does not wait for is running to be true
    void start();
    //stops the thread and waits for it to end properly before returning
    //cannot be called if keepalive is already false.
    void stop();
    //return true if the thread is processing instructions
    bool isRunning() const {return running.load();}

   private:
    //keeps evaluating the action queue until running becomes false.
    void run();
    //evalue all the actions until the queue is empty
    void processAll();
    std::atomic<bool> keepAlive;
    std::atomic<bool> keepAliveMySelft;
    std::atomic<bool> running;
    std::atomic<bool> startCanReturn;
    std::mutex mutex;
    SafeQueue<std::function<void()> > actionQueue;

   protected:
    virtual void onStop() {};
    virtual void onStart() {};
    void terminateNow();
    void runLater(std::function<void()> operation) {actionQueue.offer(std::move(operation));}

  };
} // namespace utils

#endif //CULT_CONSUMERTHREAD_HPP
