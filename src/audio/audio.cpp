#include <SDL2/SDL.h>
#include <cmath>
#include "audio.h"

SDL_AudioDeviceID Note::get_device(SDL_AudioSpec &req_spec, SDL_AudioSpec &resp_spec) {

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		return 0;
	}
	SDL_zero(resp_spec);

	SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &req_spec, &resp_spec, 0);

	if (device == 0) {
		SDL_Quit();
		return 0;
	}

	return device;
}

void Note::create_buffer(Sint16* buffer, int buffer_size){
	for (int i = 0; i < buffer_size; i++) {
		double time = static_cast<double>(i) / buffer_size;
		buffer[i] = static_cast<Sint16>(amplitude * sin(2.0 * M_PI * note_frequency * time));
	}
}

int Note::play() {
	SDL_AudioDeviceID device = get_device(req_spec, resp_spec);
	const int buffer_size = resp_spec.freq;
	Sint16 buffer[buffer_size];
	create_buffer(buffer, buffer_size);
	SDL_QueueAudio(device, buffer, sizeof(buffer));
	SDL_PauseAudioDevice(device, 0);
	SDL_Delay(1000);
	SDL_CloseAudioDevice(device);
	SDL_Quit();
	return 0;
}

