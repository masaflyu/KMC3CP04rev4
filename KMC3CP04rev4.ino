#include <SPI.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "P_Ports.h"
#include "P_Gcode.h"
#include "P_Motor.h"

//const int LengthOfStringBuffer = 192;
//char strbuf[LengthOfStringBuffer]="";

char* strbuf;

long debugcount = 0;

void setup() 
{
  // put your setup code here, to run once:

  //全てのポートの入出力を設定
  initializePorts();

  initializeInterrupt();

  //SPI系設定
  initializeSerial();

  //SD設定
  initializeSD();
  
  gCodeOpen("GCODE.gco");

//  strbuf = getStrBuf();

  initMotorDriverParam();

  //initX();
  //initY();
  //initZ();
  
  //moveX(-200.0);
  //moveY(20.0);
  //moveZ(5.0);
  //moveEs(120,5);
  //delay(2400);
  watchdogEnable( 2000 ); //ウォッチドッグタイマをオンに
}

void loop() 
{
  statusCheck();
  // put your main code here, to run repeatedly:
  //digitalWrite(LED1,1);

  if( debugcount % 1000 < 500)
  {
    digitalWrite(LED1,1);
  }
  else
  {
    digitalWrite(LED1,0);
  }
  if( debugcount % 1000 >= 500)
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

  debugcount++;
  //Serial.println(debugcount);
  //if(debugcount == 0) exit(0);
}

void statusCheck()
{
  watchdogReset();  //ウォッチドッグタイマ
}



