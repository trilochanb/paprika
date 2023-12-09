void show_usage();

int parse_int(char* str);

struct cmdline_opts {
	int work_duration;
	int break_duration;
	bool play_sound;
	bool verbose;
	bool daemonize;
	bool kill_daemon;
};

typedef struct cmdline_opts opts;

opts parse_arguments(int argc, char** argv);

void check_arguments(int argc);
