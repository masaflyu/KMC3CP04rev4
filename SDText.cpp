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






int cutALineFromBuffer(char* strbuffer, char* linestring){
  //strbufferの1行目を取り出す．
  
  do{
    linestring = strtok( strbuffer , "\r\n" );
    if (linestring == NULL) return 0;
  }while(strlen(linestring)==0); //長さが0より大きくなるまで繰り返す（

  strbuffer = linestring + strlen(linestring) + 1;  //strbufferポインタをlinestringの後ろへ移動

  return strlen(linestring);
}
