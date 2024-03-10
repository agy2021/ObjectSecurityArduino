//rgb led 1
int ledor = 10;
int ledog = 9;
int ledob = 8;

//rgb led 2
int tr = 3;
int tg = 4;
int tb = 5;

//joystick
int jbutton = A5;
int jx = A4;
int jy = A3;

//buzzer
int bz = 7;

const int defx = 516;
const int defy = 495;

//ir object detection sensor
int obj = 6;
float objd = 0;

int alarm = 0;

bool disarmed = false;
bool armed = false;

void setup() {
  pinMode(tr, OUTPUT);
  pinMode(tg, OUTPUT);
  pinMode(tb, OUTPUT);
  pinMode(bz, OUTPUT);
  pinMode(jbutton, INPUT);
  
  digitalWrite(jbutton, HIGH);
  Serial.begin(9600);

  pinMode(ledor, OUTPUT);
  pinMode(ledog, OUTPUT);
  pinMode(ledob, OUTPUT);
}


void loop() {
  int objd = digitalRead(obj);

  if (objd == 0) {
    armed = true;
//    noTone(bz);
    digitalWrite(tr, 0);
    digitalWrite(ledor, 0);
    digitalWrite(tb, 0);
    digitalWrite(ledob, 0);
    digitalWrite(tg, 1);
    digitalWrite(ledog, 1);

  //x>900 = right, x<200 = left
  //y<300 = up, y>800 = down

    if (abs(analogRead(jy))>800) { 
      Serial.print("down \n");
      delay(1000);

      if (abs(analogRead(jx))>900){
        Serial.print("right \n");
        delay(1000);

        if (abs(analogRead(jx))<200){
          Serial.print("left \n");
          delay(1000);

          if (abs(analogRead(jy))<300){
            Serial.print("up \n");
            
            disarmed = true;
            digitalWrite(tr, 0);
            digitalWrite(ledor, 0);
            digitalWrite(tg, 0);
            digitalWrite(ledog, 0);
            digitalWrite(tb, 1);
            digitalWrite(ledob, 1);
            delay(1000);
            digitalWrite(tb, 0);
            digitalWrite(ledob, 0);
            armed = false;
          }
        }
      }
    }

    if (disarmed == true) {
      armed = false;  
    }
  } 

  if (armed == true) {
    if (objd == 1) {
      digitalWrite(tg, 0);
      digitalWrite(ledog, 0);
      digitalWrite(tr, 0);
      digitalWrite(ledor, 1);
      tone(bz, 1000);
      delay(700);
      digitalWrite(tr, 1);
      digitalWrite(ledor, 0);
      noTone(bz);
      delay(700);
    }
    
  } else {
      Serial.print("Safe to take \n");
    }
}
