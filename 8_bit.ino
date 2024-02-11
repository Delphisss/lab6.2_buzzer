#define LD 23
#define BT 22
hw_timer_t *My_timer = NULL;
int FF = 500000;


int D = FF/1175;
int A = FF/1760;
int B = FF/1976;
int G = FF/1568;
int F = FF/1480;
int E = FF/1319;


int Note[] = {D,D,A,A,B,B,A,G,G,F,F,E,E,D,
              A,A,G,G,F,F,E,A,A,G,G,F,F,E,
              D,D,A,A,B,B,A,G,G,F,F,E,E,D};
int Num_F = 0;

float lv[]={7,6,4,2,0.5};
bool doingWork = false;

void IRAM_ATTR button(){
  Num_F++;
  if(Num_F==5) Num_F=0;
}
void IRAM_ATTR onTimer(){
  digitalWrite(LD, !digitalRead(LD));
}


void setup() {
  Serial.begin(115200);
  Serial.println("Starting!!");
  pinMode(LD, OUTPUT);
  pinMode(BT, INPUT);
  My_timer = timerBegin(0, 80, true);
  attachInterrupt(BT,button,FALLING);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmEnable(My_timer);  
}

void loop() {
  for(int i=0;i<42;i++){
     timerAlarmWrite(My_timer, Note[i], true);
     timerAlarmEnable(My_timer);
     delay(2*Note[i]);
     timerAlarmDisable(My_timer);
     delay(lv[Num_F]*Note[i]);
  }
}
  
