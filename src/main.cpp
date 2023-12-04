#include <iostream>
#include <cstring>
#include <unistd.h>
#include "audio/audio.h"
using namespace std;

void show_usage() {
	cout << "pomusi --work <work-duration> --break <break-duration>" << endl <<
		"--work <time-in-seconds>" << " time to run pomodoro duration for" << endl <<
		"--break <time-in-seconds>" << " time to run break duration for" << endl <<
		"--quiet" << " disable sound notifications" << endl;
}

int parse_int(char* str) {
	int num = 0;
	int length = strlen(str);
	for(int i = 0; i < length; i++) {
		num = (num * 10) + (static_cast<int>(str[i]) - 48);
	}
	return num;
}

int main(int argc, char* argv[]) {
	int work_duration;
	int break_duration;
	bool play_sound = true;

	Note G(392.0);
	Note C(261.63);


	// exit if there is no --work or --break flag and their parameters
	if(argc < 5) {
		show_usage();
		exit(0);
	}

	for(int i = 0; i < argc; i++) {
		if(!strcmp("--work", argv[i])) work_duration = parse_int(argv[i+1]);
		else if(!strcmp("--break", argv[i])) break_duration = parse_int(argv[i+1]);
		else if(!strcmp("--quiet", argv[i])) play_sound = false;
	}

	while(true) {
		cout << "Pomodoro started." << endl;
		if (play_sound) C.play();
		sleep(work_duration);
		cout << "Break started." << endl;
		if (play_sound) G.play();
		sleep(break_duration);
	}

	return 0;
}
