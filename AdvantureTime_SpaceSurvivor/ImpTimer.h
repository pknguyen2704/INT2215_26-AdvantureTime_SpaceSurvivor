#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

class ImpTimer
{
public:
	ImpTimer();
	void Start();
	void Stop();
	void Pause();
	void Unpause();
	int GetTicks();
	bool IsStarted();
	bool IsPaused();

private:
	//time at started
	int startTick_;
	//The ticks stored when the timer was paused
	int pausedTick_;
	bool isPaused_;
	bool isStarted_;
};

#endif