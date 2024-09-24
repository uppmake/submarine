#include <Arduino.h>
#include <Wire.h>
//#include <HMC5883L_Simple.h>
#include <SoftwareSerial.h>
#include "RS485_protocol.h"//300, 600, 1200, 2400, 4800, 9600, //14400, 19200, 28800, 31250, 38400, 57600, and 115200.
SoftwareSerial rs485 (7, 8);  // receive pin, transmit pin
const byte ENABLE_PIN = 4;
//HMC5883L_Simple Compass; //SCL 5 SDA4

void fWrite (const byte what)
{
  rs485.write (what);
}
int fAvailable ()
{
  return rs485.available ();
}
int fRead ()
{
  return rs485.read ();
}
//definiera stift
const byte stepperDirection = 2; // sätt pin 2 som riktning för stegmotor
const byte motorOutPin3 = 3;  //sätt stift 10 som motorstyrning
// pin4 är upptagen med Enable rs485
const byte motorOutPin1 = 5; //sätt stift 5 som motorstyrning
const byte motorOutPin2 = 6; //sätt stift 6 som motorstyrning
//pin 7 är upptagen med rs485 receive
//pin 8 är upptagen med rs 485 transmit
const byte tiltStep = 9;  //pin 9 är upptagen med TiltStep
const byte rollStep = 10; //pin 10 är upptagen med TiltRoll
const byte motorOutPin4 = 11;  //sätt stift 11 som motorstyrning
//pin 12 är upptagen med    [  ]
//pin 13 är upptagen med    [LarmLED]
const byte lightToggle = 14;  //pin A0/14 är upptagen med [lightToggle]
const byte depthSensor = A1; //pin A1/15 är upptagen med [djupsensor]
  //pin A2/16 är ledig
const byte Voltage = A3;      //pin A3/17 är upptagen med [stigning]
const byte comp = A4;
const byte throttleDown = 16; // pin A4/18 är upptagen med stig
const byte throttleUp = 19;//pin A5/19 är upptagen med stig

//skapa banker
int motorSpeedX     = 130; //bygg box för mappat värde
int motorSpeedY     = 130; //bygg box för mappat värde
byte voltMeter      = 0;
byte angle          = 0;
byte depth          = 0;
int joyValueX       = 0;
int joyValueY       = 0;
byte tiltSteps      = 0;
byte rollSteps      = 0;
//byte servoPos       =0;
byte XIdle;
byte YIdle;
byte snittBitFlag (0);
byte received;
int snittAngle;
byte snitt[4];
byte buf [20]; //max storlek på datasträngen. begränsar Masters maxsträng
long int passedMillis;
long int storedMillis;
void setup()
{
  rs485.begin (28800);
  Serial.begin (9600);
  Wire.begin();

  //pinMode (depthSensor, INPUT_PULLUP);
  pinMode (ENABLE_PIN, OUTPUT);  // driver output enable
  pinMode (throttleDown , OUTPUT);
  pinMode (throttleUp, OUTPUT);
  pinMode (lightToggle, OUTPUT);
  pinMode (stepperDirection, OUTPUT);
  pinMode (rollStep, OUTPUT);
  pinMode (tiltStep, OUTPUT);
  //pinMode (Voltage, INPUT);
  //pinMode (A4, INPUT_PULLUP);
  //pinMode (A5, INPUT_PULLUP);
  digitalWrite (lightToggle, LOW);
  digitalWrite (rollStep, LOW);
  digitalWrite (tiltStep, LOW);

  /*Compass.SetDeclination(23,39, 'E');
    Compass.SetSamplingMode(COMPASS_SINGLE);
    Compass.SetScale(COMPASS_SCALE_130); //088, 130,190,250,400,470,560,810
    Compass.SetOrientation(COMPASS_HORIZONTAL_Y_NORTH); */
}
void loop()
{
  voltMeter = analogRead (A3) / 4;
  //depth = analogRead (depthSensor) / 8; //Analog1
  communication ();
  //Serial.println("hejhej");
  //Serial.println(voltMeter);


  lightControl ();

  if ((received) && (buf [9] == 1)) //stoppa styrning om kommunikationen slutar
  {
    steering ();
  }
  if (buf [9] == 2)
  {
    descend();
  }
  if (buf [9] == 3)
  {
    cameraControl ();
  }
  compass ();
}
