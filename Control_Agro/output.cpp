#include "output.h"
Output::Output(){
	/**
	 * @brief : 
	 */
	int id = 0;
	/**
	 * @brief : 
	 */
	int program_id = 0;
	/**
	 * @brief : 
	 */
	int pinOut = 0;
	/**
	 * @brief : 
	 */
	int state = 0;
	/**
	 * @brief : 
	 */
	int next_state = 0;
	/**
	 * @brief : 
	 */
	inputs = vector<Input>();
	/**
	 * @brief : 
	 */
	time_on = {0,0,0,0,0};
	/**
	 * @brief : 
	 */
	minute = {0,0,0,0,0};
	/**
	 * @brief : 
	 */
	hour = {0,0,0,0,0};
	/**
	 * @brief : 
	 */
	days = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // A: L,M,X,J,V,S,D ; B: L,M,X,J,V,S,D ;...
}
/**
  * @brief : Destructor por defecto.
  */
Output::~Output(){
}
/**
  * @brief : Inicializa todas las variables.
  */
int Output::init(void){
	return 0;
}
/**
  * @brief : Inicializa todas las variables configurando la salida como funcion de las entradas rescatando los datos desde la SD Card.
  */
int Output::init(vector<Input> in){
	return 0;
}
/**
  * @brief : Entrega el estado actual de la salida en formato String.
  */
String Output::getState(int id){
	return String();
}
/**
  * @brief : Setea el estado de la salida con identificador id y lo guarda en la SD Card.
  */
int Output::setState(int id, int state){
	return 0;
}
/**
  * brief : Calcula el siguiente estado en funcion de las entradas
  */
int Output::calcNextState(void){
	return 0;
}
/**
  * @brief : Entrega el listado de entradas que se consideran para la lógica de la salida 
  */
String Output::getInputLogic(int id){
	return String;
}
/**
  * @brief : Setea las entradas que generan la lógica de la salida y las guarda en la SD CARD.
  */
int Output::setInputLogic(vector<Input> in){
	return 0;
}
/*
  * @brief : Setea el tiempo en minutos que la salida estará activa, pero sin mesionar el tiempo de partida y lo guarda en la SD Card.
  */
int Output::setOutputTime(int min){
	return 0;
}
/**
  * @brief : Setea la hora y minuto en que la salida se activa todos los dias y lo guarda en la SD Card.
  */
int Output::setOutputTime(int hour, int min){
	return 0;
}
/**
  * @brief : Setea el dia, hora y minuto en que la salida se activa todas las semanas y lo guarda en la SD Card.
  */
int Output::setOutputTime(int day, int hour, int min){
	return 0;
}
/**
 * @brief : Setea los dias de la semana, hora, y minuto en que se activa la salida y lo guarda en la SD Card.
 */
int Output::setOutputTime(int days[], int hour, int min){
	return 0;
}
/**
 * @brief : Setea el ID de la salida que puede ser tanto local como de un módulo de expansion.
 */
int Output::setId(int id){
	return 0;
}
/**
 * @brief : Setea el programa activo, por defaul siempre parte con el A.
 */
int Output::setProgram(int program_id){
	return 0;
}
/**
 * @brief : Actualiza el estado de las salidas por el calculado con calcNextState().
 */
int Output::updateState(void){
	return 0;
}