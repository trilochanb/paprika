#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "utils.h"
using namespace std;

void show_usage() {
	cout << "paprika --work <work-duration> --break <break-duration>" << endl <<
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

opts parse_arguments(int argc, char** argv) {
	opts o;
	o.play_sound = true;
	o.verbose = false;
	o.daemonize = false;
	o.kill_daemon = false;
	for(int i = 0; i < argc; i++) {
		if(!strcmp("--work", argv[i])) o.work_duration = parse_int(argv[i+1]);
		else if(!strcmp("--break", argv[i])) o.break_duration = parse_int(argv[i+1]);
		else if(!strcmp("--quiet", argv[i])) o.play_sound = false;
		else if(!strcmp("--verbose", argv[i])) o.verbose = true;
		else if(!strcmp("--detach", argv[i])) o.daemonize = true;
		else if(!strcmp("kill", argv[i])) o.kill_daemon = true;
	}
	return o;
};
