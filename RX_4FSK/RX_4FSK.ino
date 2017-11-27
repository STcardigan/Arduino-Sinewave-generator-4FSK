#ifndef cbi
#define cbi(sft, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr,bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define r_slope 80
unsigned long time;
unsigned long timetmp;
unsigned long timeans;
int tmp;
int prev = 0;
int check = false;
int max = 0;

unsigned int t1max = 8000; //00
unsigned int t1min = 6000;
unsigned int t2max = 5999; //01
unsigned int t2min = 4000;
unsigned int t3max = 3999; //10
unsigned int t3min = 2500;
unsigned int t4max = 2499; //11
unsigned int t4min = 0;
/*
unsigned int t1max = 8000; //00
unsigned int t1min = 4501;
unsigned int t2max = 4500; //01
unsigned int t2min = 3001;
unsigned int t3max = 3000; //10
unsigned int t3min = 2001;
unsigned int t4max = 2000; //11
unsigned int t4min = 0;
*/
int count =0;
int countc =0;
int chk=0;
int chkp=0;


void setup() {
  // put your setup code here, to run once
  Serial.begin(115200);
  sbi(ADCSRA,ADPS2);
  sbi(ADCSRA,ADPS1);
  sbi(ADCSRA,ADPS0 );
}

void loop() {
  // put your main code here, to run repeatedly:
  int tmp = analogRead(A0);
  if(tmp-prev > r_slope && check == false)
  {
    max = 0;
    check = true;
  }
  if(tmp > max)
  {
    max = tmp;
  }
  if(max-tmp > r_slope)
  {
    if(check == true)
    {
      //Serial.println(count);
      //Serial.println("ppp");
      //count = 0;
       if(chk==1){
          time = micros();
          timeans = time - timetmp;
          timetmp = time;
          //Serial.println(timeans);
       }
       if(chk==0){
          //Serial.println("ppp");
          //chk=1;
          time = micros();
          timetmp = time;
          //Serial.println(timetmp);
          //count++;
       }
       if(t1min<timeans && timeans<t1max &&chk==1 ){
          //Serial.println("0 0 ");
          countc = 2;
          //count++;
          //Serial.println(countc);
       }
       else if(t2min<timeans && timeans<t2max &&chk==1){
          //Serial.println("0 1 ");
          countc = 3;
          //count++;
          //Serial.println(countc);
       }
       else if(t3min<timeans && timeans<t3max &&chk==1){
          //Serial.println("1 0 ");
          countc = 4;
          //count++;
          //Serial.println(countc);
       }
       else if(t4min<timeans && timeans<t4max &&chk==1){
          //Serial.println("1 1 ");
          countc = 5;
          //count++;
          //Serial.println(countc);
       }
       count++;
       //Serial.println(count);
       chk=1;
       if(count == countc)
       {
          //Serial.println();
          count = 0;
          //chkp++;
          if(countc==2) {
            Serial.print("0 0 ");
            chk=0;
            chkp++;
          }
          else if(countc==3) {
            Serial.print("0 1 ");
            chk=0;
            chkp++;
          }
          else if(countc==4) {
            Serial.print("1 0 ");
            chk=0;
            chkp++;
          }
          else if(countc==5) {
            Serial.print("1 1 ");
            chk=0;
            chkp++;
          }
          if(chkp==4) {
            count=0;
            countc=0;
            chkp=0;
            chk=0;
            Serial.println();
          }
       }
       
    }
    check = false;
  }
  prev = tmp;

}
