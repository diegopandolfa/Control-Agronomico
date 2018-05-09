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
	//var_freq = ModbusMaster();
	input_01 = Input();
	input_02 = Input();
	input_03 = Input();
	input_04 = Input();
	input_05 = Input();
	input_06 = Input();
	input_07 = Input();
	input_08 = Input();
	input_09 = Input();
	input_10 = Input();
	output_01 = Output();
	output_02 = Output();
	output_03 = Output();
	output_04 = Output();
	output_05 = Output();
	output_06 = Output();
	output_07 = Output();
	output_08 = Output();
	//vector_exp_in = std::vector<Input>();
	//vector_exp_out = std::vector<Output>();
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
	input_01.init(1, pinInCurrentAnalog_01);
	input_02.init(2, pinInCurrentAnalog_02);
	input_03.init(3, pinInVoltageAnalog_01);
	input_04.init(4, pinInVoltageAnalog_02);
	input_05.init(5, pinInVoltageAnalog_03);
	input_06.init(6, pinGPIO_01);
	input_07.init(7, pinGPIO_02);
	input_08.init(8, pinGPIO_03);
	input_09.init(9, pinGPIO_04);
	input_10.init(10, pinGPIO_05);
	output_01 = Output(1, pinOut_01);
	output_02 = Output(2, pinOut_02);
	output_03 = Output(3, pinOut_03);
	output_04 = Output(4, pinOut_04);
	output_05 = Output(5, pinOut_05);
	output_06 = Output(6, pinOut_06);
	output_07 = Output(7, pinOut_07);
	output_08 = Output(8, pinOut_08);
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
int Control_Agro::getStatusForOutput(int output, String &status){
	switch(output){
		case 1:
			return output_01.getState(output, status);
			break;
		case 2:
			return output_02.getState(output, status);
			break;
		case 3:
			return output_02.getState(output, status);
			break;
		case 4:
			return output_02.getState(output, status);
			break;
		case 5:
			return output_02.getState(output, status);
			break;
		case 6:
			return output_02.getState(output, status);
			break;
		case 7:
			return output_02.getState(output, status);
			break;
		case 8:
			return output_02.getState(output, status);
			break;
		default :
			return -1;
			break;
	}
/*	std::vector<Output>::iterator it = vector_exp_out.begin();
	while(it != vector_exp_out.end()){
		if(it->getId() == output){
			return it->getState(output, status);
		}
		it++;
	}*/
	return -1;
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
int Control_Agro::setOutputAsInputLogic(int output, int inputs){
	/*std::vector<Input> v_logic_in_temp;
	for(int i=2; i<10; i++){
		if( ((inputs>>i)&(0x01)) == 0x01){
			switch(i){
				case 3:
					v_logic_in_temp.push_back(input_03);
					break;
				case 4:
					v_logic_in_temp.push_back(input_04);
					break;
				case 5:
					v_logic_in_temp.push_back(input_05);
					break;
				case 6:
					v_logic_in_temp.push_back(input_06);
					break;
				case 7:
					v_logic_in_temp.push_back(input_07);
					break;
				case 8:
					v_logic_in_temp.push_back(input_08);
					break;
				case 9:
					v_logic_in_temp.push_back(input_09);
					break;
				case 10:
					v_logic_in_temp.push_back(input_10);
					break;
				default :
					break; // agregar casos en que el iterador es mayor, es decir, la entrada es de un módulo de expansion.
			}			
		}
		else{
			;
		}
	}
	switch(output){
		case 1:
			return output_01.setInputLogic(v_logic_in_temp);
			break;
		case 2:
			return output_02.setInputLogic(v_logic_in_temp);
			break;
		case 3:
			return output_02.setInputLogic(v_logic_in_temp);
			break;
		case 4:
			return output_02.setInputLogic(v_logic_in_temp);
			break;
		case 5:
			return output_02.setInputLogic(v_logic_in_temp);
			break;
		case 6:
			return output_02.setInputLogic(v_logic_in_temp);
			break;
		case 7:
			return output_02.setInputLogic(v_logic_in_temp);
			break;
		case 8:
			return output_02.setInputLogic(v_logic_in_temp);
			break;
		default :
			return -1;
			break;
	}*/
	return -1;
} // todas las entradas estan en OR