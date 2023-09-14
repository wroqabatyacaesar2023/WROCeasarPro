#include"BluetoothSerial.h"
BluetoothSerial SerialBT;

char c;
String msg;
void initBT() {
  // put your setup code here, to run once:

 SerialBT.begin("SBT");

}

void readBT() {
  // put your main code here, to run repeatedly:
  
  if (SerialBT.available())  {
    msg="";
      while(SerialBT.available()){
    c=SerialBT.read();
    msg=msg+c;
  
  } 
  Serial.print("msg is:"); Serial.println(msg); 
  if(msg=="s" || msg=="S"){motion_mode=STOP;}
  if(msg=="r" || msg=="R"){ESP.restart();}
  
  if(msg.charAt(msg.length()-1)=='p'){Serial.print("Kp=");        kp = msg.toDouble(); steering.write(88); delay(50); driveTime=millis();}
  else if(msg.charAt(msg.length()-1)=='i'){Serial.print("Ki=");   ki =msg.toDouble();  steering.write(88); delay(50); driveTime=millis();}
  else if(msg.charAt(msg.length()-1)=='d'){Serial.print("Kd=");   kd =msg.toDouble();  steering.write(88); delay(50); driveTime=millis();}
  Serial.println(msg.toDouble());
  }

}
