#include <g3log/logworker.hpp>
#include "Engine.hpp"

int main(int, char** argv) {
  auto worker = g3::LogWorker::createLogWorker();
  auto defaultHandler = worker->addDefaultLogger("log", argv[0]);
  g3::initializeLogging(worker.get());

  LOG(INFO) << "Starting Cult" << std::endl;

  GEngine::Engine::getEngine().init();
  GEngine::Engine::getEngine().start();

  GEngine::Engine::getEngine().terminate();

  return 0;
}
