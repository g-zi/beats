// Encoder Right #################################################################################
  
  rightnewPos = rightEnc.read() / 4;
  if (rightnewPos != rightPos || bitRead(rightLCDView, 5) == 1)
  {
    bitClear(rightLCDView, 5);
    
    if (MenuDepth % 2 == 1) { // main menue
      bitClear(MenuDepth, 3); // right menu on
      if (rightnewPos > rightTFT_MenuLines + 1) {
        rightnewPos = 2; rightEnc.write(rightnewPos * 4);
      }
      if (rightnewPos < 2) {
        rightnewPos = rightTFT_MenuLines + 1; rightEnc.write(rightnewPos * 4);
      }
      EncButtonTFT(); // update Encoder LED's
      rightTFT_MenuSelect(rightnewPos);
    }
    
    else if (MenuDepth == 10) { // sub menue left encoder
      if (shift == true && (leftLastEncoder + 8 != CountLenghtEE)) {
        if (rightnewPos < rightPos) { rightnewPos = rightnewPos - 9; rightEnc.write(rightnewPos * 4); }
        if (rightnewPos > rightPos) { rightnewPos = rightnewPos + 9; rightEnc.write(rightnewPos * 4); }
      }
      
      if (rightnewPos < 1 ) { rightnewPos = 0; rightEnc.write(rightnewPos * 4); }
        switch (leftLastEncoder + 8) { // sub menue of left encoder
          case CountLenghtEE: // Beat count length
          if (shift == false) { // no shift pressed
            if (rightnewPos < rightPos) { rightnewPos = (rightnewPos + 1) / 2; rightEnc.write(rightnewPos * 4); } // encoder switch released?
            if (rightnewPos > rightPos) { rightnewPos = (rightnewPos * 2) - 1; rightEnc.write(rightnewPos * 4); } // encoder switch released?
          }
          if (rightnewPos < 1 ) { rightnewPos = 1; rightEnc.write(rightnewPos * 4); }
          if (rightnewPos > 254 ) { rightnewPos = 255; rightEnc.write(rightnewPos * 4); }
          CountLenght = rightnewPos;
          rightnewPos++; rightEnc.write(rightnewPos * 4);
          TFT_2_MenuValue();
          rightnewPos--;
          tft.setFont(A24n);
          tft.setTextColor(TFT_Cyan);        
          if( bitRead(MIDIChannel, 7) == 0 ) {
            tft.setCursor(_tw/2+_ts*6, _c1+_ts);
            tft.print("Beats"); }
          else {
            tft.setCursor(_tw/2+_ts*12, _c1+_ts);
            tft.print("Bars"); }
          break;
      }
    }
  
    else if (MenuDepth == 2) { // sub menue right encoder
      if (shift == true) {
        if (rightnewPos < rightPos) { rightnewPos = rightnewPos - 9; rightEnc.write(rightnewPos * 4); }
        if (rightnewPos > rightPos) { rightnewPos = rightnewPos + 9; rightEnc.write(rightnewPos * 4); }
      }
      if (rightnewPos < 1 ) { rightnewPos = 0; rightEnc.write(rightnewPos * 4); }

      switch (rightLastEncoder - 2) {
        
        case DMXBaseEE: // DMX base address
          if (rightnewPos < 1 ) { rightnewPos = 0; rightEnc.write(rightnewPos * 4); }
          if (rightnewPos > 254 ) { rightnewPos = 255; rightEnc.write(rightnewPos * 4); }
          DMXBase = rightnewPos;
          TFT_MenuValue(rightnewPos);
          break;
          
        case DMXUnitsEE: // DMX units selection
          if (DMXUnits > 0) {
            if (rightnewPos < 1 ) { rightnewPos = 4; rightEnc.write(rightnewPos * 4); }
            if (rightnewPos > 4 ) { rightnewPos = 1; rightEnc.write(rightnewPos * 4); }}
          else {
            if (rightnewPos < 1 ) { rightnewPos = 3; rightEnc.write(rightnewPos * 4); }
            if (rightnewPos > 3 ) { rightnewPos = 1; rightEnc.write(rightnewPos * 4); }}
  
          tft.fillRect(_mx, _my, _tw, _mh, TFT_Black); // clear area
          
          tft.setTextSize(1);
          tft.setFont(A24n);
          tft.setTextColor(TFT_Gray);
          if (rightnewPos == 1) {
            tft.setCursor(_ts*2, _c1);
            tft.setFont(A14n);
            tft.setTextColor(TFT_LightCyan);
            tft.print("Cameo Pixbar 650 - 8 COB");
            tft.setFont(A24n);
            tft.setTextColor(TFT_White);
            leftEnc.write(((DMXUnits & 0b00000011)+1) * 4);
            leftPos = (DMXUnits & 0b00000011)+1; }
            
          tft.setCursor(_cy + _ts * 15, _c2);
          tft.print("Pixbar");
          
          tft.setCursor(_i3-_ts*2, _c2);
          if ((DMXUnits & 0b00000011) == 0) tft.print("off");
          else {
            tft.setTextColor(TFT_Yellow);
            tft.print(DMXUnits & 0b00000011);
            tft.print("   ");
            tft.setTextColor(TFT_Gray);
            tft.print((DMXUnits & 0b00000011) * 30); }
          
          tft.setTextColor(TFT_Gray);
          if (rightnewPos == 2) {
            tft.setCursor(_ts*2, _c1);
            tft.setFont(A14n);
            tft.setTextColor(TFT_LightCyan);
            tft.print("SC-X50 MKII LED Scanner");
            tft.setFont(A24n);          
            tft.setTextColor(TFT_White); }
  
          tft.setCursor(_cy, _c3);
          tft.print("Scanner");
          tft.setCursor(_i3-_ts*2, _c3);
          if ( bitRead(DMXUnits, 2) == 0 ) tft.print("off");
          else {
            tft.setTextColor(TFT_Yellow);
            tft.print("on");
            tft.print(" ");
            tft.setTextColor(TFT_Gray);
            tft.print("64"); }
  
          tft.setTextColor(TFT_Gray);
          if (rightnewPos == 3) {
            tft.setCursor(_ts*2, _c1);
            tft.setFont(A14n);
            tft.setTextColor(TFT_LightCyan);
            tft.print("4x COB 16x30W (64 COB)");
            tft.setFont(A24n);          
            tft.setTextColor(TFT_White); 
            leftEnc.write((((DMXUnits & 0b00011000)>>3)+1) * 4);
            leftPos = ((DMXUnits & 0b00011000)>>3)+1; }
  
          tft.setCursor(_cy + _ts * 3, _c4);
          tft.print("64 COB");
          tft.setCursor(_i3-_ts*2, _c4);
          if ((DMXUnits & 0b00011000) >> 3 == 0) tft.print("off");
          else {
            tft.setTextColor(TFT_Yellow);          
            tft.print((DMXUnits & 0b00011000) >> 3);
            tft.print(" ");
            tft.setTextColor(TFT_Gray);
            tft.print(((DMXUnits & 0b00011000) >> 3) * 192); } 
   
          if((DMXUnits & 0b00011111) > 0) {
            if(rightnewPos == 4) {
              tft.setCursor(_ts*2, _c1);
              tft.setFont(A14n);
              tft.setTextColor(TFT_LightCyan);
              tft.print("Select DMX Base Address");
              tft.setFont(A24n); } 
  
            tft.setTextColor(TFT_Gray);
            tft.setCursor(_cy+_ts*3, _c5);
            if (rightnewPos == 4) {
              tft.setTextColor(TFT_White);
              leftEnc.write(DMXBase * 4);
              leftPos = DMXBase; }
  
            tft.print("Adr. ");
            tft.setTextColor(TFT_Yellow);
            tft.print(DMXBase);
            tft.setTextColor(TFT_Gray);
            tft.print(" - ");
            if(DMXBase + (DMXUnits & 0b00000011) * 30 + ((DMXUnits & 0b00000100) >> 2) * 64 + ((DMXUnits & 0b00011000) >> 3) * 192 > 512) {
              tft.setTextColor(TFT_Red,TFT_Black); }
            tft.print(DMXBase + (DMXUnits & 0b00000011) * 30 + ((DMXUnits & 0b00000100) >> 2) * 64 + ((DMXUnits & 0b00011000) >> 3) * 192);
            tft.print("      ");            
          }
          
          break;
  
        case DMXPatternEE: // DMX pattern for 8x8 COB
          if (rightnewPos < 1 ) { rightnewPos = 0; rightEnc.write(rightnewPos * 4); }
          if (rightnewPos > 254 ) { rightnewPos = 255; rightEnc.write(rightnewPos * 4); }
          DMXPattern = rightnewPos;
          left_str = "Pixbar";
          left_half_bound = _ts*6 ;
          right_str = "64COB";
          right_half_bound = _ts*2 ;
          TFT_2_MenuValue();
          break;
  
        case DMXBrightEE: // DMX brightness
          if (rightnewPos < rightPos && shift == false) { rightnewPos = rightnewPos - 4; rightEnc.write(rightnewPos * 4); }
          if (rightnewPos > rightPos && shift == false) { rightnewPos = rightnewPos + 4; rightEnc.write(rightnewPos * 4); }
          if (rightnewPos < 1 ) { rightnewPos = 0; rightEnc.write(rightnewPos * 4); }
          if (rightnewPos > 254 ) { rightnewPos = 255; rightEnc.write(rightnewPos * 4); }
          DMXBright = rightnewPos;
          left_str = "Back";
          left_half_bound = _ts * 11 ;
          right_str = "Bright";
          right_half_bound = _ts * 8 ;
          TFT_2_MenuValue();
          break;
  
        case HATPatternEE: // Display 64, HAT screen for DMX 8x8, Waveshare or Unicorn
          if (rightnewPos < 1 ) { rightnewPos = 2; rightEnc.write(rightnewPos * 4); }
          if (rightnewPos > 2 ) { rightnewPos = 1; rightEnc.write(rightnewPos * 4); }
          HATPattern = rightnewPos;
          tft.fillRect(_mx, _my, _tw, _mh, TFT_Black); // clear area
          tft.setFont(A24b);
          tft.setTextSize(1);
          tft.setTextColor(TFT_Yellow, TFT_Black);
          switch (HATPattern) {
            case 1: tft.setCursor(_ts*6, _c3); tft.print("Linear Output"); break;
            case 2: tft.setCursor(_ts*10, _c3); tft.print("Unicorn HAT"); break;
          }
          break;
  
        case NeoPixelBrightEE: // Neopixel brightness
          if (rightnewPos < 1 ) { rightnewPos = 0; rightEnc.write(rightnewPos * 4); }
          if (rightnewPos > 50 ) { rightnewPos = 50; rightEnc.write(rightnewPos * 4); }
          NeoPixelBright = rightnewPos;
          TFT_MenuValue(rightnewPos);
          if ( RUN == true) {
            Counter--;
            ClockCounter();
          }
          else {
            for (int i = 0; i < 16; i++) pixels.setPixelColor(i, pixels.Color(NeoPixelBright, NeoPixelBright, 0));  // show
          }
          pixels.show();
          break;
      }
    }
    
    
    
    else if (MenuDepth == 0) { // no menue
    
      // map active UnitsView to encoder
      if ( !(rightLCDView == 4 && shift == true && ProgMode == true) ) { // not in prog mode with shift pressed and motion selected
        if (shift == true) {
          if (rightnewPos < rightPos ) { rightnewPos = rightnewPos - 9 ; rightEnc.write(rightnewPos * 4 + 3); }
          if (rightnewPos > rightPos ) { rightnewPos = rightnewPos + 9 ; rightEnc.write(rightnewPos * 4); }
        }
        if (rightnewPos < 1 ) { rightnewPos = 0; rightEnc.write(rightnewPos * 4); }
        if (rightnewPos > 254 ) { rightnewPos = 255; rightEnc.write(rightnewPos * 4); }
      }
/*      
      else if (UnitsView == 0 && rightLCDView == 1) {
        if (rightnewPos < rightPos && digitalRead(rightENC_BTN) == LOW) { rightnewPos = rightnewPos - 4 ; rightEnc.write(rightnewPos * 4); }
        if (rightnewPos > rightPos && digitalRead(rightENC_BTN) == LOW) { rightnewPos = rightnewPos + 4 ; rightEnc.write(rightnewPos * 4); }
      }
*/      
      
      tft.setFont();
      tft.setTextSize(_ts);
      switch(UnitsView) { // unit views encoder mappings
        case 0: // MIDI
          if ( ProgMode == false ) { // --------------------------------------------------------------
            if (rightLCDView == 0 ) { 
              if (rightnewPos > 127 ) { rightnewPos = 127; rightEnc.write(rightnewPos * 4); }
              rightEncMIDI_D = rightnewPos; 
              usbMIDI.sendControlChange(3 + MIDIBaseAdr - 1, rightnewPos, MIDIChannel & 0b00001111); // Send Control (control, value, channel)
//              MIDI.sendControlChange(3 + MIDIBaseAdr - 1, rightnewPos, MIDIChannel & 0b00001111); // Send Control (control, value, channel)
            }
            if (rightLCDView == 1 ) { 
              if (rightnewPos > 127 ) { rightnewPos = 127; rightEnc.write(rightnewPos * 4); }
              rightEncMIDI_E = rightnewPos; 
              usbMIDI.sendControlChange(4 + MIDIBaseAdr - 1, rightnewPos, MIDIChannel & 0b00001111); // Send Control (control, value, channel)
//              MIDI.sendControlChange(4 + MIDIBaseAdr - 1, rightnewPos, MIDIChannel & 0b00001111); // Send Control (control, value, channel)
            }
            else if (rightLCDView == 2 ) { 
              if (rightnewPos > 127 ) { rightnewPos = 127; rightEnc.write(rightnewPos * 4); }
              rightEncMIDI_F = rightnewPos; 
              usbMIDI.sendControlChange(5 + MIDIBaseAdr - 1, rightnewPos, MIDIChannel & 0b00001111); // Send Control (control, value, channel)
//              MIDI.sendControlChange(5 + MIDIBaseAdr - 1, rightnewPos, MIDIChannel & 0b00001111); // Send Control (control, value, channel)
            }
            break;
          }
          else { // ..................................................................................
              if (rightnewPos > 100 ) { rightnewPos = 100; rightEnc.write(rightnewPos * 4); }
              bpm = (int)bpm + rightnewPos/100;
            break;
          }
          
        case 1: // Scanner
          if ( ProgMode == false ) { //---------------------------------------------------------------
            if (ScanSelected > 0) {
              switch(leftnewPos) {
                case 0: ScanPan = rightnewPos;    tft.setTextColor(TFT_Yellow,TFT_Black); TFT_Focus(     0, ScanSelected-1, rightnewPos); bitSet(FixtureActiv,0); break;
                case 1: ScanTilt = rightnewPos;   tft.setTextColor(TFT_Yellow,TFT_Black); TFT_Focus(     1, ScanSelected-1, rightnewPos); bitSet(FixtureActiv,1); break;
                case 2: ScanColor = rightnewPos;                                          TFT_ColorWheel(2, ScanSelected-1, rightnewPos); bitSet(FixtureActiv,2); break;
                case 3: ScanStrobe = rightnewPos; tft.setTextColor(TFT_Yellow,TFT_Black); TFT_Strobe(    3, ScanSelected-1, rightnewPos); bitSet(FixtureActiv,3); break;
                case 4: ScanGobo = rightnewPos;   tft.setTextColor(TFT_Yellow,TFT_Black); TFT_GoboWheel( 4, ScanSelected-1, rightnewPos); bitSet(FixtureActiv,4); break;
                case 5: ScanRotate = rightnewPos;                                         TFT_GoboRotate(5, ScanSelected-1, rightnewPos); bitSet(FixtureActiv,5); break;
                case 6: ScanPrisma = rightnewPos;                                         TFT_Prisma(    6, ScanSelected-1, rightnewPos); bitSet(FixtureActiv,6); break;
                case 7: ScanFocus = rightnewPos;  tft.setTextColor(TFT_Yellow,TFT_Black); TFT_Focus(     7, ScanSelected-1, rightnewPos); bitSet(FixtureActiv,7); break;
              }
              ScanActivFixture[64+ScanSelected-1] = FixtureActiv; drawFixtureSelected(ScanSelected, leftnewPos);
              ScanActivFixture[leftnewPos+(ScanSelected-1)*8] = rightnewPos;
              DMXset(SCANNER_BASE_ADR+(ScanSelected-1)*8+leftnewPos, rightnewPos);
            }
            else {
              if (rightnewPos > 127 ) { rightnewPos = 127; rightEnc.write(rightnewPos * 4); }
              ScanMotion = rightnewPos;
              if ( bitRead(ScanActiv,0) == 1 ) { ScanAngle[0] = rightnewPos; ScanMove[0] = rightLCDView; }
              if ( bitRead(ScanActiv,1) == 1 ) { ScanAngle[1] = rightnewPos; ScanMove[1] = rightLCDView; }
              if ( bitRead(ScanActiv,2) == 1 ) { ScanAngle[2] = rightnewPos; ScanMove[2] = rightLCDView; }
              if ( bitRead(ScanActiv,3) == 1 ) { ScanAngle[3] = rightnewPos; ScanMove[3] = rightLCDView; }
              if ( bitRead(ScanActiv,4) == 1 ) { ScanAngle[4] = rightnewPos; ScanMove[4] = rightLCDView; }
              if ( bitRead(ScanActiv,5) == 1 ) { ScanAngle[5] = rightnewPos; ScanMove[5] = rightLCDView; }
              if ( bitRead(ScanActiv,6) == 1 ) { ScanAngle[6] = rightnewPos; ScanMove[6] = rightLCDView; }
              if ( bitRead(ScanActiv,7) == 1 ) { ScanAngle[7] = rightnewPos; ScanMove[7] = rightLCDView; }
            }
            break;
          }
          else { // Scanner programming mode .........................................................
            if      (rightLCDView == 0 ) { ScanTilt   = rightnewPos; SetScannerFixture(ScanActiv, 1, ScanTilt,   SCANNER_BASE_ADR); }
            else if (rightLCDView == 1 ) { ScanStrobe = rightnewPos; SetScannerFixture(ScanActiv, 3, ScanStrobe, SCANNER_BASE_ADR); }
            else if (rightLCDView == 2 ) { ScanRotate = rightnewPos; SetScannerFixture(ScanActiv, 5, ScanRotate, SCANNER_BASE_ADR); }
            else if (rightLCDView == 3 ) { ScanFocus  = rightnewPos; SetScannerFixture(ScanActiv, 7, ScanFocus,  SCANNER_BASE_ADR); }
            else if (rightLCDView == 4 && shift == false ) { 
              if (rightnewPos > 127 ) { rightnewPos = 127; rightEnc.write(rightnewPos * 4); }
              ScanMotion = rightnewPos; 
            }
            else if (rightLCDView == 4 && shift == true ) {
              ScanSpdMove = ScanSpdMove + ((rightnewPos-rightPos)<<5);
              rightnewPos = rightPos;
              rightEnc.write(rightnewPos * 4);
            }
            if ( bitRead(FixtureActiv, rightLCDView*2+1) == 0 && shift == false ) { 
              bitSet(FixtureActiv, rightLCDView*2+1);
              pixels.setPixelColor(21+rightLCDView*6,pixels.Color(0,2+NeoPixelBright,0));
              pixels.show();
            }
            preFixtureActiv = setTFTfixture(FixtureActiv, leftLCDView, rightLCDView, preFixtureActiv, ScanSpdMove);
            break;
          }
        case 2: // COB
          if (rightLCDView == 0 ) { DMXPattern = rightnewPos; }
          else if (rightLCDView == 1 ) { 
            if (shift == false) {
              if (rightnewPos < rightPos ) { rightnewPos = rightnewPos - 4 ; rightEnc.write(rightnewPos * 4 + 3); } // needs to be checked
              if (rightnewPos > rightPos ) { rightnewPos = rightnewPos + 4 ; rightEnc.write(rightnewPos * 4); }
            }
            DMXBright = rightnewPos; }
          else if (rightLCDView == 2 ) { leftEncRED = rightnewPos; }
          else if (rightLCDView == 3 ) { leftEncBlue = rightnewPos; }
          break;
      }
      tft.setTextColor(TFT_Yellow, TFT_Black);
      tft.setCursor(_tw-_ts*27, _tw-_th+_ts*2);
      tft.setFont(A18n);
      TFTnumber(rightnewPos);
    }
    
    if (MenuDepth < 2) { // exit sub-menue
      if ( RUN == false && rightLastEncoder - 2 == NeoPixelBrightEE ) {
        for (int i = 0; i < 15; i++) pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // clear neopixel ring
        pixels.setPixelColor(15, pixels.Color(1, 1, 0)); // top LED orientation
        pixels.show();
      }
    }
    
    if ( rightnewPos > 254 || rightnewPos < 1 || MenuDepth > 0 ) { rightEnc.write(rightnewPos * 4); }
    rightPos = rightnewPos;
  }
  
// Encoder Button ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
  current_ms_right = millis();
  
  if (digitalRead(rightENC_BTN) == HIGH)
  {
    if (rightEncPressed == false) { // pressed right encoder button
      Serial.print("right Enc pressed ");
      Serial.print(rightEncPressed);
      Serial.print("  millis ");
      Serial.print(current_ms_right - previous_ms_right);
      Serial.print("   UnitsView ");
      Serial.print(UnitsView);
      Serial.print("   ProgMode ");
      Serial.print(ProgMode);
      Serial.print("   rightLCDView ");
      Serial.print(rightLCDView);
      Serial.print("   Shift ");
      Serial.print(shift);
      Serial.print("   rightnewPos ");
      Serial.println(rightnewPos);      
    }
    rightEncPressed = true;
    
    if (current_ms_right - previous_ms_right >= 600 && current_ms_right - previous_ms_right < 650 ) // -> enter edit mode (>600ms)
    {
      if (MenuDepth == 0) // enter menu
      {
        MenuDepth = 1;
        rightLastEncoder = EEPROM.read(rightEncoderStartEE);
        rightEnc.write(rightLastEncoder * 4);
        rightTFT_MenuSelect(rightLastEncoder);
      }
      else // exit menu (>600ms)
      {
        for (int i = 0; i < 16; i++) pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // clear neopixel
        ClockCounter();
  
        if (MenuDepth == 2) { // red LED on, save value
          if(rightLastEncoder - 2 == DMXUnitsEE) {
            EEPROM.write(DMXUnitsEE, DMXUnits);
            EEPROM.write(DMXBaseEE, DMXBase);
          }
          else EEPROM.write(rightLastEncoder - 2, rightnewPos);
          delay(10);
  
          if (rightLastEncoder + 8 != CountLenghtEE) {
            EEPROM.write(rightLastEncoder + 8, leftnewPos);
            delay(10);
          }
        }
        MenuDepth = 0;
        LCD_bck_Color = LCD_Color(LCDBackColor);
        tft.fillRect(_clx, _cly, _clw, _clw-_cly, TFT_Black); // clear
        EEPROM.write(rightEncoderStartEE, rightLastEncoder);
        delay(10);
        TFT_Draw_Count();
      }
    }    
  }
  
  else
  {
    if (rightEncPressed == true) { // released right encoder button (<500ms)
      Serial.print("right Enc released ");
      Serial.print(rightEncPressed);
      Serial.print("  millis ");
      Serial.println(current_ms_right - previous_ms_right);
    }

    if (rightEncPressed == true && current_ms_right - previous_ms_right < 500) { 
      if (shift == true) { ProgMode = !ProgMode; }
      
      if (MenuDepth > 0) // Edit mode on (green LED on)
      {
        bitSet(rightLCDView, 5);

        if (MenuDepth == 1) // enter 2nd level menu
        {
          MenuDepth = 2;
          rightLastEncoder = rightnewPos;
          tft.fillRect(_tx, _ty, _tw, _th, TFT_Red); // titel
          tft.setFont();
          tft.setTextSize(_ts);
          tft.setCursor((_tw - strlen(rightTFT_LongMenu[rightLastEncoder - 2]) * 6 * _ts) / 2, _tty);
          tft.setTextColor(TFT_Yellow);
          tft.println(rightTFT_LongMenu[rightLastEncoder - 2]); //
          int i = EEPROM.read(rightLastEncoder - 2);
          rightEnc.write(i * 4);
          rightPos = i;
          int j = EEPROM.read(rightLastEncoder + 8);
          leftEnc.write(j * 4);
          leftPos = j;
        }
    
        else if (MenuDepth == 2) // exit 2nd level menue
        {
          MenuDepth = 1;
          if(rightLastEncoder - 2 == DMXUnitsEE) {
            EEPROM.write(DMXUnitsEE, DMXUnits);
            EEPROM.write(DMXBaseEE, DMXBase);
          }
          else EEPROM.write(rightLastEncoder - 2, rightnewPos);
          delay(10);
    
          if (rightLastEncoder + 8 != CountLenghtEE) {
            EEPROM.write(rightLastEncoder + 8, leftnewPos);
            delay(10);
          }
    
          rightEnc.write(rightLastEncoder * 4); // write back last menu point
          rightTFT_MenuSelect(rightLastEncoder);
        }
  
        else if (MenuDepth == 10) // 2nd level left menue, every push increase counter
        {
          switch (leftLastEncoder + 8) { // sub menue of left encoder
            case CountLenghtEE: // Beat count length
              if ( bitRead(MIDIChannel, 7) == 0 ) bitSet(MIDIChannel, 7); else bitClear(MIDIChannel, 7);
              if (shift == true) { // 2nd level left menue, every push increase counter with shift pressed
                rightPos++;
                rightEnc.write((rightPos) * 4);
              }
              break;
          }
        }
      }
      
      else if (MenuDepth == 0 ) { // no menue selected
        if ( shift == false ) { rightLCDView++; } // toggle through active units view
      }
    }
    if ( rightEncPressed == true ) { EncButtonTFT(); }
    rightEncPressed = false;
    previous_ms_right = current_ms_right;
  }

/// Encoder Right ##########################################################################
