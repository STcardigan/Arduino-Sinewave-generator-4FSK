#include<Wire.h>
#include<Adafruit_MCP4725.h>
#include<Adafruit_ADS1015.h>
Adafruit_MCP4725 dac;

#define defaultFreq 2000
#define freq0 500
#define freq1 750
#define freq2 1000
#define freq3 1250
int delayy[4];
const uint16_t S_DAC[4] = {2048, 4095, 2048, 0};
char inData[100];
int Amp = 4;
int Ndata;
int Ncycle = 0;

unsigned long time;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dac.begin(0x62);
  delayy[0] = (1000000 / freq0 - 1000000 / defaultFreq) ;
  delayy[1] = (1000000 / freq1 - 1000000 / defaultFreq) ;
  delayy[2] = (1000000 / freq2 - 1000000 / defaultFreq) ;
  delayy[3] = (1000000 / freq3 - 1000000 / defaultFreq) ;
  Serial.flush();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    Ndata=0;
    do{
      inData[Ndata] = Serial.read();
       //Serial.println((int)inData[n]);
    }while(inData[Ndata++] != -1);

    for (int i = 0; i < Ndata-1; i++) {
      for (int k = 7; k >= 0; k -= 2) {
        int tmp = inData[i] & 3;
       //Serial.println("===================");
       //Serial.println(tmp);
       //Serial.println("===================");
       if(tmp == 0){ //00
          Ncycle = 500/250;
       }
       else if(tmp == 1){ //01
          Ncycle = 750/250;
       }
       else if(tmp == 2){ //10
          Ncycle = 1000/250;
       }
       else if(tmp == 3){ //11
          Ncycle = 1250/250;
       }
        //Serial.println(Ncycle);
        for (int j = 0; j < Ncycle; j++) {
          //Serial.println(Ncycle);
          time = micros();
          for (int m = 0; m < 4; m++) {

            dac.setVoltage( (int)Amp * S_DAC[m]/4  , false);
            delayMicroseconds(delayy[tmp]);
            //Serial.println((int)Amp * S_DAC[m]/4);
          
          }
          //Serial.print("time  ");
          //Serial.println(time);
          
        }
        inData[i] >>= 2;
      }
    }
    dac.setVoltage(0, false);

  }
}
