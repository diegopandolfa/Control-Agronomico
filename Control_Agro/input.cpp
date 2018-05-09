#include "input.h"

Input::Input(){
	pinOut = 0;
	id = 0;
	state = 0;
	label = 0;
	parameter = 0;
	analogInput = 0;
	alpha = ALPHA;
	value_prev = 0;
}
Input::~Input(){
	;
}
int Input::init(int pinOut){
	this->pinOut = pinOut;
	id = 0;
	state = 0;
	label = LABEL_LOGIC;
	parameter = 1.0;
	return 0;
}
int Input::init(int id, int pinOut){
	this->pinOut = pinOut;
	this->id = id;
	state = 0;
	label = LABEL_LOGIC;
	parameter = 1.0;
	return 0;
}
int Input::getId(void){
	return this->id;
}
int Input::setId(int id){
	this->id = id;
	return 0;
}
bool Input::readInput(void){
	return digitalRead(this->pinOut);
}
double Input::readInputCurrent(void){
	double temp = (double)analogRead(this->pinOut);
	value = temp*(ALPHA) + value*(1-ALPHA);
	return value*parameter;
}
double Input::readInputVoltage(void){
	double temp = (double)analogRead(this->pinOut);
	value = temp*(ALPHA) + value*(1-ALPHA);
	return value*parameter;
}
double Input::readInputHall(void){
	static int num_call = 0;
	static int pulse = 0;
	static bool flag = false;
	static long prev = 0;
	long actual = millis();
	if(num_call >= 18000){ // 3 minutos
		num_call = 0;
		value = (double) pulse;
		value = value/180.0;
		value = value*parameter;
		pulse = 0;
	}
	else if(num_call%200 == 0){ // 2 segundos
		value_prev = (value + value_prev)/2;
	}
	else{
		value_prev = value_prev;
	}
	analogInput = analogRead(this->pinOut)*(alpha) + analogInput*(1-alpha);
	Serial.print("analogInput:\t");
	Serial.println(analogInput);
	Serial.print("flag:\t");
	Serial.println(flag);
	Serial.print("num_call:\t");
	Serial.print(num_call);
	Serial.print("pulse:\t");
	Serial.println(pulse);
	Serial.print("value:\t");
	Serial.println(value);
	Serial.print("value_prev:\t");
	Serial.println(value_prev);
	if(flag == false){
		if(analogInput >1000){
			prev = actual;
		}
		if(analogInput <= 100){
			Serial.print("tiempo:\t");
			Serial.println(actual - prev);
			flag = true;
			pulse++;
		}
		else{
			flag = flag;
		}
	}
	else{
		if(analogInput >= 800){
			flag = false;
		}
		else{
			flag = flag;
		}
	}
	num_call++;
	return value_prev;
}
int Input::setParameter(double param){
	this->parameter = param;
	return 0;
}

int Input::getParameter(int id, String &param){
	param = "";
	if(this->id == id){
		param += parameter;
		return 0;
	}
	else{
		return -1;
	}
}