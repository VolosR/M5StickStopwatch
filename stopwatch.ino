#include "stop.h"
#include "play.h"
#include "M5StickCPlus.h"
#include "DSEG7_Classic_Regular_16.h"
TFT_eSprite Disbuff = TFT_eSprite(&M5.Lcd);

#define grey 0x65DB
#define color 0xF251

int ss=0; //miliseconds/10
int s=0;   //seconds
int m=0;  //minutes

int lss[30];
int ls[30];
int lm[30];

String minutesL;
String secondsL;
String milisL;
int laps=0;
String lapTime[30];
int pom=0;  //debouncing button
int pom2=0;
int pres3 =0;//deboun

int fase=0;
int bright[4]={8,9,10,12};
int c=0;

void setup() {
   M5.begin();
   M5.Lcd.setRotation(0);
   M5.Lcd.fillScreen(BLACK);
   M5.Lcd.setSwapBytes(true);
   pinMode(26,INPUT_PULLUP);
   pinMode(39,INPUT_PULLUP);
   pinMode(25,OUTPUT);
   pinMode(0,INPUT_PULLUP);

   digitalWrite(25,1);
   M5.Axp.EnableCoulombcounter(); 
   M5.Axp.ScreenBreath(bright[0]);
   reset();
}

String seconds,minutes,milis;
String current,temp;

int winer=0;

long tt=0;
long tt2=0;

void loop() {

  if(fase<3){
  tt=millis();
  M5.Lcd.setFreeFont(&DSEG7_Classic_Regular_32);
  if(s<10) seconds="0"+String(s);else seconds=String(s);
  if(m<10) minutes="0"+String(m);else minutes=String(m);
  current=minutes+":"+seconds;

  
  if(current!=temp){
  M5.Lcd.drawString(current,10,30);
  temp=current;
  }
  
  if(ss<10) milis="0"+String(ss);else milis=String(ss);
  M5.Lcd.drawString(milis,60,76,7);
  }

  if(tt>tt2+8)
  {  
     tt2=tt;
     if(fase==1)
     ss++;
  }

  if(ss>99)
{
  s++;
  ss=0;
}
  if(s>59)
  {
    s=0;
    m++;
  }
 buttons(); 
}

void buttons()
{
  if(digitalRead(26)==0 )
  {
   if(pom==0)
   {
   if(fase==1){
   winer++;
   laps++;
   if(winer==1){
    M5.Lcd.fillRect(15,130,120,80,BLACK);
   M5.Lcd.drawString("LAP:",20,130,2);
   }
   if(winer>3){
      M5.Lcd.fillRect(15,144,120,70,BLACK);
      winer=1;
   }
   M5.Lcd.setFreeFont(&DSEG14_Classic_Mini_Regular_15);
     lss[laps]=ss;
     ls[laps]=s;
     lm[laps]=m; 

   if((lm[laps]-lm[laps-1])<10)
   minutesL="0"+String(lm[laps]-lm[laps-1]);
   else
   minutesL=String(lm[laps]-lm[laps-1]);

   if((ls[laps]-ls[laps-1])<10)
   secondsL="0"+String(ls[laps]-ls[laps-1]);
   else
   secondsL=String(ls[laps]-ls[laps-1]);

  int lsss=lss[laps]-lss[laps-1];
  if(lsss<0)
  lsss=lsss*-1;

  if(lsss<10)
  milisL="0"+String(lsss);
  else
  milisL=String(lsss);

   lapTime[laps-1]=minutesL+" : "+secondsL+" : "+milisL;
   M5.Lcd.drawString(lapTime[laps-1],18,130+winer*22);}
      
   if(fase==0)
   fase=1;
   pom=1; 
     }
  }else{pom=0;}

    if(digitalRead(0)==0 )
  {
   if(pom2==0)
     {
    fase++;
    if(fase==3)
    {
      
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setFreeFont(&DSEG14_Classic_Mini_Regular_15);
      M5.Lcd.drawString("TIME:",10,6,2);
      M5.Lcd.drawString("LAP:",10,50,2);
      M5.Lcd.drawString(current+":"+milis,10,28);
      for(int i=0;i<laps;i++){
      
      M5.Lcd.drawString(String(i+1)+".   "+lapTime[i],10,68+(14*i),2);}
      }
    if(fase>3)
       {
         
         reset();
         
       }
   
    pom2=1;
     }
  }else{pom2=0;}

 if(digitalRead(39)==0)
  {
    if(pres3==0)
        {
          pres3=1;
          c++;
          if(c>3)
          c=0;
          M5.Axp.ScreenBreath(bright[c]);
          M5.Lcd.fillRect(105,224,28,12,BLACK);
          for(int i=0;i<=c;i++)
          M5.Lcd.fillRect(105+(i*5)+(i*2),224,4,12,color); 
          }
    
    }else{pres3=0;}

  
  }
  void reset()
  {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.pushImage(7,75,48,48,stop);
    M5.Lcd.pushImage(30,136,72,72,play);
    M5.Lcd.drawString("STOPWATCH",14,7,2);
    M5.Lcd.drawString("BAT 72%",15,222,2);
    
    M5.Lcd.fillRect(105,224,4,12,color); 
    M5.Lcd.setFreeFont(&DSEG7_Classic_Regular_32);
    M5.Lcd.drawLine(0,220,128,220,grey);
    laps=0;
    lss[0]=0;
    ls[0]=0;
    lm[0]=0;
    ss=0;
    s=0;
    m=0;
    fase=0;
    winer=0;
  }
