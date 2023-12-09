#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include "audio/audio.h"
#include "utils/utils.h"
#include "pomodoro/pomodoro.h"
using namespace std;

int main(int argc, char* argv[]) {

	check_arguments(argc);

	opts options = parse_arguments(argc, argv);
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
