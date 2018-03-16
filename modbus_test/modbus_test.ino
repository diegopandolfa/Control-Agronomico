#include <avr/io.h>
#include <avr/interrupt.h>
#include <ModbusMaster.h>
#include <Metro.h>

#define PRESET_SINGLE_REGISTER 0x06
#define PRESET_MULT_REGISTER 0x10
#define REG_INV_RES 0x01
#define REG_RUN_FREQ 0x0D

Metro time_of_print_info = Metro(2000);
Metro time_of_reset_caudal = Metro(1000000);

ModbusMaster var_frec;
int address_var_frec = 0x01;
int freq = 0;
String tmp = "";

int pin_bomba = 24;
int pin_caudalimetro = 21;
volatile double waterFlow = 0;
volatile long time_prev = 0;
volatile long time_current = 0;
volatile long delta = 0;
volatile double delta_t = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // usb
  while(!Serial);
  Serial1.begin(115200); // xBee
  while(!Serial1);
  Serial2.begin(115200); // 3G
  while(!Serial2);
  Serial3.begin(9600, SERIAL_8E1); // ModBus  
  while(!Serial3);
  
  var_frec.begin(address_var_frec, Serial3);
  
  pinMode(pin_bomba,OUTPUT);
  cli();
  pinMode(pin_caudalimetro, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin_caudalimetro), pulse, RISING);  //DIGITAL Pin 2: Interrupt 0
  digitalWrite(pin_bomba, LOW);
  sei(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  tmp = "0";
  if(Serial3.available()>0){
    Serial.print("dato RTU: ");
    Serial.println(Serial3.read());  
  }
  if(Serial.available()>0){
    while(Serial.available()>0){
      char data = Serial.read();
      tmp += data;
    }
    Serial.println(tmp);
    if( tmp == "0ON" ){
      digitalWrite(pin_bomba, HIGH);
      Serial.println("BOMBA ON");
    }
    if( tmp == "0OFF" ){
      digitalWrite(pin_bomba, LOW);
      Serial.println("BOMBA OFF");
    }
    freq = atoi(tmp.c_str());
    if( (freq >=30) && (freq <= 55) ){
      freq *= 100;
      //var_frec.clearTransmitBuffer();
      Serial.print("registro : ");
      Serial.print(0x08);
      Serial.print("\tflag : ");
      Serial.println(0x02);
      var_frec.writeSingleRegister(0x08, 0x00); // dar partida
      delay(1000);
      Serial.print("registro : ");
      Serial.print(REG_RUN_FREQ);
      Serial.print("\tfreq : ");
      Serial.println(freq);
      var_frec.writeSingleRegister(REG_RUN_FREQ, freq);
    }
  }
  if(time_of_print_info.check()==1){
    Serial.println(waterFlow);
  }
  if(time_of_reset_caudal.check()==1){
    waterFlow = 0;
  }
  delay(100);
}

void pulse()   //measure the quantity of square wave
{
  cli();
  time_current = millis();
  delta = time_current - time_prev;
  delta_t = (delta/1000.0); // en segundos
  //Serial1.println(delta_t,4);
  waterFlow = 1000.0/(delta_t); //litros por segundos
  time_prev = time_current;
  time_of_reset_caudal.reset();
  sei();
}
