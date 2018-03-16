#include <avr/io.h>
#include <avr/interrupt.h>
#include <Metro.h>
#include <TimerOne.h>
#include <ModbusMaster.h>

#define REG_INV_RES 0x01
#define REG_RUN_FREQ 0x0D

ModbusMaster var_frec;
int address_var_frec = 0x01;
double freq = 0;
int freq_prev = 0;
bool bomba_on = false;

Metro time_request = Metro(8000);
Metro time_of_reset_caudal = Metro(2000);
Metro time_of_caudal = Metro(1000);
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

void setup()  
{
  Serial1.begin(115200); // xBee
  while(!Serial1);
  Serial2.begin(115200); //3g
  while(!Serial2);
  pinMode(pin_bomba,OUTPUT);
  Serial3.begin(9600, SERIAL_8E1); // ModBus  
  while(!Serial3);

  var_frec.begin(address_var_frec, Serial3);
  
  waterFlow = 0;
  cli();
  pinMode(pin_caudalimetro, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin_caudalimetro), pulse, FALLING);  //DIGITAL Pin 2: Interrupt 0
  Timer1.initialize(1000*1000*60); // 60 segundos
  Timer1.attachInterrupt(caudalimetro);
  sei();
  Serial1.println("Hola");
}

void loop()
{
  static int state = 1; 
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
        int largo_del_json = 13 + caudal__.length();
        Serial1.println(largo_del_json);
        String tmp = "POST /api/v1.6/variables/5a958eab642ab64d1917e943/values/?token=BBFF-IH5I4OcjNkdFY6IAcKjnBhbdEThV8j HTTP/1.1\r\n";
        tmp += "Host: things.ubidots.com\r\n";
        tmp += "Content-Type: application/json\r\n";
        tmp += "Content-Length: ";
        tmp += largo_del_json;
        tmp += "\r\n";
        tmp += "\r\n";
        tmp += "{";
        tmp += '"';
        tmp += "value";
        tmp += '"';
        tmp += ": ";
        tmp += '"';
        tmp += caudal;
        tmp += '"';
        tmp += "}\r\n";
        Serial2.flush();
        Serial2.print(tmp);
        Serial1.print(tmp);
        //delay(1000);
        char data_in_ = 0;
        time_request.reset();
        while(time_request.check() == 0){
          if(Serial2.available()>0){
            data_in_ = Serial2.read();
            Serial1.print(data_in_);
          }
        }
        //Serial2.flush();
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
            var_frec.writeSingleRegister(0x08, 0x02); // dar partida
          }
          Serial1.println("Bomba ON");
        }
        else{
          if(bomba_on == true){
            bomba_on == false;
            var_frec.writeSingleRegister(0x08, 0x00); // parar 
          }
          Serial1.println("Bomba OFF"); 
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
  
  Serial1.print("state:");
  Serial1.println(state);
  Serial1.print("Valor del sensor: ");
  Serial1.println(caudal,4);
  Serial1.println(waterFlow);
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
  time_of_reset_caudal.reset();
  waterFlow += 1;
  sei();
}

void caudalimetro(){
    cli();
    caudal = (waterFlow*0.002*(0.125) + caudal*(1-0.125));
    waterFlow = 0;
    sei();
}

void bomba(){

}
