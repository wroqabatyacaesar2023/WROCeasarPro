#define OFF 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4


bool start;
bool level;
void led(byte state){
  switch (state) 
  {
    case OFF:
      digitalWrite(LED_RED,LOW); digitalWrite(LED_GREEN,LOW); digitalWrite(LED_BLUE,LOW);
    break;
    case RED:
      digitalWrite(LED_RED,HIGH); digitalWrite(LED_GREEN,LOW); digitalWrite(LED_BLUE,LOW);
    break;
    case GREEN:
      digitalWrite(LED_RED,LOW); digitalWrite(LED_GREEN,HIGH); digitalWrite(LED_BLUE,LOW);
    break;
    case BLUE:
      digitalWrite(LED_RED,LOW); digitalWrite(LED_GREEN,LOW); digitalWrite(LED_BLUE,HIGH);
    break;
    case WHITE:
      digitalWrite(LED_RED,HIGH); digitalWrite(LED_GREEN,HIGH); digitalWrite(LED_BLUE,HIGH);
    break;
  }
  
  
  }
void checkStartButton(){
  level=digitalRead(MODE_KEY); if(level){led(BLUE);} else{led(GREEN);}
  if(digitalRead(START_BUTTON)==LOW){start=true;   motion_mode=FORWARD; Serial.print("Start  "); Serial.println(level);}
  }

void checkLevel(){
  level=digitalRead(MODE_KEY); if(level){led(BLUE);} else{led(GREEN);}
  }
void initRGBAndMode(){
   level=false;
  start=false;  pinMode(START_BUTTON,INPUT);
  pinMode(MODE_KEY,INPUT);
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_BLUE,OUTPUT);
  }
