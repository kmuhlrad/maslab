#ifndef COLLECT_H
#define COLLECT_H

#include "mraa.hpp"

class SensorData {
	int getNext(/*Data*/);
	void run(/*Data*/);
public:
	Collect(int num);
	virtual int process(/*Data*/);
	int getState();
};

#endif