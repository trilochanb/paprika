class Time {
	protected:
		int duration;
		double sound_freq;
	public:
		Time(): duration(0), sound_freq(0.0) {}
		Time(int dur, double freq): duration(dur), sound_freq(freq) {}

		virtual void start();

		virtual void notify();
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

class Pomodoro {
	private:
		Work w;
		Break b;
	public:
		Pomodoro(Work w, Break b): w(w), b(b) {}
		void main_loop(opts options);
};
