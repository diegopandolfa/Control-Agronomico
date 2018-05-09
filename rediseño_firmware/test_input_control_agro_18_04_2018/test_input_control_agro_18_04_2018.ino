#include <input.h>
Input flujo = Input();

void setup() {
  // put your setup code here, to run once:
  pinMode(35, INPUT_PULLUP);
  flujo.init(35);
//  flujo.setParameter(0.0977);
  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("entrada:\t");
  Serial.println(flujo.readInputHall());
  delay(9);
}
