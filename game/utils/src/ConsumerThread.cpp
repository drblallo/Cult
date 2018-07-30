//
// Created by massimo on 29/07/18.
//

#include "ConsumerThread.hpp"
#include <g3log/g3log.hpp>

namespace utils {

  ConsumerThread::ConsumerThread() :
    keepAlive(false),
    keepAliveMySelft(false),
    running(false),
    startCanReturn(false),
    mutex()
    {}

  ConsumerThread::~ConsumerThread() {
    stop();
  }

  void ConsumerThread::start() {
    std::lock_guard<std::mutex> g(mutex);

    bool expected(false);
    if (!keepAlive.compare_exchange_weak(expected, true)) {
      LOG(WARNING) << "Thread was already started" << std::endl;
      return;
    }

    startCanReturn.store(false);

    std::thread thread(std::bind(&ConsumerThread::run, this));
    thread.detach();
    while (!startCanReturn.load())
      std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  }

  void ConsumerThread::terminateNow() {
    keepAliveMySelft.store(false);
  }

  void ConsumerThread::stop() {
    std::lock_guard<std::mutex> g(mutex);
    bool expected(true);
    if (!keepAlive.compare_exchange_weak(expected, false)) {
      LOG(WARNING) << "Thread was already stopped" << std::endl;
      return;
    }

    while (running.load())
      std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  }

  void ConsumerThread::run() {
    keepAliveMySelft.store(true);
    running.store(true);
    startCanReturn.store(true);
    onStart();
    while (keepAlive.load() && keepAliveMySelft.load()) {
      processAll();
      std::this_thread::sleep_for(std::chrono::nanoseconds(10));
    }
    onStop();

    keepAlive.store(false);
    running.store(false);
  }

  void ConsumerThread::processAll() {
    while (!actionQueue.empty() && keepAlive.load() && keepAliveMySelft.load())
      actionQueue.poll()();
  }

}  // namespace utils

