
#include <Servo.h>

Servo servoBase, servoShoulder, servoElbow, servoWristRotation, servoGripper;

#define S0 3
#define S1 4
#define S2 7
#define S3 12
#define sensorOut 2

// Stores frequency read by the photodiodes
int red = 0;
int green = 0;
int blue = 0;

int pos = 0;    // variable to store the servo position

int servoShoulderPosition = 80; // > 45 back ( opisite side)
int servoElbowPosition  = 100; // > 0 down
int servoWristRotationPosition  = 0;
int servoGripperPosition  = 0; // > 90 up
int servoBasePosition = 40; //   >145 Left

//#define metalDetector 4


void setup() {
  servoShoulder.attach(10); 
  servoElbow.attach(9);  
  servoBase.attach(11);  
  servoWristRotation.attach(6); 
  servoGripper.attach(5); 

  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);

  // Setting frequency
  // scaling to 100%
    digitalWrite(S0,HIGH);
    digitalWrite(S1,LOW);


  //pinMode(metalDetector, INPUT);

  Serial.begin(9600);

  moveServoSmoothly(servoBase, servoBasePosition);
  delay(500);
  moveServoSmoothly(servoGripper, servoGripperPosition);
  delay(500);
  moveServoSmoothly(servoWristRotation, servoWristRotationPosition);
  delay(500);
  moveServoSmoothly(servoShoulder, servoShoulderPosition);
  delay(500);
  moveServoSmoothly(servoElbow, servoElbowPosition);
  delay(2000);
}

void loop() {
  moveServoSmoothly(servoShoulder, 80); // up
  moveServoSmoothly(servoBase, servoBasePosition); // intitial position base
  moveServoSmoothly(servoElbow, servoElbowPosition);


  //Serial.print("Color detected");
  color();
  
   if(red<blue && red<green && red<40){
      Serial.print("    RED     ");
      delay(1000);
   }
   else if(blue < red && blue < green) {
      Serial.print("    BLUE    ");
      moveToPositionOne();
      delay(1000);
   }
   else if (green < red && green < blue) {
      Serial.print("    GREEN   ");
      moveToPositionTwo();
      delay(1000);
   }  
   else {
      Serial.print("   NO COLOR   ");
      Serial.print("   DETECTED   ");
     delay(1000);
  }

  Serial.println();
  delay(1000);
  
}

void moveServoSmoothly(Servo servo, int targetPosition) {
  int currentPosition = servo.read();

  int increment = (targetPosition > currentPosition) ? 1 : -1;

  for (int pos = currentPosition; pos != targetPosition; pos += increment) {
    servo.write(pos);
    delay(20); // Delay for smoother movement, adjust as needed
  }
} 

void moveToPositionOne() {
    // move servoElbow down  a little bit to pick an object
    moveServoSmoothly(servoElbow, 100); 
    delay(1500);
    // move servoShoulder down to pick an object 
    moveServoSmoothly(servoShoulder, 45); 
    delay(1500);
    // Close Gripper
    moveServoSmoothly(servoGripper, 120); 
    delay(1500);
    // move servoShoulder up to go to position 1
    moveServoSmoothly(servoShoulder, 80); 
    // move elbow up  
    moveServoSmoothly(servoElbow, 125); 
    // rotate base left side 100 degree
    moveServoSmoothly(servoBase, 80);
    delay(1500);
    // move shoulder down to put the object 
    moveServoSmoothly(servoShoulder, 60); // move shoulder down
    // move servo elbow down 
    moveServoSmoothly(servoElbow, 109); 
    // Open the gripper 
    moveServoSmoothly(servoGripper, servoGripperPosition); 
    delay(1000);
  }

  void moveToPositionTwo() {
     // move servoElbow down  a little bit to pick an object
    moveServoSmoothly(servoElbow, 100); 
    delay(1500);
    // move servoShoulder down to pick an object 
    moveServoSmoothly(servoShoulder, 45); 
    delay(1500);
    // Close Gripper
    moveServoSmoothly(servoGripper, 120); 
    delay(1500);
    // move servoShoulder up to go to position 1
    moveServoSmoothly(servoShoulder, 80); 
    // move elbow up  
    moveServoSmoothly(servoElbow, 125); 
    // rotate base left side 100 degree
    moveServoSmoothly(servoBase, 0);
    delay(1500);
    // move shoulder down to put the object 
    moveServoSmoothly(servoShoulder, 60); // move shoulder down
    // move servo elbow down 
    moveServoSmoothly(servoElbow, 109); 
    // Open the gripper 
    moveServoSmoothly(servoGripper, servoGripperPosition); 
    delay(1000);
  }

  void color() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  red = pulseIn(sensorOut, LOW);
  delay(50);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  green = pulseIn(sensorOut, LOW);
  delay(50);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  blue = pulseIn(sensorOut, LOW);
  delay(50);
}

  