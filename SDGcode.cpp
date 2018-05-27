#include <SD.h>
#include "Serial.h"
#include "SDGcode.h"
#include "SDText.h"




////--------------------------------------------------------------------
////センサ等
//
////温度センサ値平均取得用サンプル数
//const int Tempavrgnum = 20;
//
//
//
//const double PLAThermal = 200.0;
//const double ABSThermal = 260.0;
//
////Gコード読み取り処理の停止
//bool hotwait = 0;
//double commandtemp = 0.0;
//double commandwaittemp = 0.0;
//
//double extrudemms = 0.0;
//
//
////センサ値格納
//double headtemp = 10.0;
//double recentheadtemp[ Tempavrgnum ] = { 20.0 } ;
//
//
//
//
//
//const int readlength = 64;
////読み取り済みGコードデータのバッファ長(readlength以上)
//const int LENrecentreaded = 192;
////コメント付きGコード1行の最大長さ
//const int GLineMaxLength = 200;
////コメント無しGコード1行の最大長さ;
//const int GcodeMaxLength = 100;
////Gコード要素の最大長さ
//const int GElementMaxLength = 20;
////Gコード要素の最大個数
//const int GElementMaxNum = 20;
//
////読み取り済みだが未処理のGCODEデータ
////char recentreaded[LENrecentreaded];  //内容
//



//Gコードファイルのハンドル
File Gfile;

//Gコードを格納するバッファ
//char* strbuf = NULL;

//Gコード格納バッファに一度に追加する文字列の長さ
const int LoadLengthToStringBuffer = 200;

//Gコード格納バッファの長さ
const int LengthOfStringBuffer = 1000;


//読み取り文字列のバッファ
char stringbuffer[LengthOfStringBuffer] = "";

////コンストラクタ風
//void gCodeConstructor(){
//  stringbuffer
//}





void gCodeOpen(String filename) {

  Gfile = SD.open(filename);
  if (Gfile) {
    Serial.print(filename);
    Serial.print(F(" open\r\n"));
  } else {
    Serial.print(filename);
    Serial.print(F(" does not exist\r\n"));
  }
  //recentreaded[0] = '\0';

}






String readNewGCode() {
  SPIselect(0);
}





String readNewGCodeALine() {
  //if( strbuf == NULL )return NULL;
  if ( isLineLoaded( stringbuffer ) )
  {

  }
  else
  {
    bool loadable;
    loadable = loadStringToBuffer( Gfile , stringbuffer , LengthOfStringBuffer , LoadLengthToStringBuffer);
    if ( loadable == false) return "";
  }

  char stringaline[LoadLengthToStringBuffer];
  cutALineFromBuffer(stringbuffer , LengthOfStringBuffer , stringaline , LoadLengthToStringBuffer);
  return stringaline;
}





////readGcode()
//void readGcode() {
//  char cbuffer[readlength + 20];
//
//  SPIselect(0);
//  //--------------------------------------------------------------------
//  //もし読み取り済みコードに完全な行が無ければ(=>Gcodeに改行が無ければ)
//  //新たにSDからreadする．改行が含まれるかを調査する．
//  //改行コードが含まれない=>1行以上読み取ってない
//  if (strstr(recentreaded, "\r") == NULL && strstr(recentreaded, "\n") == NULL) {
//    int len = Gfile.available();
//    if (len) {
//      if (len > readlength) len = readlength;
//      Gfile.read(cbuffer, len);
//      cbuffer[len] = '\0';
//
//      strcat( recentreaded , cbuffer);                          //★recentreadedに入るものに注意
//
//      //      Serial.println("SDread:____________________________");
//      //      Serial.println(recentreaded);
//      //      Serial.println("SDreadend:`````````````````````````");
//
//    } else {
//      Serial.print(F("GCODE.gco READ END\r\n"));
//      while (1) {
//        Serial.print(F("Infinite Loop\r\n"));
//        delay(1000);
//      }
//    }
//  }
//
//  //--------------------------------------------------------------------
//  //改行を検索してそれ以前を取り出し動作させる．
//  //また，残った文字列を次回以降使えるように文字配列に格納する．
//
//  //strtokは分割対象を直接書き換えてしまう．コピーして保護
//  char recentreadcpy[LENrecentreaded];
//  strcpy ( recentreadcpy , recentreaded );
//  char *tok;
//  tok = strtok( recentreadcpy , "\r\n" );
//
//  //Serial.println("read:__________________");
//  //Serial.println(tok);
//  //Serial.println("readend:```````````````");
//
//  processGcode(tok);
//  //Serial.println(tok);
//
//  //--------------------------------------------------------------------
//  //残った文字列をrecentreadedに格納する
//  int processedlength = strlen(tok);
//  //直後にある改行コードを含める
//  while (recentreaded[processedlength] == '\r' || recentreaded[processedlength] == '\n')processedlength++;
//  //ポインタをprocessedlength分だけ進める
//  char * newreadpos = recentreaded;
//  strcpy( recentreaded , newreadpos + processedlength);
//
//  //  Serial.println("recent:______________________");
//  //  Serial.print("processedlength=");
//  //  Serial.println(processedlength);
//  //  Serial.println(recentreaded);
//  //  Serial.println("recentend:```````````````````");
//}
//






////◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
////processGcode()
//void processGcode(char *gline) {
//  Serial.println("===================================");
//  Serial.print("line :");
//  Serial.println(gline);
//
//  //--------------------------------------------------------------------
//  //ポインタ受け取りなので前段への影響を防ぐため，コピーして使う
//  char glinecpy[ GLineMaxLength ];
//  strcpy(glinecpy , gline);
//  Serial.print("cpy  :");
//  Serial.println( glinecpy );
//
//  //--------------------------------------------------------------------
//  //コメント削除
//  //0文字目に;があってもstrtokは;より後を戻してくる．これを防ぐため，別途対処する．
//  if (glinecpy[0] == ';')return;
//  //strtokで;より後を読まないことで，コメントを削除する．
//  char * gcode = strtok(glinecpy , ";");
//  Serial.print("code :");
//  Serial.println(gcode);
//
//
//  //--------------------------------------------------------------------
//  //空白で分割
//
//  char gcodecpy[ GcodeMaxLength ];
//  strcpy(gcodecpy , gcode);
//  char * element[ GElementMaxNum ];
//  int ie = 0;
//  element[0] = strtok(gcodecpy , " ");
//  Serial.print("e0   :");
//  Serial.println(element[0]);
//  while (element[ie] != NULL) {
//    ie++;
//    element[ie] = strtok(NULL , " ");
//  }
//
//  char gelmcpy[GElementMaxNum][GElementMaxLength];
//  for (int ia = 0; ia < ie; ia++) {
//    strcpy(gelmcpy[ia], element[ia]);
//  }
//
//  //--------------------------------------------------------------------
//  //空白行は飛ばす
//  if (ie == 0)return;
//
//  //--------------------------------------------------------------------
//  //1番目以降の要素を英字と数字に分ける
//  char elmletter[ GElementMaxNum ] ;
//  double elmnum[ GElementMaxNum ];
//
//  for (int ib = 1 ; ib < ie ; ib ++) {
//    elmletter[ib] = gelmcpy[ib][0];
//    char * elmn[20];
//    elmn[ib] = &( gelmcpy[ib][1] );
//    elmnum[ib] = atof( elmn[ib] );
//  }
//
//  //--------------------------------------------------------------------
//  //冒頭命令別に処理する
//  //strstrで読み取っている関係上，桁の小さい命令に誤認されるケースがある(G104なのにG1として処理)
//  //桁の小さい命令は後のほうに書くこと
//
//  //ベッド温度設定
//  if ( strstr(gelmcpy[0] , "M140" ) != NULL) {
//    Serial.println( "Heater wait" );
//
//  }
//  //指定温度S[°C]になるまで待機
//  else if ( strstr(gelmcpy[0] , "M109" ) != NULL) {
//    Serial.println( "Heater wait" );
//    for (int ic = 1 ; ic < ie ; ic++) {
//      if (elmletter[ic] == 'S' || elmletter[ic] == 's') {
//        commandwaittemp = elmnum[ic];
//      }
//    }
//    if (headtemp < commandwaittemp - 1.0) {
//      hotwait = 1;
//    }
//
//  }
//  //指定温度S[°C]になるまでヒーターをオン(M109命令があるのでWaitしなくていい)
//  else if ( strstr(gelmcpy[0] , "M104" ) != NULL) {
//    Serial.println( "Heater ON!" );
//    for (int ic = 1 ; ic < ie ; ic++) {
//      if (elmletter[ic] == 'S' || elmletter[ic] == 's') {
//        commandtemp = elmnum[ic];
//      }
//    }
//  }
//  //ファンOFF
//  else if ( strstr(gelmcpy[0] , "M107" ) != NULL) {
//    Serial.println( "FAN OFF!" );
//  }
//  //現在位置を原点に設定
//  else if ( strstr(gelmcpy[0] , "G92" ) != NULL) {
//    Serial.println( "Origin set" );
//  }
//  //原点復帰
//  else if ( strstr(gelmcpy[0] , "G28" ) != NULL) {
//    Serial.println( "Back to Origin" );
//  }
//  //G1
//  else if ( strstr(gelmcpy[0] , "G1" ) != NULL) {
//    Serial.println( "Move(Control)" );
//    //moveX(elmnum[letterSearch(elmletter,'X')];
//    for (int ic = 1 ; ic < ie ; ic++) {
//      if (elmletter[ic] == 'X' || elmletter[ic] == 'x') {
//        gotoXs(elmnum[ic], 10);
//      }
//    }
//    for (int ic = 1 ; ic < ie ; ic++) {
//      if (elmletter[ic] == 'Y' || elmletter[ic] == 'y') {
//        gotoYs(elmnum[ic], 10);
//      }
//    }
//    for (int ic = 1 ; ic < ie ; ic++) {
//      if (elmletter[ic] == 'Z' || elmletter[ic] == 'z') {
//        gotoZs(elmnum[ic], 3);
//      }
//    }
//    for (int ic = 1 ; ic < ie ; ic++) {
//      if (elmletter[ic] == 'F' || elmletter[ic] == 'f') {
//        extrudemms = elmnum[ic] / 60.0;
//      }
//    }
//    for (int ic = 1 ; ic < ie ; ic++) {
//      if (elmletter[ic] == 'E' || elmletter[ic] == 'e') {
//        if (elmnum[ic] >= 0) {
//          moveEs(elmnum[ic], extrudemms);
//        }
//      }
//    }
//  }
//  //G0
//  else if ( strstr(gelmcpy[0] , "G0" ) != NULL) {
//    Serial.println( "Move(FAST)" );
//    for (int ic = 1 ; ic < ie ; ic++) {
//      if (elmletter[ic] == 'X' || elmletter[ic] == 'x') {
//        gotoXs(elmnum[ic], 30);
//      }
//    }
//    for (int ic = 1 ; ic < ie ; ic++) {
//      if (elmletter[ic] == 'Y' || elmletter[ic] == 'y') {
//        gotoYs(elmnum[ic], 30);
//      }
//    }
//    for (int ic = 1 ; ic < ie ; ic++) {
//      if (elmletter[ic] == 'Z' || elmletter[ic] == 'z') {
//        gotoZs(elmnum[ic], 3);
//      }
//    }
//    for (int ic = 1 ; ic < ie ; ic++) {
//      if (elmletter[ic] == 'F' || elmletter[ic] == 'f') {
//        extrudemms = elmnum[ic] / 60.0;
//      }
//    }
//    for (int ic = 1 ; ic < ie ; ic++) {
//      if (elmletter[ic] == 'E' || elmletter[ic] == 'e') {
//        if (elmnum[ic] >= 0) {
//          moveEs(elmnum[ic], extrudemms);
//        }
//      }
//    }
//  }
//  else {
//    Serial.println("$$$$$$$$$$$$$$$$$$Unknow Command$$$$$$$$$$$$$$$$");
//  }


////◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
////letterSearch()
//int letterSearch(char * elml , char letter) {
//  for (int ic = 1 ; ic < GElementMaxNum ; ic++) {
//    if (elml[ic] == letter)return ic;
//  }
//  return NULL;
//}
