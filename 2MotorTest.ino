
/* 
(NOTE - Move Both Arms At Middle Point Before Run This)

1 - Left Motor Forward 10 Steps 
2 - Left Motor Bakcward 10 Steps 
3 - Right Motor Forward 10 Steps 
4 - Right Motor Backward 10 Steps 

 */

// Variable declaration

// intialize end step for both rotation arm
const int endStep = 5200;

// intialize begin step for both rotation arm
const int beginStep = 0;

// Error indicator
bool errorIndicator = false;

// current step of left Current Position
int leftCurrentPosition = 100;

// current step of right Current Position
int rightCurrentPosition  = 100;

// Speed for motors
const int speedOfMotor = 500; // to increase speed , decrease this value (NOTE - this can't be equal to zero)
//-----------------------------------------------------------

//----Pin Number Initiate----
const int leftMicroSwitch = 2;
const int rightMicroSwitch = 3;
const int leftImpactSwitch = 4;
const int rightImpactSwitch = 5;
const int leftMotorDir = 6;
const int leftMotorStep = 7;
const int rightMotorDir = 8;
const int rightMotorStep = 9;
const int leftEnable = 10;
const int rightEnable = 11;
const int indicateLed = 13;

bool leftImpactSwitchPressed = false;
bool rightImpactSwitchPressed = false;
bool leftMicroSwitchPressed = false;
bool rightMicroSwitchPressed = false;

//-----------------------------------------------------------

// Methods For Motor Function

void leftArmDirectionForward(){
  digitalWrite( leftMotorDir, HIGH );
}

void leftArmDirectionBackward(){
  digitalWrite( leftMotorDir, LOW );
}

void rightArmDirectionForward(){
  digitalWrite( rightMotorDir, HIGH );
}

void rightArmDirectionBackward(){
  digitalWrite( rightMotorDir, LOW );
}

void stepLeftMotor() {
  digitalWrite(leftEnable, HIGH);
  digitalWrite( leftMotorStep, HIGH );
  delayMicroseconds( int(speedOfMotor / 2) );
  digitalWrite( leftMotorStep, LOW );
  delayMicroseconds( int(speedOfMotor / 2) );
  digitalWrite(leftEnable, LOW);
}

void stepRightMotor() {
  digitalWrite(rightEnable, HIGH);
  digitalWrite( rightMotorStep, HIGH );
  delayMicroseconds( int(speedOfMotor / 2) );
  digitalWrite( rightMotorStep, LOW );
  delayMicroseconds( int(speedOfMotor / 2) );
  digitalWrite(rightEnable, LOW);
}

// Method for Task Functioning

void moveLeftArm( int randNumber ) {
  leftCurrentPosition += randNumber;
  if ( randNumber > 0 ) {
    leftArmDirectionForward();
  } else {
    leftArmDirectionBackward();
    randNumber *= -1;
  }
  for ( int i = 0; i < randNumber; i++) {
    stepLeftMotor();
  }
}

void moveRightArm( int randNumber ) {
  rightCurrentPosition += randNumber;
  if ( randNumber > 0 ) {
    rightArmDirectionForward();
  } else {
    rightArmDirectionBackward();
    randNumber *= -1;
  }
  for ( int i = 0; i < randNumber; i++) {
    stepRightMotor();
  }
}

//-----------------------------------------------------------

// Method For Indicate LED
void lightOn(){
  digitalWrite(indicateLed, HIGH);
}

void lightOff(){
  digitalWrite(indicateLed, LOW);
}

//-----------------------------------------------------------

void setup() {
  pinMode( leftMicroSwitch, INPUT );
  pinMode( rightMicroSwitch, INPUT );
  pinMode( leftImpactSwitch, INPUT );
  pinMode( rightImpactSwitch, INPUT );
  pinMode( leftMotorDir, OUTPUT );
  pinMode( leftMotorStep, OUTPUT );
  pinMode( rightMotorDir, OUTPUT );
  pinMode( rightMotorStep, OUTPUT );
  pinMode( leftEnable, OUTPUT );
  pinMode( rightEnable, OUTPUT );
  pinMode( indicateLed, OUTPUT );

  lightOff();

}

void loop() {

  moveLeftArm(10);

  delay(100);
  lightOn();
  delay(1000);
  lightOff();

  moveLeftArm(-10);

  delay(100);
  lightOn();
  delay(1000);
  lightOff();

  moveRightArm(10);

  delay(100);
  lightOn();
  delay(1000);
  lightOff();

  moveRightArm(-10);

  delay(100);
  lightOn();
  delay(1000);
  lightOff();

}
