#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include "audio/audio.h"
using namespace std;

void show_usage() {
	cout << "pomusi --work <work-duration> --break <break-duration>" << endl <<
		"--work <time-in-seconds>" << " time to run pomodoro duration for" << endl <<
		"--break <time-in-seconds>" << " time to run break duration for" << endl <<
		"--quiet" << " disable sound notifications" << 
		"--verbose" << "enable debug messages" << endl;
}

int parse_int(char* str) {
	int num = 0;
	int length = strlen(str);
	for(int i = 0; i < length; i++) {
		num = (num * 10) + (static_cast<int>(str[i]) - 48);
	}
	return num;
}

class Time {
	protected:
		int duration;
		double sound_freq;
	public:
		Time(): duration(0), sound_freq(0.0) {}

		Time(int dur, double freq): duration(dur), sound_freq(freq) {}

		virtual void start() {
			sleep(duration);
		}

		virtual void notify() {
			Note n(sound_freq);
			n.play();
		}
};

class Work : public Time {
	public:
		Work(): Time(0, 0.0) {}
		Work(int dur, double freq): Time(dur, freq) {}
};

class Break: public Time {
	public:
		Break(): Break(0, 0.0) {}
		Break(int dur, double freq): Time(dur, freq) {}
};

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
