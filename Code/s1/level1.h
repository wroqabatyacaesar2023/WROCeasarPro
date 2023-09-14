unsigned long runTime=0;
bool isStarted;
void debugLevel1(){
  Serial.print("encoder_count: "); Serial.print( encoder_count);
  Serial.print("rounCounter: "); Serial.print( rounCounter);
  Serial.print("setpoint: "); Serial.print( setpoint);
  Serial.println();
  }
void initLevel1(){
   isStarted=false;
   initAngle=currentAngle;
   motion_mode=STANDBY;
   initR= rangeR;
   initL= rangeL;
   initF= rangeF;
   currentAngle=(int)mpu.getAngleZ();
   rounCounter=0;
   rotionDirection=UNKNOWN_DIRECTION;
   setpoint = rangeR;
  }
void doForwardWithEncoder(){
  if(encoder_count>600){motion_mode=FORWARD; }
  else{forward(255); steering.write(steeringPID);}
  } 

void doTurn(){
    if(rotionDirection==CLOCKWIZE){steeringAngle=STRAIGHT_STEERING+35; setSteering(steeringAngle);}
    else if (rotionDirection==ANTI_CLOCKWIZE){steeringAngle=STRAIGHT_STEERING-43; setSteering(steeringAngle);}
    if(abs(currentAngle-initAngle)>=80){ steering.write(STRAIGHT_STEERING); rounCounter++; 
  
      if(rotionDirection==ANTI_CLOCKWIZE || rotionDirection==UNKNOWN_DIRECTION){ setpoint = rangeR+5;  }
      else if(rotionDirection==  CLOCKWIZE ){  setpoint = rangeL+2; }
          encoder_count=0; motion_mode=FORWARD_ENCODER; }
    
    
  }
void doPreFinal(){                       
  
   if((rotionDirection== CLOCKWIZE )&& (rangeF<(initL+25) && rangeF>1) &&  (rangeR>120 ||  rangeR==0)){initAngle=currentAngle; motion_mode=TURNE;}
    else if((rotionDirection==ANTI_CLOCKWIZE )&& (rangeF<(initR+25) && rangeF>1) &&  (rangeL>120 ||  rangeL==0)){initAngle=currentAngle; motion_mode=TURNE;}
    else{ forward(255);steering.write(steeringPID); } // go straight
  }
void doParking(){
  if(rangeF <146 && rangeF!=0){ motion_mode=STOP;}
  else{forward(255);steering.write(steeringPID);}
  }
void doForward(){
  
  if(rotionDirection==UNKNOWN_DIRECTION){// if direction not set
    if(rangeR>120  || (rangeR==0 )){rotionDirection=CLOCKWIZE;}
    else if(rangeL>120  || rangeL==0){rotionDirection=ANTI_CLOCKWIZE;}
    }

 // if(rounCounter==11){motion_mode=PRE_FINAL;}
  if(rounCounter==12){motion_mode=PARKING;}                                                               /*  ,prevRangeL*/
  else{
    if((rotionDirection== CLOCKWIZE || rotionDirection==UNKNOWN_DIRECTION)&& (rangeF<95   && rangeF>1) &&  (rangeR>120  ||  rangeR==0 )){initAngle=currentAngle; motion_mode=TURNE;}
    else if((rotionDirection==ANTI_CLOCKWIZE || rotionDirection==UNKNOWN_DIRECTION)&& (rangeF<95  &&  rangeF>1) &&  ((rangeL>120)||  ( prevRangeL==0 ))){initAngle=currentAngle; motion_mode=TURNE;}
    else{ forward(255);steering.write(steeringPID); } // go straight
    }
  

}
//the main function of level 1
void doLevel1(){
  switch (motion_mode) 
  {
  case STANDBY:
  break;
  case FORWARD:
    if(!isStarted){isStarted=true; runTime=millis();}
    doForward();    
  break;
  case FORWARD_ENCODER:
    doForwardWithEncoder();
  break;
  case PRE_FINAL:
    doPreFinal();
  break;
  case TURNE:
    doTurn();
  break;
  case PARKING:
    doParking();
  break;
  case STOP:
    stop();
    isStarted=false ; Serial.print("Time is : ");Serial.println((millis()-runTime)/1000);
    ESP.restart();
  break;
  }
  }
