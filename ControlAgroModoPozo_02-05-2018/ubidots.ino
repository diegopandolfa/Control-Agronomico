int ubidots_requets_for_control(){
  String tmp = "GET /api/v1.6/devices/sala-de-riego/bomba/lv?token=BBFF-IH5I4OcjNkdFY6IAcKjnBhbdEThV8j";
  tmp += " HTTP/1.1\r\n";
  tmp += "HOST: things.ubidots.com\r\n";
  tmp += "\r\n";
  MODULO_3G.flush();
  MODULO_3G.print(tmp);
  DEBUG.print(tmp);
  data_in_ = 0;
  time_request.reset();
  int count__ = 0;
  while(time_request.check() == 0){
    if(MODULO_3G.available()>0){
      data_in_ = MODULO_3G.read();
      DEBUG.print(data_in_);
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
  DEBUG.print(tmp);
  data_in_ = 0;
  time_request.reset();
  count__ = 0;
  while(time_request.check() == 0){
    if(MODULO_3G.available()>0){
      data_in_ = MODULO_3G.read();
      DEBUG.print(data_in_);
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
    DEBUG.println(token);
    if(largo < 5){
      token = strtok(NULL, delim);
      DEBUG.println(token);
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
  json += "5af59999642ab650fcb3f789"; // input_0
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
  json += "5af599a5642ab650fcb3f78a"; // input_1
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
  json += "5af599ac642ab651132fa4c1"; // input_2
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
  json += "5af599c1642ab650bb136762"; // input_3
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
  json += "5af599cb642ab650bb136763"; // input_4
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
  json += "5af599d8642ab65134e9a85b"; // input_5
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
  json += "5af599f4642ab650bb136778"; // input_6
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
  json += "5af599fe642ab650a74b19e0"; // input_7
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
  json += "5af59a08642ab650bb136783"; // input_8
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
  json += "5af59a10642ab650bb136789"; // input_9
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
  json += "5af59a2f642ab65110b912ef"; // output_0
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += status_salida_0;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5af59a3d642ab650a74b19e1"; // output_1
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += status_salida_1;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5af59a47642ab650fcb3f7d7"; // output_2
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += status_salida_2;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5af59a54642ab650a74b19f6"; // output_3
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += status_salida_3;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5af59a5d642ab650fcb3f7de"; // output_4
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += status_salida_4;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5af59a65642ab65134e9a87e"; // output_5
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += status_salida_5;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5af59a74642ab65134e9a88a"; // output_6
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += status_salida_6;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5af59a81642ab65110b91318"; // output_7
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += status_salida_7;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5af59a8a642ab650fcb3f7f8"; // output_8
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += status_salida_8;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5af59a92642ab651ff110cd2"; // output_9
  json += '"';
  json += ", ";
  json += '"';
  json += "value";
  json += '"';
  json += ":"; 
  json += status_salida_9;
  json += "}, {";
  json += '"';
  json += "variable";
  json += '"';
  json += ": ";
  json += '"';
  json += "5af59ab6642ab65213a4266e"; // conexion 3G
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
  DEBUG.print(tmp);
  data_in_ = 0;
  time_request.reset();
  while(time_request.check() == 0){
    if(MODULO_3G.available()>0){
      data_in_ = MODULO_3G.read();
      DEBUG.print(data_in_);
    }
  }
  DEBUG.println();
}
