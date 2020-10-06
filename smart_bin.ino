
#include <FirebaseArduino.h>


#include  <ESP8266WiFi.h>


#define FIREBASE_HOST "firebase username or database address"
#define FIREBASE_AUTH "firebase key"
#define WIFI_SSID "" // Change the name of your WIFI
#define WIFI_PASSWORD "" // Change the password of your WIFI

#define trigPin1  5
#define echoPin1 0
#define trigPin2 14
#define echoPin2 2
#define trigPin3 12
#define echoPin3 13
long duration1, distance1,duration2,distance2,duration3, distance3,vol;
void setup() 
{

   Serial.begin (115200);
   pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT); 
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println ("");
  Serial.println ("WiFi Connected!");
    // Firebase.setFloat ("Status",1);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  
}
  

void loop()
{ distance();


}
void distance()
{ 
  while(1)
{

  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);

  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 /2) / 29.1;

  delay(500);
  digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin2, HIGH);

  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 /2) / 29.1;

  delay(500);
  digitalWrite(trigPin3, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin3, HIGH);

  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = (duration3 /2) / 29.1;

  delay(500);
volume();

  }
  }

void volume()
{
  while(1)
  {
    if(distance>0)
{  
  vol=3.14*distance3*distance2;
  Firebase.setFloat ("Volume",vol);
Serial.print(vol);
}
else if(distance1<0)
 { vol=0; 
  Firebase.setFloat ("Volume",vol);
 }
 else if(distance2>0)
 {    vol=3.14*distance3*distance2;
 // lcd.clear(); 
  //lcd.print(" Bin is full plz pick it up");
      if(vol==0)
  { 
    Firebase.setFloat ("Volume",vol);
    Serial.print("plz pick it up1"); 
    }
 else 
 Serial.print("not full");
 }
 else if(distance2<0)
 {  vol=3.14*distance3*10.5;
    Firebase.setFloat ("Volume",vol);
 }
  else if(distance2<0)
 {  
  vol=3.14*distance3*10.5;
   if(vol==0)
    {  
     vol=0;
     Firebase.setFloat ("Volume",vol);
     Serial.print("plz pick it up2");
    }
    else
    Serial.print("not full2");
 }

 else if(distance3>0)
  { 
    vol=3.14*distance3*10.5;
    Firebase.setFloat ("Volume",vol);
    Serial.print("plz pick it up3");
  }
    else if(distance3>0)
 {  
  vol=3.14*distance3*10.5;
  if(vol==0)
  { 
    vol=0;
    Firebase.setFloat ("Volume",vol);
     Serial.print("plz pick it up2");
  }
  else
    Serial.print("not full2");
 }
  }
}
