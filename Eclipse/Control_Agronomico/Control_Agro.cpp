#include "Control_Agro.h"
/**
 * @breif : 
 */
Control_Agro::Control_Agro(){
	status3G = 0;
	statusMesh = 0;
	StatusGPRS = 0;
	signalStrength = 0;
	statusPeakTime = 0; // habilitado o no
	startPeakTime = 0;
	endPeakTime = 0;
	timestamp = 0;
	year = 0;
	month = 0;
	day = 0;
	week = 0;
	hour = 0;
	minute = 0;
	second = 0;
	inputs = 0;
	labelInputCurrentAnalog_01 = "";
	labelInputCurrentAnalog_02 = "";
	labelInputVoltageAnalog_01 = "";
	labelInputVoltageAnalog_02 = "";
	labelInputVoltageAnalog_03 = "";
	labelGPIO_01 = "";
	labelGPIO_02 = "";
	labelGPIO_03 = "";
	labelGPIO_04 = "";
	labelGPIO_05 = "";
	paramInputCurrentAnalog_01 = 0;
	paramInputCurrentAnalog_02 = 0;
	paramInputVoltageAnalog_01 = 0;
	paramInputVoltageAnalog_02 = 0;
	paramInputVoltageAnalog_03 = 0;
	paramInputGPIO_01 = 0;
	paramInputGPIO_02 = 0;
	paramInputGPIO_03 = 0;
	paramInputGPIO_04 = 0;
	paramInputGPIO_05 = 0;
	outputs = 0;
	labelOutput_01 = "";
	labelOutput_02 = "";
	labelOutput_03 = "";
	labelOutput_04 = "";
	labelOutput_05 = "";
	statusOutType = 0; // salida por horario, entradas o variable web?
	statusInType = 0; // sensor efecto hall, lógico, ?
	showMenu = 0; // menu visible en pantalla?
	stateMenu = 0; // estado del menu
	stateSubMenu = 0; // estado del submenu
	stateSubSubMenu = 0; // estado del subsubmenu
	stateSubSubSubMenu = 0; // estado del subsubsubmenu
	showStatus = 0; // muestra estatus seleccionado en pantalla?
	pinOut_01 = 0;
	pinOut_02 = 0;
	pinOut_03 = 0;
	pinOut_04 = 0;
	pinOut_05 = 0;
	pinOut_06 = 0;
	pinOut_07 = 0;
	pinOut_08 = 0;
	pinOut_09 = 0;
	pinOut_10 = 0;
	pinEnable_RS485 = 0;
	pinButtons = 0;
	pinGPIO_01 = 0;
	pinGPIO_02 = 0;
	pinGPIO_03 = 0;
	pinGPIO_04 = 0;
	pinGPIO_05 = 0;
	pinInCurrentAnalog_01 = 0;
	pinInCurrentAnalog_02 = 0;
	pinInVoltageAnalog_01 = 0;
	pinInVoltageAnalog_02 = 0;
	pinInVoltageAnalog_03 = 0;
	pinTransistorToReset = 0;
	pinPowerSense = 0;
	GPIO_01_value = 0;
	GPIO_02_value = 0;
	GPIO_03_value = 0;
	GPIO_04_value = 0;
	GPIO_05_value = 0;
	inputCurrentAnalog_01_value = 0;
	inputCurrentAnalog_02_value = 0;
	inputVoltageAnalog_01_value = 0;
	inputVoltageAnalog_02_value = 0;
	inputVoltageAnalog_03_value = 0;
	out_01_value = 0;
	out_02_value = 0;
	out_03_value = 0;
	out_04_value = 0;
	out_05_value = 0;
	out_06_value = 0;
	out_07_value = 0;
	out_08_value = 0;
	out_09_value = 0;
	out_10_value = 0;
	out_10_value = 0;
	flag_error_3G = 0;
	flag_error_xBee = 0;
	flag_error_RTC = 0;
	flag_error_PowerSupply = 0;
	var_freq = ModbusMaster();
}
/**
 * @breif : 
 */
Control_Agro::~Control_Agro(){

}
/**
 * @breif : 
 */
int Control_Agro::init(void){
	status3G = 0;
	statusMesh = 0;
	StatusGPRS = 0;
	signalStrength = 0;
	statusPeakTime = 0; // habilitado o no
	startPeakTime = 0;
	endPeakTime = 0;
	timestamp = 0;
	year = 0;
	month = 0;
	day = 0;
	week = 0;
	hour = 0;
	minute = 0;
	second = 0;
	inputs = 0;
	labelInputCurrentAnalog_01 = "";
	labelInputCurrentAnalog_02 = "";
	labelInputVoltageAnalog_01 = "";
	labelInputVoltageAnalog_02 = "";
	labelInputVoltageAnalog_03 = "";
	labelGPIO_01 = "";
	labelGPIO_02 = "";
	labelGPIO_03 = "";
	labelGPIO_04 = "";
	labelGPIO_05 = "";
	paramInputCurrentAnalog_01 = 0;
	paramInputCurrentAnalog_02 = 0;
	paramInputVoltageAnalog_01 = 0;
	paramInputVoltageAnalog_02 = 0;
	paramInputVoltageAnalog_03 = 0;
	paramInputGPIO_01 = 0;
	paramInputGPIO_02 = 0;
	paramInputGPIO_03 = 0;
	paramInputGPIO_04 = 0;
	paramInputGPIO_05 = 0;
	outputs = 0;
	labelOutput_01 = "";
	labelOutput_02 = "";
	labelOutput_03 = "";
	labelOutput_04 = "";
	labelOutput_05 = "";
	statusOutType = 0; // salida por horario, entradas o variable web?
	statusInType = 0; // sensor efecto hall, lógico, ?
	showMenu = 0; // menu visible en pantalla?
	stateMenu = 0; // estado del menu
	stateSubMenu = 0; // estado del submenu
	stateSubSubMenu = 0; // estado del subsubmenu
	stateSubSubSubMenu = 0; // estado del subsubsubmenu
	showStatus = 0; // muestra estatus seleccionado en pantalla?
	pinOut_01 = 2;
	pinOut_02 = 5;
	pinOut_03 = 11;
	pinOut_04 = 12;
	pinOut_05 = 24;
	pinOut_06 = 25;
	pinOut_07 = 26;
	pinOut_08 = 27;
	pinOut_09 = 28;
	pinOut_10 = 29;
	pinEnable_RS485 = 6;
	pinButtons = 35;
	pinGPIO_01 = 16;
	pinGPIO_02 = 15;
	pinGPIO_03 = 14;
	pinGPIO_04 = 13;
	pinGPIO_05 = 39;
	pinInCurrentAnalog_01 = 20;
	pinInCurrentAnalog_02 = 17;
	pinInVoltageAnalog_01 = 23;
	pinInVoltageAnalog_02 = 22;
	pinInVoltageAnalog_03 = 21;
	pinTransistorToReset = 0;
	pinPowerSense = 0;
	GPIO_01_value = 0;
	GPIO_02_value = 0;
	GPIO_03_value = 0;
	GPIO_04_value = 0;
	GPIO_05_value = 0;
	inputCurrentAnalog_01_value = 0;
	inputCurrentAnalog_02_value = 0;
	inputVoltageAnalog_01_value = 0;
	inputVoltageAnalog_02_value = 0;
	inputVoltageAnalog_03_value = 0;
	out_01_value = 0;
	out_02_value = 0;
	out_03_value = 0;
	out_04_value = 0;
	out_05_value = 0;
	out_06_value = 0;
	out_07_value = 0;
	out_08_value = 0;
	out_09_value = 0;
	out_10_value = 0;
	flag_error_3G = 0;
	flag_error_xBee = 0;
	flag_error_RTC = 0;
	flag_error_PowerSupply = 0;
	DEBUG.begin(115200); // debug
	while(!Serial);
	XBEE_MESH.begin(115200); // xBee
	while(!Serial1);
	XBEE_3G.begin(115200); // 3G
	while(!Serial2);
	MODBUS.begin(9600); // Modbus
	while(!Serial3);
	EXP_IN.begin(9600); // RS232 se saca del diseño y se coloca el serial para los módulos de entrada.
	while(!Serial4);
	EXP_OUT.begin(9600); // módulos de salida
	while(!Serial5);
	var_freq.begin(INV_DIR, MODBUS);
	return 0;
}
/**
 * @breif : 
 */
int startVF(void){

	return 0;
}
/**
 * @brief :
 */
int stopVF(void){
	return 0;
}
/**
 * @brief :
 */
int changeFreqVF(void){
	return 0;
}
/**
 * @breif : 
 */
int Control_Agro::setTime(int year, int month, int day, int week, int hour, int minute, int second){
	
	return 0;
}
/**
 * @breif : entre
 */
int Control_Agro::getTime(int format){
	
	return 0;
}
/**
 * @breif : 
 */
int Control_Agro::setStartPeakTime(int hour, int minute, int second){
	return 0;
}
/**
 * @breif : 
 */
int Control_Agro::setEndPeakTime(int hour, int minute, int second){
	return 0;
}
/**
 * @breif : 
 */
int Control_Agro::enablePeakTime(void){
	return 0;
}
/**
 * @breif : 
 */
int Control_Agro::disablePeakTime(void){
	return 0;
}
/**
 * @breif : 
 */
String Control_Agro::getTime(void){
	return String();
}
/**
 * @breif : 
 */
String Control_Agro::getStatus3G(void){
	
	return String();
}
/**
 * @breif : 
 */
String Control_Agro::getStatusGPRS(void){
	return String();
}
/**
 * @breif : 
 */
String Control_Agro::getStatusMesh(void){
	return String();
}
/**
 * @breif : 
 */
int Control_Agro::writeOn3G(String frame){
	if(!Serial2){
		return -1;
	}
	else{
		Serial2.print(frame);
		return 0;
	}
}
/**
 * @breif : 
 */
int Control_Agro::writeOnMesh(String frame){
	if(!Serial1){
		return -1;
	}
	else{
		Serial1.print(frame);
		return 0;
	}
}
/**
 * @breif : 
 */
int Control_Agro::debug(String frame){
	if(!Serial){
		return -1;
	}
	else{
		Serial.print(frame);
		return 0;
	}
}
/**
 * @breif : 
 */
int Control_Agro::writeOnDisplay(String frame){
	return 0;
}
/**
 * @breif : 
 */
int Control_Agro::enableAnalogInput(void){
	return 0;
}
/**
 * @breif : 
 */
int Control_Agro::enableDigitalInput(void){
	return 0;
}
/**
 * @breif : 
 */
int Control_Agro::setInputAs(int param){
	return 0;
} // tipo de sensor
/**
 * @breif : 
 */
int Control_Agro::setParameterForInput(double param){
	return 0;
} // factor de escala
/**
 * @breif : 
 */
String Control_Agro::getParameterForInput(int input){
	return String();
}
/**
 * @breif : 
 */
String Control_Agro::getStatusForInput(int input){
	return String();
}
/**
 * @breif : 
 */
int Control_Agro::readInput(int input){// cada bit en alto indica la entrada a sensar
	return 0;
} 
/**
 * @breif : 
 */
int Control_Agro::filterInput(void){
	return 0;
}
/**
 * @breif : 
 */
int Control_Agro::setLabel(String label){
	return 0;
}
/**
 * @breif : 
 */
String Control_Agro::getLabel(void){
	return String();
}
/**
 * @breif : 
 */
int Control_Agro::enableOutput(void){
	return 0;
}
/**
 * @breif : 
 */
String Control_Agro::getStatusForOutput(int output){
	return String();
}
/**
 * @breif : 
 */
int Control_Agro::setOutputAsTimeLogic(int output){
	return 0;
}
/**
 * @breif : 
 */
int Control_Agro::setOutputAsInputLogic(int inputs){
	return 0;
} // todas las entradas estan en OR