#include <TimeLib.h>

int anno;
int mes;
int dia;
int hora;
int minuto;
int segundo;

time_t current_time;
void setup() {
  // put your setup code here, to run once:
  current_time = Teensy3Clock.get();
  Serial.begin(115200);
  while(!Serial);
  Serial.print("timestamp:\t");
  Serial.println(current_time);
  anno = 1970 + current_time/31540000;
  mes = (current_time%31540000)/2628000;
  dia = ((current_time%31540000)%2628000)/86400;
  hora = (((current_time%31540000)%2628000)%86400)/3600;
  minuto = ((((current_time%31540000)%2628000)%86400)%3600)/60;
  segundo = ((((current_time%31540000)%2628000)%86400)%3600)%60;
  Serial.print("fecha y hora:\t");
  Serial.print(dia);
  Serial.print("/");
  Serial.print(mes);
  Serial.print("/");
  Serial.print(anno);
  Serial.print("\t");
  Serial.print(hora);
  Serial.print(":");
  Serial.print(minuto);
  Serial.print(":");
  Serial.print(segundo);
  Serial.print("\n");
  long modulo = 1924732800%604800;
  String dia_de_la_semana = (modulo >= 0 && modulo < 86400)?("Jueves"):
                            (modulo >= 86400 && modulo < 172800)?("Viernes"):
                            (modulo >= 172800 && modulo < 259200)?("Sabado"):
                            (modulo >= 259200 && modulo < 345600)?("Domingo"):
                            (modulo >= 345600 && modulo < 432000)?("Lunes"):
                            (modulo >= 432000 && modulo < 518400)?("Martes"):
                            (modulo >= 518400 && modulo < 604800)?("Miercoles"):("Error");
  Serial.print("el dia de la semana es:\t");
  Serial.println(dia_de_la_semana);
  Serial.println(current_time%604800);
  Serial.println(604799%604800);
}

void loop() {
  // put your main code here, to run repeatedly:
  current_time = Teensy3Clock.get();
  Serial.print("timestamp:\t");
  Serial.println(current_time);
  anno = 1970 + current_time/31536000;
  mes = (current_time%31536000)/2592000;
  dia = ((current_time%31536000)%2592000)/86400;
  hora = (((current_time%31536000)%2592000)%86400)/3600;
  minuto = ((((current_time%31536000)%2592000)%86400)%3600)/60;
  segundo = ((((current_time%31536000)%2592000)%86400)%3600)%60;
  Serial.print("fecha y hora:\t");
  Serial.print(dia);
  Serial.print("/");
  Serial.print(mes);
  Serial.print("/");
  Serial.print(anno);
  Serial.print("\t");
  Serial.print(hora);
  Serial.print(":");
  Serial.print(minuto);
  Serial.print(":");
  Serial.print(segundo);
  Serial.print("\n");
  delay(1000);
}
