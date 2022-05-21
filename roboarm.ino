#include <Servo.h>

const int RESET_PIN = 0;
const int BASE_PIN = 3;
const int SHOULDER_PIN = 5;
const int ELBOW_PIN = 6;

const int BASE_LEFT_PIN = 8;
const int BASE_RIGHT_PIN = 9;
const int SHOULDER_LEFT_PIN = 10;
const int SHOULDER_RIGHT_PIN = 11;
const int ELBOW_LEFT_PIN = 12;
const int ELBOW_RIGHT_PIN = 13;

const int DELAY_DUR = 500;
const int BASE_STATIONARY = 1500;
const int BASE_RIGHT_PULSE = 1000;
const int BASE_LEFT_PULSE = 2000;

const int MIN_S51_POS = 0;
const int MAX_S51_POS = 0;

int shoulder_position = 0;
int elbow_position = 0;
int reset = 1;

Servo base;
Servo shoulder;
Servo elbow;

void setup()
{
  Serial.begin(115200);
  pinMode(RESET_PIN, INPUT_PULLUP);
  pinMode(BASE_LEFT_PIN, INPUT_PULLUP);
  pinMode(BASE_RIGHT_PIN, INPUT_PULLUP);
  pinMode(SHOULDER_LEFT_PIN, INPUT_PULLUP);
  pinMode(SHOULDER_RIGHT_PIN, INPUT_PULLUP);
  pinMode(ELBOW_LEFT_PIN, INPUT_PULLUP);
  pinMode(ELBOW_RIGHT_PIN, INPUT_PULLUP);

  base.attach(BASE_PIN);
  shoulder.attach(SHOULDER_PIN);
  elbow.attach(ELBOW_PIN);

  base.writeMicroseconds(BASE_STATIONARY);
  shoulder.write(shoulder_position);
  elbow.write(elbow_position);
}

void loop()
{
  reset = digitalRead(RESET_PIN);
  int base_left = digitalRead(BASE_LEFT_PIN);
  int base_right = digitalRead(BASE_RIGHT_PIN);
  int shoulder_left = digitalRead(SHOULDER_LEFT_PIN);
  int shoulder_right = digitalRead(SHOULDER_RIGHT_PIN);
  int elbow_left = digitalRead(ELBOW_LEFT_PIN);
  int elbow_right = digitalRead(ELBOW_RIGHT_PIN);

  base.writeMicroseconds(BASE_STATIONARY);
  shoulder.write(shoulder_position);
  elbow.write(elbow_position);

  if (reset == LOW)
  {
    return;
  }

  if (base_left == LOW)
  {
    base.writeMicroseconds(BASE_LEFT_PULSE);
  }

  if (base_right == LOW)
  {
    base.writeMicroseconds(BASE_RIGHT_PULSE);
  }
  
  if ((shoulder_left == LOW) and (shoulder_position != MIN_S51_POS))
  {
    shoulder.write(--shoulder_position);
  }

  if ((shoulder_right == LOW) and (shoulder_position != MAX_S51_POS))
  {
    shoulder.write(++shoulder_position);
  }

  if ((elbow_left == LOW) and (elbow_position != MIN_S51_POS))
  {
    elbow.write(--elbow_position);
  }

  if ((elbow_right == LOW) and (elbow_position != MAX_S51_POS))
  {
    elbow.write(++elbow_position);
  }

  delay(DELAY_DUR);
}
