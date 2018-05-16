int input_config(){
  for(int i=0; i<10; i++){ // solo entradas locales
    if(inputs[i][0] == 0){
      int input___ = inputs[i][1];
      int mode___ = inputs[i][2];
      switch(input___){
        case 0 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_entrada_logica_0, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_entrada_logica_0, INPUT_PULLUP);
              break;
            }
            case 2 : {
              pinMode(pin_entrada_logica_0, INPUT);
              break;
            }
            case 3 : {
              pinMode(pin_entrada_logica_0, INPUT);
              break;
            }
            case 4 : {
              pinMode(pin_entrada_logica_0, INPUT_PULLUP);
              break;
            }
            default : {
              pinMode(pin_entrada_logica_0, INPUT_PULLDOWN);
              break;  
            } 
          }
        }
        case 1 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_entrada_logica_1, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_entrada_logica_1, INPUT_PULLUP);
              break;
            }
            case 2 : {
              pinMode(pin_entrada_logica_1, INPUT);
              break;
            }
            case 3 : {
              pinMode(pin_entrada_logica_1, INPUT);
              break;
            }
            case 4 : {
              pinMode(pin_entrada_logica_1, INPUT_PULLUP);
              break;
            }
            default : {
              pinMode(pin_entrada_logica_1, INPUT_PULLDOWN);
              break;  
            } 
          }
        }
        case 2 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_entrada_logica_2, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_entrada_logica_2, INPUT_PULLUP);
              break;
            }
            case 2 : {
              pinMode(pin_entrada_logica_2, INPUT);
              break;
            }
            case 3 : {
              pinMode(pin_entrada_logica_2, INPUT);
              break;
            }
            case 4 : {
              pinMode(pin_entrada_logica_2, INPUT_PULLUP);
              break;
            }
            default : {
              pinMode(pin_entrada_logica_2, INPUT_PULLDOWN);
              break;  
            } 
          }
        }
        case 3 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_entrada_logica_3, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_entrada_logica_3, INPUT_PULLUP);
              break;
            }
            case 2 : {
              pinMode(pin_entrada_logica_3, INPUT);
              break;
            }
            case 3 : {
              pinMode(pin_entrada_logica_3, INPUT);
              break;
            }
            case 4 : {
              pinMode(pin_entrada_logica_3, INPUT_PULLUP);
              break;
            }
            default : {
              pinMode(pin_entrada_logica_3, INPUT_PULLDOWN);
              break;  
            } 
          }
        }
        case 4 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_entrada_logica_4, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_entrada_logica_4, INPUT_PULLUP);
              break;
            }
            case 2 : {
              pinMode(pin_entrada_logica_4, INPUT);
              break;
            }
            case 3 : {
              pinMode(pin_entrada_logica_4, INPUT);
              break;
            }
            case 4 : {
              pinMode(pin_entrada_logica_4, INPUT_PULLUP);
              break;
            }
            default : {
              pinMode(pin_entrada_logica_4, INPUT_PULLDOWN);
              break;  
            }
          }
        }
        case 5 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_entrada_analoga_0, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_entrada_analoga_0, INPUT_PULLUP);
              break;
            }
            case 2 : {
              pinMode(pin_entrada_analoga_0, INPUT);
              break;
            }
            case 3 : {
              pinMode(pin_entrada_analoga_0, INPUT);
              break;
            }
            case 4 : {
              pinMode(pin_entrada_analoga_0, INPUT_PULLUP);
              break;
            }
            default : {
              pinMode(pin_entrada_analoga_0, INPUT_PULLDOWN);
              break;  
            } 
          }
        }
        case 6 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_entrada_analoga_1, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_entrada_analoga_1, INPUT_PULLUP);
              break;
            }
            case 2 : {
              pinMode(pin_entrada_analoga_1, INPUT);
              break;
            }
            case 3 : {
              pinMode(pin_entrada_analoga_1, INPUT);
              break;
            }
            case 4 : {
              pinMode(pin_entrada_analoga_1, INPUT_PULLUP);
              break;
            }
            default : {
              pinMode(pin_entrada_analoga_1, INPUT_PULLDOWN);
              break;  
            }  
          }
        }
        case 7 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_entrada_analoga_2, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_entrada_analoga_2, INPUT_PULLUP);
              break;
            }
            case 2 : {
              pinMode(pin_entrada_analoga_2, INPUT);
              break;
            }
            case 3 : {
              pinMode(pin_entrada_analoga_2, INPUT);
              break;
            }
            case 4 : {
              pinMode(pin_entrada_analoga_2, INPUT_PULLUP);
              break;
            }
            default : {
              pinMode(pin_entrada_analoga_2, INPUT_PULLDOWN);
              break;  
            }  
          }
        }
        case 8 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_entrada_analoga_3, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_entrada_analoga_3, INPUT_PULLUP);
              break;
            }
            case 2 : {
              pinMode(pin_entrada_analoga_3, INPUT);
              break;
            }
            case 3 : {
              pinMode(pin_entrada_analoga_3, INPUT);
              break;
            }
            case 4 : {
              pinMode(pin_entrada_analoga_3, INPUT_PULLUP);
              break;
            }
            default : {
              pinMode(pin_entrada_analoga_3, INPUT_PULLDOWN);
              break;  
            }  
          }
        }
        case 9 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_entrada_analoga_4, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_entrada_analoga_4, INPUT_PULLUP);
              break;
            }
            case 2 : {
              pinMode(pin_entrada_analoga_4, INPUT);
              break;
            }
            case 3 : {
              pinMode(pin_entrada_analoga_4, INPUT);
              break;
            }
            case 4 : {
              pinMode(pin_entrada_analoga_4, INPUT_PULLUP);
              break;
            }
            default : {
              pinMode(pin_entrada_analoga_4, INPUT_PULLDOWN);
              break;  
            }  
          }
        }
        default : {
          break; // entrada fuera de rango, no se hace nada  
        }
      }  
    }  
  }
  return 0;
}

int output_config(){
  for(int i=0; i<10; i++){ // solo salidas locales
    if(outputs[i][0] == 0){ // device
      int output___ = outputs[i][1]; // id
      int mode___ = outputs[i][2]; // mode
      switch(output___){
        case 0 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_salida_0, INPUT_PULLDOWN);
              DEBUG.println("hola se esta deshabilitando la salida 0");
              break;
            }
            case 1 : {
              pinMode(pin_salida_0, OUTPUT);
              DEBUG.println("hola se esta definiendo salida 0 como salida");
              break;
            }
            default : {
              pinMode(pin_salida_0, INPUT_PULLDOWN);
              DEBUG.println("hola se esta deshabilitando por defecto");
              break;
            }  
          }
        }
        case 1 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_salida_1, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_salida_1, OUTPUT);
              break;
            }
            default : {
              pinMode(pin_salida_1, INPUT_PULLDOWN);
              break;
            }  
          }
        }
        case 2 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_salida_2, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_salida_2, OUTPUT);
              break;
            }
            default : {
              pinMode(pin_salida_2, INPUT_PULLDOWN);
              break;
            }  
          }
        }
        case 3 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_salida_3, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_salida_3, OUTPUT);
              break;
            }
            default : {
              pinMode(pin_salida_3, INPUT_PULLDOWN);
              break;
            }  
          }
        }
        case 4 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_salida_4, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_salida_4, OUTPUT);
              break;
            }
            default : {
              pinMode(pin_salida_4, INPUT_PULLDOWN);
              break;
            }  
          }
        }
        case 5 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_salida_5, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_salida_5, OUTPUT);
              break;
            }
            default : {
              pinMode(pin_salida_5, INPUT_PULLDOWN);
              break;
            }  
          }
        }
        case 6 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_salida_6, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_salida_6, OUTPUT);
              break;
            }
            default : {
              pinMode(pin_salida_6, INPUT_PULLDOWN);
              break;
            }  
          }
        }
        case 7 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_salida_7, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_salida_7, OUTPUT);
              break;
            }
            default : {
              pinMode(pin_salida_7, INPUT_PULLDOWN);
              break;
            }  
          }
        }
        case 8 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_salida_8, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_salida_8, OUTPUT);
              break;
            }
            default : {
              pinMode(pin_salida_8, INPUT_PULLDOWN);
              break;
            }  
          }
        }
        case 9 : {
          switch(mode___){
            case 0 : {
              pinMode(pin_salida_9, INPUT_PULLDOWN);
              break;
            }
            case 1 : {
              pinMode(pin_salida_9, OUTPUT);
              break;
            }
            default : {
              pinMode(pin_salida_9, INPUT_PULLDOWN);
              break;
            }  
          }
        }
        default : { // salida fuera de index, no se hace nada
          break;
        }  
      }
    }
  }
  return 0;
}

int rtc_config(){
  String tmp = "HEAD /api/v1.6";
  tmp += " HTTP/1.1\r\n";
  tmp += "HOST: things.ubidots.com\r\n";
  tmp += "Connection: close\r\n";
  tmp += "\r\n";
  //delay(10000);
  MODULO_3G.flush();
  delay(100);
  MODULO_3G.print(tmp);
  DEBUG.print(tmp);
  char data_in_ = 0;
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Esperando Servidor");
  Metro time_request_rtc = Metro(20000);
  time_request_rtc.reset();
  int count__ = 0;
  Metro timer_one_second = Metro(1000);
  timer_one_second.reset();
  while(time_request_rtc.check() == 0){
    if(MODULO_3G.available()>0){
      data_in_ = MODULO_3G.read();
      DEBUG.print(data_in_);
      bufferAnswer[count__] = data_in_;
      count__++;
    }
    if(timer_one_second.check() == 1){
      static int i = 0;
      lcd.setCursor(i++, 2);
      lcd.print(".");
    }
  }

  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Procesando...");
  
  bufferAnswer[count__] = '\0';
  const char delim[] = {'\r','\n','\0'};
  char *token;
  int largo = 0;
  token = strtok(bufferAnswer, delim);

  while(token != NULL){
    largo = strlen(token);
    DEBUG.println(token);
    if(largo > 32){
      //token = strtok(NULL, delim);
      DEBUG.println(token);
      token = strtok(token, " ");
      token = strtok(NULL, " ");
      token = strtok(NULL, " ");
      count__ = 0;
      while(token != NULL){
        largo = strlen(token);
        DEBUG.println(token);
        if(count__ == 0){
          day_ = token;  
        }
        else if(count__ == 1){
          month_ = token;  
        }
        else if(count__ == 2){
          year_ = token;  
        }
        else{
          ;  // nothing else
        }
        count__++;
        if(largo > 6){
          DEBUG.println(token);
          token = strtok(token, ":");
          count__ = 0;
          while(token != NULL){
            if(count__ == 0){
              hour_ = token;  
            }
            else if(count__ == 1){
              minute_ = token;  
            }
            else if(count__ == 2){
              second_ = token;  
            }
            else{
              ;  // nothing else
            }
            count__++;
            DEBUG.println(token);
            token = strtok(NULL, ":");
          }
          break;  
        }
        token = strtok(NULL, " ");  
      }
      break;
    }
    token = strtok(NULL, delim);
  }
  if(year_ != NULL && month_ != NULL && day_ != NULL && hour_ != NULL && minute_ != NULL && second_ != NULL){
      DEBUG.print("fecha y hora:\t");
      DEBUG.print(day_);
      DEBUG.print("/");
      DEBUG.print(month_);
      DEBUG.print("/");
      DEBUG.print(year_);
      DEBUG.print(" ");
      DEBUG.print(hour_);
      DEBUG.print(":");
      DEBUG.print(minute_);
      DEBUG.print(":");
      DEBUG.println(second_);
      anno = atoi(year_);
      mes = (strstr(month_, "Jan"))?(1):
            (strstr(month_, "Feb"))?(2):
            (strstr(month_, "Mar"))?(3):
            (strstr(month_, "Apr"))?(4):
            (strstr(month_, "May"))?(5):
            (strstr(month_, "Jun"))?(6):
            (strstr(month_, "Jul"))?(7):
            (strstr(month_, "Aug"))?(8):
            (strstr(month_, "Sep"))?(9):
            (strstr(month_, "Oct"))?(10):
            (strstr(month_, "Nov"))?(11):
            (strstr(month_, "Dec"))?(12):(1);
      dia = ((atoi(hour_) - 3) < 0 )?(atoi(day_) - 1):(atoi(day_));
      hora = ( (atoi(hour_) - 3) < 0 )?(24 + (atoi(hour_) - 3)):(atoi(hour_) - 3);
      minuto = atoi(minute_);
      segundo = atoi(second_);
  }
  DEBUG.print("fecha y hora:\t");
  DEBUG.print(dia);
  DEBUG.print("/");
  DEBUG.print(mes);
  DEBUG.print("/");
  DEBUG.print(anno);
  DEBUG.print(" ");
  DEBUG.print(hora);
  DEBUG.print(":");
  DEBUG.print(minuto);
  DEBUG.print(":");
  DEBUG.println(segundo);

  TimeElements tm;
  tm.Second = segundo;
  tm.Minute = minuto;
  tm.Hour = hora;
  tm.Day = dia;
  tm.Month = mes;
  tm.Year = anno - 1970;

  time_t t = makeTime(tm);
  DEBUG.println(t);
  if(t != 0){
    if(t > 1520000000){
      Teensy3Clock.set(t);
      setTime(t);
    }
    else{
      print_rtc_config_fail_msg();
      delay(TIME_MSG);
    }
  }
  else {
    print_rtc_config_fail_msg(); 
    delay(TIME_MSG);
  }
  return 0;
}

/**
 * @brief : si es un device esclavo, entonces usa el XBEE
 */
int rtc_config_other_devices(){
  String tmp = "HEAD /api/v1.6";
  tmp += " HTTP/1.1\r\n";
  tmp += "HOST: things.ubidots.com\r\n";
  tmp += "Connection: close\r\n";
  tmp += "\r\n";
  //delay(10000);
  XBEE.flush();
  delay(100);
  XBEE.print(tmp);
  DEBUG.print(tmp);
  char data_in_ = 0;
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Esperando Servidor");
  Metro time_request_rtc = Metro(20000);
  time_request_rtc.reset();
  int count__ = 0;
  Metro timer_one_second = Metro(1000);
  timer_one_second.reset();
  while(time_request_rtc.check() == 0){
    if(XBEE.available()>0){
      data_in_ = XBEE.read();
      DEBUG.print(data_in_);
      bufferAnswer[count__] = data_in_;
      count__++;
    }
    if(timer_one_second.check() == 1){
      static int i = 0;
      lcd.setCursor(i++, 2);
      lcd.print(".");
    }
  }

  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Procesando...");
  
  bufferAnswer[count__] = '\0';
  const char delim[] = {'\r','\n','\0'};
  char *token;
  int largo = 0;
  token = strtok(bufferAnswer, delim);

  while(token != NULL){
    largo = strlen(token);
    DEBUG.println(token);
    if(largo > 32){
      //token = strtok(NULL, delim);
      DEBUG.println(token);
      token = strtok(token, " ");
      token = strtok(NULL, " ");
      token = strtok(NULL, " ");
      count__ = 0;
      while(token != NULL){
        largo = strlen(token);
        DEBUG.println(token);
        if(count__ == 0){
          day_ = token;  
        }
        else if(count__ == 1){
          month_ = token;  
        }
        else if(count__ == 2){
          year_ = token;  
        }
        else{
          ;  // nothing else
        }
        count__++;
        if(largo > 6){
          DEBUG.println(token);
          token = strtok(token, ":");
          count__ = 0;
          while(token != NULL){
            if(count__ == 0){
              hour_ = token;  
            }
            else if(count__ == 1){
              minute_ = token;  
            }
            else if(count__ == 2){
              second_ = token;  
            }
            else{
              ;  // nothing else
            }
            count__++;
            DEBUG.println(token);
            token = strtok(NULL, ":");
          }
          break;  
        }
        token = strtok(NULL, " ");  
      }
      break;
    }
    token = strtok(NULL, delim);
  }
  if(year_ != NULL && month_ != NULL && day_ != NULL && hour_ != NULL && minute_ != NULL && second_ != NULL){
      DEBUG.print("fecha y hora:\t");
      DEBUG.print(day_);
      DEBUG.print("/");
      DEBUG.print(month_);
      DEBUG.print("/");
      DEBUG.print(year_);
      DEBUG.print(" ");
      DEBUG.print(hour_);
      DEBUG.print(":");
      DEBUG.print(minute_);
      DEBUG.print(":");
      DEBUG.println(second_);
      anno = atoi(year_);
      mes = (strstr(month_, "Jan"))?(1):
            (strstr(month_, "Feb"))?(2):
            (strstr(month_, "Mar"))?(3):
            (strstr(month_, "Apr"))?(4):
            (strstr(month_, "May"))?(5):
            (strstr(month_, "Jun"))?(6):
            (strstr(month_, "Jul"))?(7):
            (strstr(month_, "Aug"))?(8):
            (strstr(month_, "Sep"))?(9):
            (strstr(month_, "Oct"))?(10):
            (strstr(month_, "Nov"))?(11):
            (strstr(month_, "Dec"))?(12):(1);
      dia = ((atoi(hour_) - 3) < 0 )?(atoi(day_) - 1):(atoi(day_));
      hora = ( (atoi(hour_) - 3) < 0 )?(24 + (atoi(hour_) - 3)):(atoi(hour_) - 3);
      minuto = atoi(minute_);
      segundo = atoi(second_);
  }
  DEBUG.print("fecha y hora:\t");
  DEBUG.print(dia);
  DEBUG.print("/");
  DEBUG.print(mes);
  DEBUG.print("/");
  DEBUG.print(anno);
  DEBUG.print(" ");
  DEBUG.print(hora);
  DEBUG.print(":");
  DEBUG.print(minuto);
  DEBUG.print(":");
  DEBUG.println(segundo);

  TimeElements tm;
  tm.Second = segundo;
  tm.Minute = minuto;
  tm.Hour = hora;
  tm.Day = dia;
  tm.Month = mes;
  tm.Year = anno - 1970;

  time_t t = makeTime(tm);
  DEBUG.println(t);
  if(t != 0){
    if(t > 1520000000){
      Teensy3Clock.set(t);
      setTime(t);
      flag_rtc_sync = true;
    }
    else{
      print_rtc_config_fail_msg();
      delay(TIME_MSG);
    }
  }
  else {
    print_rtc_config_fail_msg(); 
    delay(TIME_MSG);
  }
  return 0;
}

int peakTime_config(){
  return 0;
}

int stay_for_3G_connection(){
  lcd.setCursor(0,2);
  for(int i=0; i<20; i++){
    delay(1200);
    lcd.print(".");
    lcd.setCursor(i, 2);
  }
  return 0;
}

int system_config(){
  return 0;
}
