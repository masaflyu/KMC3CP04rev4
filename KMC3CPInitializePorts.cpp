
#include "KMC3CPDefinePorts.h"
#include<Arduino.h>

void initializePorts(){

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

