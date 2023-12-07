#include <cstdlib>
#include <unistd.h>
#include "../audio/audio.h"
#include "pomodoro.h"

void Time::start() {
	sleep(duration);
}

void Time::notify() {
	Note n(sound_freq);
	n.play();
}
