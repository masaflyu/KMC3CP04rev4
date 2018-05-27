#include <SD.h>


void gCodeOpen(String filename);

String readNewGCodeALine();

void readGcode();

void processGcode(char *gline);

int letterSearch(char * elml , char letter);


