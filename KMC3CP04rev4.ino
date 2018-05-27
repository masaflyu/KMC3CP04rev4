#include "KMC3CPDefinePorts.h"
\
#include <SPI.h>

#include <string.h>
#include <math.h>
#include <stdlib.h>
//#include "KMC3CPDefinePorts.h"
#include "KMC3CPinitializePorts.h"
#include "Serial.h"
#include "SDGcode.h"

//const int LengthOfStringBuffer = 192;
//char strbuf[LengthOfStringBuffer]="";

char* strbuf;

//int debugcount = 100;

void setup() {
  // put your setup code here, to run once:

  //全てのポートの入出力を設定
  initializePorts();

  //SPI系設定
  initializeSerial();
  
  gCodeOpen("GCODE.gco");

//  strbuf = getStrBuf();

}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(LED1,1);

  if( digitalRead(BSW1) == 1)
  {
    digitalWrite(LED1,1);
  }
  else
  {
    digitalWrite(LED1,0);
  }
  if( digitalRead(BSW2) == 1)
  {
    digitalWrite(LED2,1);
  }
  else
  {
    digitalWrite(LED2,0);
  }
  //delay(500);

  Serial.println(readNewGCodeALine());

  Serial.flush(); //シリアル送信完了を待つ関数 (昔は別の意味の関数だったので調べるときは注意）

  //debugcount--;
  //if(debugcount == 0) exit(0);
}
