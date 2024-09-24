void batteryAlarm ()
// larm för batteri. både för ubåten och för dosan
{
  if (receivedVoltmeter < 173 && loopMillis > larmMillis + 500 && loopMillis > larmMute + muteTime)

  { larmMillis = loopMillis;
    if (buzzerState == LOW)
    {
      buzzerState = HIGH;
    }
    else
    {
      buzzerState = LOW;
    }
  }
  if (receivedVoltmeter > 173 && loopMillis > larmMute + muteTime)
  {
    buzzerState = LOW;
  }
  digitalWrite(buzzer, buzzerState);
 /* if (digitalRead (camButton) != LOW)
  {
    larmMute = loopMillis;
    buzzerState = LOW;
  }*/
  {
    loopMillis = millis ();
  }
}
