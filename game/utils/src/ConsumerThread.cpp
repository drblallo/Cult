//
// Created by massimo on 29/07/18.
//

#include "ConsumerThread.hpp"
#include <g3log/g3log.hpp>

namespace utils {

  ConsumerThread::ConsumerThread() :
      started(false), running(false), ended(false) {}

  ConsumerThread::~ConsumerThread() {
      stop();
  }

  void ConsumerThread::start(bool detachThread) {
    if (wasStarted()) {
      LOG(WARNING) << "Thread was already started" << std::endl;
      return;
    }
    if (detachThread) {
      started = true;
      running = true;

      std::thread thread(std::bind(&ConsumerThread::run, this));
      thread.detach();
    } else {
      processAll();
    }
  }

  void ConsumerThread::stop() {
    if (!isRunning()) {
      LOG(WARNING) << "Trying to stop a already stopped thread" << std::endl;
      return;
    }
    running = false;
    while (!hasEnded())
      std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  }

  void ConsumerThread::run() {
    while (running) {
      processAll();
      std::this_thread::sleep_for(std::chrono::nanoseconds(10));
    }
    onStop();
    ended = true;
  }

  void ConsumerThread::processAll() {
    while (!actionQueue.empty()) {
      actionQueue.poll()();
    }
  }

}  // namespace utils

