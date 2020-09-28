
/* 

1 - Left Micro Switch
2 - Right Miicro Switch
3 - Left Impact Switch
4 - Right Impact Switch

 */

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

void onLight(){
  digitalWrite( indicateLed, HIGH );
  delay(500);
  digitalWrite( indicateLed, LOW );
}

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

}

void loop() {
  if( digitalRead(leftMicroSwitch) == 1 ){
    leftMicroSwitchPressed = true;
  }
  if(leftMicroSwitchPressed){ 
    onLight();  // On Light

    if( digitalRead(rightMicroSwitch)==1 ){
      rightMicroSwitchPressed = true;
    }
    if(rightMicroSwitchPressed){  
      onLight();  // On Light

      if( digitalRead(leftImpactSwitch)==1 ){
        leftImpactSwitchPressed = true;
      }
      if(leftImpactSwitchPressed){  
        onLight();  // On Light

        if( digitalRead(rightImpactSwitch)==1 ){
          rightImpactSwitchPressed = true;
        }
        if(rightImpactSwitchPressed){ 
          onLight();  // On Light
        }
      }
    }
  }
}
