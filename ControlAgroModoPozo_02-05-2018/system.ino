int system_inputs_read(){
  for(int i=0;)
}

int system_outputs_update(){
  
}

int system_output_write(){
  digitalWrite(pin_salida_0, HIGH);
  digitalWrite(pin_salida_1, HIGH);
  digitalWrite(pin_salida_2, HIGH);
  digitalWrite(pin_salida_3, HIGH);
  digitalWrite(pin_salida_4, HIGH);
  digitalWrite(pin_salida_5, HIGH);
  digitalWrite(pin_salida_6, HIGH);
  digitalWrite(pin_salida_7, HIGH);
  digitalWrite(pin_salida_8, HIGH);
  digitalWrite(pin_salida_9, HIGH);
  Serial.println("salidas high");
  delay(100);
}
