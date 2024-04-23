/* CrawlerBot
 *  Jeremy Dalbeck
*/
#include <Servo.h>
#include <IBusBM.h>
 
#define SERVO_PIN 4
#define MOTOR_PIN 6
#define SERVO_TRIM A0
#define MOTOR_TRIM A1

// Create iBus Object
IBusBM ibus;

Servo servo;  // create servo object to control the servo
Servo motor;  // create servo object to control the motor

int servoTrim;
int motorTrim;
uint16_t ch1;
uint16_t ch2;

void setup() {
  servo.attach(SERVO_PIN);
  servo.write(90); // center the steering
  motor.attach(MOTOR_PIN);
  motor.writeMicroseconds(1500); // stop the motor
 
  // Attach iBus object to serial port
  ibus.begin(Serial1);
  while (ibus.cnt_rec==0) delay(100);
}

void loop() {

  // Get RC channel values
  ch1 = ibus.readChannel(0);
  ch2 = ibus.readChannel(1);

  // Get the servo and motor trim values, and map them on a scale from -500 to 500
  servoTrim = analogRead(SERVO_TRIM);
  servoTrim = map(servoTrim, 0, 1023, -500, 500);
  motorTrim = analogRead(MOTOR_TRIM);
  motorTrim = map(motorTrim, 0, 1023, -500, 500);

  // Combine the servo channel and trim values, and output to servo
  ch1 = ch1 + servoTrim;
  ch1 = constrain(ch1, 1000, 2000);
  servo.writeMicroseconds(ch1);

  // Combine the motor channel and trim values, and output to motor
  ch2 = ch2 + motorTrim;
  ch2 = constrain(ch2, 1000, 2000);
  motor.writeMicroseconds(ch2);

  delay(79);

  /*
  for (pos = 80; pos <= 100; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
   // myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 100; pos >= 80; pos -= 1) { // goes from 180 degrees to 0 degrees
    //myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  */
}
