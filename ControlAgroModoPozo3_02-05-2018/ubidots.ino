int ubidots_requets_for_control(){
  String tmp = "GET /api/v1.6/devices/sala-de-riego/bomba/lv?token=BBFF-IH5I4OcjNkdFY6IAcKjnBhbdEThV8j";
  tmp += " HTTP/1.1\r\n";
  tmp += "HOST: things.ubidots.com\r\n";
  tmp += "\r\n";
  MODULO_3G.flush();
  MODULO_3G.print(tmp);
  //DEBUG.print(tmp);
  data_in_ = 0;
  time_request.reset();
  int count__ = 0;
  while(time_request.check() == 0){
    if(MODULO_3G.available()>0){
      data_in_ = MODULO_3G.read();
      //DEBUG.print(data_in_);
      bufferAnswer[count__] = data_in_;
      count__++;
    }
  }
  bufferAnswer[count__] = '\0';
  if(strstr(bufferAnswer, "\r\n1.0\r\n")){
    remote_output_0 = 1; // bomba ON
    DEBUG.println("Remote Bomba ON");
  }
  else{
    remote_output_0 = 0; // bomba OFF 
    DEBUG.println("Remote Bomba OFF");
  }
  tmp = "GET /api/v1.6/devices/sala-de-riego/variador-de-frecuencia/lv?token=BBFF-IH5I4OcjNkdFY6IAcKjnBhbdEThV8j";
  tmp += " HTTP/1.1\r\n";
  tmp += "HOST: things.ubidots.com\r\n";
  tmp += "\r\n";
  MODULO_3G.flush();
  MODULO_3G.print(tmp);
  //DEBUG.print(tmp);
  data_in_ = 0;
  time_request.reset();
  count__ = 0;
  while(time_request.check() == 0){
    if(MODULO_3G.available()>0){
      data_in_ = MODULO_3G.read();
      //DEBUG.print(data_in_);
      bufferAnswer[count__] = data_in_;
      count__++;
    }
  }
  bufferAnswer[count__] = '\0';
  const char delim[] = {'\r','\n','\0'};
  char *token;
  int largo = 0;
  token = strtok(bufferAnswer, delim);
  while(token != NULL){
    largo = strlen(token);
    //DEBUG.println(token);
    if(largo < 5){
      token = strtok(NULL, delim);
      //DEBUG.println(token);
      break;
    }
    token = strtok(NULL, delim);
  }
  freq = atof(token);
  if( (freq >= 30.0) && (freq <= 55.0) ){
    if( freq_prev != freq){
      DEBUG.print("registro : ");
      DEBUG.print(REG_RUN_FREQ);
      DEBUG.print("\tfreq : ");
      DEBUG.println(freq);
      set_freq_inverter(freq);
      freq_prev = freq;
    }
    request_http_ok = true;
  }
  return 0;
}

/**
 * @brief : Send info to IoT Cloud.
 */
int ubidots_post_request(){
  /**
   * @brief : Make a json object
   */
  String json = "";
  json += "[{";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"'; 
  json += "5a95a1eb642ab65a0e044acb"; // input_0 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_0;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae7448c642ab63fd1572cd8"; // input_1 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":";
  json += valor_1;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74498140c73367bbdc2cb"; // input_2 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":";
  json += valor_2;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae744a3642ab6400a4fb8d3"; // input_3 //ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_3;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae744ba642ab6405a5f6fd9"; // input_4 //ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_4;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae744d3642ab6405a5f6ff2"; // input_5 //ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_5;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae744d7642ab6400a4fb901"; // input_6 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_6;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74528642ab63fe4ff3e8a"; // input_7 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_7;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae7453b642ab6401d9ba59a"; // input_8 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_8;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74549642ab63fd1572ce8"; // input_9 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_9;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5adb80c2642ab6033af94cd4"; // output_0 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_0;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5adb80c2642ab6033af94cd4"; // output_1 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_1;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74570642ab63fe4ff3e9b"; // output_2 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_2;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74585642ab63ff7ee6b6a"; // output_3 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_3;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae745c5642ab641db104d95"; // output_4 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_4;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74633642ab64201f4a89e"; // output_5 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_5;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74623642ab6419b4cb5cc"; // output_6 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_6;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74642140c73378db3a7e6"; // output_7 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_7;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae7464e642ab6419b4cb5d7"; // output_8 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_8;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74658642ab6419b4cb5d8"; // output_9 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_9;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ada3c57642ab6080b6e4d29"; // conexion 3G
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += 1;
  json += "}]\r\n";

  /**
   * @brief : Concatenate HEAD (tmp) with json object
   */
  String tmp = "POST /api/v1.6/collections/values/?token=BBFF-IH5I4OcjNkdFY6IAcKjnBhbdEThV8j HTTP/1.1\r\n";
  tmp += "Host: things.ubidots.com\r\n";
  tmp += "Content-Type: application/json\r\n";
  tmp += "Content-Length: ";
  tmp += json.length();
  tmp += "\r\n";
  tmp += "\r\n";
  tmp += json;

  /**
   * @brief : Send request and stand by response
   */
  MODULO_3G.flush();
  MODULO_3G.print(tmp);
  //DEBUG.print(tmp);
  data_in_ = 0;
  time_request.reset();
  while(time_request.check() == 0){
    if(MODULO_3G.available()>0){
      data_in_ = MODULO_3G.read();
      //DEBUG.print(data_in_);
    }
  }
  //DEBUG.println();
  return 0;
}

void ubidots_request_for_other_devices(){
  XBEE.print("1");
  time_of_xbee.reset();
  while(time_of_xbee.check() == 0);
  MODULO_3G.flush();
  time_of_xbee.reset();
  if(XBEE.available()>0){
    while(time_of_xbee.check() == 0){
      if(XBEE.available()>0){
        MODULO_3G.print(XBEE.read());
      }
      else{
        ;
      }
    }
    data_in_ = 0;
    time_request.reset();
    while(time_request.check() == 0){
      if(MODULO_3G.available()>0){
        data_in_ = MODULO_3G.read();
        XBEE.print(data_in_);
      }
    }
  }
  
  XBEE.print("2");
  time_of_xbee.reset();
  while(time_of_xbee.check() == 0);
  MODULO_3G.flush();
  data_in_ = 0;
  time_of_xbee.reset();
  if(XBEE.available()>0){
    while(time_of_xbee.check() == 0){
      if(XBEE.available()>0){
        data_in_ = XBEE.read();
        MODULO_3G.print(data_in_);
        DEBUG.print(data_in_);
      }
      else{
        ;
      }
    }
    data_in_ = 0;
    time_request.reset();
    while(time_request.check() == 0){
      if(MODULO_3G.available()>0){
        data_in_ = MODULO_3G.read();
        XBEE.print(data_in_);
        DEBUG.print(data_in_);
      }
    }
  }
}

void ubidots_post_for_other_devices(){
  XBEE.print("1");
  time_of_xbee.reset();
  while(time_of_xbee.check() == 0);
  MODULO_3G.flush();
  time_of_xbee.reset();
  if(XBEE.available()>0){
    while(time_of_xbee.check() == 0){
      if(XBEE.available()>0){
        MODULO_3G.print(XBEE.read());
      }
      else{
        ;
      }
    }
    data_in_ = 0;
    time_request.reset();
    while(time_request.check() == 0){
      if(MODULO_3G.available()>0){
        data_in_ = MODULO_3G.read();
        XBEE.print(data_in_);
      }
    }
  }
  
  XBEE.print("2");
  time_of_xbee.reset();
  while(time_of_xbee.check() == 0);
  MODULO_3G.flush();
  data_in_ = 0;
  time_of_xbee.reset();
  if(XBEE.available()>0){
    while(time_of_xbee.check() == 0){
      if(XBEE.available()>0){
        data_in_ = XBEE.read();
        MODULO_3G.print(data_in_);
        DEBUG.print(data_in_);
      }
      else{
        ;
      }
    }
    data_in_ = 0;
    time_request.reset();
    while(time_request.check() == 0){
      if(MODULO_3G.available()>0){
        data_in_ = MODULO_3G.read();
        XBEE.print(data_in_);
        DEBUG.print(data_in_);
      }
    }
  }
}

/**
 * 
 * 
 */

int ubidots_request_for_control_slave(){
  String tmp = "GET /api/v1.6/devices/control-pozo/bomba/lv?token=BBFF-IH5I4OcjNkdFY6IAcKjnBhbdEThV8j";
  tmp += " HTTP/1.1\r\n";
  tmp += "HOST: things.ubidots.com\r\n";
  tmp += "\r\n";
  XBEE.flush();
  XBEE.print(tmp);
  //DEBUG.print(tmp);
  data_in_ = 0;
  time_request.reset();
  int count__ = 0;
  while(time_request.check() == 0){
    if(XBEE.available()>0){
      data_in_ = XBEE.read();
      //DEBUG.print(data_in_);
      bufferAnswer[count__] = data_in_;
      count__++;
    }
  }
  bufferAnswer[count__] = '\0';
  if(strstr(bufferAnswer, "\r\n1.0\r\n")){
    remote_output_0 = 1; // bomba ON
    DEBUG.println("Remote Bomba ON");
  }
  else{
    remote_output_0 = 0; // bomba OFF 
    DEBUG.println("Remote Bomba OFF");
  }
  tmp = "GET /api/v1.6/devices/sala-de-riego/variador-de-frecuencia/lv?token=BBFF-IH5I4OcjNkdFY6IAcKjnBhbdEThV8j";
  tmp += " HTTP/1.1\r\n";
  tmp += "HOST: things.ubidots.com\r\n";
  tmp += "\r\n";
  XBEE.flush();
  XBEE.print(tmp);
  //DEBUG.print(tmp);
  data_in_ = 0;
  time_request.reset();
  count__ = 0;
  while(time_request.check() == 0){
    if(XBEE.available()>0){
      data_in_ = XBEE.read();
      //DEBUG.print(data_in_);
      bufferAnswer[count__] = data_in_;
      count__++;
    }
  }
  bufferAnswer[count__] = '\0';
  const char delim[] = {'\r','\n','\0'};
  char *token;
  int largo = 0;
  token = strtok(bufferAnswer, delim);
  while(token != NULL){
    largo = strlen(token);
    //DEBUG.println(token);
    if(largo < 5){
      token = strtok(NULL, delim);
      //DEBUG.println(token);
      break;
    }
    token = strtok(NULL, delim);
  }
  freq = atof(token);
  if( (freq >= 30.0) && (freq <= 55.0) ){
    if( freq_prev != freq){
      DEBUG.print("registro : ");
      DEBUG.print(REG_RUN_FREQ);
      DEBUG.print("\tfreq : ");
      DEBUG.println(freq);
      set_freq_inverter(freq);
      freq_prev = freq;
    }
    request_http_ok = true;
  }
  return 0;
}

/**
 * 
 * 
 */

int ubidots_post_request_slave(){
  /**
   * @brief : Make a json object
   */
  String json = "";
  json += "[{";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"'; 
  json += "5a95a1eb642ab65a0e044acb"; // input_0 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_0;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae7448c642ab63fd1572cd8"; // input_1 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":";
  json += valor_1;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74498140c73367bbdc2cb"; // input_2 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":";
  json += valor_2;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae744a3642ab6400a4fb8d3"; // input_3 //ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_3;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae744ba642ab6405a5f6fd9"; // input_4 //ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_4;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae744d3642ab6405a5f6ff2"; // input_5 //ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_5;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae744d7642ab6400a4fb901"; // input_6 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_6;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74528642ab63fe4ff3e8a"; // input_7 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_7;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae7453b642ab6401d9ba59a"; // input_8 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_8;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74549642ab63fd1572ce8"; // input_9 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += valor_9;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5adb80c2642ab6033af94cd4"; // output_0 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_0;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5adb80c2642ab6033af94cd4"; // output_1 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_1;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74570642ab63fe4ff3e9b"; // output_2 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_2;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74585642ab63ff7ee6b6a"; // output_3 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_3;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae745c5642ab641db104d95"; // output_4 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_4;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74633642ab64201f4a89e"; // output_5 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_5;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74623642ab6419b4cb5cc"; // output_6 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_6;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74642140c73378db3a7e6"; // output_7 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_7;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae7464e642ab6419b4cb5d7"; // output_8 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_8;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ae74658642ab6419b4cb5d8"; // output_9 // ok
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += !status_salida_9;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5ada3c57642ab6080b6e4d29"; // conexion 3G
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += 1;
  json += "}]\r\n";

  /**
   * @brief : Concatenate HEAD (tmp) with json object
   */
  String tmp = "POST /api/v1.6/collections/values/?token=BBFF-IH5I4OcjNkdFY6IAcKjnBhbdEThV8j HTTP/1.1\r\n";
  tmp += "Host: things.ubidots.com\r\n";
  tmp += "Content-Type: application/json\r\n";
  tmp += "Content-Length: ";
  tmp += json.length();
  tmp += "\r\n";
  tmp += "\r\n";
  tmp += json;

  /**
   * @brief : Send request and stand by response
   */
  XBEE.flush();
  XBEE.print(tmp);
  //DEBUG.print(tmp);
  data_in_ = 0;
  time_request.reset();
  while(time_request.check() == 0){
    if(XBEE.available()>0){
      data_in_ = XBEE.read();
      //DEBUG.print(data_in_);
    }
  }
  //DEBUG.println();
  return 0;
}
