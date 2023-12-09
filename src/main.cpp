#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <csignal>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include "audio/audio.h"
#include "utils/utils.h"
#include "pomodoro/pomodoro.h"
using namespace std;


int main(int argc, char* argv[]) {

	opts options = parse_arguments(argc, argv);
	
	if(options.kill_daemon) {
		pid_t pid;
		ifstream pidfile("paprika.pid");
		pidfile >> pid;
		kill(pid, SIGKILL);
		exit(0);
	}

	Work w = Work(options.work_duration, 392.0); // G note
	Break b = Break(options.break_duration, 261.63); // C note

	if(options.daemonize) {
		pid_t pid = fork();

		if(pid < 0) {
			if(options.verbose) cout << "Error: Failed to detach." << endl;
			return EXIT_FAILURE;
		}

		if(pid > 0) {
			if(options.verbose) cout << "Detaching to background." << endl;
			ofstream pidfile("paprika.pid");
			pidfile << pid;
			pidfile.close();

			return EXIT_SUCCESS;
		}

		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}

	Pomodoro p(w, b);
	p.main_loop(options);

	return 0;
}
