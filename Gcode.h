#include <SD.h>

void gCodeOpen(String filename);

void readGcode();

int isLineLoaded(char* strbuffer);

bool loadStringToBuffer(File  file , char* strbuffer , int bufferlength , int loadlength );

int cutALineFromBuffer(char* strbuffer, char* linestring);

void processGcode(char *gline);

int letterSearch(char * elml , char letter);


