#include <Arduino.h>
#include "P_Ports.h"
#include "P_Motor.h"
#include "L6470Library.h"


//Xを指定した絶対位置[mm]移動させる
void moveX(double posmm) {
  l6470goto (MOTORX , (long)( -posmm / X1microstep128 ) );
}





//Yを指定した絶対位置[mm]移動させる
void moveY(double posmm) {
  l6470goto (MOTORY , (long)( posmm / Y1microstep128 ) );
}







//Zを指定した絶対位置[mm]移動させる
void moveZ(double posmm) {
  l6470goto (MOTORZ , (long)( posmm / Z1microstep64 ) );
}






//Xを指定した速度で，指定した絶対位置[mm]移動させる
void gotoXs(double posmm, double mms) {
  //[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])
  set6470maxspeed(MOTORX, (long)((mms / X1step) / 15.25 - 1));
  l6470goto (MOTORX , (long)( -posmm / X1microstep128 ) );
}







//Yを指定した絶対位置[mm]移動させる
void gotoYs(double posmm, double mms) {
  set6470maxspeed(MOTORY, (long)((mms / Y1step) / 15.25 - 1));
  l6470goto (MOTORY , (long)( posmm / Y1microstep128 ) );
}






//Zを指定した絶対位置[mm]移動させる
void gotoZs(double posmm, double mms) {
  set6470maxspeed(MOTORZ, (long)((mms / Z1step) / 15.25 - 1));
  l6470goto (MOTORZ , (long)( posmm / Z1microstep64 ) );
}






void initX()
{
  
}




void initY()
{
  
}




void initZ()
{

}



/*デバッグ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//Extruderを指定した長さ[mm]排出させる
void moveEs(double mm, double mms) {
  //  Serial.print("moveEs: move {");
  //  Serial.print(mm);
  //  Serial.print("}[mm] by {");
  //  Serial.print(mms);
  //  Serial.println("}[mm/s].");

  //set6470maxspeed(4, (long)( (mms / Extrude1step) / 15.25) );
  //l6470move(4 , 0 , (long)( mm / Extrude1microstep32 ) );

  set6470abspos(MOTORE, 0);
  set6470maxspeed(MOTORE, (long)((mms / Extrude1step) / 15, 25 - 1));
  if ( mm >= 0.0 ) {
    l6470goto( MOTORE , (long) ( - mm / Extrude1microstep32 ) );
  } else {
    l6470goto( MOTORE , (long) ( - mm / Extrude1microstep32 ) );
  }

}

 
 
 

 void motorDriverParamSet() {

  selectSPIDevice(MOTOR);
  //--------------------------------------------------------------------
  //  X軸
  //その他//////////////////////////
  //[R, WH]ステップモードdefault 0x07 (1+3+1+3bit)
  set6470stepmode(MOTORX, 0x07);
  //加速度に関すること///////////////
  //[R, WS] 加速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  set6470acc(MOTORX, 0x74);
  //[R, WS] 減速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  set6470dec(MOTORX, 0x74);

  //速度に関すること/////////////////
  //[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])
  set6470maxspeed(MOTORX, 0x18);
  //[R, WS]最小速度default 0x000 (1+12bit) (0.238*val+[step/s])
  set6470minspeed(MOTORX, 0x00);
  //[R, WR]μステップからフルステップへの切替点速度default 0x027 (10bit) (15.25*val+7.63[step/s])
  set6470fsspd(MOTORX, 0x10);

  //電圧に関すること/////////////////
  //[R, WR]停止時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvalhold(MOTORX, 0x0F);
  //[R, WR]定速回転時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvalrun(MOTORX, 0x4F);
  //[R, WR]加速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvalacc(MOTORX, 0x4F);
  //[R, WR]減速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvaldec(MOTORX, 0x4F);

  //電流に関すること
  //[R, WR]過電流しきい値default 0x8 (4bit) (375*val+375[mA])
  set6470ocdth(MOTORX, 0xF);
  //[R, WR]失速電流しきい値？default 0x40 (7bit) (31.25*val+31.25[mA])
  set6470stallth(MOTORX, 0x3F);

  //--------------------------------------------------------------------
  // Y軸

  //その他//////////////////////////
  //[R, WH]ステップモードdefault 0x07 (1+3+1+3bit)
  set6470stepmode(MOTORY, 0x07);
  //加速度に関すること///////////////
  //[R, WS] 加速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  set6470acc(MOTORY, 0x74);
  //[R, WS] 減速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  set6470dec(MOTORY, 0x74);

  //速度に関すること/////////////////
  //[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])
  set6470maxspeed(MOTORY, 0x18);
  //[R, WS]最小速度default 0x000 (1+12bit) (0.238*val+[step/s])
  set6470minspeed(MOTORY, 0x00);
  //[R, WR]μステップからフルステップへの切替点速度default 0x027 (10bit) (15.25*val+7.63[step/s])
  set6470fsspd(MOTORY, 0x10);

  //電圧に関すること/////////////////
  //[R, WR]停止時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvalhold(MOTORY, 0x0F);
  //[R, WR]定速回転時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvalrun(MOTORY, 0x4F);
  //[R, WR]加速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvalacc(MOTORY, 0x4F);
  //[R, WR]減速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvaldec(MOTORY, 0x4F);

  //電流に関すること
  //[R, WR]過電流しきい値default 0x8 (4bit) (375*val+375[mA])
  set6470ocdth(MOTORY, 0xF);
  //[R, WR]失速電流しきい値？default 0x40 (7bit) (31.25*val+31.25[mA])
  set6470stallth(MOTORY, 0x3F);

  //--------------------------------------------------------------------
  // Z軸

  //その他//////////////////////////
  //[R, WH]ステップモードdefault 0x07 (1+3+1+3bit)
  set6470stepmode(MOTORZ, 0x06);
  //加速度に関すること///////////////
  //[R, WS] 加速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  set6470acc(MOTORZ, 0x34);
  //[R, WS] 減速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  set6470dec(MOTORZ, 0x34);

  //速度に関すること/////////////////
  //[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])
  set6470maxspeed(MOTORZ, 0x18);
  //[R, WS]最小速度default 0x000 (1+12bit) (0.238*val+[step/s])
  set6470minspeed(MOTORZ, 0x00);
  //[R, WR]μステップからフルステップへの切替点速度default 0x027 (10bit) (15.25*val+7.63[step/s])
  set6470fsspd(MOTORZ, 0x10);

  //電圧に関すること/////////////////
  //[R, WR]停止時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvalhold(MOTORZ, 0x0F);
  //[R, WR]定速回転時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvalrun(MOTORZ, 0xFF);
  //[R, WR]加速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvalacc(MOTORZ, 0xFF);
  //[R, WR]減速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvaldec(MOTORZ, 0xFF);

  //電流に関すること
  //[R, WR]過電流しきい値default 0x8 (4bit) (375*val+375[mA])
  set6470ocdth(MOTORZ, 0xF);
  //[R, WR]失速電流しきい値？default 0x40 (7bit) (31.25*val+31.25[mA])
  set6470stallth(MOTORZ, 0x3F);

  //--------------------------------------------------------------------
  // エクストルーダ

  //その他//////////////////////////
  //[R, WH]ステップモードdefault 0x07 (1+3+1+3bit)
  set6470stepmode(MOTORE, 0x07);
  //加速度に関すること///////////////
  //[R, WS] 加速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  set6470acc(MOTORE, 0x74);
  //[R, WS] 減速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  set6470dec(MOTORE, 0x74);

  //速度に関すること/////////////////
  //[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])
  set6470maxspeed(MOTORE, 0x18);
  //[R, WS]最小速度default 0x000 (1+12bit) (0.238*val+[step/s])
  set6470minspeed(MOTORE, 0x00);
  //[R, WR]μステップからフルステップへの切替点速度default 0x027 (10bit) (15.25*val+7.63[step/s])
  set6470fsspd(MOTORE, 0x10);

  //電圧に関すること/////////////////
  //[R, WR]停止時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvalhold(MOTORE, 0x0F);
  //[R, WR]定速回転時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvalrun(MOTORE, 0xFF);
  //[R, WR]加速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvalacc(MOTORE, 0xFF);
  //[R, WR]減速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  set6470kvaldec(MOTORE, 0xFF);


  //電流に関すること
  //[R, WR]過電流しきい値default 0x8 (4bit) (375*val+375[mA])
  set6470ocdth(MOTORE, 0xF);
  //[R, WR]失速電流しきい値？default 0x40 (7bit) (31.25*val+31.25[mA])
  set6470stallth(MOTORE, 0x3F);

}
