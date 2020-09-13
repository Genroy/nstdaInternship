
#include "PololuDriver.h"
#include "Ramps.h"
#include <SimpleTimer.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16,2); //lcd fo type 8574T
//LiquidCrystal_I2C lcd(0x3F,16,2); //lcd fo type 8574AT

//#define rxPin 17
//#define txPin 16
//SoftwareSerial ram = SoftwareSerial(rxPin,txPin);

const int Y_STEP_PIN = 60;
const int Y_DIR_PIN = 61;
const int Y_ENABLE_PIN = 56;

const int X_STEP_PIN = 54;
const int X_DIR_PIN = 55;
const int X_ENABLE_PIN = 38;

#define LED_PIN 13

volatile int roll = 5000; // สั่งให้หมุน

volatile int lcdlight = 5000;
//----------------------------------------------
static int lcdmomo = 10000;
//------------------------------------------

//------------------------------
volatile int keepS;

void setup() {

  lcd.begin();
  lcd.print("Hello Hello");
  delay(4000);
  lcd.clear();
  lcd.print("Get Command");
  lcd.setCursor(0, 1);   
  lcd.print("on your Mobile");
  delay(3000);

  //ram.begin(9600);
  Serial.begin(115200);
  Serial2.begin(115200);
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(Y_STEP_PIN,OUTPUT);
  pinMode(Y_DIR_PIN,OUTPUT);
  pinMode(Y_ENABLE_PIN,OUTPUT);
  digitalWrite(Y_ENABLE_PIN,HIGH);
  digitalWrite(Y_DIR_PIN,LOW);

  pinMode(X_STEP_PIN,OUTPUT);
  pinMode(X_DIR_PIN,OUTPUT);
  pinMode(X_ENABLE_PIN,OUTPUT);
  digitalWrite(X_ENABLE_PIN,HIGH);
  digitalWrite(X_DIR_PIN,LOW);

}

void loop() {

door();  //เปิดปิดประตูรั้ว
ses(); // แปลงค่า เป็น Int เพื่อสั่งทำ
countTm();//นับเวลาหน้าจอ LCD
level();//ปรับระดับความเร็ว

}//loop

void door(){

 static unsigned long Timedoor = millis();
 
  
  if(keepS == 7)
  {     
    digitalWrite(X_ENABLE_PIN,LOW);
    digitalWrite(X_DIR_PIN,LOW);
   
    if((millis() - Timedoor)> lcdmomo){ 
    Timedoor = millis();
    digitalWrite(X_ENABLE_PIN,HIGH);
               
    }
    
  }
  
 else if(keepS == 8)
  {     
    digitalWrite(X_ENABLE_PIN,LOW);
    digitalWrite(X_DIR_PIN,HIGH);
    
    if((millis() - Timedoor)> lcdmomo){ 
    Timedoor = millis();
    digitalWrite(X_ENABLE_PIN,HIGH);
               
    }
    
  }
    digitalWrite(X_STEP_PIN,HIGH);
    delayMicroseconds(1500);   
    digitalWrite(X_STEP_PIN,LOW);

}//door

void level(){

 if(keepS == 3)
  {   
    digitalWrite(Y_ENABLE_PIN,HIGH);
    
  }//1 if

 else if(keepS == 4)
  {   
    digitalWrite(Y_ENABLE_PIN,LOW);
    digitalWrite(Y_DIR_PIN,HIGH);
  }//1 if
  
 if(keepS == 5)
  {   
    roll = 5000;
  }//1 if

  else if(keepS == 6)
  {   
    roll = 1000;
  }//1 if

    digitalWrite(Y_STEP_PIN,HIGH);
    delayMicroseconds(roll);   
    digitalWrite(Y_STEP_PIN,LOW);

}//level


void ses(){
  
  static int state = 0;
  static int index = 0;
  static char Buffer[2];
  static int va,va2;

 keepS=va;

Serial.println(keepS);

  if(Serial2.available()>0){
    char data = Serial2.read();

    va2= atoi(data);
    
   if(data == '1') 
   { 
    lcd.clear();
    lcd.print("Turn OFF Light");
    
   }

   else if (data == '2') 
   { 
    lcd.clear();
    lcd.print("Turn ON Light");
    
   }

   else if (data == '3') 
   { 
    lcd.clear();
    lcd.print("Turn OFF Roll");
   }
   
   else if (data == '4') 
   { 
    lcd.clear();
    lcd.print("Turn ON Roll");
   }
   
   else if (data == '5') 
   { 
    lcd.clear();
    lcd.print("Rolling LEVEL 1");
   }
   
   else if (data == '6') 
   { 
    lcd.clear();
    lcd.print("Rolling LEVEL 2");
   }

   else if (data == '7') 
   { 
    lcd.clear();
    lcd.print("Door are Closing");
   }

   else if (data == '8') 
   { 
    lcd.clear();
    lcd.print("Open The GATE!");
   }
    
    
    switch(state){
    case 0: if(data == '#'){
        index = 0;
        state = 1;
      }//if
      break;
      
    case 1: if(data == ':'){
        Buffer[index] = '\0';
       va = atoi(Buffer);
       index = 0;
        state = 0;
      }//if 
      else{
        Buffer[index] = data;
        index++;
        }//else

  }//switch
  }//serial
}//void

void countTm(){

static unsigned long Timecount = millis();
  if((millis() - Timecount)> 10000){
  Timecount = millis();  
  lcd.clear();     
  lcd.print("Get Command");
  lcd.setCursor(0, 1);   
  lcd.print("on your Mobile");
  }

}//count Tm
