#include <Metro.h>

Metro time_request = Metro(8000);
String tmp = "";
char bufferAnswer[2048];
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

void setup() {
  Serial1.begin(115200);
  Serial2.begin(115200);
  delay(10000);
  // put your setup code here, to run once:
  tmp = "HEAD /api/v1.6";
  tmp += " HTTP/1.1\r\n";
  tmp += "HOST: things.ubidots.com\r\n";
  tmp += "Connection: close\r\n";
  tmp += "\r\n";
  Serial2.flush();
  Serial2.print(tmp);
  Serial1.print(tmp);
  char data_in_ = 0;
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
}

void loop() {
  // put your main code here, to run repeatedly:

}
