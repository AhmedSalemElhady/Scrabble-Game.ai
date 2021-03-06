#pragma once

#include <iostream>
#include <conio.h>
#include <time.h>
#include <string>
#include "../SharedClasses/TrainerComm.hpp"

using namespace std;

class TimerGUI
{
private:
	TrainerComm *Communicator;
	bool resetted;
	bool running;
	unsigned long beg;
	unsigned long end;
	unsigned long finalendtime;

public:
	TimerGUI(TrainerComm *, unsigned long);
	void start();
	void stop();
	void reset();
	bool isRunning();
	unsigned long getTime();
	bool isOver(unsigned long seconds);
	void SendTime();
};
