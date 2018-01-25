
//Add library
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>



//Explicit

int myOutput = D0;
int myDelayTime =1000;
//การกำหนดค่าคงที่
//String wifiSSID=""
#define wifiSSID "MastreEWTC_2.4G"
#define wifiPassword "12345abcde"
#define firebaseHost "rmutsvnodemcu-9fa10.firebaseio.com"
#define firebaseKey "Xqp2pZu5Q7DveVWQbRwMF3HY0dAmUM5xMC8uibjQ"

int intIndex=0;
int intSwitch=0;

void setup() {

pinMode(myOutput,OUTPUT);
//  การกำหนดช่องทางในการ moritor
  Serial.begin(9600);
//การกำหนดข้อมูลเกี่ยวกับการเชื่อมต่อ wifi
WiFi.mode(WIFI_STA);
WiFi.begin(wifiSSID,wifiPassword);
Serial.println("Start Find WiFi");

while (WiFi.status()!= WL_CONNECTED)
{
//   ถ้า Condition True จะทำงานที่นี่

   Serial.print("#");
   delay(500);
   
  
  
}
//ถ้ามาทำงานตรงนี้คือ Connect WiFi ได้แล้ว
Serial.println();
Serial.println("Success Connect WiFi");
Serial.println(WiFi.localIP());

//ส่วนของการเชื่อมต่อ Firebase

  Firebase.begin(firebaseHost,firebaseKey);

}// setup

void loop() {
  
//  Serial.println("Hello Master UNG");
//  delay(2000);

//Check Connected Firebase

Firebase.setInt("myTimes",intIndex);
if(Firebase.failed()) 
{
//  เมื่อไหร่ก็ตามที่ไม่สามารถเข้าถึง Firebase 
  Serial.print("Cannot Connected Firebase :");
  Serial.println(Firebase.error());
  return;
  }

  Serial.print("Sucuess Connected Firebase Times ==> ");
  Serial.println(Firebase.getInt("myTimes"));

  intIndex = Firebase.getInt("myTimes");
 
  intIndex++;
  
 intSwitch =Firebase.getInt("Switch");
if(intSwitch==1) {

 digitalWrite(myOutput, LOW);    // turn the LED off by making the voltage LOW
   
}
else
{
   digitalWrite(myOutput, HIGH);
}


  
  delay(myDelayTime);


}// loop
