int display_init(){
  lcd.init();
  delay(40);
  lcd.backlight();
  delay(40);
  lcd.clear();
  return 0;
}

void print_welcome_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,0);
  lcd.print("IEH INGENIERIA SPA");
  lcd.setCursor(0,1);
  lcd.print("IZARO PRINCIPAL");
  lcd.setCursor(0,2);
  lcd.print("POZO 3");
}

void print_error_sd_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,0);
  lcd.print("ERROR:");
  lcd.setCursor(0,1);
  lcd.print("SD CARD NOT FOUND");
  lcd.setCursor(0,2);
  lcd.print("OR FILE IS CORRUPT");
}

void print_sd_card_ok_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("SD CARD OK");
}

void print_error_load_config(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("ERROR:");
  lcd.setCursor(0,2);
  lcd.print("FILE IS CORRUPT!");
}

void print_load_config_ok_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("LOAD CONFIG OK");
}

void print_config_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("SYSTEM");
  lcd.setCursor(0,2);
  lcd.print("CONFIGURATION");
}

void print_input_config_ok_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("INPUT CONFIG OK");
}

void print_output_config_ok_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("OUTPUT CONFIG OK");
}

void print_rtc_config_ok_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("RTC CONFIG OK");
}

void print_rtc_config_fail_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("SERVER NOT FOUND");
  lcd.setCursor(0,2);
  lcd.print("RTC NO SYNC");
}

void print_config_ok_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("CONFIGURATION OK");
}

void print_stay_for_3G_connection(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("STAY FOR 3G");
}

void print_rtc_config_init(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("RTC CONFIG");
}

void print_variables(){
  lcd.clear();
  str_lcd[0] = "IN_0 :";
  str_lcd[0] += valor_0;
  str_lcd[1] = "IN_1 :";
  str_lcd[1] += valor_1;
  str_lcd[2] = "IN_2 :";
  str_lcd[2] += valor_2;
  str_lcd[3] = "IN_3 :";
  str_lcd[3] += valor_3;
  str_lcd[4] = "IN_4 :";
  str_lcd[4] += valor_4;
  str_lcd[5] = "IN_5 :";
  str_lcd[5] += valor_5;
  str_lcd[6] = "IN_6 :";
  str_lcd[6] += valor_6;
  str_lcd[7] = "IN_7 :";
  str_lcd[7] += valor_7;
  str_lcd[8] = "IN_8 :";
  str_lcd[8] += valor_8;
  str_lcd[9] = "IN_9 :";
  str_lcd[9] += valor_9;
  str_lcd[10] = "OUT_0:";
  str_lcd[10] += status_salida_0;
  str_lcd[11] = "OUT_1:";
  str_lcd[11] += status_salida_1;
  str_lcd[12] = "OUT_2:";
  str_lcd[12] += status_salida_2;
  str_lcd[13] = "OUT_3:";
  str_lcd[13] += status_salida_3;
  str_lcd[14] = "OUT_4:";
  str_lcd[14] += status_salida_4;
  str_lcd[15] = "OUT_5:";
  str_lcd[15] += status_salida_5;
  str_lcd[16] = "OUT_6:";
  str_lcd[16] += status_salida_6;
  str_lcd[17] = "OUT_7:";
  str_lcd[17] += status_salida_7;
  str_lcd[18] = "OUT_8:";
  str_lcd[18] += status_salida_8;
  str_lcd[19] = "OUT_9:";
  str_lcd[19] += status_salida_9;
 
  lcd.setCursor(0,0);
  lcd.print(str_lcd[iterador_lcd]);
  lcd.setCursor(0,1);
  lcd.print(str_lcd[iterador_lcd+1]);
  lcd.setCursor(0,2);
  lcd.print(str_lcd[iterador_lcd+2]);
  lcd.setCursor(0,3);
  lcd.print(str_lcd[iterador_lcd+3]);

  String tmp = "";
  tmp += "3G:";
  tmp += (request_http_ok == true)?("OK  "):("FAIL");
  lcd.setCursor(13,0);
  lcd.print(tmp);

  tmp = "";
  tmp += "@ ";
  if(hora < 10){
    tmp += "0";
    tmp += hora; 
  }
  else {
    tmp += hora;  
  }
  tmp += ":";
  if(minuto < 10){
    tmp += "0";
    tmp += minuto; 
  }
  else {
    tmp += minuto;  
  }
  lcd.setCursor(13,1);
  lcd.print(tmp);
  /*
  str_lcd += (status_salida_0 == 0)?("ON "):("OFF");
  str_lcd += " @";
  str_lcd += freq_prev;
  lcd.setCursor(8,0);
  lcd.print(str_lcd);
  lcd.setCursor(8,1);
  str_lcd = "";
  str_lcd += caudal;
  lcd.print(str_lcd);
  lcd.setCursor(8,2);
  str_lcd = (request_http_ok == true)?("OK  "):("FAIL");
  str_lcd += "  @";
  if(hora < 10){
    str_lcd += "0";
    str_lcd += hora; 
  }
  else {
    str_lcd += hora;  
  }
  str_lcd += ":";
  if(minuto < 10){
    str_lcd += "0";
    str_lcd += minuto; 
  }
  else {
    str_lcd += minuto;  
  }
  lcd.print(str_lcd);
  lcd.setCursor(8,3);
  str_lcd = "";
  if(flag_func){
    str_lcd += (enable_var_frec == true)?("ALTO       *"):("BAJO       *");
  }
  else{
    str_lcd += (enable_var_frec == true)?("ALTO        "):("BAJO        ");
  }
  flag_func = !flag_func;
  lcd.print(str_lcd);
  */
}

void print_system_config_ok_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("SYSTEM CONFIG OK");
}
