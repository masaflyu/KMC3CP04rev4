void set6470abspos(char spino , long val);
void set6470elpos(char spino , long val);
void set6470mark(char spino , long val);
void set6470acc(char spino , long val);
void set6470dec(char spino , long val);
void set6470maxspeed(char spino , long val);
void set6470minspeed(char spino , long val);
void set6470fsspd(char spino , long val);
void set6470kvalhold(char spino , long val);
void set6470kvalrun(char spino , long val);
void set6470kvalacc(char spino , long val);
void set6470kvaldec(char spino , long val);
void set6470intspd(char spino , long val);
void set6470stslp(char spino , long val);
void set6470fnslpacc(char spino , long val);
void set6470fnslpdec(char spino , long val);
void set6470ktherm(char spino , long val);
void set6470ocdth(char spino , long val);
void set6470stallth(char spino , long val);
void set6470stepmode(char spino , long val);
void set6470alareen(char spino , long val);
void set6470config(char spino , long val);

long get6470abspos(char spino);
long get6470elpos(char spino);
long get6470mark(char spino);
long get6470speed(char spino);
long get6470acc(char spino);
long get6470dec(char spino);
long get6470maxspeed(char spino);
long get6470minspeed(char spino);
long get6470fsspd(char spino);
long get6470kvalhold(char spino);
long get6470kvalrun(char spino);
long get6470kvalacc(char spino);
long get6470kvaldec(char spino);
long get6470intspd(char spino);
long get6470stslp(char spino);
long get6470fnslpacc(char spino);
long get6470fnslpdec(char spino);
long get6470ktherm(char spino);
long get6470adcout(char spino);
long get6470ocdth(char spino);
long get6470stallth(char spino);
long get6470stepmode(char spino);
long get6470alareen(char spino);
long get6470config(char spino);
long get6470status(char spino);

void setChainNum(char num);

char busypin(char spino);

void l6470run(char spino, int dia, long spd);

void l6470stepclock(char spino, int dia);

void l6470move(char spino, int dia,long n_step);

void l6470goto(char spino, long pos);

void l6470gotodia(char spino, int dia,int pos);

void l6470gountil(char spino, int act,int dia,long spd);

void l6470relesesw(char spino, int act,int dia);

void l6470gohome(char spino);

void l6470gomark(char spino);

void l6470resetpos(char spino);

void l6470resetdevice(char spino);

void l6470softstop(char spino);

void l6470hardstop(char spino);

void l6470softhiz(char spino);

void l6470hardhiz(char spino);

void transfer6470(char spino, int add, int bytes, long val);

long get6470param(char spino , int add , int bytes);

void send6470(char spino, unsigned char data);

void send6470force(char spino, unsigned char data);

void l6470busydelay(char port,long time);


