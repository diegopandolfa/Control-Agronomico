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
