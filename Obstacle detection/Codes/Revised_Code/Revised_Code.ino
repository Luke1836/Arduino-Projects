#include <Servo.h>

Servo myservo;

#define echoPin 5 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 6 //attach pin D3 Arduino to pin Trig of HC-SR04

#define in1 12
#define in2 10
#define in3 11
#define in4 3

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

int distance_0=0,distance_90=0,distance_180=0;
int threshold_distance=40;
int dir=0;


int distance_calc(){
  ///////////////////////ultrasonic distance calculation/////////////////////////////////////////////
  
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  return distance;
  }

void check_direction(){
  myservo.write(180);
  distance_180 = distance_calc();
  delay(200);
  
  myservo.write(0);
  delay(200);
  distance_0 = distance_calc();

  if(distance_180>distance_0)dir=1;
  else if(distance_0>distance_180)dir=2;
  }
void setup() {

  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
   

  myservo.attach(2);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  
  
}
void loop() {
  
  myservo.write(90);
  delay(200);
  distance_90 = distance_calc();

  if(distance_90<threshold_distance){

                digitalWrite(in1,LOW);
                digitalWrite(in2,LOW);
              
                digitalWrite(in3,LOW);
                digitalWrite(in4,LOW);
                check_direction();
                if(dir==1){
              
                digitalWrite(in1,HIGH);
                digitalWrite(in2,LOW);
              
                digitalWrite(in3,LOW);
                digitalWrite(in4,HIGH);
                  }
                
                else if(dir==2){
                  
                digitalWrite(in1,LOW);
                digitalWrite(in2,HIGH);
              
                digitalWrite(in3,HIGH);
                digitalWrite(in4,LOW);
                }
    }//dir change over
   else{
        digitalWrite(in1,HIGH);
        digitalWrite(in2,LOW);
              
        digitalWrite(in3,HIGH);
        digitalWrite(in4,LOW);
    }//keep moving
  
}
