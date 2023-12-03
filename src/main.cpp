#include <iostream>
#include <cstring>
#include <unistd.h>
#include "audio/audio.h"
using namespace std;

void show_usage() {
	cout << "pomusi --work <work-duration> --break <break-duration>" << endl;
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

	Note G(392.0);
	Note C(261.63);


	if(argc != 5) {
		show_usage();
		exit(0);
	}

	for(int i = 0; i < argc; i++) {
		if(!strcmp("--work", argv[i])) work_duration = parse_int(argv[i+1]);
		else if(!strcmp("--break", argv[i])) break_duration = parse_int(argv[i+1]);
	}

	while(true) {
		cout << "Pomodoro started." << endl;
		C.play();
		sleep(work_duration);
		cout << "Break started." << endl;
		G.play();
		sleep(break_duration);
	}

	return 0;
}
