/*
*FileName* 
Made by Valery S for Hack ISU X 
 
 */

 #include <Servo.h>

 namespace Communication
{
const int GET_FOREIGN_POLICY = 0;
const int GET_PAT_CO = 1;
const int GET_MEDIA = 2;
const int GET_JUDICIAL_0 = 3;
const int GET_JUDICIAL_1 = 4;
const int GET_JUDICIAL_2 = 5;
const int GET_BALL_READY_3 = 6;
const int SET_LIGHTS_BLACK_MONDAY = 7;
const int SET_LIGHTS_ASSASINATION_ATTEMPT = 8;
const int SET_LIGHTS_AIDS_CRISIS = 9;
const int SET_LIGHTS_JUDICIAL_0 = 10;
const int SET_LIGHTS_JUDICIAL_1 = 11;
const int SET_LIGHTS_FOREIGN_POLICY = 12;
const int SET_LIGHTS_PATCO = 13;
const int SET_RELEASE_BERLIN_WALL = 14;
const int UNSET_LIGHTS_BLACK_MONDAY = 15;
const int UNSET_LIGHTS_ASSASINATION_ATTEMPT = 16;
const int UNSET_LIGHTS_AIDS_CRISIS = 17;
const int UNSET_LIGHTS_JUDICIAL_0 = 18;
const int UNSET_LIGHTS_JUDICIAL_1 = 19;
const int UNSET_LIGHTS_FOREIGN_POLICY = 20;
const int UNSET_LIGHTS_PATCO = 21;
} // namespace Communication


Servo rFlip;
Servo lFlip;
Servo BerlinWall;


void checkSensor(int sensor){
  Serial.write(!digitalRead(sensor));
}

void lightChange(int light, bool change){
 digitalWrite(light,change);
}


int leftButtonPressed() {
  return !digitalRead(2);
}

void handleLeftButtonStateChanges()  {
    static int leftButtonPressedAlready = 0;
    if(leftButtonPressed() && !leftButtonPressedAlready){
        leftButtonPressedAlready = 1;
        lFlip.write(90);
    }
    
    if (!leftButtonPressed() && leftButtonPressedAlready) {
      leftButtonPressedAlready = 0;
      lFlip.write(180);
    }
}

int rightButtonPressed() {
  return !digitalRead(A0);
}

void handleRightButtonStateChanges()  {
    static int rightButtonPressedAlready = 0;
    if(rightButtonPressed() && !rightButtonPressedAlready){
        rightButtonPressedAlready = 1;
        rFlip.write(90);
    }
    
    if (!rightButtonPressed() && rightButtonPressedAlready) {
      rightButtonPressedAlready = 0;
      rFlip.write(180);
    }
}

void setup() {

Serial.begin(9600);
  rFlip.attach(5);
  lFlip.attach(6);
  BerlinWall.attach(3);
  pinMode(2,INPUT_PULLUP);//flipperRbutt
  pinMode(4,INPUT_PULLUP);//foreign policy 
  pinMode(7,INPUT_PULLUP);//PAT_CO
  pinMode(8,INPUT_PULLUP);//MEDIA
  pinMode(9,INPUT_PULLUP);//JUDICIAL_0
  pinMode(10,INPUT_PULLUP);//JUDICIAL_1
  pinMode(11,INPUT_PULLUP);//JUDICIAL_2
  pinMode(12,INPUT_PULLUP);//GET_BALL_READY
  pinMode(A0,INPUT_PULLUP);
  pinMode(13,OUTPUT);//BLACK_MONDAY
  pinMode(A1,OUTPUT);//ASS ATTEMPT
  pinMode(A2,OUTPUT);//AIDS CRISSIS
  pinMode(A3,OUTPUT);//FOREIGNPOLICY
  pinMode(A4,OUTPUT);//JUDICIAL0
  pinMode(A5,OUTPUT);//JUDICIAL1
  pinMode(A6,OUTPUT);//PATCO


}
void loop() {
    handleLeftButtonStateChanges();
    handleRightButtonStateChanges();

    
    if(Serial.available() > 0){
        switch (Serial.read()){
            case Communication::GET_FOREIGN_POLICY:
            Serial.write(!digitalRead(4));
            break;

            case Communication::GET_PAT_CO:
            Serial.write(!digitalRead(7));
            break;

            case Communication::GET_MEDIA:
            Serial.write(!digitalRead(8));
            break;
    
            case Communication::GET_JUDICIAL_0:
            Serial.write(!digitalRead(9));
            break;

            case Communication::GET_JUDICIAL_1:
            Serial.write(!digitalRead(10));
            break;

            case Communication::GET_JUDICIAL_2:
            Serial.write(!digitalRead(11));
            break;

            case Communication::GET_BALL_READY_3:
            Serial.write(!digitalRead(12));
            break;

            case Communication::UNSET_LIGHTS_BLACK_MONDAY:
            digitalWrite(13,0);
            break;

            case Communication::UNSET_LIGHTS_ASSASINATION_ATTEMPT:
            digitalWrite(A1,0);
            
            break;

            case Communication::UNSET_LIGHTS_AIDS_CRISIS:
            digitalWrite(A2,0);
            break;

            case Communication::UNSET_LIGHTS_JUDICIAL_0:
            digitalWrite(A3,0);
            break;

            case Communication::UNSET_LIGHTS_JUDICIAL_1:
            digitalWrite(A4,0);
            break;

            case Communication::UNSET_LIGHTS_FOREIGN_POLICY:
            digitalWrite(A5,0);
            break;

            case Communication::UNSET_LIGHTS_PATCO:
            digitalWrite(A6,0);
            break;

            case Communication::SET_RELEASE_BERLIN_WALL:
            BerlinWall.write(95);
            break;

            case Communication::SET_LIGHTS_BLACK_MONDAY:
            digitalWrite(13,1);
            break;

            case Communication::SET_LIGHTS_ASSASINATION_ATTEMPT:
            digitalWrite(A1,1);
            
            break;

            case Communication::SET_LIGHTS_AIDS_CRISIS:
            digitalWrite(A2,1);
            break;

            case Communication::SET_LIGHTS_JUDICIAL_0:
            digitalWrite(A3,1);
            break;

            case Communication::SET_LIGHTS_JUDICIAL_1:
            digitalWrite(A4,1);
            break;

            case Communication::SET_LIGHTS_FOREIGN_POLICY:
            digitalWrite(A5,1);
            break;

            case Communication::SET_LIGHTS_PATCO:
            digitalWrite(A6,1);
            break;
     }
  }
  
}
