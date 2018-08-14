#include <iostream>

#include "Engine.hpp"
#include "g3log/logworker.hpp"

struct CoutSink
{
	void ReceiveLogMessage(g3::LogMessageMover logEntry)
	{
		std::cout << logEntry.get().toString();
	}
};

int main(int, char**)
{
	auto worker = g3::LogWorker::createLogWorker();
	// auto defaultHandler = worker->addDefaultLogger("log", argv[0]);
	worker->addSink(std::make_unique<CoutSink>(), &CoutSink::ReceiveLogMessage);
	g3::initializeLogging(worker.get());

	LOG(INFO) << "Starting Cult" << std::endl;
	GEngine::Engine::blockingStart();

	return 0;
}
