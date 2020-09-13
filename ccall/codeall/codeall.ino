#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>     


//SoftwareSerial sserial(D6, D7); // RX | TX

#include <TridentTD_LineNotify.h>


char auth[] = "d4b1d55276794b36a68e23974e2ebc64";  
char linn[] = "3vXT2xs8Inh1MkITML7JRqt6iByYA7Z7Rd1sw2ehcUe";

#define light D2

volatile int sertov3;

void setup()
{
  WiFiManager wifiManager;
  wifiManager.resetSettings();  
  //sserial.begin(9600);
  EEPROM.begin(1200);
  Serial.begin(115200);
  pinMode(light , OUTPUT);

  wifiManager.autoConnect("Connect to 8266");
  Serial.println("connected...yeey :)");
  Blynk.begin(auth, WiFi.SSID().c_str(), WiFi.psk().c_str());
  
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V1)
{
  LINE.setToken(linn);
    int RelayStatus1 = param.asInt();
    if (RelayStatus1 == 0) 
  {  
    digitalWrite(light, LOW);
    LINE.notify("ปิดไฟให้แล้ว");
    Serial.write('#');
    Serial.print(1);
    Serial.print(':');
    Serial.println();
    //Serial.print("ปิดไฟ Turnning off Light");
  }

   else if (RelayStatus1 == 1) 
  {  
    digitalWrite(light, HIGH);
    LINE.notify("เปิดไฟให้แล้ว");
    Serial.write('#');
    Serial.print(2);
    Serial.print(':');
    Serial.println();
    //Serial.print("เปิดไฟ Turnning on Light");
   
  }

}//V1

BLYNK_WRITE(V2)
{
  LINE.setToken(linn);
  int Status2 = param.asInt();
  sertov3 = Status2;
  
    if (Status2 == 0) 
  {  
    //Serial.println("ปิด Servo");
    LINE.notify("ปิดตัวหมุนใหเรียบร้อยแล้วครับ");
    Serial.write('#');
    Serial.print(3);
    Serial.print(':');
    Serial.println();
   
  }

   else if (Status2 == 1) 
  {  
    //Serial.println("เปิด Servo");
    LINE.notify("ตัวหมุนถูกเปิดใช้งาน");
    Serial.write('#');
    Serial.print(4);
    Serial.print(':');
    Serial.println();
   
  }
  
}//V2

BLYNK_WRITE(V3)
{
  LINE.setToken(linn);
  int ser = param.asInt();
  
  
if(sertov3 == 1 && ser == 1){

    LINE.notify("หมุนระดับ 1");
    Serial.write('#');
    Serial.print(5);
    Serial.print(':');
    Serial.println();

}//if

else if(sertov3 == 1 && ser == 2){

    LINE.notify("หมุนระดับ 2");
    Serial.write('#');
    Serial.print(6);
    Serial.print(':');
    Serial.println();


}//else if
  
else if(sertov3 == 0 && ser >=1)
{
  LINE.notify("กรุณากดปุ่มเปิดตัวหมุนก่อนนะครับ^^");
}

}//V3

BLYNK_WRITE(V4){

  LINE.setToken(linn);
  int push = param.asInt();
  
  
   if(push == 0) 
  {     
    LINE.notify("ประตูรั้วได้ปิดเรียบร้อยแล้ว");
    Serial.write('#');
    Serial.print(7);
    Serial.print(':');
    Serial.println();
  }

  if(push == 1) 
  {  
    LINE.notify("ประตูรั้วได้ถูกเปิดออก");
    Serial.write('#');
    Serial.print(8);
    Serial.print(':');
    Serial.println();
  }
  
}


