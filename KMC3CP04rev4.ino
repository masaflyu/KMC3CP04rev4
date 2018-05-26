#include "DefinePorts.h"
\
#include <SPI.h>

#include <string.h>
#include <math.h>
#include <stdlib.h>
//#include "DefinePorts.h"
#include "initializePorts.h"
#include "Serial.h"
#include "Gcode.h"


void setup() {
  // put your setup code here, to run once:

  //全てのポートの入出力を設定
  initializePorts();

  //SPI系設定
  initializeSerial();
  
  gCodeOpen("GCODE.gco");

  

}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(LED1,1);

  if( digitalRead(BSW1) == 1){
    digitalWrite(LED1,1);
  }
  else
  {
    digitalWrite(LED1,0);
  }
  if( digitalRead(BSW2) == 1){
    digitalWrite(LED2,1);
  }
  else
  {
    digitalWrite(LED2,0);
  }
  //delay(500);
}
