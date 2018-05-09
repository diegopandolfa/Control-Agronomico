#include<output.h>

Output out1 = Output(1,13);
int flag = 0;
String tmp = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
  out.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  out.setState(1, LOW);
  out.getState(1, tmp);
  Serial.println(tmp);
  out.action();
  delay(2000);
  out.setState(1, HIGH);
  out.getState(1, tmp);
  Serial.println(tmp);
  out.action();
  delay(2000);
}
