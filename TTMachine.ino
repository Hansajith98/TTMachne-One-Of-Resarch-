#include <Thread.h>
#include <ThreadController.h>

//-----------------------------------------------------------

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// intialize end step for both rotation arm
const int endStep = 5200;

// intialize begin step for both rotation arm
const int beginStep = 0;

// Error indicator
bool errorIndicator = false;

// current step of left Current Position
int leftCurrentPosition;

// current step of right Current Position
int rightCurrentPosition;

// Speed for motors
const int speedOfMotor = 500;

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

//-----------------------------------------------------------

// Methods for Indicate States
void indicateInitalState() {
  digitalWrite(indicateLed, HIGH);
}

void indicateError() {
  for ( int i = 0; i < 3; i++) {
    digitalWrite(indicateLed, HIGH);
    delay(500);
    digitalWrite(indicateLed, HIGH);
    delay(100);
  }
  delay(2000);

}

void indicateOffState() {
  digitalWrite(indicateLed, LOW);
}

//-----------------------------------------------------------

//method for Motor functioning

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

void setToInitialState() {

  // indicate initial State
  indicateInitalState();

  const int singleStep = 1;
  while ( digitalRead( leftMicroSwitch ) == 0 || digitalRead( rightMicroSwitch ) == 0 ) {
    // Error Checking
    if ( leftCurrentPosition < beginStep || rightCurrentPosition < beginStep ) {
      errorIndicator = true;
      break;
    }
    // Moving Motors to Initial Position
    if ( digitalRead( leftMicroSwitch ) == 0 ) {
      leftArmDirectionBackward();
      stepLeftMotor();
    }
    if ( digitalRead( rightMicroSwitch ) == 0 ) {
      rightArmDirectionBackward();
      stepRightMotor();
    }
    delay( 10 );

  }
  // indicate off State
  indicateOffState();

  leftCurrentPosition = 0;
  rightCurrentPosition = 0;

}

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

int getRandomNumber() {
  int randNumber = random( beginStep, endStep );
  return randNumber;
}

int getLeftRandNumber() {
  int randNumber = getRandomNumber();
  int directon = random( 0, 2 );
  if ( directon == 0 ) {
    if ( (leftCurrentPosition+ randNumber) > endStep ) {
      randNumber = -randNumber;
    }
  } else {
    if ( (leftCurrentPosition - randNumber) > 0 ) {
      randNumber = -randNumber;
    }
  }
  return randNumber;
}

int getRightRandNumber() {
  int randNumber = getRandomNumber();
  int directon = random( 0, 2 );
  if ( directon == 0 ) {
    if ( (rightCurrentPosition + randNumber) > endStep ) {
      randNumber = -randNumber;
    }
  } else {
    if ( (rightCurrentPosition - randNumber) > 0 ) {
      randNumber = -randNumber;
    }
  }
  return randNumber;
}

void moveLeftArmThread() {
  if ( leftImpactSwitch == HIGH) {
    int leftrandNumber = getLeftRandNumber();
    moveLeftArm( leftrandNumber );
  }
}

void moveRightArmThread() {
  if ( rightImpactSwitch == HIGH) {
    int rightrandNumber = getRightRandNumber();
    moveRightArm( rightrandNumber );
  }

}

//-----------------------------------------------------------

// Creating Threads
Thread leftSide;
Thread  rightSide;

// Creating Thread Controller
ThreadController cpu;

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

  // Set Thread
  leftSide.setInterval(1);
  leftSide.onRun(moveLeftArmThread);

  rightSide.setInterval(1);
  rightSide.onRun(moveRightArmThread);

  cpu.add( &rightSide );
  cpu.add( &leftSide );

  // Set To Initial State
  setToInitialState();

}

//-----------------------------------------------------------

void loop() {
  if ( errorIndicator == true ) {
    indicateError();
  } else {
    // Run Threads
    cpu.run();
  }

}
