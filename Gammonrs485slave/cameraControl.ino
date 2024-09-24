void cameraControl ()
{
  //Tilt Camera down
  if (buf [9] == 3) //buffer 9 aka joystickCameraMode
  {
Serial.println (buf[2]);
    if (buf [2] < 40) //buffer 7 aka JOystickValueCameraTilt
    {
      digitalWrite (stepperDirection, HIGH);
      digitalWrite (tiltStep, HIGH);
      delay (3);
      //digitalWrite (stepperDirection, LOW);
      tiltSteps = tiltSteps + 1;
    }
  else 
  {
    digitalWrite (stepperDirection, LOW);
        digitalWrite (tiltStep, LOW);

  }


  //tilt camera up
  if (buf [2] > 60)
  {
    digitalWrite (stepperDirection, LOW);
    digitalWrite (tiltStep, HIGH);
    delay (3);
    digitalWrite (tiltStep, LOW);
    tiltSteps = tiltSteps - 1;
  }

  else 
  {
    digitalWrite (stepperDirection, LOW);
        digitalWrite (tiltStep, LOW);

  }


  //roll camera CCW
  if (buf [3] < 40)
  {
    digitalWrite (stepperDirection, HIGH);
    digitalWrite (rollStep, HIGH);
    delay(3);
    digitalWrite (rollStep, LOW);
    rollSteps = rollSteps + 1;
  }

  else 
  {
    digitalWrite (stepperDirection, LOW);
        digitalWrite (rollStep, LOW);

  }


  //Roll Camera CW
  if (buf [3] > 60)
  {
    digitalWrite (stepperDirection, LOW);
    digitalWrite (rollStep, HIGH);
    delay(3);
    digitalWrite (stepperDirection ,LOW); 
    
    rollSteps = rollSteps - 1;
  }
  else
  {
        digitalWrite (stepperDirection ,LOW); 
    digitalWrite (rollStep, LOW);

  }
  }
  else 
  {
    digitalWrite (stepperDirection, LOW);
        digitalWrite (rollStep, LOW);
    digitalWrite (tiltStep, LOW);

  }
}
