
//--------------------------------------------------------------------
//機構
const double PulleyDiameter = 18.5;
const double PulleyCircumference = 58.12;
const double X1step = 0.1453; //[mm]
const double Y1step = 0.1453; //[mm]
const double Z1step = 0.00375; //[mm]
const double Xmicrostep = 128;
const double Ymicrostep = 128;
const double Zmicrostep = 64;
const double X1microstep128 = 0.001135; //[mm]
const double Y1microstep128 = 0.001135; //[mm]
const double Z1microstep64 = 0.00005859; //[mm]

const double ExtrudeGearDiameter = 14.0;
const double ExtrudeGearCircumference = 43.98;
const double Extrude1step = 0.2199;
//const double Extrudemicrostep = 128;
//const double Extrude1microstep128 = 0.001718;
const double Extrudemicrostep = 32;
const double Extrude1microstep32 = 0.00687223;

const double XSize = 300;
const double YSize = 180;
const double ZSize = 105;
const double XLimitPos = -2.0;
const double YLimitPos = -10.0;
//const double ZLimitPos = 108.3;
//const double ZLimitPos = 106.3;

//const double ZLimitPos = 104; //1mmくらい空いてた
const double ZLimitPos = 104.2;

void moveX(double posmm);

void moveY(double posmm);

void moveZ(double posmm);

void gotoXs(double posmm, double mms);

void gotoYs(double posmm, double mms);

void gotoZs(double posmm, double mms);

void gotoEs(double posmm, double mms);

void initX();

void initY();

void initZ();

void motorDriverParamSet();


