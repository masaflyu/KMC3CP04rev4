#include <string.h>
#include <SD.h>



int isLineLoaded(char* strbuffer)
{
  if ( strpbrk( strbuffer , "\r\n" ) == NULL )
  {
    return 0;
  }
  else
  {
    return strcspn( strbuffer , "\r\n" );
  }
}






bool loadStringToBuffer(File  file , char* strbuffer , int bufferlength , int loadlength )
{

  int unprocessedlength = file.available(); //未処理の文字列の長さを調べる

  char temporarybuffer[loadlength + 1];
  if ( unprocessedlength > 0 ) { //まだ未処理分がある場合
    if ( unprocessedlength > loadlength) {
      file.read(temporarybuffer , loadlength);
      temporarybuffer[loadlength] = '\0';
    }
    else {
      file.read(temporarybuffer , unprocessedlength);
      temporarybuffer[unprocessedlength] = '\0';
    }

    strcat( strbuffer , temporarybuffer);

    //    Serial.print(F("FORDEBUG:@loadStringToBuffer()-end temporarybuffer="));
    //    Serial.flush();
    //    Serial.println(temporarybuffer);
    //    Serial.flush();
    //    Serial.print(F("FORDEBUG:@loadStringToBuffer()-end strbuffer="));
    //    Serial.flush();
    //    Serial.println(strbuffer);
    //    Serial.flush();

    return true;
  }
  else //未処理文字列が無い場合
  {
    Serial.print(F("FileEnd"));
    return false;
  }


}






char* cutALineFromBuffer(char* strbuffer , int bufferlength , char* linestring , int linebuflength)
{

  //strtok()により，最初に発見した改行コード(\r\n)を\0に置き換え
  do {
    strtok( strbuffer , "\r\n" );
    if (strbuffer == NULL) return 0;
  } while ( strlen( strbuffer ) == 0 ); //長さが0より大きくなるまで繰り返す（

  strcpy( linestring , strbuffer );   //linestring配列にstrbufferの1行分だけをコピー

  strcpy( strbuffer , strbuffer + strlen( strbuffer ) + 1 ); //linestringより2行目以降の文字列をstrbufferに格納．1行目を削除．

  //
  //  Serial.print(F("FORDEBUG:@cutALIneFromBuffer()-end strbuffer="));
  //  Serial.flush();
  //  Serial.println(strbuffer);
  //  Serial.flush();
  //  Serial.print(F("FORDEBUG:@cutALIneFromBuffer()-end linestring="));
  //  Serial.flush();
  //  Serial.println(linestring);
  //  Serial.flush();

  return linestring;
}
