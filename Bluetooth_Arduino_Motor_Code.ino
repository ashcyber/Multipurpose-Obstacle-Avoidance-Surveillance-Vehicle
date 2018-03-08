Arduino Code *************************************************************
#include <AFMotor.h>      //add Adafruit Motor Shield library
#include <Servo.h>        //add Servo Motor library            
#include <NewPing.h>      //add Ultrasonic sensor library
char voice;
#define TRIG_PIN A0 // Pin A0 on the Motor Drive Shield soldered to the ultrasonic sensor
#define ECHO_PIN A1 // Pin A1 on the Motor Drive Shield soldered to the ultrasonic sensor
#define MAX_DISTANCE 300 // sets maximum useable sensor measuring distance to 300cm
#define MAX_SPEED 200 // sets speed of DC traction motors to 150/250 or about 70% of full speed - to get power drain down.
#define MAX_SPEED_OFFSET 40 // this sets offset to allow for differences between the two DC traction motors
#define COLL_DIST 40                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          // sets distance at which robot stops and reverses to 30cm
#define TURN_DIST COLL_DIST+20 // sets distance at which robot veers away from object
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // sets up sensor library to use the correct pins to measure distance.

AF_DCMotor leftMotor1(1, MOTOR12_1KHZ); // create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor rightMotor1(3, MOTOR34_1KHZ);// create motor #3, using M3 output, set to 1kHz PWM frequency
Servo myservo;


int leftDistance, rightDistance; //distances on either side
int curDist = 0;
String motorSet = "";
int speedSet = 0;

void turnRight();
void turnLeft();
void moveStop();
int readPing();
void moveForward();
void moveBackward();
void turnAround();
void compareDistance();
void changePath();
void anti_collision();


void setup()
{
  Serial.begin(9600);
  myservo.attach(10);  // attaches the servo on pin 10 (SERVO_1 on the Motor Drive Shield to the servo object
  myservo.write(90); // tells the servo to position at 90-degrees ie. facing forward.
  delay(1000); // delay for one seconds
}

void loop()
{

  while (Serial.available()) { //Check if there is an available byte to read
    delay(20); //Delay added to make thing stable
    char c = Serial.read(); //Conduct a serial read
    voice = c;
  }

  switch (voice) {
    case '6' :
      anti_collision();
      break; 
      
    case '2':
      back_car();
      voice = ' ';
      break;

    case '1':
      forward_car();
      voice = ' ';
      break; 
      
    case '4':
      right_car();
      voice = ' ';
      break; 
      
    case '3':
      left_car();
      voice = ' ';
      break; 
      
    case '5':
      stop_car();
      voice = ' ';
      break; 
      

  }

}

void anti_collision() {
  myservo.write(90);  // move eyes forward
  delay(10);
  curDist = readPing();   // read distance
  if (curDist < COLL_DIST) {
    changePath();
  }  // if forward is blocked change direction
  moveForward();  // move forward
  delay(500);
}



void changePath() {
  moveStop();   // stop forward movement
  myservo.write(36);  // check distance to the right
  delay(500);
  rightDistance = readPing(); //set right distance
  delay(500);
  myservo.write(144);  // check distace to the left
  delay(700);
  leftDistance = readPing(); //set left distance
  delay(500);
  myservo.write(90); //return to center
  delay(100);
  compareDistance();
}


void compareDistance()   // find the longest distance
{
  if (leftDistance > rightDistance) //if left is less obstructed
  {
    turnLeft();
  }
  else if (rightDistance > leftDistance) //if right is less obstructed
  {
    turnRight();
  }
  else //if they are equally obstructed
  {
    turnAround();
  }
}


//-------------------------------------------------------------------------------------------------------------------------------------

int readPing() { // read the ultrasonic sensor distance
  delay(70);
  unsigned int uS = sonar.ping();
  int cm = uS / US_ROUNDTRIP_CM;
  return cm;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void moveStop() {
  leftMotor1.run(RELEASE);
  rightMotor1.run(RELEASE);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void moveForward() {
  motorSet = "FORWARD";
  leftMotor1.run(FORWARD);      // turn it on going forward
  rightMotor1.run(FORWARD);     // turn it on going forward
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    leftMotor1.setSpeed(speedSet);
    rightMotor1.setSpeed(speedSet);
    delay(5);
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------
void moveBackward() {
  motorSet = "BACKWARD";
  leftMotor1.run(BACKWARD);     // turn it on going backward
  rightMotor1.run(BACKWARD);    // turn it on going backward
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    leftMotor1.setSpeed(speedSet);
    rightMotor1.setSpeed(speedSet);
    delay(5);
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------
void turnRight() {
  motorSet = "RIGHT";
  leftMotor1.run(FORWARD);      // turn motor 1 forward
  rightMotor1.run(BACKWARD);    // turn motor 3 backward
  rightMotor1.setSpeed(speedSet + MAX_SPEED_OFFSET);
  delay(500); // run motors this way for 1500
  motorSet = "FORWARD";
  leftMotor1.run(FORWARD);      // set both motors back to forward
  rightMotor1.run(FORWARD);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void turnLeft() {
  motorSet = "LEFT";
  leftMotor1.run(BACKWARD);      // turn motor 1 backward
  leftMotor1.setSpeed(speedSet + MAX_SPEED_OFFSET);
  rightMotor1.run(FORWARD);     // turn motor 3 forward
  delay(500); // run motors this way for 1500
  motorSet = "FORWARD";
  leftMotor1.run(FORWARD);      // turn it on going forward
  rightMotor1.run(FORWARD);     // turn it on going forward
}
//-------------------------------------------------------------------------------------------------------------------------------------
void turnAround() {
  motorSet = "RIGHT";
  leftMotor1.run(FORWARD);      // turn motor 1 forward
  rightMotor1.run(BACKWARD);    // turn motor 3 backward
  rightMotor1.setSpeed(speedSet + MAX_SPEED_OFFSET);
  delay(1700); // run motors this way for 1700
  motorSet = "FORWARD";
  leftMotor1.run(FORWARD);      // set both motors back to forward
  rightMotor1.run(FORWARD);
}

void forward_car()
{
  delay(1000);
  leftMotor1.run(FORWARD);
  leftMotor1.setSpeed(200);
  rightMotor1.run(FORWARD);
  rightMotor1.setSpeed(200);
  delay(2000);
  leftMotor1.run(RELEASE);
  rightMotor1.run(RELEASE);
}

void back_car()
{
  delay(1000);
  leftMotor1.run(BACKWARD);
  leftMotor1.setSpeed(200);
  rightMotor1.run(BACKWARD);
  rightMotor1.setSpeed(200);
  delay(2000);
  leftMotor1.run(RELEASE);
  rightMotor1.run(RELEASE);
}

void right_car()
{
  leftMotor1.run(FORWARD);
  leftMotor1.setSpeed(200);
  rightMotor1.run(BACKWARD);
  rightMotor1.setSpeed(200);
  delay(500);
  leftMotor1.run(RELEASE);
  rightMotor1.run(RELEASE);
}

void left_car()
{
  leftMotor1.run(BACKWARD);
  leftMotor1.setSpeed(200);
  rightMotor1.run(FORWARD);
  rightMotor1.setSpeed(200);
  delay(500);
  leftMotor1.run(RELEASE);
  rightMotor1.run(RELEASE);
}



void stop_car ()
{
  leftMotor1.run(RELEASE);
  rightMotor1.run(RELEASE);
}




