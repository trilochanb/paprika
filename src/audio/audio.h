#include <SDL2/SDL.h>

class Note {
private:
    double note_frequency;
    double amplitude;
    SDL_AudioSpec req_spec;
    SDL_AudioSpec resp_spec;

    SDL_AudioDeviceID get_device(SDL_AudioSpec& req_spec, SDL_AudioSpec& resp_spec);

    void create_buffer(Sint16* buffer, int buffer_size);

public:
    Note(float note_frequency)  {
        this->note_frequency = note_frequency;
        amplitude = 20000.0;

        SDL_zero(req_spec);
        req_spec.freq = 44100;
        req_spec.format = AUDIO_S16SYS;
        req_spec.channels = 1;
        req_spec.samples = 2048;
    }

    int play();
};
