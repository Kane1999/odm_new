#include "Framework.h"

Framework framework;
// main program
void setup(){
  Serial.begin(9600);
  framework.Init();
}

void loop(){
  framework.execute();
}