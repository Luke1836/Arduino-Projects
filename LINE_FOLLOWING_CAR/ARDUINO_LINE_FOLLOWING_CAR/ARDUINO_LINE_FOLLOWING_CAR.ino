//including the libraries
#include <AFMotor.h>

//defining pins and variables
#define lefts A3
#define rights A1

//defining motors
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(3, MOTOR12_1KHZ);


void setup() {
  //Setting the motor speed
  motor1.setSpeed(180);
  motor2.setSpeed(180);

  //Declaring PIN input types
  pinMode(lefts,INPUT);
  pinMode(rights,INPUT);
  //Begin serial communication
  Serial.begin(9600);
  
}

void loop(){
  //Printing values of the sensors to the serial monitor
  Serial.println(analogRead(lefts));
  Serial.println(analogRead(rights));
  delay(100);
  //line detected by both
  if(analogRead(lefts)<=350 || analogRead(rights)<=350){
    //Forward
    delay(100);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }
  //line detected by left sensor
  else if(analogRead(lefts)<=370 && !analogRead(rights)<=370){
    //turn left
    motor1.run(FORWARD);
    delay(100);
    motor2.run(BACKWARD);    
  }
  //line detected by right sensor
  else if(!analogRead(lefts)<=370 && analogRead(rights)<=370){
    //turn right
    motor1.run(BACKWARD);
    delay(100);
    motor2.run(FORWARD);   
  }
  //line detected by none
  else if(!analogRead(lefts)<=370 && !analogRead(rights)<=370){
    //stop
    motor1.run(RELEASE);
    delay(100);
    motor2.run(RELEASE);   
  }
}
