#include <g3log/logworker.hpp>
#include <iostream>
#include "Engine.hpp"

struct CoutSink {
  void ReceiveLogMessage(g3::LogMessageMover logEntry) {
    std::cout << logEntry.get().toString();
  }
};

int main(int, char** argv) {
  auto worker = g3::LogWorker::createLogWorker();
  //auto defaultHandler = worker->addDefaultLogger("log", argv[0]);
  worker->addSink(std::make_unique<CoutSink>(), &CoutSink::ReceiveLogMessage);
  g3::initializeLogging(worker.get());

  LOG(INFO) << "Starting Cult" << std::endl;

  GEngine::Engine::getEngine().init();
  GEngine::Engine::getEngine().start();

  GEngine::Engine::getEngine().terminate();

  return 0;
}
