#ifndef __CONTROL_AGRO__H__
#define __CONTROL_AGRO__H__
#include "Arduino.h"
//#include <avr/io.h>
//#include <avr/interrupt.h>
#include <Metro.h>
//#include <TimerOne.h>
#include <ModbusMaster.h>
//#include <RTClib.h>
//#include <SD.h>
//#include <stdlib.h>
//#include <vector>
#include "input.h"
#include "output.h"
//#include "struct_control_agro.h"

#define INV_DIR	0x01
#define REG_INV_RES 0x01
#define REG_RUN_FREQ 0x0D
#define REG_INV_START 0x02
#define REG_INV_STOP 0x00

#define DEBUG Serial
#define XBEE_MESH Serial1
#define XBEE_3G Serial2
#define MODBUS Serial3
#define EXP_IN Serial4
#define EXP_OUT Serial5

class Control_Agro{
public:
	/**
	 * @breif : 
	 */
	Control_Agro();
	/**
	 * @breif : 
	 */
	~Control_Agro();
	/**
	 * @breif : 
	 */
	int init(void);
	/**
	 * @breif : 
	 */
	int setTime(int year, int month, int day, int week, int hour, int minute, int second);
	/**
	 * @breif : 
	 */
	int getTime(int format);
	/**
	 * @breif : 
	 */
	int setStartPeakTime(int hour, int minute, int second);
	/**
	 * @breif : 
	 */
	int setEndPeakTime(int hour, int minute, int second);
	/**
	 * @breif : 
	 */
	int enablePeakTime(void);
	/**
	 * @breif : 
	 */
	int disablePeakTime(void);
	/**
	 * @breif : 
	 */
	String getTime(void);
	/**
	 * @breif : 
	 */
	String getStatus3G(void);
	/**
	 * @breif : 
	 */
	String getStatusGPRS(void);
	/**
	 * @breif : 
	 */
	String getStatusMesh(void);
	/**
	 * @breif : 
	 */
	int writeOn3G(String frame);
	/**
	 * @breif : 
	 */
	int writeOnMesh(String frame);
	/**
	 * @breif : 
	 */
	int debug(String frame);
	/**
	 * @breif : 
	 */
	int writeOnDisplay(String frame);
	/**
	 * @brief :
	 */
	int startVF(void);
	/**
	 * @brief :
	 */
	int stopVF(void);
	/**
	 * @brief :
	 */
	int changeFreqVF(void);
	/**
	 * @breif : 
	 */
	int enableAnalogInput(void);
	/**
	 * @breif : 
	 */
	int enableDigitalInput(void);
	/**
	 * @breif : 
	 */
	int setInputAs(int param); // tipo de sensor
	/**
	 * @breif : 
	 */
	int setParameterForInput(double param); // factor de escala
	/**
	 * @breif : 
	 */
	String getParameterForInput(int input);
	/**
	 * @breif : 
	 */
	String getStatusForInput(int input);
	/**
	 * @breif : 
	 */
	int readInput(int input); // cada bit en alto indica la entrada a sensar
	/**
	 * @breif : 
	 */
	int filterInput(void);
	/**
	 * @breif : 
	 */
	int setLabel(String label);
	/**
	 * @breif : 
	 */
	String getLabel(void);
	/**
	 * @breif : 
	 */
	int enableOutput(void);
	/**
	 * @breif : 
	 */
	int getStatusForOutput(int output, String &status);
	/**
	 * @breif : 
	 */
	int setOutputAsTimeLogic(int output);
	/**
	 * @breif : 
	 */
	int setOutputAsInputLogic(int output, int inputs); // todas las entradas estan en OR

private:
	ModbusMaster var_freq;
	/**
	 * @breif : 
	 */
	int status3G;
	/**
	 * @breif : 
	 */
	int statusMesh;
	/**
	 * @breif : 
	 */
	int StatusGPRS;
	/**
	 * @breif : 
	 */
	int signalStrength;
	/**
	 * @breif : 
	 */
	int statusPeakTime; // habilitado o no
	/**
	 * @breif : 
	 */
	int startPeakTime;
	/**
	 * @breif : 
	 */
	int endPeakTime;
	/**
	 * @breif : 
	 */
	long timestamp;
	/**
	 * @breif : 
	 */
	int year;
	/**
	 * @breif : 
	 */
	int month;
	/**
	 * @breif : 
	 */
	int day;
	/**
	 * @breif : 
	 */
	int week;
	/**
	 * @breif : 
	 */
	int hour;
	/**
	 * @breif : 
	 */
	int minute;
	/**
	 * @breif : 
	 */
	int second;
	/**
	 * @breif : 
	 */
	int inputs;
	/**
	 * @breif : 
	 */
	String labelInputCurrentAnalog_01;
	/**
	 * @breif : 
	 */
	String labelInputCurrentAnalog_02;
	/**
	 * @breif : 
	 */
	String labelInputVoltageAnalog_01;
	/**
	 * @breif : 
	 */
	String labelInputVoltageAnalog_02;
	/**
	 * @breif : 
	 */
	String labelInputVoltageAnalog_03;
	/**
	 * @breif : 
	 */
	String labelGPIO_01;
	/**
	 * @breif : 
	 */
	String labelGPIO_02;
	/**
	 * @breif : 
	 */
	String labelGPIO_03;
	/**
	 * @breif : 
	 */
	String labelGPIO_04;
	/**
	 * @breif : 
	 */
	String labelGPIO_05;
	/**
	 * @breif : 
	 */
	int paramInputCurrentAnalog_01;
	/**
	 * @breif : 
	 */
	int paramInputCurrentAnalog_02;
	/**
	 * @breif : 
	 */
	int paramInputVoltageAnalog_01;
	/**
	 * @breif : 
	 */
	int paramInputVoltageAnalog_02;
	/**
	 * @breif : 
	 */
	int paramInputVoltageAnalog_03;
	/**
	 * @breif : 
	 */
	int paramInputGPIO_01;
	/**
	 * @breif : 
	 */
	int paramInputGPIO_02;
	/**
	 * @breif : 
	 */
	int paramInputGPIO_03;
	/**
	 * @breif : 
	 */
	int paramInputGPIO_04;
	/**
	 * @breif : 
	 */
	int paramInputGPIO_05;
	/**
	 * @breif : 
	 */
	int outputs;
	/**
	 * @breif : 
	 */
	String labelOutput_01;
	/**
	 * @breif : 
	 */
	String labelOutput_02;
	/**
	 * @breif : 
	 */
	String labelOutput_03;
	/**
	 * @breif : 
	 */
	String labelOutput_04;
	/**
	 * @breif : 
	 */
	String labelOutput_05;
	/**
	 * @breif : 
	 */
	int statusOutType; // salida por horario, entradas o variable web?
	/**
	 * @brief :
	 */
	int statusInType; // sensor efecto hall, lógico, ?
	/**
	 * @brief :
	 */
	int showMenu; // menu visible en pantalla?
	/**
	 * @brief :
	 */
	int stateMenu; // estado del menu
	/**
	 * @brief :
	 */
	int stateSubMenu; // estado del submenu
	/**
	 * @brief :
	 */
	int stateSubSubMenu; // estado del subsubmenu
	/**
	 * @brief :
	 */
	int stateSubSubSubMenu; // estado del subsubsubmenu
	/**
	 * @brief :
	 */
	int showStatus; // muestra estatus seleccionado en pantalla?
	/**
	 * @brief : 
	 */
	int pinOut_01;
	/**
	 * @brief : 
	 */
	int pinOut_02;
	/**
	 * @brief : 
	 */
	int pinOut_03;
	/**
	 * @brief : 
	 */
	int pinOut_04;
	/**
	 * @brief : 
	 */
	int pinOut_05;
	/**
	 * @brief : 
	 */
	int pinOut_06;
	/**
	 * @brief : 
	 */
	int pinOut_07;
	/**
	 * @brief : 
	 */
	int pinOut_08;
	/**
	 * @brief : 
	 */
	int pinOut_09;
	/**
	 * @brief : 
	 */
	int pinOut_10;
	/**
	 * @brief : 
	 */
	int pinEnable_RS485;
	/**
	 * @brief : 
	 */
	int pinButtons;
	/**
	 * @brief : 
	 */
	int pinGPIO_01;
	/**
	 * @brief : 
	 */
	int pinGPIO_02;
	/**
	 * @brief : 
	 */
	int pinGPIO_03;
	/**
	 * @brief : 
	 */
	int pinGPIO_04;
	/**
	 * @brief : 
	 */
	int pinGPIO_05;
	/**
	 * @brief : 
	 */
	int pinInCurrentAnalog_01;
	/**
	 * @brief : 
	 */
	int pinInCurrentAnalog_02;
	/**
	 * @brief : 
	 */
	int pinInVoltageAnalog_01;
	/**
	 * @brief : 
	 */
	int pinInVoltageAnalog_02;
	/**
	 * @brief : 
	 */
	int pinInVoltageAnalog_03;
	/**
	 * @brief : 
	 */
	int pinTransistorToReset;
	/**
	 * @brief :
	 */
	int pinPowerSense;
	/**
	 * @brief :
	 */
	int GPIO_01_value;
	/**
	 * @brief :
	 */
	int GPIO_02_value;
	/**
	 * @brief :
	 */
	int GPIO_03_value;
	/**
	 * @brief :
	 */
	int GPIO_04_value;
	/**
	 * @brief :
	 */
	int GPIO_05_value;
	/**
	 * @brief :
	 */
	int inputCurrentAnalog_01_value;
	/**
	 * @brief :
	 */
	int inputCurrentAnalog_02_value;
	/**
	 * @brief :
	 */
	int inputVoltageAnalog_01_value;
	/**
	 * @brief :
	 */
	int inputVoltageAnalog_02_value;
	/**
	 * @brief :
	 */
	int inputVoltageAnalog_03_value;
	/**
	 * @brief :
	 */
	int out_01_value;
	/**
	 * @brief :
	 */
	int out_02_value;
	/**
	 * @brief :
	 */
	int out_03_value;
	/**
	 * @brief :
	 */
	int out_04_value;
	/**
	 * @brief :
	 */
	int out_05_value;
	/**
	 * @brief :
	 */
	int out_06_value;
	/**
	 * @brief :
	 */
	int out_07_value;
	/**
	 * @brief :
	 */
	int out_08_value;
	/**
	 * @brief :
	 */
	int out_09_value;
	/**
	 * @brief :
	 */
	int out_10_value;
	/**
	 * @brief :
	 */
	int flag_error_3G;
	/**
	 * @brief :
	 */
	int flag_error_xBee;
	/**
	 * @brief :
	 */
	int flag_error_RTC;
	/**
	 * @brief :
	 */
	int flag_error_PowerSupply;
	/**
	 * @brief :
	 */
	Input input_01;
	/**
	 * @brief :
	 */
	Input input_02;
	/**
	 * @brief :
	 */
	Input input_03;
	/**
	 * @brief :
	 */
	Input input_04;
	/**
	 * @brief :
	 */
	Input input_05;
	/**
	 * @brief :
	 */
	Input input_06;
	/**
	 * @brief :
	 */
	Input input_07;
	/**
	 * @brief :
	 */
	Input input_08;
	/**
	 * @brief :
	 */
	Input input_09;
	/**
	 * @brief :
	 */
	Input input_10;
	/**
	 * @brief :
	 */
	Output output_01;
	/**
	 * @brief :
	 */
	Output output_02;
	/**
	 * @brief :
	 */
	Output output_03;
	/**
	 * @brief :
	 */
	Output output_04;
	/**
	 * @brief :
	 */
	Output output_05;
	/**
	 * @brief :
	 */
	Output output_06;
	/**
	 * @brief :
	 */
	Output output_07;
	/**
	 * @brief :
	 */
	Output output_08;
	/**
	 * @brief :
	 */
	//std::vector<Input> vector_exp_in;
	/**
	 * @brief :
	 */
	//std::vector<Output> vector_exp_out;
};

#endif