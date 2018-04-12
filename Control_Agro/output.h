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
#include <stdlib.h>
#include <vector>
#include "input.h"
#include "/home/diego/Documents/arduino-1.8.2/hardware/teensy/avr/libraries/SD/SD.h"

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
	int init(vector<Input> in);
	/**
 	 * @brief : Entrega el estado actual de la salida en formato String.
 	 */
	String getState(int id);
	/**
 	 * @brief : Setea el estado de la salida con identificador id y lo guarda en la SD Card.
 	 */
	int setState(int id, int state);
	/**
 	 * brief : Calcula el siguiente estado en funcion de las entradas
 	 */
	int calcNextState(void);
	/**
 	 * @brief : Entrega el listado de entradas que se consideran para la lógica de la salida 
 	 */
	String getInputLogic(int id);
	/**
 	 * @brief : Setea las entradas que generan la lógica de la salida y las guarda en la SD CARD.
 	 */
	int setInputLogic(vector<Input> in);
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
	int setOutputTime(int days[], int hour, int min);
	/**
	 * @brief : Setea el ID de la salida que puede ser tanto local como de un módulo de expansion.
	 */
	int setId(int id);
	/**
	 * @brief : Setea el programa activo, por defaul siempre parte con el A.
	 */
	int setProgram(int program_id);
	/**
	 * @brief : Actualiza el estado de las salidas por el calculado con calcNextState().
	 */
	int updateState(void);

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
	vector<Input> inputs;
	/**
	 * @brief : Tiempo que permanece activada la salida.
	 */
	int time_on[];
	/**
	 * @brief : Minuto en que es activada la salida.
	 */
	int minute[];
	/**
	 * @brief : Hora en que es activada la salida.
	 */
	int hour[];
	/**
	 * @brief : Días en que es activada la salida.
	 */
	int days[];
	/**
	 * @brief : Archivo que contiene los parametros guardados en la SD Card.
	 */
	File output_param;
}
#endif