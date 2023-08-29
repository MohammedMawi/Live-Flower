/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

#include <CapacitiveSensor.h>

CapacitiveSensor cs_4_2 = CapacitiveSensor(4,2);

Servo myServo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int pRes = A0;
int value;
int led = 3;


void setup() {
  myServo.attach(7);  // attaches the servo on pin 9 to the servo object
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);

  pinMode(led,OUTPUT);
 
  Serial.begin(9600);
  
  pinMode(pRes, INPUT);
}

void loop() {
  value = analogRead(pRes);
  Serial.print("Light Value: ");
  Serial.print(value);

  long start = millis();
  long total1 = cs_4_2.capacitiveSensor(30);

  Serial.print("\t");

  Serial.print(millis() - start);
  Serial.print("\t");

  Serial.println(total1);
  
  if(value > 100){
    myServo.write(100);
    
    if(total1 > 600){
        digitalWrite(led, HIGH);
      }
    else{
        digitalWrite(led, LOW);
      }
  }

  else{
    myServo.write(0);
  }
  
   
  
  

}

