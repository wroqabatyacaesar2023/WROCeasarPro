#include <ESP32Servo.h>

#define CLOCKWIZE 0
#define ANTI_CLOCKWIZE 1
#define UNKNOWN_DIRECTION -1

//#define STRAIGHT_STEERING 88
#define STRAIGHT_STEERING 90
#define SPEED2 200
int initR,initL,initF;
int rounCounter=0;
int rotionDirection=UNKNOWN_DIRECTION;
bool pinAttached;
Servo steering;
int steeringAngle;

// Setting PWM properties
const int freq = 40000;
const int pwmChannel = 2;
const int resolution = 8;
//int dutyCycle = 200;
volatile unsigned long encoder_count = 0;
int speed;
unsigned long driveTime = 0;

 void IRAM_ATTR isr() {
	encoder_count++;
}
void initCar() {

  speed=0;
  steering.attach(STEERING_PIN);
  //steeringAngle=89; //  >90 Rigth     <90 LEFT
  steering.write(STRAIGHT_STEERING);
  // put your setup code here, to run once:
 pinMode(PWM,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(ENCODER_PIN,INPUT);

attachInterrupt(ENCODER_PIN, isr, CHANGE);
   // configure LED PWM functionalitites
 ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(PWM, pwmChannel);
  pinAttached=true;
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,LOW);
 speed=0;

  steering.setPeriodHertz(50);// standard 50 hz servo
	//myservo.attach(servoPin, 1000, 2000); // attaches the servo on pin 18 to the servo object

}
void setSteering(int ang){
   steering.write(ang);
}

void forward(int speed){
  //ledcAttachPin(PWM, pwmChannel);
  //analogWrite(PWM,speed);
  if(speed>254){if(pinAttached){ledcDetachPin(PWM); pinAttached=false;} digitalWrite(PWM,HIGH);}
  else{if(!pinAttached){ledcAttachPin(PWM, pwmChannel); pinAttached=true;}ledcWrite(pwmChannel, speed); } 
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

}
void reverse(int speed){
  //analogWrite(PWM,speed);
  ledcWrite(pwmChannel, speed); 
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
}



void stop(){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
}
