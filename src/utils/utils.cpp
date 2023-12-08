#include <iostream>
#include <cstring>
#include "utils.h"
using namespace std;

void show_usage() {
	cout << "pomrika --work <work-duration> --break <break-duration>" << endl <<
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
