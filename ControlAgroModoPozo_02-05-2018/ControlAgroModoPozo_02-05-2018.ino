////////////////////////////////////////////////////////////////////////
//                                                                    //
//  @project    : Control Agronomico                                  //
//  @version    : 1.3                                                 //
//  @company    : IEH Electricidad SpA                                //
//  @client     : Matias Valladares                                   //
//  @developed  : Tectronix SpA                                       //
//  @author     : Diego Pandolfa                                      //
//  @date       : Apr, 2018                                           //
//  @description  : Firmware desarrollado para el uso exclusivo en    //
//                  modo pozo con el DevKit Teensy 3.5 basado en el   //
//                  microccontrolador NXP Kinnetics MK64FX512VMD12    //
//                  con la arquitectura ARM Cortex M4F; y con la      //
//                  placa desarrollada en la iteracion 1.3            //
//  @brief  : -Reconoce pozo seco (contacto NO de rele de nivel).     //
//            -Reconoce acumulador casa patronal ('').                //
//            -Reconoce funcionamiento en modo automatico (3G).       //
//            -Reconoce funcionamiento en modo manual.                //
//            -Reconoce horario punta.                                //
//            -Comunicacion EIA-RS485 con Protocolo Modbus con        //
//            variador de frecuencia Mitsubishi F-800.                //
//            -Comunicacion inalámbrica (modulo 3G) con nube IoT      //
//            Ubidots.com.                                            //
//            -Comunicación xBee STAR DIGIMESH con otros dispositivos.//
//            -datalogg en SD Card.                                   //
//            -RTC sincronizado con la nube IoT.                      //
//            -entre otros ...                                        //
////////////////////////////////////////////////////////////////////////
/**
 * @brief : cabeceras para la administracion de la SD Card.
 */
#include <SD.h>
#include <SPI.h>

/**
 * @brief : cabeceras para la administracion del display
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/**
 * @brief : cabeceras para el manejo de interrupciones
 */
#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * @brief : cabeceras para el uso de "timers" por software
 */
#include <Metro.h>

/**
 * @brief : cabecera para el manejo de interrupciones por timer
 */
#include <TimerOne.h>

/**
 * @brief : cabecera para el manejo del EIA-RS485 con el protocolo Modbus
 */
#include <ModbusMaster.h>

/**
 * @brief : cabecera para el manejo del RTC del teensy
 */
#include <TimeLib.h>

/**
 * @brief : definicion de macros utiles para el programa
 */
#define REG_INV_RES   0x01 // registro RESET of F800
#define REG_RUN_FREQ  0x0D // registro RUN freq of F800
#define REG_RUN       0x08 // registro RUN
#define START_INV     0x02 // start inverter
#define STOP_INV      0x00 // stop inverter

#define DEBUG Serial  // cable USB
#define XBEE Serial1  // modulo DIGI xBee Pro S2C ZigBee
#define MODULO_3G Serial2 // modulo DIGI 3G xBee Cellular 
#define RS485 Serial3 // hardware embedded on board

/**
 * @brief : definicion de pines del teensy asignados a las salidas optoacopladas y transistorisadas
 */
#define PIN_SALIDA_0  2
#define PIN_SALIDA_1  5
#define PIN_SALIDA_2  11
#define PIN_SALIDA_3  12
#define PIN_SALIDA_4  24
#define PIN_SALIDA_5  25
#define PIN_SALIDA_6  26
#define PIN_SALIDA_7  27
#define PIN_SALIDA_8  28
#define PIN_SALIDA_9  29

/**
 * @brief : asignacion por defecto
 */
int pin_salida_0 = PIN_SALIDA_0;
int pin_salida_1 = PIN_SALIDA_1;
int pin_salida_2 = PIN_SALIDA_2;
int pin_salida_3 = PIN_SALIDA_3;
int pin_salida_4 = PIN_SALIDA_4;
int pin_salida_5 = PIN_SALIDA_5;
int pin_salida_6 = PIN_SALIDA_6;
int pin_salida_7 = PIN_SALIDA_7;
int pin_salida_8 = PIN_SALIDA_8;
int pin_salida_9 = PIN_SALIDA_9;

/**
 * @brief : variables que guardan el status de las salidas.
 */
int status_salida_0 = 0;
int status_salida_1 = 0;
int status_salida_2 = 0;
int status_salida_3 = 0;
int status_salida_4 = 0;
int status_salida_5 = 0;
int status_salida_6 = 0;
int status_salida_7 = 0;
int status_salida_8 = 0;
int status_salida_9 = 0;
int status_salida_10 = 0;

int remote_output_0 = 0;
int remote_output_1 = 0;
int remote_output_2 = 0;
int remote_output_3 = 0;
int remote_output_4 = 0;
int remote_output_5 = 0;
int remote_output_6 = 0;
int remote_output_7 = 0;
int remote_output_8 = 0;
int remote_output_9 = 0;
/**
 * @brief : definicion y asignacion por defecto de pines de entrada.
 */

#define PIN_ENTRADA_ANALOGA_0 23
#define PIN_ENTRADA_ANALOGA_1 22
#define PIN_ENTRADA_ANALOGA_2 21
#define PIN_ENTRADA_ANALOGA_3 20
#define PIN_ENTRADA_ANALOGA_4 17

int pin_entrada_analoga_0 = PIN_ENTRADA_ANALOGA_0;
int pin_entrada_analoga_1 = PIN_ENTRADA_ANALOGA_1;
int pin_entrada_analoga_2 = PIN_ENTRADA_ANALOGA_2;
int pin_entrada_analoga_3 = PIN_ENTRADA_ANALOGA_3;
int pin_entrada_analoga_4 = PIN_ENTRADA_ANALOGA_4;

#define PIN_ENTRADA_LOGICA_0  16
#define PIN_ENTRADA_LOGICA_1  15
#define PIN_ENTRADA_LOGICA_2  14
#define PIN_ENTRADA_LOGICA_3  13
#define PIN_ENTRADA_LOGICA_4  39

int pin_entrada_logica_0 = PIN_ENTRADA_LOGICA_0;
int pin_entrada_logica_1 = PIN_ENTRADA_LOGICA_1;
int pin_entrada_logica_2 = PIN_ENTRADA_LOGICA_2;
int pin_entrada_logica_3 = PIN_ENTRADA_LOGICA_3;
int pin_entrada_logica_4 = PIN_ENTRADA_LOGICA_4;

/**
 * @brief : estatus de las entradas
 */
volatile int status_entrada_0 = 0;// logicas
volatile int status_entrada_1 = 0;
volatile int status_entrada_2 = 0;
volatile int status_entrada_3 = 0;
volatile int status_entrada_4 = 0;
volatile int status_entrada_5 = 0;// analogas
volatile int status_entrada_6 = 0;
volatile int status_entrada_7 = 0;
volatile int status_entrada_8 = 0;
volatile int status_entrada_9 = 0;

/**
 * @brief : valor asociado a la entrada multiplicado por el factor de param segun la lógica configurada
 */
volatile double valor_0 = 0.0;
volatile double valor_1 = 0.0;
volatile double valor_2 = 0.0;
volatile double valor_3 = 0.0;
volatile double valor_4 = 0.0;
volatile double valor_5 = 0.0;
volatile double valor_6 = 0.0;
volatile double valor_7 = 0.0;
volatile double valor_8 = 0.0;
volatile double valor_9 = 0.0;

/**
 * declaración de variables asociadas a la comunicacion EIA-RS485 con el variador F-800
 */
ModbusMaster var_frec;
int address_var_frec = 0x01;
double freq = 0;
int freq_prev = 0;

/**
 * @brief : declaracion de variables asociadas al sistema.
 */
bool bomba_on = false;
bool enable_var_frec = false;
int GPIO_1 = 0; // auto_internet
int GPIO_2 = 0; // nivel_agua_potable
int GPIO_3 = 0; // relé de nivel pozo
int GPIO_4 = 0; // manual
bool auto_internet = false;
bool casa_patronal = false;
int flag_pulse = 0x0000;

/**
 * @brief : variables asociadas a la comunicacion 3G
 */
Metro time_request = Metro(3500);
char bufferAnswer[4096];
int counter = 0;

/**
 * @brief : variables auxiliares
 */
int pin_caudalimetro = 21;
volatile long quantity_pulse[] = {0,0,0,0,0,0,0,0,0,0};
volatile double caudal = 0;
volatile long time_prev = 0;
volatile long time_current = 0;
volatile long delta = 0;
volatile double delta_t = 0;
int count = 0;
int count_pulse = 0;
volatile int sensor_value = 0;

/**
 * variables asociadas a el display
 */
LiquidCrystal_I2C lcd(0x3F,20,4);
#define TIME_MSG  2000 // 2 segundos

/**
 * @brief : flags de status
 */
bool flag_func = true;
bool request_http_ok = false;
bool hora_punta = false;

/**
 * @brief : variables asociadas a la SD Card.
 */
const int chipSelect = BUILTIN_SDCARD;
String dataString = "";

Metro time_of_log = Metro(1000*60); // 1 minuto

/**
 * @brief : variables asociadas al RTC
 */
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

/**
 * @brief : variables de configuracion.
 */
int device_id = 0;
int msio = 0;
int peakTime_enable = 0;
 
int input_id = 0;
int input_mode = 0;
double input_param = 1.0;

double inputs[320][4]; // 10 inputs for 32 devices, each with 4 parameters.

int output_id = 0;
int output_mode = 0;
int output_status = 0;

double outputs[320][4]; // 10 outputs for devices, each with 4 parameters.

char data_in_ = 0;
char *token = NULL;

/**
 * @brief : inicializacion del sistema.
 */
void setup() {
  /**
   * @brief : primero se deben inicializar los módulos criticos como el display y la SD Card y los puertos serial.
   */
  DEBUG.begin(115200);// usb debug only
  XBEE.begin(9600);
  while(!XBEE);
  MODULO_3G.begin(115200);
  while(!MODULO_3G);
  RS485.begin(9600, SERIAL_8E1);
  while(!RS485);
  
  while(display_init() != 0){
    delay(100);
    DEBUG.println("ERROR: display no init");
  }
  print_welcome_msg();
  delay(TIME_MSG);
  while(sd_card_init() != 0){
    print_error_sd_msg();
    delay(1000); 
  }
  print_sd_card_ok_msg();
  delay(TIME_MSG);

  /**
   * @brief : segundo, se debe cargar la configuracion desde la SD
   */
  while(load_sd_card_config() != 0){ // implementar en sd card
    print_error_load_config();
    delay(1000); 
  }
  print_load_config_ok_msg();
  delay(TIME_MSG);

  /**
   * @brief : tercero, se debe configurar el equipo
   */
  print_config_msg();
  delay(TIME_MSG);
  input_config(); // se configuran las entradas.
  print_input_config_ok_msg();
  delay(TIME_MSG);
  output_config(); // se onfiguran las salidas
  print_output_config_ok_msg();
  delay(TIME_MSG);
  system_config(); // se configuran variables del sistema
  print_system_config_ok_msg();
  delay(TIME_MSG);
  print_stay_for_3G_connection();
  stay_for_3G_connection(); // se espera por conexion 3G
  print_rtc_config_init();
  rtc_config(); // se configura el RTC
  print_rtc_config_ok_msg();
  delay(TIME_MSG);
  peakTime_config(); // se habilita/dehabilita el horario punta
  print_config_ok_msg();
  delay(TIME_MSG);

  /**
   * @brief : cuarto, habilitar interrupciones y modulos externos.
   */
  digitalWrite(6, HIGH); // habilita el RS485
  var_frec.begin(address_var_frec, RS485);

  cli();
  Timer1.initialize(10*1000); // 10 ms
  Timer1.attachInterrupt(measure);
  sei();
}

void loop() {
  /**
   * @brief : primero se deben leer las señales remotas de control desde la nube.
   */
  ubidots_requets_for_control();
  /**
   * @brief : luego se deben leer las entradas locales que tienen mayor prioridad por sobre las remotas
   *          por lo que eventualmente podrian sobreesccribir algun valor anterior.
   */
  system_inputs_read();
  /**
   * @brief : en tercer lugar se deben definir las salidas en funcion de las entradas.
   */
  system_outputs_update();
  /**
   * @brief : en cuarto lugar se debe actuar sobre las salidas.
   */   
  system_output_write();
  /**
   * @brief : en quinto lugar se debe notificar via display las variables de interes.
   */
  print_variables();
  /**
   * @brief : en sexto lugar se debe notificar via 3G hacia la nube el estado de todas las entradas y salidas.
   */
  ubidots_post_request();
}


/**
 * @brief : realiza mediciones cada 10 ms con una interrupcion por timer.
 */
void measure(){   //measure the quantity of square wave
  cli();
  count_pulse++;
  for(int i=0; i<10; i++){ // for each input
    switch(i){
      case 0 : { // entrada 0
        switch((int)inputs[0][2]){ // in case mode selected
          case 1 : {
            status_entrada_0 = digitalRead(pin_entrada_logica_0);
            break;
          }
          case 2 : {
            status_entrada_0 = (int)((double)analogRead(pin_entrada_logica_0))*0.0978; // 0 - 100 percent
            break;
          }
          case 3 : {
            status_entrada_0 = (int)((double)analogRead(pin_entrada_logica_0))*0.0978;
            break;
          }
          case 4 : {
            status_entrada_0 = ( analogRead(pin_entrada_logica_0)*0.1 + status_entrada_0*(1-0.1) );
            if( (status_entrada_0 <= 100 ) && (flag_pulse&0x0001 == 0x0000) ){
              quantity_pulse[0] += 1;
              flag_pulse |= 0x0001; // true
            }
            else if(status_entrada_0 >=700){
              quantity_pulse[0] = quantity_pulse[0];
              flag_pulse &= 0xFFFE; // false
            }
            else{
              quantity_pulse[0] = quantity_pulse[0];
              flag_pulse = flag_pulse; // nothing else
            }
            break;
          }
          default : {
            status_entrada_0 = 0;
            break;
          }  
        }
      } // entrada 1
      case 1 : {
        switch((int)inputs[1][2]){ // in case mode selected
          case 1 : {
            status_entrada_1 = digitalRead(pin_entrada_logica_1);
            break;
          }
          case 2 : {
            status_entrada_1 = (int)((double)analogRead(pin_entrada_logica_1))*0.0978; // 0 - 100 percent
            break;
          }
          case 3 : {
            status_entrada_1 = (int)((double)analogRead(pin_entrada_logica_1))*0.0978;
            break;
          }
          case 4 : {
            status_entrada_1 = ( analogRead(pin_entrada_logica_1)*0.1 + status_entrada_1*(1-0.1) );
            if( (status_entrada_1 <= 100 ) && (flag_pulse&0x0002 == 0x0000) ){
              quantity_pulse[1] += 1;
              flag_pulse |= 0x0002; // true
            }
            else if(status_entrada_1 >=700){
              quantity_pulse[1] = quantity_pulse[1];
              flag_pulse &= 0xFFFD; // false
            }
            else{
              quantity_pulse[1] = quantity_pulse[1];
              flag_pulse = flag_pulse; // nothing else
            }
            break;
          }
          default : {
            status_entrada_1 = 0;
            break;
          }  
        }
      }
      case 2 : { // entrada 2
        switch((int)inputs[2][2]){ // in case mode selected
          case 1 : {
            status_entrada_2 = digitalRead(pin_entrada_logica_2);
            break;
          }
          case 2 : {
            status_entrada_2 = (int)((double)analogRead(pin_entrada_logica_2))*0.0978; // 0 - 100 percent
            break;
          }
          case 3 : {
            status_entrada_2 = (int)((double)analogRead(pin_entrada_logica_2))*0.0978;
            break;
          }
          case 4 : {
            status_entrada_2 = ( analogRead(pin_entrada_logica_2)*0.1 + status_entrada_2*(1-0.1) );
            if( (status_entrada_2 <= 100 ) && (flag_pulse&0x0004 == 0x0000) ){
              quantity_pulse[2] += 1;
              flag_pulse |= 0x0004; // true
            }
            else if(status_entrada_2 >=700){
              quantity_pulse[2] = quantity_pulse[2];
              flag_pulse &= 0xFFFB; // false
            }
            else{
              quantity_pulse[2] = quantity_pulse[2];
              flag_pulse = flag_pulse; // nothing else
            }
            break;
          }
          default : {
            status_entrada_2 = 0;
            break;
          }  
        }
      }
      case 3 : { // entrada 3
        switch((int)inputs[3][2]){ // in case mode selected
          case 1 : {
            status_entrada_3 = digitalRead(pin_entrada_logica_3);
            break;
          }
          case 2 : {
            status_entrada_3 = (int)((double)analogRead(pin_entrada_logica_3))*0.0978; // 0 - 100 percent
            break;
          }
          case 3 : {
            status_entrada_3 = (int)((double)analogRead(pin_entrada_logica_3))*0.0978;
            break;
          }
          case 4 : {
            status_entrada_3 = ( analogRead(pin_entrada_logica_3)*0.1 + status_entrada_3*(1-0.1) );
            if( (status_entrada_3 <= 100 ) && (flag_pulse&0x0008 == 0x0000) ){
              quantity_pulse[3] += 1;
              flag_pulse |= 0x0008; // true
            }
            else if(status_entrada_3 >=700){
              quantity_pulse[3] = quantity_pulse[3];
              flag_pulse &= 0xFFF7; // false
            }
            else{
              quantity_pulse[3] = quantity_pulse[3];
              flag_pulse = flag_pulse; // nothing else
            }
            break;
          }
          default : {
            status_entrada_3 = 0;
            break;
          }  
        }
      }
      case 4 : { // entrada 4
        switch((int)inputs[4][2]){ // in case mode selected
          case 1 : {
            status_entrada_4 = digitalRead(pin_entrada_logica_4);
            break;
          }
          case 2 : {
            status_entrada_4 = (int)((double)analogRead(pin_entrada_logica_4))*0.0978; // 0 - 100 percent
            break;
          }
          case 3 : {
            status_entrada_4 = (int)((double)analogRead(pin_entrada_logica_4))*0.0978;
            break;
          }
          case 4 : {
            status_entrada_4 = ( analogRead(pin_entrada_logica_4)*0.1 + status_entrada_4*(1-0.1) );
            if( (status_entrada_4 <= 100 ) && (flag_pulse&0x0010 == 0x0000) ){
              quantity_pulse[4] += 1;
              flag_pulse |= 0x0010; // true
            }
            else if(status_entrada_4 >=700){
              quantity_pulse[4] = quantity_pulse[4];
              flag_pulse &= 0xFFEF; // false
            }
            else{
              quantity_pulse[4] = quantity_pulse[4];
              flag_pulse = flag_pulse; // nothing else
            }
            break;
          }
          default : {
            status_entrada_4 = 0;
            break;
          }  
        }
      }
      case 5 : { // entrada 5
        switch((int)inputs[5][2]){ // in case mode selected
          case 1 : {
            status_entrada_5 = digitalRead(pin_entrada_analoga_0);
            break;
          }
          case 2 : {
            status_entrada_5 = (int)((double)analogRead(pin_entrada_analoga_0))*0.0978; // 0 - 100 percent
            break;
          }
          case 3 : {
            status_entrada_5 = (int)((double)analogRead(pin_entrada_analoga_0))*0.0978;
            break;
          }
          case 4 : {
            status_entrada_5 = ( analogRead(pin_entrada_analoga_0)*0.1 + status_entrada_5*(1-0.1) );
            if( (status_entrada_5 <= 100 ) && (flag_pulse&0x0020 == 0x0000) ){
              quantity_pulse[5] += 1;
              flag_pulse |= 0x0020; // true
            }
            else if(status_entrada_5 >=700){
              quantity_pulse[5] = quantity_pulse[5];
              flag_pulse &= 0xFFDF; // false
            }
            else{
              quantity_pulse[5] = quantity_pulse[5];
              flag_pulse = flag_pulse; // nothing else
            }
            break;
          }
          default : {
            status_entrada_5 = 0;
            break;
          }  
        }
      }
      case 6 : { // entrada 6
        switch((int)inputs[6][2]){ // in case mode selected
          case 1 : {
            status_entrada_6 = digitalRead(pin_entrada_analoga_1);
            break;
          }
          case 2 : {
            status_entrada_6 = (int)((double)analogRead(pin_entrada_analoga_1))*0.0978; // 0 - 100 percent
            break;
          }
          case 3 : {
            status_entrada_6 = (int)((double)analogRead(pin_entrada_analoga_1))*0.0978;
            break;
          }
          case 4 : {
            status_entrada_6 = ( analogRead(pin_entrada_analoga_1)*0.1 + status_entrada_6*(1-0.1) );
            if( (status_entrada_6 <= 100 ) && (flag_pulse&0x0040 == 0x0000) ){
              quantity_pulse[6] += 1;
              flag_pulse |= 0x0040; // true
            }
            else if(status_entrada_6 >=700){
              quantity_pulse[6] = quantity_pulse[6];
              flag_pulse &= 0xFFBF; // false
            }
            else{
              quantity_pulse[6] = quantity_pulse[6];
              flag_pulse = flag_pulse; // nothing else
            }
            break;
          }
          default : {
            status_entrada_6 = 0;
            break;
          }  
        }
      }
      case 7 : { // entrada 7
        switch((int)inputs[7][2]){ // in case mode selected
          case 1 : {
            status_entrada_7 = digitalRead(pin_entrada_analoga_2);
            break;
          }
          case 2 : {
            status_entrada_7 = (int)((double)analogRead(pin_entrada_analoga_2))*0.0978; // 0 - 100 percent
            break;
          }
          case 3 : {
            status_entrada_7 = (int)((double)analogRead(pin_entrada_analoga_2))*0.0978;
            break;
          }
          case 4 : {
            status_entrada_7 = ( analogRead(pin_entrada_analoga_2)*0.1 + status_entrada_7*(1-0.1) );
            if( (status_entrada_7 <= 100 ) && (flag_pulse&0x0080 == 0x0000) ){
              quantity_pulse[7] += 1;
              flag_pulse |= 0x0080; // true
            }
            else if(status_entrada_7 >=700){
              quantity_pulse[7] = quantity_pulse[7];
              flag_pulse &= 0xFF7F; // false
            }
            else{
              quantity_pulse[7] = quantity_pulse[7];
              flag_pulse = flag_pulse; // nothing else
            }
            break;
          }
          default : {
            status_entrada_7 = 0;
            break;
          }  
        }
      }
      case 8 : { // entrada 8
        switch((int)inputs[8][2]){ // in case mode selected
          case 1 : {
            status_entrada_8 = digitalRead(pin_entrada_analoga_3);
            break;
          }
          case 2 : {
            status_entrada_8 = (int)((double)analogRead(pin_entrada_analoga_3))*0.0978; // 0 - 100 percent
            break;
          }
          case 3 : {
            status_entrada_8 = (int)((double)analogRead(pin_entrada_analoga_3))*0.0978;
            break;
          }
          case 4 : {
            status_entrada_8 = ( analogRead(pin_entrada_analoga_3)*0.1 + status_entrada_8*(1-0.1) );
            if( (status_entrada_8 <= 100 ) && (flag_pulse&0x0100 == 0x0000) ){
              quantity_pulse[8] += 1;
              flag_pulse |= 0x0100; // true
            }
            else if(status_entrada_8 >=700){
              quantity_pulse[8] = quantity_pulse[8];
              flag_pulse &= 0xFEFF; // false
            }
            else{
              quantity_pulse[8] = quantity_pulse[8];
              flag_pulse = flag_pulse; // nothing else
            }
            break;
          }
          default : {
            status_entrada_8 = 0;
            break;
          }  
        }
      }
      case 9 : { // entrada 9
        switch((int)inputs[9][2]){ // in case mode selected
          case 1 : {
            status_entrada_9 = digitalRead(pin_entrada_analoga_4);
            break;
          }
          case 2 : {
            status_entrada_9 = (int)((double)analogRead(pin_entrada_analoga_4))*0.0978; // 0 - 100 percent
            break;
          }
          case 3 : {
            status_entrada_9 = (int)((double)analogRead(pin_entrada_analoga_4))*0.0978;
            break;
          }
          case 4 : {
            status_entrada_9 = ( analogRead(pin_entrada_analoga_4)*0.1 + status_entrada_9*(1-0.1) );
            if( (status_entrada_9 <= 100 ) && (flag_pulse&0x0200 == 0x0000) ){
              quantity_pulse[9] += 1;
              flag_pulse |= 0x0200; // true
            }
            else if(status_entrada_9 >=700){
              quantity_pulse[9] = quantity_pulse[9];
              flag_pulse &= 0xFDFF; // false
            }
            else{
              quantity_pulse[9] = quantity_pulse[9];
              flag_pulse = flag_pulse; // nothing else
            }
            break;
          }
          default : {
            status_entrada_9 = 0;
            break;
          }  
        }
      }
      default : {
        break;
      }
    }
  }
  if(count_pulse >= 18000){ // actualizar los valores del efecto hall cada 3 min
    update_hall();
    count_pulse = 0;
  }
  if(count_pulse%100 == 0){ // se escriben las salidas cada 1 segundo
    system_output_write();
  }
  sei();
}

void update_hall(){
  cli();
  valor_0 = ((int)inputs[0][2] == 4)?( (quantity_pulse[0])*(inputs[0][3]) ):(valor_0);
  valor_1 = ((int)inputs[1][2] == 4)?( (quantity_pulse[1])*(inputs[1][3]) ):(valor_1);
  valor_2 = ((int)inputs[2][2] == 4)?( (quantity_pulse[2])*(inputs[2][3]) ):(valor_2);
  valor_3 = ((int)inputs[3][2] == 4)?( (quantity_pulse[3])*(inputs[3][3]) ):(valor_3);
  valor_4 = ((int)inputs[4][2] == 4)?( (quantity_pulse[4])*(inputs[4][3]) ):(valor_4);
  valor_5 = ((int)inputs[5][2] == 4)?( (quantity_pulse[5])*(inputs[5][3]) ):(valor_5);
  valor_6 = ((int)inputs[6][2] == 4)?( (quantity_pulse[6])*(inputs[6][3]) ):(valor_6);
  valor_7 = ((int)inputs[7][2] == 4)?( (quantity_pulse[7])*(inputs[7][3]) ):(valor_7);
  valor_8 = ((int)inputs[8][2] == 4)?( (quantity_pulse[8])*(inputs[8][3]) ):(valor_8);
  valor_9 = ((int)inputs[9][2] == 4)?( (quantity_pulse[9])*(inputs[9][3]) ):(valor_9);
  for(int i=0; i<10; i++){
    quantity_pulse[i] = 0;
  }
  sei();
}
