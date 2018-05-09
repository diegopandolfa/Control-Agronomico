#include "output.h"

Output::Output(){
	/**
	 * @brief : 
	 */
	id = 0;
	/**
	 * @brief : 
	 */
	program_id = 0;
	/**
	 * @brief : 
	 */
	mode = 0;
	/**
	 * @brief : 
	 */
	label = 0;
	/**
	 * @brief : 
	 */
	pinOut = 0;
	/**
	 * @brief : 
	 */
	state = 0;
	/**
	 * @brief : 
	 */
	next_state = 0;
	/**
	 * @brief : 
	 */
	//inputs = NULL;
	/**
	 * @brief : 
	 */
	time_on = new int[5];
	/**
	 * @brief : 
	 */
	minute = new int[5];
	/**
	 * @brief : 
	 */
	hour = new int[5];
	/**
	 * @brief : 
	 */
	days = new int[35]; // A: L,M,X,J,V,S,D ; B: L,M,X,J,V,S,D ;...
	/**
	 * @brief : 
	 */
	peakTime = false;
}

Output::Output(int id, int pinOut){
	/**
	 * @brief : 
	 */
	this->id = id;
	/**
	 * @brief : 
	 */
	program_id = 0;
	/**
	 * @brief : 
	 */
	this->pinOut = pinOut;
	/**
	 * @brief : 
	 */
	mode = 0;
	/**
	 * @brief : 
	 */
	label = 0;
	/**
	 * @brief : 
	 */
	state = 0;
	/**
	 * @brief : 
	 */
	next_state = 0;
	/**
	 * @brief : 
	 */
	//inputs = NULL;
	/**
	 * @brief : 
	 */
	time_on = new int[5];
	/**
	 * @brief : 
	 */
	minute = new int[5];
	/**
	 * @brief : 
	 */
	hour = new int[5];
	/**
	 * @brief : 
	 */
	days = new int[35]; // A: L,M,X,J,V,S,D ; B: L,M,X,J,V,S,D ;...
	/**
	 * @brief : 
	 */
	peakTime = false;
}
/**
  * @brief : Destructor por defecto.
  */
Output::~Output(){
	delete time_on;
	delete minute;
	delete hour;
	delete days;
}
/**
  * @brief : Inicializa todas las variables.
  */
int Output::init(void){
	/**
	 * @brief : 
	 */
	program_id = PROGRAM_A;
	/**
	 * @brief : 
	 */
	mode = MODE_SELECTED_POZO;
	/**
	 * @brief : 
	 */
	label = LABEL_OUT_CONTACT;
	/**
	 * @brief : 
	 */
	state = LOW;
	/**
	 * @brief : 
	 */
	next_state = LOW;
	/**
	 * @brief : 
	 */
	//inputs = NULL;
	/**
	 * @brief : 
	 */
	for(int i=0; i<5; i++){
		time_on[i] = 0;
		minute[i] = 0;
		hour[i] = 0;
	}
	for(int i=0; i<35; i++){
		days[i] = 0; // A: L,M,X,J,V,S,D ; B: L,M,X,J,V,S,D ;...
	}
	/**
	 * @brief : 
	 */
	peakTime = false;
	pinMode(pinOut, OUTPUT);
	return 0;
}

//int Output::init(Node_in *inputs, int label){
//	this->label = label;
//	/**
//	 * @brief : 
//	 */
//	program_id = PROGRAM_A;
//	/**
//	 * @brief : 
//	 */
//	state = LOW;
//	/**
//	 * @brief : 
//	 */
//	next_state = LOW;
//	/**
//	 * @brief : 
//	 */
//	//this->inputs = inputs;
//	/**
//	 * @brief : 
//	 */
//	for(int i=0; i<5; i++){
//		time_on[i] = 0;
//		minute[i] = 0;
//		hour[i] = 0;
//	}
//	for(int i=0; i<35; i++){
//		days[i] = 0; // A: L,M,X,J,V,S,D ; B: L,M,X,J,V,S,D ;...
//	}
//	/**
//	 * @brief : 
//	 */
//	peakTime = false;
//	return 0;
//}

/**
  * @brief : Entrega el estado actual de la salida en formato String.
  */
int Output::getState(int id, String &state){
	if(this->id == id){
		state = "ID ";
		state += String(this->id);
		state += " : ";
		state += (this->state == HIGH)?("HIGH"):("LOW");
		return 0;
	}
	else{
		state = "error state";
		return -1;
	}
}
/**
  * @brief : Setea el estado de la salida con identificador id y lo guarda en la SD Card.
  */
int Output::setState(int id, int state){
	if(this->id == id){
		this->state = state;
		return 0;
	}
	else{
		return -1;
	}
}
/**
  * brief : Calcula el siguiente estado en funcion de las entradas y la hora
  */
int Output::calcNextState(int day, int hour, int minute){
	/*bool tmp = false;
	switch(mode){
		case MODE_SELECTED_POZO : { // si esta en modo pozo
			if(label == LABEL_OUT_PUMP){ // si la salida es una bomba
				if(peakTime == false){		// si no es horario punta
					if(inputs != NULL){ // si hay logica de entradas
						Node_in *it = inputs; // nos posicionamos en el primer elemento que es relé de nivel del pozo
						it = inputs->next;											// nos saltamos este porque está reservado para el relé de nivel.
						while( it != NULL){ // mientras no llegue al final
							tmp |= it->input->readInput(); // leo el estado de la entrada correspondiente
							it = it->next;					// se pasa a la siguiente entrada
						}
						tmp &= inputs->input->readInput(); // si hay agua se mantiene la lógica, sino se apaga.
						next_state = (tmp == true)?(HIGH):(LOW); // se define el siguiente estado en funcion de las entradas
						return 0; 								// seretorna con estatus 0 (OK)
					}
					else{ //no hay logica de entradas
						next_state = LOW;
						return -1;
					}
				}
				else{ // hora punta
					next_state = LOW;
					return 0;
				}
			}
			else{ // si la salida no es bomba
				if(inputs != NULL){ // si hay logica de entradas
					Node_in *it = inputs; // nos posicionamos en el primer elemento que es relé de nivel del pozo
					it->next;											// nos saltamos este porque está reservado para el relé de nivel.
					while( it != NULL){ // mientras no llegue al final
						tmp |= it->input->readInput(); // leo el estado de la entrada correspondiente
						it = it->next;					// se pasa a la siguiente entrada
					}
					next_state = (tmp == true)?(HIGH):(LOW); // se define el siguiente estado en funcion de las entradas
					return 0;
				}
				else{ // si no hay lógica de entradas
					next_state = LOW;
					return -1;
				}
			}
			break;
		}
		default:
			next_state = LOW;
			break;
	}*/
	return 0;
}
/**
  * @brief : Entrega el listado de entradas que se consideran para la lógica de la salida 
  */
int Output::getInputLogic(int id, String &input_logic){
	/*if(this->id == id){
		input_logic = "";
		Node_in *it = inputs;
		while( it != NULL){
			input_logic += String(it->input->getId());
			input_logic += ",";
			it = it->next;
		}
		return 0;
	}
	else{
		input_logic = "error id";
		return -1;
	}
	*/
}
/**
  * @brief : Setea las entradas que generan la lógica de la salida y las guarda en la SD CARD.
  */
/*int Output::setInputLogic(Node_in *in){
	this->inputs = in;
	return 0;
}
*/
/*
  * @brief : Setea el tiempo en minutos que la salida estará activa, pero sin mesionar el tiempo de partida y lo guarda en la SD Card.
  */
int Output::setOutputTime(int min){
	this->time_on[program_id] = min;
	return 0;
}
/**
  * @brief : Setea la hora y minuto en que la salida se activa todos los dias y lo guarda en la SD Card.
  */
int Output::setOutputTime(int hour, int min){
	this->hour[program_id] = hour;
	this->minute[program_id] = min;
	return 0;
}
/**
  * @brief : Setea el dia, hora y minuto en que la salida se activa todas las semanas y lo guarda en la SD Card.
  */
int Output::setOutputTime(int day, int hour, int min){
	this->days[(program_id-1)*7 + day] = 1;
	this->hour[program_id] = hour;
	this->minute[program_id] = min;
	return 0;
}
/**
 * @brief : Setea los dias de la semana, hora, y minuto en que se activa la salida y lo guarda en la SD Card.
 */
int Output::setOutputTime(int days[], int hour[], int min[]){
	this->days = days;
	this->hour = hour;
	this->minute = min;
	return 0;
}
/**
 * @brief : Setea el ID de la salida que puede ser tanto local como de un módulo de expansion.
 */
int Output::setId(int id){
	this->id=id;
	return 0;
}
/**
 * @brief : Entrega el ID de la salida que puede ser tanto local como de un módulo de expansion.
 */
int Output::getId(void){
	return this->id;
}
/**
 * @brief : Setea el programa activo, por defaul siempre parte con el A.
 */
int Output::setProgram(int program_id){
	this->program_id = program_id;
	return 0;
}
/**
 * @brief : Actualiza el estado de las salidas por el calculado con calcNextState().
 */
int Output::updateState(void){
	this->state = this->next_state;
	return 0;
}
/**
 * @brief : Entrega un String con la trama de los parametros a guardar en la SD.
 */
String Output::getDataStorage(void){
	return String();
}

/**
 * @brief : 
 */
int Output::setPeakTime(bool peakTime){
	this->peakTime = peakTime;
	return 0;
}

/**
 * @brief : 
 */
int Output::action(void){
	digitalWrite(this->pinOut, this->state);
	return 0;
}
