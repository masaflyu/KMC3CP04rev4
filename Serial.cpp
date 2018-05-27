#include <SD.h>
#include <SPI.h>
#include "KMC3CPDefinePorts.h"
#include "Serial.h"

void initializeSerial(){
  //シリアルポート初期化
  Serial.begin(9600);
  // SSピン（Unoは10番、Megaは53番）は使わない場合でも出力にする必要があります。
  // そうしないと、SPIがスレーブモードに移行し、ライブラリが動作しなくなります。
  pinMode(SS, OUTPUT);
  SPIselect(SD_CS);

  //--------------------------------------------------------------------
  //SDライブラリを初期化
  Serial.println("[SDCARD]____________________________");
  Serial.print(F("Initializing SD card..."));
  if ( !SD.begin(SD_CS) ) {
    Serial.println(F(" Card failed, or not present\r\n"));
  }
  else
  {
    Serial.println(F("ok.\r\n"));    
  }
  // 日付と時刻を返す関数を登録
  SdFile::dateTimeCallback( &dateTime );
}


void SPIselect(char device) {
  //char deviceenable[6] = { 0 };
  if ( device >= 0 && device <= 5 ) {
    
    //deviceenable[device] = 1;
    if (device == 0)SPI.setDataMode(SPI_MODE0);
    else SPI.setDataMode(SPI_MODE3);
    
    //書き込み．Highで非対象，LOWで通信対象
    digitalWrite( 32 , 1 );
    digitalWrite( 34 , 1 );
    digitalWrite( 36 , 1 );
    digitalWrite( 38 , 1 );
    digitalWrite( 40 , 1 );
    digitalWrite( 42 , 1 );
    //    PIN_SPI_SS = 32+2*device;
    //    PIN_BUSY = 33+2*device;
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
