
/*
  Basic code for X configuration quadcopters. Uses MPU6050 sensor, Arduino Pro Mini and 4 channel RC remote.
 Algorithm used is PID.
 Mainly intented for demonstartion. This code needs to be modified appropriately for actual use.
 Uses i2cdevlib library by Jeff Rowberg for MPU DMP utilisation and PinChangeInt library by Mike Schwager for interrupt extension.
 
 Copyright© RoboCET 2015.
 WWW.ROBOCET.COM
 
 */


#include <PinChangeInt.h>
#include <Servo.h>
#include <Wire.h>
#include "I2Cdev.h"
#include "helper_3dmath.h"
#include "MPU6050_6Axis_MotionApps20.h"

//Quadcopter motor configuration
/*    M0  M1      
        \/
        /\   
      M3  M2
*/

#define RX_PIN_CH0 4 //defines the pins on arduino where the four channels are connected.
#define RX_PIN_CH1 6
#define RX_PIN_CH2 7
#define RX_PIN_CH3 8

#define CH0_MIN 1205 //defines the min output of each channel.Needs to be determined practically.
#define CH1_MIN 1225
#define CH2_MIN 1260
#define CH3_MIN 1020

#define CH0_MAX 1940 //defines the max output of each channel.Needs to be determined practically.
#define CH1_MAX 1880
#define CH2_MAX 1916
#define CH3_MAX 1760


#define ESC0_PIN 3 //defines the pins on arduino where the four ESCs are connected.
#define ESC1_PIN 9
#define ESC2_PIN 10
#define ESC3_PIN 11

#define ESC_TAKEOFF_CUTOFF 1350 //the value of ESC inputs at which the Quadcopter starts to lift off. 
#define THRO_MAX 1550 //the max value due to throttle.
#define ESC_MIN 1060 //the max value of ESC input at which the motor is off.

#define PITCH_MIN -15 //the min pitch, roll and yaw angles that we want.
#define ROLL_MIN -15
#define YAW_MIN -15

#define PITCH_MAX 15 //the max pitch, roll and yaw angles that we want.
#define ROLL_MAX 15
#define YAW_MAX 15

#define KP_PITCH 1.9 //KP, KD and KI values of PID for pitch.
#define KD_PITCH 4.2
#define KI_PITCH .005

#define KP_ROLL 2 //KP, KD and KI values of PID for roll.
#define KD_ROLL 3.85
#define KI_ROLL .1551

#define KP_YAW 2 //KP, KD and KI values of PID for yaw.
#define KD_YAW 0
#define KI_YAW 0

#define PID_SAMPLE_TIME 70 //PID refresh interval in milliseconds.

#define SETROLL_CONSTRAIN 180 //max output value of PID for pitch, roll and yaw.
#define SETPITCH_CONSTRAIN 180
#define SETYAW_CONSTRAIN  50



Servo ESC0,ESC1,ESC2,ESC3; //servo objects for interfacing with the ESCs.
unsigned long rxStart[4],rxVal[4]; //variables to calculate and store receiver pwm outputs.
int tThro=0,tYaw=0,tRoll=0,tPitch=0; //the target/desired pitch, roll and yaw angles.
int cYaw=0,cPitch=0,cRoll=0; //current pitch,roll and yaw angles of the quadcopter which are read from the MPU.


int errorP,errorR,errorY; //error in pitch, roll and yaw. error = (current angle reading from MPU - target/desired angle reading from receiver)
int lasterrorP=0,lasterrorR=0,lasterrorY=0; //previous error values in pitch,roll and yaw
int errordiffP,errordiffR,errordiffY; //difference in error values for pitch, roll and yaw
float errsumP=0,errsumR=0,errsumY=0; //integral accumulated error values for pitch, roll and yaw
int setPitch,setRoll,setYaw; //PID output for pitch, roll and yaw

unsigned long NOW,PAST=0,TIMECHANGE; //time variables used in the PID loop
int ESC0_VAL,ESC1_VAL,ESC2_VAL,ESC3_VAL; //values ehich are given to the ESCs



MPU6050 mpu;                           // mpu interface object
uint8_t mpuIntStatus;                  // mpu statusbyte
uint8_t devStatus;                     // device status    
uint16_t packetSize;                   // estimated packet size  
uint16_t fifoCount;                    // fifo buffer size   
uint8_t fifoBuffer[64];                // fifo buffer 

Quaternion q;                          // quaternion for mpu output
VectorFloat gravity;                   // gravity vector for ypr
float ypr[3] = {0.0f,0.0f,0.0f};       // yaw pitch roll values from MPU
volatile bool mpuInterrupt = false;
bool dmpReady = false;


void setup()
{
  mpuInit(); //initialise the MPU
  escInit(); //initialise the ESCs
  rxInit(); //initialise the receiver interrupts
}

void loop()
{
  rxMap(); //get values from the remote. Map the values to angles. Store them in tPitch, tRoll, tYaw.
  mpuRead(); //read the current angle values from MPU. Store them in cPitch, cRoll, cYaw.
  pid(); //calculate pid outputs. Store them in setPitch, setRoll and setYaw.
  updateMotors(); //apply the flight dynamics logic and give inputs to the ESCs utilising the PID outputs.
}

void mpuInit()
{
  Wire.begin(); //Join I2C bus (I2Cdev library doesn't do this automatically)
  TWBR = 24; //400kHz I2C clock (200kHz if CPU is 8MHz)
  mpu.initialize();
  devStatus = mpu.dmpInitialize(); // verify connection

  mpu.setXGyroOffset(220);//supply your own gyro offsets here, scaled for min sensitivity
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); 

  if (devStatus == 0) // make sure it worked (returns 0 if so)
  {
    mpu.setDMPEnabled(true);
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize(); // get expected DMP packet size for later comparison
  } 
}

inline void dmpDataReady() 
{
  mpuInterrupt = true; 
}


void escInit()
{
  ESC0.attach(ESC0_PIN); //attach each ESC to the desired pins
  ESC1.attach(ESC1_PIN);
  ESC2.attach(ESC2_PIN);
  ESC3.attach(ESC3_PIN);
  delay(100);
  ESC0.writeMicroseconds(2000); //ESC calibration code starts here
  ESC1.writeMicroseconds(2000);
  ESC2.writeMicroseconds(2000);
  ESC3.writeMicroseconds(2000);
  delay(1000);
  ESC0.writeMicroseconds(1000);
  ESC1.writeMicroseconds(1000);
  ESC2.writeMicroseconds(1000);
  ESC3.writeMicroseconds(1000);
  delay(2000);
  ESC0.writeMicroseconds(0);
  ESC1.writeMicroseconds(0);
  ESC2.writeMicroseconds(0);
  ESC3.writeMicroseconds(0); //ESC calibration code ends here
}

void rxInit()
{
  //Initialize interface with Rx by attaching interrupts
  PCintPort::attachInterrupt(RX_PIN_CH0, chan0, CHANGE);
  PCintPort::attachInterrupt(RX_PIN_CH1, chan1, CHANGE);
  PCintPort::attachInterrupt(RX_PIN_CH2, chan2, CHANGE);
  PCintPort::attachInterrupt(RX_PIN_CH3, chan3, CHANGE);
}

void rxMap()
{
  tThro=map(rxVal[2],CH2_MIN,CH2_MAX,ESC_MIN,THRO_MAX); //map throttle values to desired range.
  tPitch=map(rxVal[1],CH1_MIN,CH1_MAX,PITCH_MIN,PITCH_MAX); //the desired pitch angle is obtained here after mapping.
  tRoll=map(rxVal[0],CH0_MIN,CH0_MAX,ROLL_MAX,ROLL_MIN); //the desired roll angle is obtained here after mapping.
  tYaw=map(rxVal[3],CH3_MIN,CH3_MAX,YAW_MIN,YAW_MAX); //the desired yaw angle is obtained here after mapping.

  constrain(tThro,ESC_MIN,THRO_MAX);   //constrain values within the limits to be safe
  constrain(tPitch,PITCH_MIN,PITCH_MAX);
  constrain(tRoll,ROLL_MIN,ROLL_MAX);
  constrain(tYaw,YAW_MIN,YAW_MAX);
}


void mpuRead()
{

  if (!dmpReady) return;
  while (!mpuInterrupt && fifoCount < packetSize) 
  {
    // other program behavior stuff here
    // .
    // .
    // .
    // if you are really paranoid you can frequently test in between other
    // stuff to see if mpuInterrupt is true, and if so, "break;" from the
    // while() loop to immediately process the MPU data
    // .
    // .
    // .
  }
  mpuInterrupt = false; // reset interrupt flag and get INT_STATUS byte
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount(); // get current FIFO count
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) // check for overflow 
  {
    mpu.resetFIFO(); // reset so we can continue cleanly
  } 
  else if (mpuIntStatus & 0x02) 
  {

    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount(); //wait for correct available data length, should be a VERY short wait
    mpu.getFIFOBytes(fifoBuffer, packetSize);  // read a packet from FIFO
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    ypr[0]=ypr[0]*180/M_PI; //yaw, pitch and roll angles are stored in the float array ypr[3] in radians, we convert them to degrees
    ypr[1]=ypr[1]*180/M_PI;
    ypr[2]=ypr[2]*180/M_PI;

    cPitch=ypr[1]; //we need only integer precision, so we assign ypr values to integer variables
    cRoll=ypr[2];
    cYaw=ypr[0];
  }
}

void pid()
{

  NOW=millis(); //present time.
  TIMECHANGE=NOW-PAST; //time elapsed since last pid calculation.
  if(TIMECHANGE>=PID_SAMPLE_TIME) //if the time elapsed is more than the set sample time, run the pid function. 
  { 
    errorP=cPitch-tPitch; //error in pitch, which is (current pitch angle read from MPU - pitch angle sent from the RC remote).
    errordiffP=errorP-lasterrorP; //present error in pitch - previous error in pitch.
    errsumP+=KI_PITCH*errorP; //the integral term of pitch error in PID, which is accumulated in errorsumP.
    if(errsumP>50) //if the integral error is greater or less than a preset threshold, we will assign it the same value.
      errsumP=50;
    if(errsumP<-50)
      errsumP=-50;
    setPitch=KP_PITCH*errorP + KD_PITCH*errordiffP + errsumP; //result of the PID controller for pitch control.
    lasterrorP=errorP; //save current error value for use as lasterror value in the next iteration.

    errorR=cRoll-tRoll; //error in roll, which is (current roll angle read from MPU - roll angle sent from the RC remote).
    errordiffR=errorR-lasterrorR; //present error in roll - previous error in roll.
    errsumR+=KI_ROLL*errorR; //the integral term of roll error in PID, which is accumulated in errorsumR.
    if(errsumR>50) //if the integral error is greater or less than a preset threshold, we will assign it the same value.
      errsumR=50;
    if(errsumR<-50)
      errsumR=-50;
    setRoll=KP_ROLL*errorR + KD_ROLL*errordiffR + errsumR; //result of the PID controller for roll control.
    lasterrorR=errorR; //save current error value for use as lasterror value in the next iteration.

    errorY=cYaw-tYaw; //error in yaw, which is (current yaw angle read from MPU - yaw angle sent from the RC remote).
    errordiffY=errorY-lasterrorY; //present error in yaw - previous error in yaw.
    errsumY+=KI_YAW*errorY; //the integral term of yaw error in PID, which is accumulated in errorsumY.
    if(errsumY>50) //if the integral error is greater or less than a preset threshold, we will assign it the same value.
      errsumY=50;
    if(errsumY<-50)
      errsumY=-50;
    setYaw=KP_YAW*errorY + KD_YAW*errordiffY +errsumY; //result of the PID controller for yaw control.
    lasterrorY=errorY; //save current error value for use as lasterror value in the next iteration.

    PAST=NOW; //store the present time as past time for the next iteration 

    constrain(setPitch,-SETPITCH_CONSTRAIN,SETPITCH_CONSTRAIN); //constrain output of pid within some limits so that the motor is not at max power at any time
    constrain(setRoll,-SETROLL_CONSTRAIN,SETROLL_CONSTRAIN);
    constrain(setYaw,-SETYAW_CONSTRAIN,SETYAW_CONSTRAIN);
  }
}





void updateMotors()
{  
  ESC0_VAL = tThro  + setRoll + setPitch - setYaw; //the values that need to be sent to the four ESCs which are calculated by PID and applied logically as per the flight dynamics.
  ESC1_VAL = tThro  - setRoll + setPitch + setYaw;
  ESC2_VAL = tThro  - setRoll- setPitch - setYaw;
  ESC3_VAL = tThro  + setRoll - setPitch + setYaw;

  if(tThro<ESC__MIN+10) //if throttle is in the lowest position we need to switch off all the motors and reset the accumulated integral values
  { 
    ESC0_VAL=ESC1_VAL=ESC2_VAL=ESC3_VAL=0;
    errsumR=0;
    errsumP=0;
    errsumY=0;
  }
  ESC0.writeMicroseconds(ESC0_VAL);
  ESC1.writeMicroseconds(ESC1_VAL);
  ESC2.writeMicroseconds(ESC2_VAL);
  ESC3.writeMicroseconds(ESC3_VAL);

}


// Function attached to RX_PIN_CH0 interrupt.
// Measures pulse lengths of input servo signals.
void chan0()
{

  if (digitalRead(RX_PIN_CH0) == HIGH) // if pin is high, new pulse. Record time
  {
    rxStart[0] = micros();
  }
  else // if pin is low, end of pulse. Calculate pulse length and add channel flag. Also reset channel start.
  {
    rxVal[0] = micros() - rxStart[0];
    rxStart[0] = 0;
  }
}

// Function attached to RX_PIN_CH1 interrupt.
// Measures pulse lengths of input servo signals.
void chan1()
{
  if (digitalRead(RX_PIN_CH1) == HIGH) // if pin is high, new pulse. Record time
  {
    rxStart[1] = micros();
  }
  else // if pin is low, end of pulse. Calculate pulse length and add channel flag. Also reset channel start.
  {
    rxVal[1] = micros() - rxStart[1];
    rxStart[1] = 0;
  }
}

// Function attached to RX_PIN_CH2 interrupt.
// Measures pulse lengths of input servo signals.
void chan2()
{
  if (digitalRead(RX_PIN_CH2) == HIGH) // if pin is high, new pulse. Record time
  {
    rxStart[2] = micros();
  }
  else // if pin is low, end of pulse. Calculate pulse length and add channel flag. Also reset channel start.
  {
    rxVal[2] = micros() - rxStart[2];
    rxStart[2] = 0;
  }
}

// Function attached to RX_PIN_CH3 interrupt.
// Measures pulse lengths of input servo signals.
void chan3()
{
  if (digitalRead(RX_PIN_CH3) == HIGH) // if pin is high, new pulse. Record time
  {
    rxStart[3] = micros();
  }
  else // if pin is low, end of pulse. Calculate pulse length and add channel flag. Also reset channel start.
  {
    rxVal[3] = micros() - rxStart[3];
    rxStart[3] = 0;
  }
}







