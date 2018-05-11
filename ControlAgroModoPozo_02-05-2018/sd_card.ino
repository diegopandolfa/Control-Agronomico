int sd_card_init(){
  DEBUG.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    DEBUG.println("Card failed, or not present");
    return -1;
  }
  DEBUG.println("card initialized.");
  return 0;
}

int load_sd_card_config(){
  /**
   * @brief : clean arrays.
   */
  for(int i=0; i<320; i++){
    for(int j=0; j<3; j++){
      inputs[i][j] = 0;
    }
  }
  for(int i=0; i<320; i++){
    for(int j=0; j<3; j++){
      outputs[i][j] = 0;
    }
  }
  /**
   * @brief : se abre el archivo y se cargan las configuraciones
   */
  //--------------------inputs---------------------//
  File myFile = SD.open("input.csv");
  String lines_input[320]; // 10 inputs for 32 devices
  String line = "";
  int count_line = 0;
  if (myFile) {
    DEBUG.println("input.csv:");
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      if(count_line >= 320) break; // number config overflow
      data_in_ = myFile.read();
      DEBUG.write(data_in_);
      line += data_in_;
      if(data_in_ == '\n'){
        lines_input[count_line] = line;
        count_line++;
        DEBUG.print("nueva linea!!! :\t");
        DEBUG.println(line);
        line = "";
      }
    }
    // close the file:
    myFile.close();
    for(int i=0; i<count_line; i++){
      token = (char *)lines_input[i].c_str();
      token = strtok(token, ",");
      int count_cols = 0;
      while(token != NULL){
        DEBUG.print(token);
        if(count_cols == 0){
          inputs[i][0] = atoi(token);
          count_cols++;
        }
        else if(count_cols == 1){
          inputs[i][1] = atoi(token);
          count_cols++;
        }
        else if(count_cols == 2){
          inputs[i][2] = atoi(token);
          count_cols++;
        }
        else if(count_cols == 3){
          inputs[i][3] = atof(token);
          count_cols++;
        }
        else{
          break;  
        }
        token = strtok(NULL, ",");
      } 
    }
  }
  else{
    DEBUG.println("archivo input.csv no encontrado");  
  }
  DEBUG.println("mostrando arreglo");
  for(int i=0; i<320; i++){
    for(int j=0; j<4; j++){
      DEBUG.print(inputs[i][j]);
      DEBUG.print(",");  
    }
    DEBUG.println();
  }
  //------------- end inputs ----------------//

  //--------------------outputs---------------------//
  myFile = SD.open("output.csv");
  String lines_output[320]; // 10 inputs for 32 devices
  line = "";
  count_line = 0;
  if (myFile) {
    DEBUG.println("output.csv:");
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      if(count_line >= 320) break; // number config overflow
      data_in_ = myFile.read();
      DEBUG.write(data_in_);
      line += data_in_;
      if(data_in_ == '\n'){
        lines_output[count_line] = line;
        count_line++;
        DEBUG.print("nueva linea!!! :\t");
        DEBUG.println(line);
        line = "";
      }
    }
    // close the file:
    myFile.close();
    for(int i=0; i<count_line; i++){
      token = (char *)lines_output[i].c_str();
      token = strtok(token, ",");
      int count_cols = 0;
      while(token != NULL){
        if(count_cols == 0){
          outputs[i][0] = atoi(token);
          count_cols++;
        }
        else if(count_cols == 1){
          outputs[i][1] = atoi(token);
          count_cols++;
        }
        else if(count_cols == 2){
          outputs[i][2] = atoi(token);
          count_cols++;
        }
        else if(count_cols == 3){
          outputs[i][3] = atoi(token);
          count_cols++;
        }
        else{
          break;  
        }
        token = strtok(NULL, ",");
      } 
    }
  }
  else{
    DEBUG.println("archivo output.csv no encontrado");  
  }
  DEBUG.println("mostrando arreglo");
  for(int i=0; i<320; i++){
    for(int j=0; j<4; j++){
      DEBUG.print(outputs[i][j]);
      DEBUG.print(",");  
    }
    DEBUG.println();
  }
  //------------- end outputs ----------------//

  //--------------------system---------------------//
  myFile = SD.open("system.csv");
  String lines_system[2]; // 10 inputs for 32 devices
  line = "";
  count_line = 0;
  if (myFile) {
    DEBUG.println("system.csv:");
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      if(count_line >= 2) break; // number config overflow
      data_in_ = myFile.read();
      DEBUG.write(data_in_);
      line += data_in_;
      if(data_in_ == '\n'){
        lines_system[count_line] = line;
        count_line++;
        DEBUG.print("nueva linea!!! :\t");
        DEBUG.println(line);
        line = "";
      }
    }
    // close the file:
    myFile.close();
    for(int i=0; i<count_line; i++){
      token = (char *)lines_system[i].c_str();
      token = strtok(token, ",");
      int count_cols = 0;
      while(token != NULL){
        if(count_cols == 0){
          device_id = atoi(token);
          DEBUG.print("device_id:\t");
          DEBUG.println(device_id);
          count_cols++;
        }
        else if(count_cols == 1){
          msio = atoi(token);
          DEBUG.print("msio:\t");
          DEBUG.println(msio);
          count_cols++;
        }
        else if(count_cols == 2){
          peakTime_enable = atoi(token);
          DEBUG.print("peakTime:\t");
          DEBUG.println(peakTime_enable);
          count_cols++;
        }
        else{
          break;  
        }
        token = strtok(NULL, ",");
      } 
    }
  }
  //------------- end system ----------------//
  return 0;
}

int system_datalogg(){
  if(time_of_log.check() == 1){
    dataString = "";
    dataString += current_time;
    dataString += ",";
    dataString += valor_0;
    dataString += ",";
    dataString += valor_1;
    dataString += ",";
    dataString += valor_2;
    dataString += ",";
    dataString += valor_3;
    dataString += ",";
    dataString += valor_4;
    dataString += ",";
    dataString += valor_5;
    dataString += ",";
    dataString += valor_6;
    dataString += ",";
    dataString += valor_7;
    dataString += ",";
    dataString += valor_8;
    dataString += ",";
    dataString += valor_9;
    dataString += ",";
    dataString += status_salida_0;
    dataString += ",";
    dataString += status_salida_1;
    dataString += ",";
    dataString += status_salida_2;
    dataString += ",";
    dataString += status_salida_3;
    dataString += ",";
    dataString += status_salida_4;
    dataString += ",";
    dataString += status_salida_5;
    dataString += ",";
    dataString += status_salida_6;
    dataString += ",";
    dataString += status_salida_7;
    dataString += ",";
    dataString += status_salida_8;
    dataString += ",";
    dataString += status_salida_9;
    dataString += ",";
    dataString += (status_salida_0 == 1)?("ON "):("OFF");
    dataString += ",";
    dataString += caudal;
    dataString += ",";
    dataString += freq;
    dataString += ",";
    dataString += (request_http_ok == true)?("OK  "):("FAIL");
    dataString += ",";
    dataString += (enable_var_frec == true)?("ALTO"):("BAJO");
    dataString += '\n';
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      DEBUG.println(dataString);
    }  
    // if the file isn't open, pop up an error:
    else {
      DEBUG.println("error opening datalog.txt");
    }
  }
  else{
    return 0;  
  }
  return 0;
}
