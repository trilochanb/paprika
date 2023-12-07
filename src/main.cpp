#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include "audio/audio.h"
#include "utils/utils.h"
#include "pomodoro/pomodoro.h"
using namespace std;

int main(int argc, char* argv[]) {
	Work w;
	Break b;
	bool play_sound = true;
	bool verbose = false;
	bool daemonize = false;

	Note G(392.0);
	Note C(261.63);


	// exit if there is no --work or --break flag and their parameters
	if(argc < 5) {
		show_usage();
		exit(0);
	}

	for(int i = 0; i < argc; i++) {
		if(!strcmp("--work", argv[i])) w = Work(parse_int(argv[i+1]), 392.0); // G note
		else if(!strcmp("--break", argv[i])) b = Break(parse_int(argv[i+1]), 261.63); // C note
		else if(!strcmp("--quiet", argv[i])) play_sound = false;
		else if(!strcmp("--verbose", argv[i])) verbose = true;
		else if(!strcmp("--detach", argv[i])) daemonize = true;
	}

	if(daemonize) {
		pid_t pid = fork();

		if(pid < 0) {
			if(verbose) cout << "Error: Failed to detach." << endl;
			return EXIT_FAILURE;
		}

		if(pid > 0) {
			if(verbose) cout << "Detaching to background." << endl;
			return EXIT_SUCCESS;
		}

		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}

	while(true) {
		if (verbose) cout << "Pomodoro started." << endl;
		if (play_sound) w.notify();
		w.start();
		if (verbose) cout << "Break started." << endl;
		if (play_sound) b.notify();
		b.start();
	}

	return 0;
}
