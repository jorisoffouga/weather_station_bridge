#include <iostream>
#include <unistd.h>
#include <thread>
#include <signal.h>
#include "Bridge.hpp"

static void usage(void)
{
	fprintf(stdout, "wheather-station-bridge -p <tty> \n");
	fprintf(stdout,
			" Available OPTIONS\n"
			" -h : print help and exit\n"
			" -p : tty \n"
	);
	fprintf(stdout, "wheather-station-bridge -p /dev/ttyUBS0 \n");
}

int main(int argc, char **argv)
{
	int c;
	std::string device;

	while ((c = getopt(argc, argv, "p:h")) != EOF) {
		switch (c) {
		case 'p':
			device.append(optarg);
			break;
		case 'h':
			usage();
			exit(EXIT_SUCCESS);
		default:
			usage();
			exit(EXIT_FAILURE);
		}
	}

	if (device.empty()) {
		std::cerr << "Empty tty interface provides " << std::endl;
		usage();
		exit(EXIT_FAILURE);
	}

	Bridge bridge;

	if (bridge.init(device) < 0){
		std::cerr << "Init Failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	bridge.run();

	exit(EXIT_SUCCESS);
}
