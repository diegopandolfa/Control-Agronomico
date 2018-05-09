#ifndef __INPUT_H__
#define __INPUT_H__

#include "Arduino.h"

#define LABEL_4_20_MA	1
#define LABEL_0_5_V  	2
#define LABEL_LOGIC 	3

#define ALPHA 0.125

class Input
{
public:
	Input();
	~Input();
	int init(int pinOut);
	int init(int id, int pinOut);
	int getId(void);
	int setId(int id);
	bool readInput(void);
	double readInputCurrent(void);
	double readInputVoltage(void);
	double readInputHall(void);
	int setParameter(double param);
	int getParameter(int id, String &parameter);
private:
	int pinOut;
	int id;
	int state;
	int label;
	double parameter;
	double analogInput;
	double alpha;
	double value_prev;
	double value;
};
#endif
