// motor controll joystick mode


void buttonsRead()
{
  int multibuttonVal1 = (analogRead(multiButtons1));
  int multibuttonVal2 = (analogRead(multiButtons2));
  //Serial.println(multibuttonidleVal1);
  /*
    if ((analogRead (multibuttons1))>= multibuttonIdleVal+50)
    {//om knappen ger mer än 50 i värdeökning så har en förändring skett.
    multibuttonIdleVal = analogRead, multibuttons1 (); //ändra viloläge till den nya standarden.
    buttonFlag1 == HIGH //Knappflaggan tänds
    }
    if
  */

  if ((multibuttonVal1 > multibuttonidleVal1 + 50 ) && ( buttonFlag1 == LOW))
  { //tryckflagga görs hög medan knappen är nere

    buttonFlag1 = HIGH;
    Serial.println("knapp1 steg1");

  }
  if ((multibuttonVal1 > multibuttonidleVal1 + 50 ) && ( buttonFlag1 == HIGH))
  { //Gör ingenting om knappen är intryckt och flaggan är hög

    Serial.println("knapp1 steg2");

  }
  else if ((multibuttonVal1 <= multibuttonidleVal1 + 30) && ( buttonFlag1 == HIGH))
  { //knappen är släppt och bara flaggan är kvar. genomför koden och återställ knappflaggan
    Serial.println("knapp1 steg3");
    buttonFlag1 = LOW;
    refreshScreen = true;
    Push = !Push;
  }
  //Regler för att växla till kamerastyrning
  if ((multibuttonVal1 < multibuttonidleVal1 - 50) && (buttonFlag2 == 0))
  { //tryckflagga görs hög medan knappen är nere
    Serial.println("kameraknappen steg1");
    buttonFlag2 = HIGH;
  }
  if ((multibuttonVal1 < multibuttonidleVal1 - 50) && (buttonFlag2 == HIGH))
  { //Gör ingenting om knappen är intryckt och flaggan är hög
    Serial.println("kameraknappen steg 2");
    //Serial.println(multibuttonVal1);

  }
  else if ((multibuttonVal1 >= multibuttonidleVal1 - 30) && (buttonFlag2 == HIGH))
  { //knappen är släppt och bara flaggan är kvar. genomför koden och återställ knappflaggan
    Serial.println("kameraknappen steg 3");
    Push = !Push;
    JoystickMode++;
    Serial.println(JoystickMode);
    buttonFlag2 = LOW;
    refreshScreen = true;

  }
  if (JoystickMode > 3)
  {
    JoystickMode = 1;
    refreshScreen =true;
  }
  //Regler för aktivering av knapp 3 slå av och på lyset
  if ((multibuttonVal2 > multibuttonidleVal2 + 50) && (buttonFlag3 == LOW))
  { //tryckflagga görs hög medan knappen är nere
    Serial.println("lampknappen steg 1");
    delay(debounce);
    buttonFlag3 = HIGH;
  }
  if ((multibuttonVal2 > multibuttonidleVal2 + 50) && (buttonFlag3 == HIGH))
  { //Gör ingenting om knappen är intryckt och flaggan är hög
    Serial.println ("lampknappen steg 2");
  }
  else if ((multibuttonVal2 <= multibuttonidleVal2 + 30) && (buttonFlag3 == HIGH))
  { //knappen är släppt och bara flaggan är kvar. genomför koden och återställ knappflaggan
    Serial.println("lampknappen steg 3");
    lightToggle = !lightToggle;
    Push = !Push;
    buttonFlag3 = LOW;
  }
  //Regler för aktivering av knapp 4 LH konverter
  if ((multibuttonVal2 < multibuttonidleVal2 - 50) && (buttonFlag4 == LOW))
  { //tryckflagga görs hög medan knappen är nere
    delay(debounce);
    Serial.println ("knapp4 steg1");
    buttonFlag4 = HIGH;
  }
  if ((multibuttonVal2 < multibuttonidleVal2 - 50) && (buttonFlag4 == HIGH))
  { //Gör ingenting om knappen är intryckt och flaggan är hög
    Serial.println("knapp4 steg2");
  }
  else if ((multibuttonVal2 > multibuttonidleVal2 - 30) && (buttonFlag4 == HIGH))
  { //knappen är släppt och bara flaggan är kvar. genomför koden och återställ knappflaggan
    Serial.println("knapp4 steg3");
    buttonFlag4 = LOW;
    Push = !Push;
  }

  //Normal drift nedan

  joyXlevel = map ( analogRead(A1), 0,  JoyXneutral * 2,  0,  100 ); //number to map,fromlow,fromhigh,tolow,tohigh.

  joyYlevel = map ( analogRead(A0), 0,  JoyYneutral * 2,  100,  0 ); //number to map,fromlow,fromhigh,tolow,tohigh.
}




/*
  {
   // if (digitalRead (ascend) == LOW)
    {
      //Serial.println("ascend");
      rise = true;
      dive = false;
    }
    else
    {
      rise = false;
    }
    //if (digitalRead (descend) == LOW)
    {
      //Serial.println("descend");
      rise = false;
      dive = true;
    }
    else
    {
      dive = false;
    }*/
