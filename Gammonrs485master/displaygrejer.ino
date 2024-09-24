/* allt som har med displayen att göra hamnar här:
    batteristatus ()
    toggleindikering på strålkastare ()
    djupsensor ()
    toggleindikering på kameraläge
*/

void displayen ()
{


  if ((lightToggle == true) && (refreshLED == true))
  {
    ucg.setColor(0, 255, 255, 0);
    ucg.setPrintPos (10, 120); //horisont, vertikal
    ucg.print("LED on");
    refreshLED  = false;
  }

  if ((lightToggle == false) && (refreshLED == false))
  {
    ucg.setColor(0, 50, 0, 30);
    ucg.setPrintPos (10, 120); //horisont, vertikal
    ucg.print("LED on");
    //ucg.drawBox(10,100,60,20);

    refreshLED = true;
  }

  if  (oldreceivedVoltmeter != receivedVoltmeter)
  {
    ucg.setColor(0, 255, 255, 255);
    ucg.drawBox(112, 76, 8, 4);   // batteripolen( horval,verVal, Width, height
    ucg.drawBox(110, 80, 12, 20); //batteriet( horval,verVal, Width, height
    ucg.setColor(0, 0, 0, 0);
    ucg.drawBox(112, 80, 8, receivedVoltmeter / 14); //horisontal, vertikal, bredd, höjd
    oldreceivedVoltmeter = receivedVoltmeter;
  }

  //gör detta endast en gång. tänd kameratexten
  if ((JoystickMode == 1) && (refreshScreen == true))
  {
        ucg.setPrintPos (10, 105);
    ucg.setColor(255, 255, 255, 255);
    ucg.print("camControl");
    
    ucg.setPrintPos (10, 105);
    ucg.setColor(0, 255, 255, 0);
    ucg.print("navigate");
    refreshScreen = false;
  }

  //Släck kameratexten
  if ((JoystickMode == 2) && (refreshScreen == true))
  {
    ucg.setPrintPos (10, 105);
    ucg.setColor(255, 255, 255, 255);
    ucg.print("navigate");

    ucg.setPrintPos (10, 105);
    ucg.setColor(0, 255, 255, 0);
    ucg.print("lift");
    refreshScreen = false;
    
  }
    if ((JoystickMode == 3) && (refreshScreen == true))
  {
        ucg.setPrintPos (10, 105);
    ucg.setColor(255, 255, 255, 255);
    ucg.print("lift");
    
    ucg.setPrintPos (10, 105);
    ucg.setColor(0, 255, 255, 0);
    ucg.print("camControl");
    refreshScreen = false;
  }


  if (connectionFlag == 1)
  {
    ucg.setPrintPos (10, 90);
    ucg.setColor(0, 0, 0, 0);
    ucg.print("connect");
  }
  if (connectionFlag == 0)
    {
    ucg.setPrintPos (10, 90);
    ucg.setColor(255, 0, 0, 0);
    ucg.print("connect");
  }
}
/*
  //analogRead (rosepotPin) / 4; //
  int Position  [] = {  1,  15, 32,  47,  63, 79, 95, 111, 127, 143, 159, 175, 191, 207, 223, 239};
  int pixelXpos [] = { 16,  20, 25,  29,  30,  29,  25,  19,  16,  10,   5,   2,   1,   2,   5,  10};
  int pixelYpos [] = {  1,   2,  4,   9,  16,  21,  26,  29,  30,  29,  26,  21,  16,  10,   5,   2};

  //rosePos = angle; //läs in nålens värde från rs485

  if ((rosePos >  Position [count]) && (rosePos <  Position [count + 1]))
    //om Rosepos är större än hysteres +position 1-16 & mindre än hysteres +position 1-16
  {
    ucg.setColor(0, 0, 0, 0);
    ucg.drawDisc(cirk_xPos , cirk_yPos , cirkRad - 1 , UCG_DRAW_ALL);



    //skapa och ändra kompasssymbol.
    //Ucglib::drawLine(x1,y1,x2,y2)

    ucg.drawLine(cirk_xPos, cirk_yPos, pixelXpos [count + 1] + needleEndpointX, pixelYpos [count + 1] + needleEndpointY );
    ucg.drawLine(cirk_xPos, cirk_yPos, pixelXpos [count - 1] + needleEndpointX, pixelYpos [count - 1] + needleEndpointY );

    ucg.setColor(0, 255, 255, 0);
    ucg.drawLine(cirk_xPos, cirk_yPos, pixelXpos [count] + needleEndpointX, pixelYpos [count] + needleEndpointY );

    refreshLED = true;
    //spara föregående värde nedanför så att vi kan skriva över den
    //linjen direkt innan nästa skrivs in.
    //ucg.drawCircle(cirk_xPos + X_addedrosePos , cirk_yPos , cirkRad , ucg_DRAW_ALL);
    //lägg till IF vilkor som skriver ut kompass nollställning.
    //ucg.drawStr(1,15,"Kompass");
    // ucg.drawStr(1,23,"nollst.");
  }



  if (receivedDepth <= 9)
  {

    // ucg.setDrawColor (0);
    //   ucg. drawBox ( 40, 17 ,7,8);
    //          printPos = 46; gör plats för 1-tal

  }

  if ((receivedDepth >= 10) && (receivedDepth <= 99))
  {

    //  ucg.setDrawColor (0);
    //   ucg. drawBox ( 32, 17 ,7,17);
    //   printPos = 40; gör plats för 10 tal.
  }

  if (receivedDepth >= 100)
  {
    //    printPos = 34;
  }
  // ucg.setDrawColor (1);
  //ucg.setCursor (printPos, 25);
  // ucg.print (receivedDepth);
  // ucg.drawStr ( 54, 25,"m" );
  // ucg.sendBuffer();
  //Serial.println (printPos);




  //   angle = 0;


  delay (3);

  if (count < 16)
  {
    count++;
  }
  else if (count > 15)
  {
    count = 0;
  }
}
*/
