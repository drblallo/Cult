//
// Created by massimo on 29/07/18.
//

#include "ConsumerThread.hpp"
#include <g3log/g3log.hpp>

namespace utils {

  ConsumerThread::ConsumerThread() :
    running(false),
    terminate(false),
    workerThreadID(),
    onStart(),
    onEnd()
    {}

  ConsumerThread::ConsumerThread(
      std::function<void()> onStart,
      std::function<void()> onEnd) :
    running(false),
    terminate(false),
    workerThreadID(),
    onStart(std::move(onStart)),
    onEnd(std::move(onEnd))
{}

  ConsumerThread::~ConsumerThread() {
    if (std::this_thread::get_id() == workerThreadID) {
      LOG(FATAL) << "A thread cannot be able to destroy his own object" << std::endl;
      exit(EXIT_FAILURE);
    }

    blockingStop();
  }

  void ConsumerThread::start() {
    bool expected(false);
    if (!running.compare_exchange_weak(expected, true)) {
      LOG(WARNING) << "Thread was already started" << std::endl;
      return;
    }
    while (!actionQueue.empty())
      actionQueue.poll();

    std::thread thread(std::bind(&ConsumerThread::run, this));
    thread.detach();
  }

  void ConsumerThread::stop() {
    runLater([this] () { terminate.store(true); });
  }

  void ConsumerThread::blockingStop() {
    if (std::this_thread::get_id() == workerThreadID) {
      LOG(WARNING) << "Calls inside this thread cannot be blocking" << std::endl;
      return;
    }

    stop();

    while (running.load())
      std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  }

  void ConsumerThread::run() {
    workerThreadID = std::this_thread::get_id();
    terminate.store(false);

    if (onStart)
      onStart();

    while (!terminate.load()) {
      processAll();
      std::this_thread::sleep_for(std::chrono::nanoseconds(10));
    }

    if (onEnd)
      onEnd();

    running.store(false);
  }

  void ConsumerThread::processAll() {
    while (!actionQueue.empty() && !terminate.load())
      actionQueue.poll()();
  }

}  // namespace utils

