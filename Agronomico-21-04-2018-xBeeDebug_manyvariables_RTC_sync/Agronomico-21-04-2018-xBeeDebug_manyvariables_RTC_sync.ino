#include <SD.h>
#include <SPI.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <Metro.h>
#include <TimerOne.h>
#include <ModbusMaster.h>
#include <TimeLib.h>

#define REG_INV_RES 0x01
#define REG_RUN_FREQ 0x0D
#define XBEE Serial1

ModbusMaster var_frec;
int address_var_frec = 0x01;
double freq = 0;
int freq_prev = 0;
bool bomba_on = false;
bool enable_var_frec = false;
int PIN_GPIO_1 = 16;
int PIN_GPIO_2 = 15;
int PIN_GPIO_3 = 14;
int PIN_GPIO_4 = 13;
int GPIO_1 = 0; // auto_internet
int GPIO_2 = 0; // nivel_agua_potable
int GPIO_3 = 0; // relé de nivel pozo
int GPIO_4 = 0; // manual
bool auto_internet = false;
bool casa_patronal = false;
bool flag_flujo = false;

Metro time_request = Metro(3500);
//Metro time_of_reset_caudal = Metro(40*1000); // 40 segundos
//Metro time_of_caudal = Metro(1000);
char bufferAnswer[2048];
char *pEnd;
char *pStart;
int counter = 0;
int valueSensor;

int pin_bomba = 24;
int pin_caudalimetro = 21;
volatile long waterFlow = 0;
volatile double caudal = 0;
volatile long time_prev = 0;
volatile long time_current = 0;
volatile long delta = 0;
volatile double delta_t = 0;
int count = 0;
int count_pulse = 0;
volatile int sensor_value = 0;

LiquidCrystal_I2C lcd(0x3F,20,4);
bool flag_func = true;
bool request_http_ok = false;
bool hora_punta = false;

const int chipSelect = BUILTIN_SDCARD;
String dataString = "";

Metro time_of_log = Metro(1000*60); // 1 minuto

time_t current_time;
char *day_ = NULL;
char *month_ = NULL;
char *year_ = NULL;
char *hour_ = NULL;
char *minute_ = NULL;
char *second_ = NULL;

int anno = 0;
int mes = 0;
int dia = 0;
int hora = 0;
int minuto = 0;
int segundo = 0;

void setup()  
{
  current_time = Teensy3Clock.get();
  hora = (((current_time%31540000)%2628000)%86400)/3600;
  minuto = ((((current_time%31540000)%2628000)%86400)%3600)/60;
  segundo = ((((current_time%31540000)%2628000)%86400)%3600)%60;
  if(hora >= 17 && hora <= 23){
    hora_punta = true;  
  }
  else{
    hora_punta = false;  
  }
  pinMode(PIN_GPIO_1, INPUT); // K1 selector externo internet
  pinMode(PIN_GPIO_2, INPUT); // K2 contancto bomba agua potable
  pinMode(PIN_GPIO_3, INPUT); // Relé Nivel
  pinMode(PIN_GPIO_4, INPUT); // Manual
  pinMode(6, OUTPUT); // enable del RS485
  delay(1);
  digitalWrite(6, HIGH);
//  Serial.begin(115200); // teensy
//  while(!Serial);
  lcd.init();
  delay(100);
  lcd.backlight();
  lcd.clear();
  lcd.print("IEH INGENIERIA SPA");
  lcd.setCursor(0,1);
  lcd.print("IZARO PRINCIPAL");
  lcd.setCursor(0,2);
  lcd.print("POZO 3");
  delay(5000); 
  Serial.begin(115200); // debug
  XBEE.begin(115200); // xBee
  while(!XBEE);
  Serial2.begin(115200); // 3g
  while(!Serial2);
  pinMode(pin_bomba,OUTPUT);
  Serial3.begin(9600, SERIAL_8E1); // ModBus  
  while(!Serial3);

  var_frec.begin(address_var_frec, Serial3);
  
  waterFlow = 0;
  cli();
  pinMode(pin_caudalimetro, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(pin_caudalimetro), pulse, FALLING);  //DIGITAL Pin 2: Interrupt 0
  Timer1.initialize(10*1000); // 10 ms
  Timer1.attachInterrupt(pulse);
  sei();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Inicializando");
  lcd.setCursor(0, 2);
  lcd.print("...");
  delay(10000);
  //lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print("ok, empecemos!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("sincronizando RTC");
  lcd.setCursor(0,1);
  lcd.print("...");

  String tmp = "HEAD /api/v1.6";
  tmp += " HTTP/1.1\r\n";
  tmp += "HOST: things.ubidots.com\r\n";
  tmp += "Connection: close\r\n";
  tmp += "\r\n";
  delay(10000);
  Serial2.flush();
  Serial2.print(tmp);
  Serial1.print(tmp);
  char data_in_ = 0;
  Metro time_request_rtc = Metro(20000);
  time_request_rtc.reset();
  int count__ = 0;
  while(time_request_rtc.check() == 0){
    if(Serial2.available()>0){
      data_in_ = Serial2.read();
      Serial1.print(data_in_);
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
    Serial1.println(token);
    if(largo > 32){
      //token = strtok(NULL, delim);
      Serial1.println(token);
      token = strtok(token, " ");
      token = strtok(NULL, " ");
      token = strtok(NULL, " ");
      count__ = 0;
      while(token != NULL){
        largo = strlen(token);
        Serial1.println(token);
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
          Serial1.println(token);
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
            Serial1.println(token);
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
      Serial1.print("fecha y hora:\t");
      Serial1.print(day_);
      Serial1.print("/");
      Serial1.print(month_);
      Serial1.print("/");
      Serial1.print(year_);
      Serial1.print(" ");
      Serial1.print(hour_);
      Serial1.print(":");
      Serial1.print(minute_);
      Serial1.print(":");
      Serial1.println(second_);
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
  Serial1.print("fecha y hora:\t");
  Serial1.print(dia);
  Serial1.print("/");
  Serial1.print(mes);
  Serial1.print("/");
  Serial1.print(anno);
  Serial1.print(" ");
  Serial1.print(hora);
  Serial1.print(":");
  Serial1.print(minuto);
  Serial1.print(":");
  Serial1.println(segundo);

  TimeElements tm;
  tm.Second = segundo;
  tm.Minute = minuto;
  tm.Hour = hora;
  tm.Day = dia;
  tm.Month = mes;
  tm.Year = anno - 1970;

  time_t t = makeTime(tm);
  Serial1.println(t);
  if(t != 0){
    Teensy3Clock.set(t);
    setTime(t);
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("bomba:");
  lcd.setCursor(0,1);
  lcd.print("flujo:");
  lcd.setCursor(0,2);
  lcd.print("3G:");
  lcd.setCursor(0,3);
  lcd.print("Nivel:");
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
  }
  Serial.println("card initialized.");
}

void loop()
{
  current_time = Teensy3Clock.get();
  Serial.println(current_time);
  hora = (((current_time%31536000)%2592000)%86400)/3600;
  minuto = ((((current_time%31536000)%2592000)%86400)%3600)/60;
  segundo = ((((current_time%31536000)%2592000)%86400)%3600)%60;
  if(hora >= 17 && hora <= 23){
    hora_punta = true;  
  }
  else{
    hora_punta = false;  
  }
  //request_http_ok = false;
  String entradas = "Entradas: \t";
  entradas += GPIO_1;
  entradas += "\t";
  entradas += GPIO_2;
  entradas += "\t";
  entradas += GPIO_3;
  entradas += "\t";
  entradas += GPIO_4;
  Serial1.println(entradas);
  if(GPIO_3 == LOW){ // si hay agua
    enable_var_frec = true;
    if(GPIO_4 == LOW){ // si se enciende manual
      bomba_on = true;
      auto_internet = false;
    }
    else if(GPIO_1 == LOW){ // si se enciende auto_inernet
      auto_internet = true;
      if(GPIO_2 == LOW){ // si pide agua la casa patronal
        bomba_on = true;
        casa_patronal = true;
      }
      else {
        bomba_on = false;
        casa_patronal = false;
      }
    }
    else{ // OFF
      bomba_on = false;
      auto_internet = false;
      casa_patronal = false;
    }
  }
  else { // no hay agua en el pozo
    bomba_on = false;
    enable_var_frec = false;
  }
  static int state = 3; 
  switch(state){
    case 1:
    {
      if(ModemON() == HIGH){
        state = 2;
      }
    break;
    }
    case 2:
    {
      if(ModemConnect() == 7){
        state = 3;
      }
    break;
    }
    case 3:
    {
/*      String tmp = "GET /api/postvalue?token=BBFF-IH5I4OcjNkdFY6IAcKjnBhbdEThV8j&variable=5a958eab642ab64d1917e943&value=";
      tmp += caudal;
      tmp += " HTTP/1.1 \r\n";
      tmp += "HOST: translate.ubidots.com\r\n";
      tmp += "\r\n";
      Serial2.print(tmp);
      Serial1.print(tmp);
*///      Serial2.flush();
//      if(SendCommand("AT#SD=1,0,80,things.ubidots.com,0,0,0","CONNECT", 8000, HIGH) == '1'){
/*        String tmp = "GET /api/v1.6/devices/sala-de-riego/bomba/?token=BBFF-IH5I4OcjNkdFY6IAcKjnBhbdEThV8j";
        tmp += " HTTP/1.1\r\n";
        tmp += "HOST: things.ubidots.com\r\n";
        tmp += "\r\n";
        
*/      String caudal__ = "";
        caudal__ += caudal;
        int largo_del_json = 157 + caudal__.length();
        largo_del_json += (enable_var_frec == true)?(3):(1);
        Serial1.println(largo_del_json);
        String tmp = "POST /api/v1.6/collections/values/?token=BBFF-IH5I4OcjNkdFY6IAcKjnBhbdEThV8j HTTP/1.1\r\n";
        tmp += "Host: things.ubidots.com\r\n";
        tmp += "Content-Type: application/json\r\n";
        tmp += "Content-Length: ";
        tmp += largo_del_json;
        tmp += "\r\n";
        tmp += "\r\n";
        tmp += "[{";
        tmp += '"';
        tmp += "variable";
        tmp += '"';
        tmp += ": ";
        tmp += '"'; //15
        tmp += "5a958eab642ab64d1917e943"; // 24
        tmp += '"';
        tmp += ", ";
        tmp += '"';
        tmp += "value";
        tmp += '"';
        tmp += ":"; // 50
        tmp += caudal;
        tmp += "}, {";
        tmp += '"';
        tmp += "variable";
        tmp += '"';
        tmp += ": ";
        tmp += '"';
        tmp += "5a95a1eb642ab65a0e044acb";
        tmp += '"';
        tmp += ", ";
        tmp += '"';
        tmp += "value"; //100
        tmp += '"';
        tmp += ":";
        tmp += (enable_var_frec == true)?(100):(0);
        tmp += "}, {";
        tmp += '"';
        tmp += "variable";
        tmp += '"';
        tmp += ": ";
        tmp += '"';
        tmp += "5ada3c57642ab6080b6e4d29";
        tmp += '"';
        tmp += ", ";
        tmp += '"';
        tmp += "value";
        tmp += '"';
        tmp += ":";
        tmp += (request_http_ok == true)?(1):(0);
        tmp += "}]\r\n"; //56
        Serial2.flush();
        Serial2.print(tmp);
        Serial1.print(tmp);
        //delay(1000);
        char data_in_ = 0;
        request_http_ok = false;
        time_request.reset();
        while(time_request.check() == 0){
          if(Serial2.available()>0){
            data_in_ = Serial2.read();
            Serial1.print(data_in_);
          }
        }
        Serial1.println();
        //Serial2.flush();
        if( (auto_internet == true) && (enable_var_frec == true) ){
        tmp = "GET /api/v1.6/devices/sala-de-riego/bomba/lv?token=BBFF-IH5I4OcjNkdFY6IAcKjnBhbdEThV8j";
        tmp += " HTTP/1.1\r\n";
        tmp += "HOST: things.ubidots.com\r\n";
        tmp += "\r\n";
        Serial2.flush();
        Serial2.print(tmp);
        Serial1.print(tmp);
        //delay(1000);
        data_in_ = 0;
        time_request.reset();
        int count__ = 0;
        while(time_request.check() == 0){
          if(Serial2.available()>0){
            data_in_ = Serial2.read();
            Serial1.print(data_in_);
            bufferAnswer[count__] = data_in_;
            count__++;
          }
        }
        bufferAnswer[count__] = '\0';
        if(strstr(bufferAnswer, "\r\n1.0\r\n")){
          if(bomba_on == false){
            bomba_on = true;
            //var_frec.writeSingleRegister(0x08, 0x02); // dar partida
          }
          Serial1.println("Bomba ON");
        }
        else{
          if(bomba_on == true){
            if(casa_patronal == false){
              bomba_on == false;
              Serial1.println("Bomba OFF");
            }
            else{
              bomba_on = true;
              Serial1.println("Bomba ON");  
            }
            //var_frec.writeSingleRegister(0x08, 0x00); // parar 
          }
          else{
            bomba_on = false;  
          } 
        }
        tmp = "GET /api/v1.6/devices/sala-de-riego/variador-de-frecuencia/lv?token=BBFF-IH5I4OcjNkdFY6IAcKjnBhbdEThV8j";
        tmp += " HTTP/1.1\r\n";
        tmp += "HOST: things.ubidots.com\r\n";
        tmp += "\r\n";
        Serial2.flush();
        Serial2.print(tmp);
        Serial1.print(tmp);
        //delay(1000);
        data_in_ = 0;
        time_request.reset();
        count__ = 0;
        while(time_request.check() == 0){
          if(Serial2.available()>0){
            data_in_ = Serial2.read();
            Serial1.print(data_in_);
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
          Serial1.println(token);
          if(largo < 5){
            token = strtok(NULL, delim);
            Serial1.println(token);
            break;
          }
          token = strtok(NULL, delim);
        }
        freq = atof(token);
        if( (freq >=30) && (freq <= 55) ){
          int freq__ = freq*100;
          if( freq_prev != freq__){
            Serial1.print("registro : ");
            Serial1.print(REG_RUN_FREQ);
            Serial1.print("\tfreq : ");
            Serial1.println(freq__);
            var_frec.writeSingleRegister(REG_RUN_FREQ, freq__);
            freq_prev = freq__;
          }
          request_http_ok = true;
        }
        }
        else{
          if(bomba_on == true){
            bomba_on = false;
            var_frec.writeSingleRegister(0x08, 0x00); // parar 
          }  
        }
        delay(1);
//      }
      state = 3;
      break;
    }
    
    case 4:
    {
      if(CloseServer() == HIGH){
        state = 2;
      }
      else {
        state = 3;
      }
      break;
    }
  }
  if(bomba_on == true && hora_punta == false){
    var_frec.writeSingleRegister(0x08, 0x02); // dar partida
    Serial1.println("encendiendo bomba");
  }
  else{
    Serial1.println("parando bomba");
    var_frec.writeSingleRegister(0x08, 0x00); // parar
    bomba_on = false;
  }
  Serial1.print("state:");
  Serial1.println(state);
  Serial1.print("Valor del sensor: ");
  Serial1.println(caudal,4);
  Serial1.println(waterFlow);
  String tmp_lcd = "";
  tmp_lcd += (bomba_on == true)?("ON "):("OFF");
  tmp_lcd += " @";
  tmp_lcd += freq_prev;
  lcd.setCursor(8,0);
  lcd.print(tmp_lcd);
  lcd.setCursor(8,1);
  tmp_lcd = "";
  tmp_lcd += caudal;
  lcd.print(tmp_lcd);
  lcd.setCursor(8,2);
  tmp_lcd = (request_http_ok == true)?("OK  "):("FAIL");
  tmp_lcd += "  @";
  if(hora < 10){
    tmp_lcd += "0";
    tmp_lcd += hora; 
  }
  else {
    tmp_lcd += hora;  
  }
  tmp_lcd += ":";
  if(minuto < 10){
    tmp_lcd += "0";
    tmp_lcd += minuto; 
  }
  else {
    tmp_lcd += minuto;  
  }
  lcd.print(tmp_lcd);
  /*char d = 0;
  if(SendCommand("+++","OK", 3000, HIGH) == '1'){
    SendCommand("ATDB\r\n","0", 2000, LOW);
    while(Serial2.available()>0){
      d = Serial2.read();
      tmp_lcd += d;
      delay(100);
    }
    lcd.print(tmp_lcd);
    lcd.setCursor(15,2);
    if(SendCommand("ATAI\r\n","OK", 2000, HIGH) == '1'){
      lcd.print("CON  ");
    }
    else{
      lcd.print("DIS  ");  
    }
    SendCommand("ATCN\r\n","OK", 2000, HIGH);
  }
  else{
    lcd.setCursor(8,2);
    lcd.print("            ");
  }*/
  lcd.setCursor(8,3);
  tmp_lcd = "";
  if(flag_func){
    tmp_lcd += (enable_var_frec == true)?("ALTO       *"):("BAJO       *");
  }
  else{
    tmp_lcd += (enable_var_frec == true)?("ALTO        "):("BAJO        ");
  }
  flag_func = !flag_func;
  lcd.print(tmp_lcd);
  Serial.print(hora);
  Serial.print(":");
  Serial.println(minuto);
  if(time_of_log.check() == 1){
    dataString = "";
    dataString += current_time;
    dataString += ",";
    dataString += (bomba_on == true)?("ON "):("OFF");
    dataString += ",";
    dataString += caudal;
    dataString += ",";
    dataString += (request_http_ok == true)?("OK  "):("FAIL");
    dataString += ",";
    dataString += (enable_var_frec == true)?("ALTO"):("BAJO");
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      Serial.println(dataString);
    }  
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error opening datalog.txt");
    }
  }
}

// ----------------------------------
boolean ModemON()
{ 
  boolean onState;
  delay(1000);
  if(SendCommand("AT", "OK", 10000, HIGH) == '1')
  {
    Serial1.println("Modem ON");
    onState = HIGH;
  }
  else
  {
    Serial1.println("Modem OFF");
    onState = LOW;
  }  
  return onState;  
}

// ----------------------------------
int ModemConnect()
{
  static int var = 1;
  int state = 1;
  
  switch (var) 
  {
    case 1:
      Serial1.println();
      Serial1.print("Echo off ");
      if(SendCommand("ATE0","OK", 5000, HIGH) == '1')
      {
        var = 2;
      }
      clearBuff(bufferAnswer);
    break;
      
    case 2:
      Serial1.println();
      Serial1.print("AT command ");
      if(SendCommand("AT","OK", 5000, HIGH) == '1')
      {
        var = 3;
      }
      clearBuff(bufferAnswer);
    break;
      
    case 3:
      Serial1.println();
      Serial1.print("Set APN ");
      if(SendCommand("AT+CGDCONT=1,\"IP\",\"bam.entelpcs.cl\"","OK", 8000, HIGH) == '1')  // AT+CGDCONT=1,"IP","web.tmovil.cl"
      {
        var = 4;
      }
      clearBuff(bufferAnswer);
    break;
      
    case 4:
      Serial1.println();
      Serial1.print("Network connecting ");
      if(SendCommand("AT#SGACT=1,1","#SGACT:", 8000, HIGH) == '1')
      {
        var = 5;
      }
      clearBuff(bufferAnswer);
    break;
      
    case 5:
      Serial1.println();
      Serial1.print("No flow control ");
      if(SendCommand("AT&K0","OK", 5000, HIGH) == '1')
      {
        var = 6;
      }
      clearBuff(bufferAnswer);
    break;
      
    case 6:
      Serial1.println();
      Serial1.print("Coonnecting Server ");
 //     if(SendCommand("AT#SD=1,0,80,translate.ubidots.com,0,0,0","CONNECT", 8000, HIGH) == '1') // Conectar al server TCP indicando puerto e IP
      if(SendCommand("AT#SD=1,0,80,industrial.ubidots.com,0,0,0","CONNECT", 8000, HIGH) == '1')
      {
        //9012 puerto
        var = 6;
        state = 7;
      }
      clearBuff(bufferAnswer);
    break;
      
    default: 
    break;
      // if nothing else matches, do the default
      // default is optional
  }
  
  return state;
}

// ----------------------------------
void clearBuff(char *dirBuff)
{
  *dirBuff = '\0';
}

boolean CloseServer()
{
  boolean onState = LOW;
  Serial2.print("+++"); 
  delay(3000);
  if(SendCommand("AT#SH=1", "OK", 1000, HIGH) == '1')
  {
    onState == HIGH;
  }
  else
  {
    onState == LOW;    
  }
}

// ----------------------------------
char SendCommand(char *command, char *ack, unsigned long time, boolean resp) // resp HIGH, espera respuesta
{
  char *pTemptBuff = bufferAnswer;
  unsigned long timeOut = millis() + time;
  char rCode = '0';
  
  Serial2.flush();
  Serial2.println(command); 
  Serial1.println(command);  // solo debug
  
  if(resp == HIGH)
  {    
    do
      {
        if(Serial2.available() > 0)
          {
            char dataIn = Serial2.read();
            Serial1.print(dataIn);
            if(pTemptBuff < (bufferAnswer + sizeof(bufferAnswer))-1)
            {
              *(pTemptBuff++) = dataIn;
              *pTemptBuff = '\0';
              timeOut = millis() + time;
              if(strstr(bufferAnswer, ack))
              {
                rCode = '1';
                break;
              }
            }
            else
            {
              pTemptBuff = bufferAnswer;
            }
          }
      }while(timeOut > millis());
  }
  
  if(timeOut < millis())
    {
      rCode = '2';
      Serial1.println("  Time out");
    } 
  //Serial.println(rCode,DEC);   // solo debug
  return rCode;
}

void pulse()   //measure the quantity of square wave
{
  cli();
  count_pulse++;
  //time_of_reset_caudal.reset();
  sensor_value = ( analogRead(pin_caudalimetro)*0.1 + sensor_value*(1-0.1) );
  if( (sensor_value <= 100 ) && (flag_flujo == false) ){
    waterFlow += 1;
    flag_flujo = true;
  }
  else if(sensor_value >=700){
    waterFlow = waterFlow;
    flag_flujo = false;  
  }
  else{
     waterFlow = waterFlow;
    flag_flujo = flag_flujo; 
  }
  if(count_pulse >= 18000){
    caudalimetro();
    count_pulse = 0;
  }
  GPIO_1 = digitalRead(PIN_GPIO_1);
  GPIO_2 = digitalRead(PIN_GPIO_2);
  GPIO_3 = digitalRead(PIN_GPIO_3);
  GPIO_4 = digitalRead(PIN_GPIO_4);
  sei();
}

void caudalimetro(){
    cli();
    caudal = (waterFlow*10.0/18.0);
    waterFlow = 0;
    sei();
}

void bomba(){

}
