//////////////////////////////////////////////////////////////
//	@ Project: Control Agronomico							//
//	@ Client:	Matias Valladares							//
//	@ Enterprice:	IEH Ingenieria SPA						//
//	@ Powered by: Tectronix SPA 							//
//	@ Author: Diego Pandolfa								//
//	@ date: April 2018										//
//////////////////////////////////////////////////////////////

#ifndef __OUTPUT_CONTROL_AGRO_H__
#define __OUTPUT_CONTROL_AGRO_H__

#include "Arduino.h"
#include "input.h"
//#include "struct_control_agro.h"
//#include <TimeLib.h>
//#include "/home/diego/Documents/arduino-1.8.2/hardware/teensy/avr/libraries/SD/SD.h"

#define PROGRAM_A	1
#define PROGRAM_B	2
#define PROGRAM_C	3
#define PROGRAM_D 	4
#define PROGRAM_E	5

#define PINOUT_S1	0
#define PINOUT_S2	0
#define PINOUT_S3	0
#define PINOUT_S4	0
#define PINOUT_S5	0
#define PINOUT_S6	0
#define PINOUT_S7	0
#define PINOUT_S8	0

#define LABEL_OUT_PUMP		1
#define LABEL_OUT_VALVE		2
#define LABEL_OUT_CONTACT	3

#define MODE_SELECTED_POZO 		1
#define MODE_SELECTED_RIEGO		2

#define LUNES 		0
#define MARTES 		1
#define MIERCOLES 	2
#define JUEVES 		3
#define VIERNES 	4
#define SABADO 		5
#define DOMINGO 	6

using namespace std;
/**
 * @brief :
 */
class Output
{
public:
	/**
 	 * @brief : Constructor por defecto.
 	 */
	Output();
	Output(int id, int pinOut);
	/**
 	 * @brief : Destructor por defecto.
 	 */
	~Output();
	/**
 	 * @brief : Inicializa todas las variables.
 	 */
	int init(void);
	/**
 	 * @brief : Inicializa todas las variables configurando la salida como funcion de las entradas rescatando los datos desde la SD Card.
 	 */
	//int init(Node_in *in, int label);
	/**
 	 * @brief : Entrega el estado actual de la salida en formato String.
 	 */
	int getState(int id, String &state);
	/**
 	 * @brief : Setea el estado de la salida con identificador id y lo guarda en la SD Card.
 	 */
	int setState(int id, int state);
	/**
 	 * brief : Calcula el siguiente estado en funcion de las entradas
 	 */
	int calcNextState(int hour, int minute , int second);
	/**
 	 * @brief : Entrega el listado de entradas que se consideran para la lógica de la salida 
 	 */
	int getInputLogic(int id, String &input_logic);
	/**
 	 * @brief : Setea las entradas que generan la lógica de la salida y las guarda en la SD CARD.
 	 */
	//int setInputLogic(Node_in *in);
	/*
 	 * @brief : Setea el tiempo en minutos que la salida estará activa, pero sin mesionar el tiempo de partida y lo guarda en la SD Card.
 	 */
	int setOutputTime(int min);
	/**
 	 * @brief : Setea la hora y minuto en que la salida se activa todos los dias y lo guarda en la SD Card.
 	 */
	int setOutputTime(int hour, int min);
	/**
 	 * @brief : Setea el dia, hora y minuto en que la salida se activa todas las semanas y lo guarda en la SD Card.
 	 */
	int setOutputTime(int day, int hour, int min);
	/**
	 * @brief : Setea los dias de la semana, hora, y minuto en que se activa la salida y lo guarda en la SD Card.
	 */
	int setOutputTime(int days[], int hour[], int min[]);
	/**
	 * @brief : Setea el ID de la salida que puede ser tanto local como de un módulo de expansion.
	 */
	int setId(int id);
	/**
	 * @brief : Obtiene el ID de la salida que puede ser tanto local como de un módulo de expansion.
	 */
	int getId(void);
	/**
	 * @brief : Setea el programa activo, por defaul siempre parte con el A.
	 */
	int setProgram(int program_id);
	/**
	 * @brief : Actualiza el estado de las salidas por el calculado con calcNextState().
	 */
	int updateState(void);
	/**
	 * @brief : Entrega un String con la trama de los parametros a guardar en la SD.
	 */
	String getDataStorage(void);
	/**
	 * @brief : Setea el modo de la salida.
	 */
	int setMode(int mode);
	/**
	 * @brief : 
	 */
	int setPeakTime(bool peakTime);
	/**
	 * @brief : 
	 */
	int action(void);

private:
	/**
	 * @brief : Identificador de la salida.
	 */
	int id;
	/**
	 * @brief : Identificador del programa en ejecución
	 */
	int program_id;
	/**
	 * @brief : Modo de funcionamiento.
	 */
	int mode;
	/**
	 * @brief : etiqueta de funcionamiento (bomba, contacto, valvula, etc).
	 */
	int label;
	/**
	 * @brief : Pin del microcontrolador.
	 */
	int pinOut;
	/**
	 * @brief : Estado de la Salida.
	 */
	int state;
	/**
	 * @brief : Siguiente estado de la salida calculado en funcion de las entradas.
	 */
	int next_state;
	/**
	 * @brief : Vector de entradas que condicionan el estado de la salida.
	 */
	//Node_in *inputs;
	/**
	 * @brief : Tiempo que permanece activada la salida.
	 */
	int *time_on;
	/**
	 * @brief : Minuto en que es activada la salida.
	 */
	int *minute;
	/**
	 * @brief : Hora en que es activada la salida.
	 */
	int *hour;
	/**
	 * @brief : Días en que es activada la salida.
	 */
	int *days;
	/**
	 * @brief : Define si esta o no activo el horario punta
	 */
	bool peakTime;
};
#endif