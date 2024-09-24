void descend()
{

  
  //Serial.println("stig/dyk");

 if (buf[2] < 50 - 5)
 {
Serial.println("UPP");
  digitalWrite (throttleDown ,LOW);
  digitalWrite (throttleUp , HIGH);
 }
 if (buf[2] > 50 + 5)
 {
  Serial.println("NER");
    digitalWrite (throttleDown, HIGH);
   digitalWrite (throttleUp, LOW);
}
else if((buf [2] >45) && (buf [2]<55))
{
  Serial.println("Stilla");
  digitalWrite ( throttleUp,HIGH );
  digitalWrite (throttleDown, HIGH);
}
}
