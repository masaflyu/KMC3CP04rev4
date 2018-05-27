#include <Arduino.h>
#include <SPI.h>
#include "L6470Library.h"
#include "P_Ports.h"

void set6470abspos(char spino , long val){transfer6470(spino , 0x01,3,val);}
void set6470elpos(char spino , long val){transfer6470(spino , 0x02,2,val);}
void set6470mark(char spino , long val){transfer6470(spino , 0x03,3,val);}
void set6470acc(char spino , long val){transfer6470(spino , 0x05,2,val);}
void set6470dec(char spino , long val){transfer6470(spino , 0x06,2,val);}
void set6470maxspeed(char spino , long val){transfer6470(spino , 0x07,2,val);}
void set6470minspeed(char spino , long val){transfer6470(spino , 0x08,2,val);}
void set6470fsspd(char spino , long val){transfer6470(spino , 0x15,2,val);}
void set6470kvalhold(char spino , long val){transfer6470(spino , 0x09,1,val);}
void set6470kvalrun(char spino , long val){transfer6470(spino , 0x0a,1,val);}
void set6470kvalacc(char spino , long val){transfer6470(spino , 0x0b,1,val);}
void set6470kvaldec(char spino , long val){transfer6470(spino , 0x0c,1,val);}
void set6470intspd(char spino , long val){transfer6470(spino , 0x0d,2,val);}
void set6470stslp(char spino , long val){transfer6470(spino , 0x0e,1,val);}
void set6470fnslpacc(char spino , long val){transfer6470(spino , 0x0f,1,val);}
void set6470fnslpdec(char spino , long val){transfer6470(spino , 0x10,1,val);}
void set6470ktherm(char spino , long val){transfer6470(spino , 0x11,1,val);}
void set6470ocdth(char spino , long val){transfer6470(spino , 0x13,1,val);}
void set6470stallth(char spino , long val){transfer6470(spino , 0x14,1,val);}
void set6470stepmode(char spino , long val){transfer6470(spino , 0x16,1,val);}
void set6470alareen(char spino , long val){transfer6470(spino , 0x17,1,val);}
void set6470config(char spino , long val){transfer6470(spino , 0x18,2,val);}

long get6470abspos(char spino){return get6470param(spino , 0x01,3);}
long get6470elpos(char spino){return get6470param(spino , 0x02,2);}
long get6470mark(char spino){return get6470param(spino , 0x03,3);}
long get6470speed(char spino){return get6470param(spino , 0x04,3);}
long get6470acc(char spino){return get6470param(spino , 0x05,2);}
long get6470dec(char spino){return get6470param(spino , 0x06,2);}
long get6470maxspeed(char spino){return get6470param(spino , 0x07,2);}
long get6470minspeed(char spino){return get6470param(spino , 0x08,2);}
long get6470fsspd(char spino){return get6470param(spino , 0x15,2);}
long get6470kvalhold(char spino){return get6470param(spino , 0x09,1);}
long get6470kvalrun(char spino){return get6470param(spino , 0x0a,1);}
long get6470kvalacc(char spino){return get6470param(spino , 0x0b,1);}
long get6470kvaldec(char spino){return get6470param(spino , 0x0c,1);}
long get6470intspd(char spino){return get6470param(spino , 0x0d,2);}
long get6470stslp(char spino){return get6470param(spino , 0x0e,1);}
long get6470fnslpacc(char spino){return get6470param(spino , 0x0f,1);}
long get6470fnslpdec(char spino){return get6470param(spino , 0x10,1);}
long get6470ktherm(char spino){return get6470param(spino , 0x11,1);}
long get6470adcout(char spino){return get6470param(spino , 0x12,1);}
long get6470ocdth(char spino){return get6470param(spino , 0x13,1);}
long get6470stallth(char spino){return get6470param(spino , 0x14,1);}
long get6470stepmode(char spino){return get6470param(spino , 0x16,1);}
long get6470alareen(char spino){return get6470param(spino , 0x17,1);}
long get6470config(char spino){return get6470param(spino , 0x18,2);}
long get6470status(char spino){return get6470param(spino , 0x19,2);}

//

char spi_chainnum = 4;

//spinoは上流から順に1,2,3...


//チェーン要素数変更

void setChainNum(char num){
  spi_chainnum = num;
}

char busypin(char spino){
  return 32+spino;
}

//////////////////////////////////////////////////////////////////
//Application層

//L6470命令関数

void l6470run(char spino, int dia, long spd){
  if(dia==1)
    transfer6470(spino,0x51,3,spd);
  else
    transfer6470(spino,0x50,3,spd);
}

void l6470stepclock(char spino, int dia){
  if(dia==1)
    transfer6470(spino,0x59,0,0);    
  else
    transfer6470(spino,0x58,0,0);
}

void l6470move(char spino, int dia,long n_step){
  if(dia==1)
    transfer6470(spino,0x41,3,n_step);
  else
    transfer6470(spino,0x40,3,n_step);
}

void l6470goto(char spino, long pos){
  transfer6470(spino,0x60,3,pos);
}

void l6470gotodia(char spino, int dia,int pos){
  if(dia==1)    
    transfer6470(spino,0x69,3,pos);
  else    
    transfer6470(spino,0x68,3,pos);
}

void l6470gountil(char spino, int act,int dia,long spd){
  if(act==1)
    if(dia==1)
      transfer6470(spino,0x8b,3,spd);
    else
      transfer6470(spino,0x8a,3,spd);
  else
    if(dia==1)
      transfer6470(spino,0x83,3,spd);
    else
      transfer6470(spino,0x82,3,spd);
}

void l6470relesesw(char spino, int act,int dia){
  if(act==1)
    if(dia==1)
      transfer6470(spino,0x9b,0,0);
    else
      transfer6470(spino,0x9a,0,0);
  else
    if(dia==1)
      transfer6470(spino,0x93,0,0);
    else
      transfer6470(spino,0x92,0,0);
}

void l6470gohome(char spino){
  transfer6470(spino,0x70,0,0);
}

void l6470gomark(char spino){
  transfer6470(spino,0x78,0,0);
}

void l6470resetpos(char spino){
  transfer6470(spino,0xd8,0,0);
}

void l6470resetdevice(char spino){
  send6470force(spino,0x00);//nop命令
  send6470force(spino,0x00);
  send6470force(spino,0x00);
  send6470force(spino,0x00);
  send6470force(spino,0xc0);
}

void l6470softstop(char spino){
  transfer6470(spino,0xb0,0,0);
}

void l6470hardstop(char spino){
  transfer6470(spino,0xb8,0,0);
}

void l6470softhiz(char spino){
  transfer6470(spino,0xa0,0,0);
}

void l6470hardhiz(char spino){
  transfer6470(spino,0xa8,0,0);
}


//////////////////////////////////////////////////////////////////
//transfer層

/*
transfer6470()
transfer層
戻り値: 無し
引数1: char spino...SPI番号(1,2,3...)
引数2: int add...書き込み先アドレス(パラメータ番号を含む)
引数3: int bytes...valの長さ[バイト]
引数4: long val...書き込む値(最大3バイト)
*/
void transfer6470(char spino, int add, int bytes, long val)
{
  int data[3];
  send6470(spino, add);
  for(int i=0;i<=bytes-1;i++){
    data[i] = val & 0xff;
    val = val >> 8;
  }
  if(bytes==3){
    send6470(spino, data[2]);
  }
  if(bytes>=2){
    send6470(spino, data[1]);
  }
  if(bytes>=1){
    send6470(spino, data[0]);
  }  
}

////////////////////////////////////////////////////////////////////
//get層

/*
get6470status()
get層．L6470のステータスを取得する．
戻り値: long val...ステータス
引数1: char spino...SPI番号(1,2,3...)
*/

// long get6470status(char spino){
//   long val=0;
//   send6470force(spino,0xd0);  
//   for(int i=0;i<=1;i++){
//     val = val << 8;
//     digitalWrite(PIN_SPI_SS, LOW); // ~SSイネーブル。
//     for(int in = spi_chainnum ; in > 0 ; in-- ){
//       if(in == spino){
//         val = val | SPI.transfer(0x00); // アドレスもしくはデータを取得。
//       }else{
//         SPI.transfer(0);    //NOP命令を送る
//       }
//     }
//     digitalWrite(PIN_SPI_SS, HIGH); // ~SSディスエーブル 
//   }
//   return val;
// }


/*
get6470param()
get層．L6470のパラメータを選択し取得する．
戻り値: long val...パラメータ
引数1: char spino...SPI番号(1,2,3...)
引数2: int add...アドレス
引数3: int bytes...パラメータ長さ[byte]
*/
long get6470param(char spino , int add , int bytes){
  long val=0;
  int send_add = add | 0x20;
  send6470force(spino,send_add);

  for(int i=0 ; i<=bytes-1 ; i++){
    val = val << 8;
    digitalWrite(MOTOR_CS, LOW); // ~SSイネーブル。
    for(int in = spi_chainnum ; in > 0 ; in-- ){
      if(in == spino){
        val = val | SPI.transfer(0x00); // アドレスもしくはデータを取得。
      }else{
        SPI.transfer(0);    //NOP命令を送る
      }
    }
    digitalWrite(MOTOR_CS, HIGH); // ~SSディスエーブル 
  }
  return val;
}


////////////////////////////////////////////////////////////////////
//Send層

/*
send6470()
send層．コマンド，データなどをSPIライブラリを使用し実際に送る．busy状態の場合には待機する．
戻り値: 無し
引数1: char spino...SPI番号(1,2,3...)
引数2: int data...書き込むデータ
*/
void send6470(char spino, unsigned char data){
  while(!digitalRead( busypin(spino) )){
  } //BESYが解除されるまで待機
  digitalWrite(MOTOR_CS, LOW); // ~SSイネーブル。
  for(int in = spi_chainnum ; in > 0 ; in-- ){
    if(in == spino){
      SPI.transfer(data); //データを送る
    }else{
      SPI.transfer(0);    //NOP命令を送る
    }
  }
  digitalWrite(MOTOR_CS, HIGH); // ~SSディスエーブル。
}

/*
send6470force()
send層．コマンド，データなどをSPIライブラリを使用し実際に送る．busyを確認せず送信する．
戻り値: 無し
引数1: char spino...SPI番号(1,2,3...)
引数2: int data...書き込むデータ
*/
void send6470force(char spino, unsigned char data){
  digitalWrite(MOTOR_CS, LOW);  // ~SSイネーブル。
  for(int in = spi_chainnum ; in > 0 ; in-- ){
    if(in == spino){
      SPI.transfer(data); //データを送る
    }else{
      SPI.transfer(0);    //NOP命令を送る
    }
  }
  digitalWrite(MOTOR_CS, HIGH); // ~SSディスエーブル。
}

/*
l6470busydelay()
send層.busy解除を待機してさらにtimeだけ待つ．
戻り値: 無し
引数1: char port...Arduinoポート番号
引数2: long time...追加遅延時間[msec]
*/
void l6470busydelay(char port,long time){//BESYが解除されるまで待機
  while(!digitalRead(port)){
  }
  delay(time);
}



