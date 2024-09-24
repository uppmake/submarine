#include "RS485_protocol.h"
#include <SoftwareSerial.h> //300, 600, 1200, 2400, 4800, 9600,14400, 19200, 28800, 31250, 38400, 57600, and 115200.
#include <Arduino.h>
#include <Wire.h>
//#include <TFT.h>
//#include <SPI.h>
#include "Ucglib.h"

/*
   tilllägg från senaste revisionen. samtliga funktioner som är kopplade till display
   och kompass

  vinkelplacering på plottad kompassros: oled 0.91 tum 128x32 pixlar
          xxxxxx               0-22
         y                      N
         y            10-2 nnv  |  nnö 22-44
         y         5-4 NV       |       NÖ 44-66
         y           2-9 nvv    |    nöö 66-88
                 1-15 V---------|---------Ö 88-110
                    2-21 svv    |    söö 29-21
                  5-26 SV       |       SÖ 25-26
                      10-2 ssv  |  ssö 19-29
                                S
                               16-30
*/




//#include <HMC5883L_Simple.h>
Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);

//#define addr 0x1E //I2C Address for The HMC5883L

//HMC5883L_Simple Compass; //lägg till kompassfunktionen.

//        ****inställningar för oled skärmen****
/*
   tillägg från senaste revisionen. kompassdelar osv.
*/
//const byte needleEndpointX (125); //tilläggsvärde för kompassnålens X coordinater sidled
//const byte needleEndpointY (20); //tilläggsvärde för kompassnålens Y coordinater höjdled
//const byte X_addedbatPos (35); //tilläggsvärde för att flytta hela batteriet i sidled
const byte cirkRad (15); //kompassens radie
const byte cirk_xPos (140); //kompassens X position centrum
const byte cirk_yPos (35); // kompassens Y position Centrum
//const byte rosepotPin = A3; //analog in för potentiometer
//const byte batpotPin = A2; //analog i för batteripotentiometer
byte rosePos (0);
byte batVal (0);
byte Push (0);
byte buttonFlag1 (0);
byte buttonFlag2 (0);
byte buttonFlag3 (0);
byte buttonFlag4 (0);
byte hysteresis (4);
byte debounce (3);
byte connectionFlag (0);
//int Position  [] = {  1,  15, 32,  47,  63, 79, 95, 111, 127, 143, 159, 175, 191, 207, 223, 239};
//int pixelXpos [] = { 16,  20, 25,  29,  30,  29,  25,  19,  16,  10,   5,   2,   1,   2,   5,  10};
//int pixelYpos [] = {  1,   2,  4,   9,  16,  21,  26,  29,  30,  29,  26,  21,  16,  10,   5,   2};
//int compassNewposition [16];
const byte dT (20); //definierar delayer
int lowlimit ();
int highLimit ();
int count ;

int buzzerState = LOW;
SoftwareSerial rs485 (2, 3);  // receive pin, transmit pin
byte joyYlevel;
byte joyXlevel;
byte joy2Ylevel;
byte joy2Xlevel;
int JoyYneutral;
int JoyXneutral;
int multibuttonidleVal1;
int multibuttonidleVal2;
int trimButtonidleVal;
byte buttonVal;
byte JOystickValueCameraTilt;
byte JOystickValueCameraRoll;
byte U;
byte printPos;
byte JoystickMode;
bool refreshLED;
bool refreshScreen;
byte lightToggle;
byte dive;
byte rise;
byte angle;
byte sendFlag; //flagga för att blockera överkommunikation
byte cameraCenter;
int CamTiltValue ;
int CamRollValue;
int cameraCenterPosition ;
const byte ENABLE_PIN = 4;
//const int descend = 8;    //skall bli led på framsidan, namnge io pin 8 till Descend
const byte buzzer = 7;//digital 10 oanvänd

//digital 11 oanvänd
//const int ascend = 12;   //namnge io pin 12 till accend
const byte LED_PIN = 6; //namnge IO pin 13 till LED_PIN.
//analog 0 /digital 14 joystick i buttonsread
//analog 1 /digital 15 joystick i buttonsread
const byte trimButtons = A2; //digital 16
//analog 3 P4 //digital 17
//analog 4 /lcd //digital 18
//analog 5 /lcd //digital 19
const byte multiButtons1 = A6;   //_analog 6 Knapp 15,16
const byte multiButtons2 = A7;//analog 7 Knapp 17,18

unsigned long loopMillis;
unsigned long readfromSerialMillis ;
unsigned long larmMillis;
unsigned long larmMute;
unsigned long buzzerMillis;
unsigned long sampleMillis;
unsigned long cameraMillis;
int muteTime(30000);
byte receivedVoltmeter (0);
byte receivedDepth (0);
byte old_joyXlevel = 0; //skapa byte old_joyXlevel
byte old_joyYlevel = 0; //skapa byte old Ylevel
byte oldcameraCenter = 0;
byte oldreceivedVoltmeter (0);
// callback routines

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

void setup()
{
  rs485.begin (28800);
  Serial.begin (9600);
  Wire.begin ();
  ucg.begin (UCG_FONT_MODE_TRANSPARENT); //skriv hälsningsfrasen.
  ucg.clearScreen();
  ucg.setRotate270();
  ucg.setColor(0, 0, 0, 255);
  ucg.setPrintPos(40, 15); //horisontal, vertikal
  ucg.setFont(ucg_font_amstrad_cpc_8f);
  ucg.print("DAS BOOT");
  ucg.setPrintPos(10, 30); //horisontal, Vertikal
  ucg.print("Djup");

  //printa kompasscirkeln en enda gång här

  ucg.setColor(0, 255, 0);
  ucg.drawCircle(cirk_xPos , cirk_yPos , cirkRad , UCG_DRAW_ALL);
  ucg.setColor(255, 255, 0);
  ucg.drawCircle(cirk_xPos , cirk_yPos , cirkRad + 2 , UCG_DRAW_ALL);


  // pinMode (rosepotPin , INPUT); //testingång för simulerad kompass
  //pinMode (batpotPin , INPUT); //testingång för batteri på display
  // pinMode (camButton, INPUT_PULLUP); //toggle för kamerastyrning
  //pinMode (descend, INPUT_PULLUP); //sänkarpumpknapp
  // pinMode (ascend, INPUT_PULLUP); //stigarpumpknapp
  pinMode (ENABLE_PIN, OUTPUT);  // driver output enable
  pinMode (LED_PIN, OUTPUT);  // built-in LED
  //pinMode (cameraSwitch, INPUT_PULLUP); //Set pin A2 as an input
  pinMode (buzzer, OUTPUT); //larmutgång till batterinivå
  pinMode (multiButtons1, INPUT_PULLUP); //larmutgång till batterinivå
  pinMode (multiButtons2, INPUT_PULLUP);
  //pinMode (lightSwitch, INPUT_PULLUP); //ingång för strålkastartoggle
  //Serial.println("hej");

  refreshScreen = true; //flagga för att skriva till skärmen
  refreshLED = false;
  lightToggle = false;
  connectionFlag = false;
  JoystickMode = 1;
  CamTiltValue = 0;
  CamRollValue = 0;
  cameraCenter = 1;
  JoyYneutral = analogRead (A0);
  JoyXneutral = analogRead (A1);
  digitalWrite (buzzer, LOW);
  
  multibuttonidleVal1 = analogRead(multiButtons1);
  multibuttonidleVal2 = analogRead(multiButtons2);
  trimButtonidleVal = analogRead(trimButtons);
}

void loop()
{

  buttonVal = analogRead (trimButtons) / 4;
  RS485 ();


  displayen ();

  buttonsRead ();

  beep ();

  //batteryAlarm ();

  //ValuesCheck();

  //if (cameraCenter == 0)
  {
    // centeringCamera ();
  }
}
