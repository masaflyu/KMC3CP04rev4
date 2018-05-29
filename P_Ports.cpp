#include<Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "P_Ports.h"
#include "P_Motor.h"

void initializePorts()
{

  pinMode( LED1 , OUTPUT );
  pinMode( LED2 , OUTPUT );
  
  pinMode( HV1 , OUTPUT );
  pinMode( HV2 , OUTPUT );
  pinMode( HV3 , OUTPUT );
  pinMode( HV4 , OUTPUT );
  pinMode( HV5 , OUTPUT );
  pinMode( HV6 , OUTPUT );

  pinMode( BSW1 , INPUT );
  pinMode( BSW2 , INPUT );
  
  pinMode( OSW1 , INPUT );
  pinMode( OSW2 , INPUT );
  pinMode( OSW3 , INPUT );
  pinMode( OSW4 , INPUT );
  pinMode( OSW5 , INPUT );
  pinMode( OSW6 , INPUT );

  pinMode( SD_CS , OUTPUT );
  pinMode( MOTOR_CS , OUTPUT );

  pinMode( MOTOR1_BUSY , INPUT );
  pinMode( MOTOR2_BUSY , INPUT );
  pinMode( MOTOR3_BUSY , INPUT );
  pinMode( MOTOR4_BUSY , INPUT );
  pinMode( MOTOR5_BUSY , INPUT );

  pinMode( Thermo1 , INPUT );
  pinMode( Thermo2 , INPUT );
  pinMode( OThermistor , INPUT );
  pinMode( OThermistor , INPUT );
}


void initializeInterrupt()
{
  attachInterrupt(OSW1,itr_LimitX,RISING);
  attachInterrupt(OSW2,itr_LimitY,RISING);
  attachInterrupt(OSW3,itr_LimitZ,RISING);
}


void initializeSerial()
{
  //念のためデフォルトの9600bpsで警告
  Serial.begin(9600);
  Serial.println(F("Please change the baudrate to 115200.") );
  Serial.end();

  //シリアル接続開始
  Serial.begin(115200);

  //
  Serial.println(F("Serial connection succeed (115200bps).") );

}





void initializeSD()
{
  // SSピン（Unoは10番、Megaは53番）は使わない場合でも出力にする必要があります。
  // そうしないと、SPIがスレーブモードに移行し、ライブラリが動作しなくなります。
  pinMode(SS, OUTPUT);
  
  selectSPIDevice(SDCARD);
  
  //SDライブラリを初期化
  Serial.print(F("Initializing SD card..."));
  if ( !SD.begin(SD_CS) ) 
  {
    Serial.println(F(" Card failed, or not present.\r\n"));
  }
  else
  {
    Serial.println(F("SD card found.\r\n"));    
  }
  
  // 日付と時刻を返す関数を登録
  SdFile::dateTimeCallback( &dateTime );

}




void selectSPIDevice(char device) 
{

  if ( device >= 0 && device <= 5 ) 
  {
    
    //SPI_MODEの切り替え．
    if (device == 0)
    {
      SPI.setDataMode(SPI_MODE0);
    }
    else
    {
      SPI.setDataMode(SPI_MODE3);
    }
  }
}





//dataTime()
//時刻の設定
void dateTime(uint16_t* date, uint16_t* time)
{
  uint16_t year = 2013;
  uint8_t month = 2, day = 3, hour = 9, minute = 0, second = 0;

  // GPSやRTCから日付と時間を取得
  // FAT_DATEマクロでフィールドを埋めて日付を返す
  *date = FAT_DATE(year, month, day);

  // FAT_TIMEマクロでフィールドを埋めて時間を返す
  *time = FAT_TIME(hour, minute, second);
}
