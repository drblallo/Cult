#include <g3log/logworker.hpp>
#include "g3log/g3log.hpp"

int main(int argc, char** argv) {
  auto worker = g3::LogWorker::createLogWorker();
  auto defaultHandler = worker->addDefaultLogger("log", argv[0]);
  g3::initializeLogging(worker.get());

  LOG(INFO) << "Hello, Worlddasd!" << std::endl;
  LOG(INFO) << "Hello, World!" << std::endl;
  LOG(INFO) << "Hello, World!" << std::endl;
  LOG(INFO) << "Hello, World!" << std::endl;
  LOG(INFO) << "Hello, World!" << std::endl;
  LOG(INFO) << "Hello, Worldasdd!" << std::endl;
  return 0;
}