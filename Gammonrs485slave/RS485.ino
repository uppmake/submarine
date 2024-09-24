void communication ()
{
  received = recvMsg (fAvailable, fRead, buf, sizeof (buf));
  //skriv emottagen data till byte received
  //Serial.println (buf[3]);
  //Serial.println(buf[11]); //skriv ut värdet från trimknappar
  
  if (received)
  {
     //Serial.println("mottaget1");
     //Serial.println (buf [3] );
    if (buf [0] != 1) //om buf 0 innehåller annat än 1...
      return;}// fel adress. börja om!

    if (buf [1] != 2)//om buf 1 innehåller annat än 2...
     {// Serial.println("fel funktion");
      
      //Serial.println("Mottaget");
      return;  // okänd funktion. börja om!
     }
    byte msg [] = 
    {//skapa svarsmeddelande...
      0,  // adress enhet 0 (master).               buf 0
      3,  // svara att LEDkommando tagits emot.     buf 1
      voltMeter,     //skicka batteristatus         buf 2
      angle,         //skicka värde från kompass    buf 3
      depth          //skicka värde från djupsensor buf 4      
    };
     //Serial.println("Enable Pin ");

    delay (1);  // give the master a moment to prepare to receive
    digitalWrite (ENABLE_PIN, HIGH);  // enable sending
    sendMsg (fWrite, msg, sizeof msg);
    digitalWrite (ENABLE_PIN, LOW);  // disable sending
  }// end if something received
