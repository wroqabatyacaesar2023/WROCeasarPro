#define INT_TIME 70000 //interrupt occured evry time (in micro sec.)
double dt;
bool pidState;
//volatile double last_time;
volatile int steeringPID;
volatile int output=0;
hw_timer_t * timer = NULL;      //H/W timer defining (Pointer to the Structure)
double integral, previous = 0.0;

double kp, ki, kd;
volatile double setpoint;

double pid(double error)
{
  double proportional = error;
  integral += error * dt;
  double derivative = (error - previous) / dt;
  previous = error;
  double output = (kp * proportional) + (ki * integral) + (kd * derivative);
  return output;
}

void IRAM_ATTR setStiring_()
{
  
 // Serial.print("dt:"); Serial.println(dt);
 
  double actual;
  if(rotionDirection==ANTI_CLOCKWIZE || rotionDirection==UNKNOWN_DIRECTION){actual = (double)rangeR;}
  else if(rotionDirection==  CLOCKWIZE ){actual = (double)rangeL;}
  if(actual!=0.0){
  //Serial.print("dist f b="); Serial.println(actual);
  double error = setpoint - actual;
  //Serial.print("setpoint="); Serial.println(setpoint);
  output =(int) pid(error);
  output=constrain(output, -4200,4200);
  output=map(output,-4200,4200,-20,20);
  output=constrain(output, -10,10);


  if(rotionDirection==ANTI_CLOCKWIZE || rotionDirection==UNKNOWN_DIRECTION){ 
      steeringPID=STRAIGHT_STEERING-output;}
  else if(rotionDirection==  CLOCKWIZE ){steeringPID=STRAIGHT_STEERING+output; }
}

}

void initSteering()
{ pidState=false;
  kp = 280.0;
  ki = 0.0;
  kd = 23.0;
  dt=(double)INT_TIME/1000000;
  timer = timerBegin(0, 80, true);             // timer 3, prescalar: 80, UP counting
  timerAttachInterrupt(timer, &setStiring_, true);   // Attach interrupt
  timerAlarmWrite(timer, INT_TIME, true);     // Match value= 70000 for 70 msec. delay.
  timerAlarmEnable(timer);                 // Enable Timer with interrupt (Alarm Enable)
 
 // setpoint = 15.0;
  steering.write(STRAIGHT_STEERING);
 
}
////////////////////////////////////////////////////


void driveBetween(){
  // setStiring_();
  }
