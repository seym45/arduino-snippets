/*
  enLeft and and enRight pin must be PWM pins, as ther are for speed control.
  And other pins are for direction control so any digital pin will do the job for controlling
*/

// defining left motor pins
#define inC 5
#define inD 6
#define enLeft 7

// defining right motor pins
#define enRight 2
#define inA 4
#define inB 3


/*
  Motor(leftspeed, rightspeed)
  here leftspeed can be -255 to +255
  similarly rightspeed can be -255 to +255

  For positive valuse this method rotate the motor in forward direction
  And negative values, rotates the motor to backward direction
*/
void motor(int leftspeed, int rightspeed)
{
  // Left motor logics
  if (leftspeed == 0)motorL( 0, 0, leftspeed);           //stop
  else if (leftspeed > 0)motorL( 1, 0, leftspeed);       //forward
  else motorL( 0, 1, (-1)*leftspeed);                    //backward


  // right motor logics
  if (rightspeed == 0) motorR( 0, 0, rightspeed);           //stop
  else if (rightspeed >= 0)motorR( 1, 0, rightspeed);       //forward
  else motorR( 0, 1, (-1)*rightspeed);                      //backward
}


/*
   motorL(...) takes two direction argument and speed of roation
*/

//left motor
void motorL(int direction_1, int direction_2, int mspeed)
{
  /*
     digitalWrite(...) takes two argument.
     pinnumber and [HIGH or LOW] as direction values
  */
  digitalWrite(inC, direction_1);
  digitalWrite(inD, direction_2);

  /*
     analogwirte(...) takes two argument
     pnnumber and 0-255 as speed of rotation
  */
  analogWrite(enLeft, mspeed);
}


//right motor
void motorR(int direction_1, int direction_2, int mspeed)
{
  digitalWrite(inA, direction_1);
  digitalWrite(inB, direction_2);
  analogWrite(enRight, mspeed);
}


void setup() {

  // pinMode(pinNumber, mode)
  // pinNumber is the connected pin
  // mode can be [ INPUT or OUTPUT or INPUT_PULLUP]

  pinMode(enLeft, OUTPUT);
  pinMode(inA, OUTPUT);
  pinMode(inB, OUTPUT);
  pinMode(inC, OUTPUT);
  pinMode(inD, OUTPUT);
  pinMode(enRight, OUTPUT);
}

int delay_milisecond = 1000;

void loop() {
  // this is to stop motors
  motor(0, 0);
  // delay is used here to witness the actions
  delay(delay_milisecond);

  // rotate left motor in forward direction
  motor(100, 0);
  delay(delay_milisecond);

  // rotate both motor in forward direction
  motor(100, 100);
  delay(delay_milisecond);

  // rotate both motor in backward direction
  motor(-100, -100);
  delay(delay_milisecond);
}
