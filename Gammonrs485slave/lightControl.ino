void lightControl ()

{
  if (buf[10] == !0)
  {
    digitalWrite (lightToggle, HIGH);
    Serial.println ("lightToggle");
  }
  else
  {
    digitalWrite (lightToggle ,LOW);
  }
}
