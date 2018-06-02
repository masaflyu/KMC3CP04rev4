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

double realclock = 0;

long a0sum=0;
long a2sum=0;
long a3sum=0;
long sumcount=0;

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

  startTimer( TC1, 0, TC3_IRQn, 500);
  
  NVIC_SetPriority((IRQn_Type)SysTick_IRQn,0);  
  NVIC_SetPriority((IRQn_Type)TC3_IRQn,1);
  NVIC_SetPriority((IRQn_Type)TC4_IRQn,2);
  NVIC_SetPriority((IRQn_Type)TC5_IRQn,3);

  digitalWrite(HV1, 1);


  //initX();
  //initY();
  //initZ();
  
  //moveX(-200.0);
  //moveY(20.0);
  //moveZ(5.0);
  //moveEs(120,5);
  //delay(2400);
  //watchdogEnable( 2000 ); //ウォッチドッグタイマをオンに
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

  a0sum += analogRead(0);
  a2sum += analogRead(2);
  a3sum += analogRead(3);
  sumcount ++;
  
  //delay(500);


  //Serial.println(readNewGCodeALine());

  //Serial.flush(); //シリアル送信完了を待つ関数 (昔は別の意味の関数だったので調べるときは注意）

  debugcount++;
  //Serial.println(debugcount);
  //if(debugcount == 0) exit(0);
}

void statusCheck()
{
  watchdogReset();  //ウォッチドッグタイマ
}

void startTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t mSec) {
  pmc_enable_periph_clk((uint32_t)irq);
  TC_Configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
  uint32_t rc = (VARIANT_MCK/2/1000)*mSec;
  TC_SetRC(tc, channel, rc);
  TC_Start(tc, channel);
  tc->TC_CHANNEL[channel].TC_IER=TC_IER_CPCS;
  tc->TC_CHANNEL[channel].TC_IDR=~TC_IER_CPCS;
  NVIC_EnableIRQ(irq);
}


void TC3_Handler() {
  TC_GetStatus(TC1, 0);
  // 割り込み発生時に実行する部分

  if(digitalRead(BSW1)==1)return;
  Serial.print("t=, ");
  Serial.print((int)(millis()/1000));
  Serial.print(", [ms] , A0=, ");
  Serial.print((int)(a0sum/sumcount));
  //Serial.print(analogRead(0));
  Serial.print(",  A2=, ");
  Serial.print((int)(a2sum/sumcount));
  //Serial.print(analogRead(2));
  Serial.print(",  A3=, ");
  Serial.print((int)(a3sum/sumcount));
  //Serial.print(analogRead(3));
  Serial.println(", .");
  Serial.flush();
  
 a0sum=0;
 a2sum=0;
 a3sum=0;
 sumcount=0;
}



