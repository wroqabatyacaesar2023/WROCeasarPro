
#include"mode.h"
#include"Pins.h"
#include"RGBAndMode.h"
#include"DriveCar.h"
#include"Rotation.h"
#include"Ultrasonic.h"
#include"setSteering.h"
#include"Bluetooth.h"
#include"level1.h"

unsigned long displayTime=0;

void setup() {
  
 
  Serial.begin(115200);
  initRGBAndMode();
  led(RED);
  initCar();
  init_mpu();
  initBT();
  initUltrasonic();
  initSteering();
  delay(500);
  readUltrasonic();
  initLevel1();
  motion_mode=STANDBY;
  checkLevel();
  driveTime=millis();
  
}

void loop() {
  
  //if(pidState){steering.write(steeringPID); }
  readUltrasonic();
  //debugUltrasonic();
  readAngle();
  readBT();
  checkStartButton();
  if (start){
    if(level){}
    else{doLevel1();}
  }
  else{if(level){} else{initLevel1();} }

  //if(millis()-displayTime>200){debugUltrasonic();/* debugLevel1(); debugRotation();*/ displayTime=millis();}

}
