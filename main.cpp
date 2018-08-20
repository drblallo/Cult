#include <iostream>

#include "Engine.hpp"
#include "SoutSink.hpp"
#include "g3log/logworker.hpp"

int main(int, char**)
{
	utils::initLogger();
	LOG(INFO) << "Starting Cult";
	engine::Engine::blockingStart();

	return 0;
}
