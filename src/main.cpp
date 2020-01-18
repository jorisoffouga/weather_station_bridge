#include <iostream>
#include <unistd.h>
#include <thread>
#include <signal.h>
#include "Bridge.hpp"

static bool stopped = false;

static void cleanThread(int iSignal)
{
	std::cout << "Kill signal detected " << iSignal << std::endl;
	stopped = true;
}

int main(int argc, char **argv)
{
	Bridge bridge("/dev/ttyUSB0");

	if (bridge.Init() < 0){
		std::cerr << "Init Failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	signal(SIGINT,  cleanThread);
	signal(SIGHUP,  cleanThread);
	signal(SIGTERM, cleanThread);
	signal(SIGKILL, cleanThread);
	signal(SIGQUIT, cleanThread);

	std::thread l_thread(&Bridge::Run, &bridge);

	while(stopped == false)
	{
		sleep(1);
	}

	l_thread.join();
	return 0;
}
