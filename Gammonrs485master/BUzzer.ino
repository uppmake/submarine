void beep ()

{  
  if (Push == HIGH)
{
  digitalWrite (buzzer, HIGH);
  buzzerMillis = millis ();
  Push = LOW;
//Serial.println ("BUZZ");
}
if (buzzerMillis+100< millis () )
{
    digitalWrite (buzzer, LOW);
}
}
