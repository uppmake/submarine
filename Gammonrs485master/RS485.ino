
void RS485()

{

  byte msg [] = //skapa byte msg. och bygg sträng av nedan:
  {
    1,                            // skriv adressen 1 i buf nr 0.
    2,                           // skriv kommando 2 i buf nr 1.
    joyXlevel,                    // skriv potvärde i buf2 "joyXlevel". buf2
    joyYlevel,                    // skriv potvärdeY i buf3 "joyYlevel". buf 3
    dive,                         //buf 4
    rise,                         //buf 5
    cameraCenter,                 //buf 6
    JOystickValueCameraTilt,      //buf 7
    JOystickValueCameraRoll,      //buf 8
    JoystickMode,                 //buf 9
    lightToggle,                  //buf 10
    buttonVal
  };

  // send to slave
  digitalWrite (ENABLE_PIN, HIGH);  // enable sending
  sendMsg (fWrite, msg, sizeof msg);
  digitalWrite (ENABLE_PIN, LOW);  // disable sending

  // receive response
  byte buf [20];
  byte received = recvMsg (fAvailable, fRead, buf, sizeof buf);

  digitalWrite (LED_PIN, received == 0);  // turn on LED if error
  connectionFlag = received;
  // only send once per successful change
  if (received) //Skriv om värdena enligt emottagen returdata
  { old_joyXlevel = joyXlevel;
    old_joyYlevel = joyYlevel;
    oldcameraCenter = cameraCenter;
    connectionFlag = true;
    receivedVoltmeter = buf[2];
    angle = buf [3];
    //Serial.println (angle);
    receivedDepth = buf[4];
    readfromSerialMillis = millis();
  }
  //sendFlag = false;
}
// end of loop
