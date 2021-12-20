#define Pro1 2
#define Pro2 3 
#define Pro3 4 
#define Pro4 5
#define motorPWM1 10
#define motorPWM 11
#define motorFwd1 11
#define motorRev1 A0
#define motorFwd2 A2
#define motorRev2 A3
#define width 20
#define LeftSpeed 400
#define RightSpeed 100
#define delayTime 370


int count1, count2, DIVIDER_POS;
float movement;
bool flag1, flag2, flag3, flag4;
unsigned long startTime, endTime;
void setup() {
  Serial.begin(1200);
  count1 = 0; 
  count2 = 0;
  movement = 0.0;
  DIVIDER_POS = 0;
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(motorFwd1, OUTPUT);
  pinMode(motorRev1, OUTPUT);
  pinMode(motorPWM1, OUTPUT);
  pinMode(motorFwd2, OUTPUT);
  pinMode(motorRev2, OUTPUT);
  pinMode(motorPWM2, OUTPUT);
  flag1 = true;
  flag2 = true;
  flag3 = true;
  flag4 = true;

}

void loop() {
  moveFwd(1000);
  int read1 = digitalRead(2);
  int read2 = digitalRead(3);
  int read3 = digitalRead(4);
  int read4 = digitalRead(5);

  startTime = millis();
  endTime = startTime;

  while ((endTime - startTime) <= 15000) {
    int read1 = digitalRead(2);
    int read2 = digitalRead(3);
    int read3 = digitalRead(4);
    int read4 = digitalRead(5);
    Serial.print(count1);
    Serial.print("\n");
    Serial.print(count2);
    Serial.print("\n");
    if ( read1 == 1 ) {
      if ( flag1 == true ) {
        count1++;
        flag1 = false;
      }
    } else {
      flag1 = true;
    }

    if ( read2 == 1 ) {
      if ( flag2 == true ) {
        count1++;
        flag2 = false;
      }
    } else {
      flag2 = true;
    }

    if ( read3 == 1 ) {
      if ( flag3 == true ) {
        count2++;
        flag3 = false;
      }
    } else {
      flag3 = true;
    }

    if ( read4 == 1 ) {
      if ( flag4 == true ) {
        count2++;
        flag4 = false;
      }
    } else {
      flag4 = true;
    }

    endTime = millis();
  }


 if ((count1 / count2) >= 2 || (count2 / count1) >= 2) {
    movement = (float)(count1 - count2) / (count1 + count2);
    Serial.print(movement);
    Serial.print("\n");
    movement *= (float)width;
    Serial.print(movement);
    int PREV_POS = DIVIDER_POS;
    DIVIDER_POS += movement;
    if (DIVIDER_POS > 10) {
        movement = (10-PREV_POS);
        DIVIDER_POS = 10;
    }
    else if (DIVIDER_POS < -10) {
        movement = -(10_PREV_POS);
        DIVIDER_POS = -10;
    }
    if (movement > 10) {
        moveRev(movement);
    }
    else {
        moveFwd(abs(movement));
    }
    reset();
 }
}


void moveFwd(int dist) {
    analogWrite(motorPWM1, LeftSpeed);
    analogWrite(motorPWM2, RightSpeed);
    digitalWrite(motorFwd1, HIGH);
    digitalWrite(motorRev1, HIGH);
    digitalWrite(motorFwd2, HIGH);
    digitalWrite(motorRev2, LOW);
    delay(dist * delayTime);
    digitalWrite(motorRev1, HIGH);
    digitalWrite(motorRev2, LOW);
}

void reset() {
    count1 = 0;
    count2 = 0;
    movement = 0;
    flag1 = true;
    flag2 = true;
    flag3 = false;
    flag4 = true;
}