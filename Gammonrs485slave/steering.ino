void steering ()
{
  if (buf [9] == 1 ) //joystick mode
  {
        Serial.println("drivläge");
    if (buf[2] > 50 + 5)
    {
      analogWrite (motorOutPin2, 0);
      motorSpeedX = map (buf [2], 10, 50, 0, 255);     //number to map,fromlow,fromhigh,tolow,tohigh.
      analogWrite (motorOutPin1, motorSpeedX);
      //motorXForward(motorSpeedX);
      Serial.println("motor går1");
    }
    else if (buf[2] < 50 - 5)
    {
      analogWrite (motorOutPin1, 0);
      motorSpeedX = map (buf [2], 50, 90, 255, 0);      //number to map,fromlow,fromhigh,tolow,tohigh.
      analogWrite (motorOutPin2, motorSpeedX);
      //motorXBackwards(motorSpeedX);

      Serial.println("motor går2");

    }
    
    if ((buf [2] >45) && (buf [2]<55))
    {
      analogWrite (motorOutPin1, 0);
      analogWrite (motorOutPin2, 0);
      Serial.println("stoppad");
    }

    if (buf[3] > 50 + 5)
    {
      analogWrite (motorOutPin4, 0);
      motorSpeedY = map (buf [3], 50, 90, 0, 255);      //number to map,fromlow,fromhigh,tolow,tohigh.
      analogWrite (motorOutPin3, motorSpeedY);
      //motorYForward(motorSpeedY);

      Serial.println("motor går4");

    }
    else if (buf[3] < 50 - 5)
    {

      analogWrite (motorOutPin3, 0);
      motorSpeedY = map (buf [3], 10, 50, 255, 0); //number to map,fromlow,fromhigh,tolow,tohigh.
      analogWrite (motorOutPin4, motorSpeedY);
      //motorYBackwards(motorSpeedY);

      Serial.println("motor går5");

    }
    
    if ((buf [3] >45) && (buf [3]<55))
    {
      analogWrite (motorOutPin3, 0);
      analogWrite (motorOutPin4, 0);
      Serial.println("stoppad");
    }
    
    //Serial.println (buf [2]);
    //Serial.println (buf [3]);
  }
}
