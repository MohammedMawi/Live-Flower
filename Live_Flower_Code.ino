#include <Servo.h>

#include <CapacitiveSensor.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define PIN 4

#define NUMPIXELS 16

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

CapacitiveSensor cs_10_3 = CapacitiveSensor(10,3);

Servo myServo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int pRes = A0;
int lightValue;    

unsigned long previousMillis1;
unsigned long previousMillis2;
unsigned long previousMillis3;
unsigned long previousMillis4;
unsigned long previousMillis5;
unsigned long previousMillis6;

// defines pins numbers
const int trigPin = 12;
const int echoPin = 13;
const int servoPin = 5;
// defines variables
long duration;
int distance;
int angle = 100;

int activationDistance = 20;
int lightActivationValue = 500;
int touchActivationValue = 1000;

const int maxBrightness = 255;
const int minBrightness = 0;

int flashBrightness = 255;
int fadeBrightness = 255;

bool fadeUp = false;
bool flashUp = false;
bool servoUp = false;

int flashInterval = 1;
int fadeInterval = 2;
int servoInterval = 750;
int shiftInterval = 100;

const uint32_t WHITE = pixels.Color(255, 255, 255);
const uint32_t BLUE = pixels.Color(0, 0, 255);
const uint32_t GREEN = pixels.Color(0, 255, 0);
const uint32_t RED = pixels.Color(255, 0, 0);
const uint32_t YELLOW = pixels.Color(255, 128, 0);

void setup() {
  Serial.begin(9600);
  cs_10_3.set_CS_AutocaL_Millis(0xFFFFFFFF);
  myServo.attach(servoPin);  // attaches the servo on pin 9 to the servo object

  pinMode(pRes, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication


  pixels.begin();
  pixels.setBrightness(255);
  }


//used with yellowInterval if statement
int i = 16;
int j = 0;

void loop() {
  UltrasonicLogic();

  long touchValue = cs_10_3.capacitiveSensor(30);

  unsigned long start = millis();
  unsigned long currentMillis1 = millis();
  unsigned long currentMillis2 = millis();
  unsigned long currentMillis3 = millis();
  unsigned long currentMillis4 = millis();
  unsigned long currentMillis5 = millis();
  unsigned long currentMillis6 = millis();


  lightValue = analogRead(pRes);

  Serial.print("Light Value: ");
  Serial.print(lightValue);
  Serial.print("\t");
  Serial.print("Touch Value: ");
  Serial.print(touchValue);
  Serial.print("\t");
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("\t");
  Serial.print("Angle: ");
  Serial.println(myServo.read());


  //LIGHT IS ON
  if(lightValue > lightActivationValue){
    
    myServo.write(100);
    pixels.fill(YELLOW);
    
    //YELLOW GREEN SHIFT EFFECT
    if (currentMillis6 - previousMillis6 >= shiftInterval) {
      previousMillis6 = currentMillis6;
      i--;
      pixels.setPixelColor(i,GREEN);
      pixels.setPixelColor(i-1,GREEN);
      pixels.setPixelColor(i-2,GREEN);
      pixels.setPixelColor(i-3,GREEN);
      pixels.show();
      if (i == 0) {
        i = 16;
      }
    }

    //LIGHT ON AND TOO CLOSE
    if (distance < activationDistance) {
      myServo.write(distance);
      //  if (currentMillis5 - previousMillis5 >= servoInterval) {
      //   previousMillis5 = currentMillis5;
      //   if (myServo.read() == 100) {
      //     myServo.write(0);
      //   } else {
      //     myServo.write(100);
      //   }
      // }     
    }


    //LIGHT ON AND TOUCHED
    if (touchValue > touchActivationValue) {
      //RAINBOW EFFECT
      pixels.rainbow(random(0, 65535), random(0, 2));
      if (currentMillis4 - previousMillis4 >= shiftInterval) {
        previousMillis4 = currentMillis4;
        pixels.rainbow(random(0, 65535), random(0, 2));
        pixels.show();
      }
    }
    
  } 
  //LIGHT IS OFF
  else if (lightValue <= lightActivationValue) {
    myServo.write(0);
    //WHITE BLUE SHIFT EFFECT
    
    if(touchValue > touchActivationValue) { 
      pixels.fill(WHITE);
        if (fadeBrightness == maxBrightness) {
          fadeUp = false;
        } else if (fadeBrightness == minBrightness) {
          fadeUp = true;
        }

        if (!fadeUp) {
          fadeBrightness-= 5;
        } else {
          fadeBrightness+= 5;
        }
        pixels.setBrightness(fadeBrightness);
      if (currentMillis3 - previousMillis3 >= shiftInterval) {
        previousMillis3 = currentMillis3;
        j++;
        pixels.setPixelColor(j, BLUE);
        pixels.setPixelColor(j+1, BLUE);
        pixels.setPixelColor(j+2, BLUE);
        pixels.show();
        if (j == 16) {
          j = 0;
        }
      }
    }
  
    //TOO CLOSE WHILE LIGHT IS OFF
    if (distance < activationDistance)  {
      if (currentMillis2 - previousMillis2 >= flashInterval) {
        previousMillis2 = currentMillis2;

        if (flashBrightness == maxBrightness) {
          flashUp = false;
        } else if (flashBrightness == minBrightness) {
          flashUp = true;
        }

        if (!flashUp) {
        flashBrightness -= 45;
        } else {
        flashBrightness += 45;
        }

      pixels.fill(RED, 0, 16);
      pixels.setBrightness(flashBrightness);
      pixels.show();
    } 
  } 
  //FAR ENOUGH WHEN LIGHT IS OFF
    else if (distance >= activationDistance && touchValue < touchActivationValue) {
      if (currentMillis1 - previousMillis1 >= fadeInterval) {
        previousMillis1 = currentMillis1;

        if (fadeBrightness == maxBrightness) {
          fadeUp = false;
        } else if (fadeBrightness == minBrightness) {
          fadeUp = true;
        }

        if (!fadeUp) {
          fadeBrightness-= 5;
        } else {
          fadeBrightness+= 5;
        }

        pixels.fill(WHITE, 0, 16);
        pixels.setBrightness(fadeBrightness);
        pixels.show();
      }
    }

  }

}

void UltrasonicLogic() {
// Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  
  distance = duration * 0.034 / 2;  
}
