#include <string.h>
#include <SD.h>





//char* getStrBuf(){
//  return stringbuffer;
//}





int isLineLoaded(char* strbuffer) {
  if( strpbrk( strbuffer , "\r\n" ) == NULL ){
    return 0;
  }
  else
  {
    return strcspn( strbuffer , "\r\n" );    
  }
}






bool loadStringToBuffer(File  file , char* strbuffer , int bufferlength , int loadlength ) {

  //Serial.print(F("FORDEBUG:@loadStringToBuffer() strbuffer="));
  //Serial.println(strbuffer);
  
  int unprocessedlength = file.available(); //未処理の文字列の長さを調べる

  char temporarybuffer[bufferlength];
  if ( unprocessedlength > 0 ) { //まだ未処理分がある場合
    if ( unprocessedlength > loadlength) {
      file.read(temporarybuffer , loadlength);
      temporarybuffer[loadlength];
    }
    else {
      file.read(temporarybuffer , unprocessedlength);
    }

    strcat( strbuffer , temporarybuffer);
  }
  else //未処理文字列が無い場合
  {
    Serial.print(F("FileEnd"));
  }


}






char* cutALineFromBuffer(char* strbuffer , int bufferlength , char* linestring , int linebuflength){
  //char linestring[ linebuflength ];
  
  //strbufferの1行目を取り出す．

  //Serial.print(F("FORDEBUG:@cutALIneFromBuffer()-begin strbuffer="));
  //Serial.println(strbuffer);
  
  do{
    strtok( strbuffer , "\r\n" );
    if (strbuffer == NULL) return 0;
  }while( strlen( strbuffer ) == 0 ); //長さが0より大きくなるまで繰り返す（

  //strbuffer = linestring + strlen(linestring) + 1;  //strbufferポインタをlinestringの後ろへ移動

  strcpy( linestring , strbuffer );
  
  strcpy( strbuffer , strbuffer + strlen( strbuffer ) + 1 ); //linestringより後の文字列をstrbufferに格納．  

  //Serial.print(F("FORDEBUG:@cutALIneFromBuffer()-end strbuffer="));
  //Serial.println(strbuffer);
  //Serial.print(F("FORDEBUG:@cutALIneFromBuffer()-end linestring="));
  //Serial.println(linestring);
  

  //return strlen(linestring);
  return linestring;
}
