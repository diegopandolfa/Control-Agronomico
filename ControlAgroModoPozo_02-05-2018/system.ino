int system_inputs_read(){
  for(int i=0; i<10; i++){
    if(inputs[i][2] != 4){ // si no es de efecto hall
      switch(i){
        case 0 : {
          valor_0 = (status_entrada_0)*(inputs[i][3]); // entrada escalada por el parametro
          break;
        }
        case 1 : {
          valor_1 = (status_entrada_1)*(inputs[i][3]);
          break;
        }
        case 2 : {
          valor_2 = (status_entrada_2)*(inputs[i][3]);
          break;
        }
        case 3 : {
          valor_3 = (status_entrada_3)*(inputs[i][3]);
          break;
        }
        case 4 : {
          valor_4 = (status_entrada_4)*(inputs[i][3]);
          break;
        }
        case 5 : {
          valor_5 = (status_entrada_5)*(inputs[i][3]);
          break;
        }
        case 6 : {
          valor_6 = (status_entrada_6)*(inputs[i][3]);
          break;
        }
        case 7 : {
          valor_7 = (status_entrada_7)*(inputs[i][3]);
          break;
        }
        case 8 : {
          valor_8 = (status_entrada_8)*(inputs[i][3]);
          break;
        }
        case 9 : {
          valor_9 = (status_entrada_9)*(inputs[i][3]);
          break;
        }
        default : {
          break;
        }
      }
    }  
  }
  return 0;
}

/**
 * @brief : actualización de las salidas en funcion de las entradas.
 */
int system_outputs_update(){
  status_salida_0 = 1;
  status_salida_1 = 1;
  status_salida_2 = 1;
  status_salida_3 = 1;
  status_salida_4 = 1;
  status_salida_5 = 1;
  status_salida_6 = 1;
  status_salida_7 = 1;
  status_salida_8 = 1;
  status_salida_9 = 1;
  
  int inputs__[] = {(int)valor_0, (int)valor_1, (int)valor_2, (int)valor_3, (int)valor_4, (int)valor_5, (int)valor_6, (int)valor_7, (int)valor_8, (int)valor_9};
  for(int i=0; i<10; i++){
    switch(i){
      case 0 : {
        for(int j = 0; j<10; j++){
          status_salida_0 &= ( (( ((int)outputs[0][3]) >> j )&0x01) == 0x01 )?(inputs__[j]):(0x01);  
        }
        break;
      }
      case 1 : {
        for(int j = 0; j<10; j++){
          status_salida_1 &= ( (( ((int)outputs[1][3]) >> j )&0x01) == 0x01 )?(inputs__[j]):(0x01);  
        }
        break;
      }
      case 2 : {
        for(int j = 0; j<10; j++){
          status_salida_2 &= ( (( ((int)outputs[2][3]) >> j )&0x01) == 0x01 )?(inputs__[j]):(0x01);  
        }
        break;
      }
      case 3 : {
        for(int j = 0; j<10; j++){
          status_salida_3 &= ( (( ((int)outputs[3][3]) >> j )&0x01) == 0x01 )?(inputs__[j]):(0x01);  
        }
        break;
      }
      case 4 : {
        for(int j = 0; j<10; j++){
          status_salida_4 &= ( (( ((int)outputs[4][3]) >> j )&0x01) == 0x01 )?(inputs__[j]):(0x01);  
        }
        break;
      }
      case 5 : {
        for(int j = 0; j<10; j++){
          status_salida_5 &= ( (( ((int)outputs[5][3]) >> j )&0x01) == 0x01 )?(inputs__[j]):(0x01);  
        }
        break;
      }
      case 6 : {
        for(int j = 0; j<10; j++){
          status_salida_6 &= ( (( ((int)outputs[6][3]) >> j )&0x01) == 0x01 )?(inputs__[j]):(0x01);  
        }
        break;
      }
      case 7 : {
        for(int j = 0; j<10; j++){
          status_salida_7 &= ( (( ((int)outputs[7][3]) >> j )&0x01) == 0x01 )?(inputs__[j]):(0x01);  
        }
        break;
      }
      case 8 : {
        for(int j = 0; j<10; j++){
          status_salida_8 &= ( (( ((int)outputs[8][3]) >> j )&0x01) == 0x01 )?(inputs__[j]):(0x01);  
        }
        break;
      }
      case 9 : {
        for(int j = 0; j<10; j++){
          status_salida_9 &= ( (( ((int)outputs[9][3]) >> j )&0x01) == 0x01 )?(inputs__[j]):(0x01);  
        }
        break;
      }
      default : {
        break;
      }  
    }  
  }

  /**
   * @brief : una vez obtenida la lógica de entradas, es necesario cruzar la info con la nube
   */
  status_salida_0 &= (remote_output_0 == 1)?(0):(1); 
  status_salida_1 &= (remote_output_1 == 1)?(0):(1); 
  status_salida_2 &= (remote_output_2 == 1)?(0):(1); 
  status_salida_3 &= (remote_output_3 == 1)?(0):(1);
  status_salida_4 &= (remote_output_4 == 1)?(0):(1);
  status_salida_5 &= (remote_output_5 == 1)?(0):(1); 
  status_salida_6 &= (remote_output_6 == 1)?(0):(1);
  status_salida_7 &= (remote_output_7 == 1)?(0):(1);
  status_salida_8 &= (remote_output_8 == 1)?(0):(1);
  status_salida_9 &= (remote_output_9 == 1)?(0):(1);

  /**
   * @brief : lógica de relé de nivel y salida de bomba.
   *          -Si hay agua en el pozo profundo el relé de nivel cierra el contacto NO.
   *          -Si la entrada esta en bajo, entonces hay agua.
   *          -Si hay agua, se mantiene la lógica de entradas.
   *          -Sino, se setea la salida en LOW
   *          
   *          Esto fija la conexion de un relé de nivel en la entrada 0 y fija la conexion
   *          de una bomba en la salida 0.
   *          
   *          Cabe destacar que la lógica de entradas para la salida 0 es la misma que
   *          para el variador de frecuencia.
   */
  status_salida_0 = (status_entrada_0 == 0)?(status_salida_0):(1);

  /**
   * @brief : verificar el horario punta.
   *          -lógica del horario punta.
   *          -Si el horario punta está activo, entonces se debe apagar la bomba.
   *          -Si el horario punta esta inactivo, entones la bomba puede encender.
   */
  if(peakTime_enable == 1){
    if(hora >= 17 && hora <= 23){
      hora_punta = true;  
    }
    else{
      hora_punta = false;  
    }  
  }
  else{
    hora_punta = false;  
  }
  status_salida_0 = (hora_punta == true)?(1):(status_salida_0);
  
  return 0;
}

int system_output_write(){
  if(status_salida_0 == 0){
    digitalWrite(pin_salida_0, HIGH);
  }
  else{
    digitalWrite(pin_salida_0, LOW);  
  }
  if(status_salida_1 == 0){
    digitalWrite(pin_salida_1, HIGH);
  }
  else{
    digitalWrite(pin_salida_1, LOW);  
  }
  if(status_salida_2 == 0){
    digitalWrite(pin_salida_2, HIGH);
  }
  else{
    digitalWrite(pin_salida_2, LOW);  
  }
  if(status_salida_3 == 0){
    digitalWrite(pin_salida_3, HIGH);
  }
  else{
    digitalWrite(pin_salida_3, LOW);  
  }
  if(status_salida_4 == 0){
    digitalWrite(pin_salida_4, HIGH);
  }
  else{
    digitalWrite(pin_salida_4, LOW);  
  }
  if(status_salida_5 == 0){
    digitalWrite(pin_salida_5, HIGH);
  }
  else{
    digitalWrite(pin_salida_5, LOW);  
  }
  if(status_salida_6 == 0){
    digitalWrite(pin_salida_6, HIGH);
  }
  else{
    digitalWrite(pin_salida_6, LOW);  
  }
  if(status_salida_7 == 0){
    digitalWrite(pin_salida_7, HIGH);
  }
  else{
    digitalWrite(pin_salida_7, LOW);  
  }
  if(status_salida_8 == 0){
    digitalWrite(pin_salida_8, HIGH);
  }
  else{
    digitalWrite(pin_salida_8, LOW);  
  }
  if(status_salida_9 == 0){
    digitalWrite(pin_salida_9, HIGH);
  }
  else{
    digitalWrite(pin_salida_9, LOW);
  }
  return 0;
}

void run_inverter(){
  var_frec.writeSingleRegister(REG_RUN, START_INV); // dar partida
}

void stop_inverter(){
  var_frec.writeSingleRegister(REG_RUN, STOP_INV); // parar
}

void set_freq_inverter(double freq){
  int freq__ = (int)freq*100.0;
  var_frec.writeSingleRegister(REG_RUN_FREQ, freq__); // setear frecuencia del variador
}
