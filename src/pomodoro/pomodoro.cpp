#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "../audio/audio.h"
#include "../utils/utils.h"
#include "pomodoro.h"
using namespace std;

void Time::start() {
	sleep(duration);
}

void Time::notify() {
	Note n(sound_freq);
	n.play();
}

void Pomodoro::main_loop(opts options) {
	while(true) {
		if (options.verbose) cout << "Pomodoro started." << endl;
		if (options.play_sound) w.notify();
		w.start();
		if (options.verbose) cout << "Break started." << endl;
		if (options.play_sound) b.notify();
		b.start();
	}
}
