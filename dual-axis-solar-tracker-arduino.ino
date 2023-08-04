/**
 * Sketch for dual-axis arduino solar tracker
 */

/* Includes */
#include <Servo.h>

/* Macros */
#define LDR_TOP_RIGHT     0
#define LDR_BOTTOM_RIGHT  1
#define LDR_TOP_LEFT      2
#define LDR_BOTTOM_LEFT   3

#define SERVO_TOP         11
#define SERVO_BOT         10

/* Object declarations */
Servo servo_top;
Servo servo_bot;

/* Global variables */
int servo_top_pos = 90;
int servo_bot_pos = 90;

void setup() {
  Serial.begin(9600);
  servo_top.attach(SERVO_TOP);
  servo_bot.attach(SERVO_BOT);
  servo_top.write(servo_top_pos);
}

void loop() {
  int error = 50;
  /* getting avg value for each side */
  int top_avg = (analogRead(LDR_TOP_RIGHT) + analogRead(LDR_TOP_LEFT)) / 2;
  int bot_avg = (analogRead(LDR_BOTTOM_RIGHT) + analogRead(LDR_BOTTOM_LEFT)) / 2;
  int right_avg = (analogRead(LDR_TOP_RIGHT) + analogRead(LDR_BOTTOM_RIGHT)) / 2;
  int left_avg = (analogRead(LDR_TOP_LEFT) + analogRead(LDR_BOTTOM_LEFT)) / 2;

  /* for testing and debugging */
  Serial.println("top");
  Serial.println(top_avg);
  Serial.println("bot");
  Serial.println(bot_avg);

  /* upper servo */
  if (abs(top_avg - bot_avg) > error)
  {
    if (top_avg > bot_avg)
    {
      servo_top_pos++;
      if (servo_top_pos > 150)
      {
        servo_top_pos = 150;
      }
    }
    else if(bot_avg > top_avg)
    {
      servo_top_pos++;
      if (servo_top_pos < 30)
      {
        servo_top_pos = 30;
      }
    }
    servo_top.write(servo_top_pos);
  }
  /* lower servo */
  if (abs(left_avg - right_avg) > error)
  {
    if (left_avg > right_avg)
    {
      servo_bot_pos++;
      if (servo_bot_pos > 150)
      {
        servo_bot_pos = 150;
      }
    }
    else if(left_avg > right_avg)
    {
      servo_top_pos++;
      if (servo_bot_pos < 30)
      {
        servo_bot_pos = 30;
      }
    }
    servo_top.write(servo_bot_pos);
  }
}
