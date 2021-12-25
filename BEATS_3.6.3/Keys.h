// Keypad ################################################################

  SCANNER_BASE_ADR = DMXBase + (DMXUnits & 0b00000011) * 30 ;

  if (shift == true) { keypad_shift = 16; } else { keypad_shift = 0; }

  // Fills keypad.key[ ] array with up-to 10 active keys.
  // Returns true if there are ANY active keys.
  if (keypad.getKeys())
  {
    for (int i=0; i < LIST_MAX; i++)   // Scan the whole key list.
    {
      if ( keypad.key[i].stateChanged )   // Only find keys that have changed state.
      {
        if(shift == true && isAlpha(keypad.key[i].kchar)) keypad_shift = 4;
        
        if(isAlpha(keypad.key[i].kchar)) { // left and right column
          switch (keypad.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
            
            case PRESSED:
              
              if (keypad.key[i].kchar == 115 || keypad.key[i].kchar == 83) { shift = true; }
              
              if (key_ana[i] == 0) key_ana[i] = 127; else key_ana[i] = 0; // toggle
              
              if ( UnitsView == 0 ) {
//              usbMIDI.sendControlChange(keypad.key[i].kchar + MIDIBaseAdr - 1 + keypad_shift, 127, MIDIChannel & 0b00001111); // Send CC (control, value, channel)
//              MIDI.sendControlChange(keypad.key[i].kchar + MIDIBaseAdr - 1 + keypad_shift, 127, MIDIChannel & 0b00001111); // Send CC (control, value, channel)
                usbMIDI.sendNoteOn(keypad.key[i].kchar + MIDIBaseAdr - 1 + keypad_shift, 127, MIDIChannel & 0b00001111); // Send Note (pitch, velocity, channel)
//                MIDI.sendNoteOn(keypad.key[i].kchar + MIDIBaseAdr - 1 + keypad_shift, 127, MIDIChannel & 0b00001111); // Send Note (pitch, velocity, channel)
              }
              if ( UnitsView == 1 ) {
                if (ProgMode == false) { // switch scanner active ----------------------------------------
                  switch(keypad.key[i].kchar + keypad_shift) {
                    case 65: // A
                      if(bitRead(ScanActiv,0)==0) {
                        bitSet(ScanActiv,0);
                        lastScanActivPressed = 0;
                        pixels.setPixelColor(16,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,0);
                        pixels.setPixelColor(16,pixels.Color(0,0,1)); }
                      break;
                    case 66: // B
                      if(bitRead(ScanActiv,2)==0) {
                        bitSet(ScanActiv,2);
                        lastScanActivPressed = 2;
                        pixels.setPixelColor(22,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,2);
                        pixels.setPixelColor(22,pixels.Color(0,0,1)); }
                      break;
                    case 67: // C
                      if(bitRead(ScanActiv,4)==0) {
                        bitSet(ScanActiv,4);
                        lastScanActivPressed = 4;
                        pixels.setPixelColor(28,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,4);
                        pixels.setPixelColor(28,pixels.Color(0,0,1)); }
                      break;
                    case 68: // D
                      if(bitRead(ScanActiv,6)==0) {
                        bitSet(ScanActiv,6);
                        lastScanActivPressed = 6;
                        pixels.setPixelColor(34,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,6);
                        pixels.setPixelColor(34,pixels.Color(0,0,1)); }
                      break;
    
                    case 97: // a
                      if(bitRead(ScanActiv,1)==0) {
                        bitSet(ScanActiv,1);
                        lastScanActivPressed = 1;
                        pixels.setPixelColor(21,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,1);
                        pixels.setPixelColor(21,pixels.Color(0,0,1)); }
                      pixels.show();
                      break;
                    case 98: // b
                      if(bitRead(ScanActiv,3)==0) {
                        bitSet(ScanActiv,3);
                        lastScanActivPressed = 3;
                        pixels.setPixelColor(27,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,3);
                        pixels.setPixelColor(27,pixels.Color(0,0,1)); }
                      break;
                    case 99: // c
                      if(bitRead(ScanActiv,5)==0) {
                        bitSet(ScanActiv,5);
                        lastScanActivPressed = 5;
                        pixels.setPixelColor(33,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,5);
                        pixels.setPixelColor(33,pixels.Color(0,0,1)); }
                      break;
                    case 100: // d
                      if(bitRead(ScanActiv,7)==0) {
                        bitSet(ScanActiv,7);
                        lastScanActivPressed = 7;
                        pixels.setPixelColor(39,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,7);
                        pixels.setPixelColor(39,pixels.Color(0,0,1)); }
                      break;
                  }
                  setTFTscanner(ScanActiv, rightLCDView, leftLCDView, ScanActivFixture);
                  setpixelsscanner(ScanActiv, NeoPixelBright);
                }
                else { // prog mode, switch fixture ......................................................
                  switch(keypad.key[i].kchar + keypad_shift) {
                    case 65: // A
                      if(bitRead(FixtureActiv,0)==0) {
                        bitSet(FixtureActiv,0);
                        pixels.setPixelColor(16,pixels.Color(0,2+NeoPixelBright,0)); }
                      else {
                        bitClear(FixtureActiv,0);
                        pixels.setPixelColor(16,pixels.Color(0,0,1)); }
                      break;
                    case 66: // B
                      if(bitRead(FixtureActiv,2)==0) {
                        bitSet(FixtureActiv,2);
                        pixels.setPixelColor(22,pixels.Color(0,2+NeoPixelBright,0)); }
                      else {
                        bitClear(FixtureActiv,2);
                        pixels.setPixelColor(22,pixels.Color(0,0,1)); }
                      break;
                    case 67: // C
                      if(bitRead(FixtureActiv,4)==0) {
                        bitSet(FixtureActiv,4);
                        pixels.setPixelColor(28,pixels.Color(0,2+NeoPixelBright,0)); }
                      else {
                        bitClear(FixtureActiv,4);
                        pixels.setPixelColor(28,pixels.Color(0,0,1)); }
                      break;
                    case 68: // D
                      if(bitRead(FixtureActiv,6)==0) {
                        bitSet(FixtureActiv,6);
                        pixels.setPixelColor(34,pixels.Color(0,2+NeoPixelBright,0)); }
                      else {
                        bitClear(FixtureActiv,6);
                        pixels.setPixelColor(34,pixels.Color(0,0,1)); }
                      break;
    
                    case 97: // a
                      if(bitRead(FixtureActiv,1)==0) {
                        bitSet(FixtureActiv,1);
                        pixels.setPixelColor(21,pixels.Color(0,2+NeoPixelBright,0)); }
                      else {
                        bitClear(FixtureActiv,1);
                        pixels.setPixelColor(21,pixels.Color(0,0,1)); }
                      break;
                    case 98: // b
                      if(bitRead(FixtureActiv,3)==0) {
                        bitSet(FixtureActiv,3);
                        pixels.setPixelColor(27,pixels.Color(0,2+NeoPixelBright,0)); }
                      else {
                        bitClear(FixtureActiv,3);
                        pixels.setPixelColor(27,pixels.Color(0,0,1)); }
                      break;
                    case 99: // c
                      if(bitRead(FixtureActiv,5)==0) {
                        bitSet(FixtureActiv,5);
                        pixels.setPixelColor(33,pixels.Color(0,2+NeoPixelBright,0)); }
                      else {
                        bitClear(FixtureActiv,5);
                        pixels.setPixelColor(33,pixels.Color(0,0,1)); }
                      break;
                    case 100: // d
                      if(bitRead(FixtureActiv,7)==0) {
                        bitSet(FixtureActiv,7);
                        pixels.setPixelColor(39,pixels.Color(0,2+NeoPixelBright,0)); }
                      else {
                        bitClear(FixtureActiv,7);
                        pixels.setPixelColor(39,pixels.Color(0,0,1)); }
                      break;
// Shift
                    case 69: // E
                      if(bitRead(ScanActiv,0)==0) {
                        bitSet(ScanActiv,0);
                        pixels.setPixelColor(16,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,0);
                        pixels.setPixelColor(16,pixels.Color(0,0,1)); }
                      break;
                    case 70: // F
                      if(bitRead(ScanActiv,2)==0) {
                        bitSet(ScanActiv,2);
                        pixels.setPixelColor(22,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,2);
                        pixels.setPixelColor(22,pixels.Color(0,0,1)); }
                      break;
                    case 71: // G
                      if(bitRead(ScanActiv,4)==0) {
                        bitSet(ScanActiv,4);
                        pixels.setPixelColor(28,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,4);
                        pixels.setPixelColor(28,pixels.Color(0,0,1)); }
                      break;
                    case 72: // H
                      if(bitRead(ScanActiv,6)==0) {
                        bitSet(ScanActiv,6);
                        pixels.setPixelColor(34,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,6);
                        pixels.setPixelColor(34,pixels.Color(0,0,1)); }
                      break;

                    case 101: // e
                      if(bitRead(ScanActiv,1)==0) {
                        bitSet(ScanActiv,1);
                        pixels.setPixelColor(21,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,1);
                        pixels.setPixelColor(21,pixels.Color(0,0,1)); }
                      break;
                    case 102: // f
                      if(bitRead(ScanActiv,3)==0) {
                        bitSet(ScanActiv,3);
                        pixels.setPixelColor(27,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,3);
                        pixels.setPixelColor(27,pixels.Color(0,0,1)); }
                      break;
                    case 103: // g
                      if(bitRead(ScanActiv,5)==0) {
                        bitSet(ScanActiv,5);
                        pixels.setPixelColor(33,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,5);
                        pixels.setPixelColor(33,pixels.Color(0,0,1)); }
                      break;
                    case 104: // h
                      if(bitRead(ScanActiv,7)==0) {
                        bitSet(ScanActiv,7);
                        pixels.setPixelColor(39,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); }
                      else {
                        bitClear(ScanActiv,7);
                        pixels.setPixelColor(39,pixels.Color(0,0,1)); }
                      break;
                  }
                  if (shift == true)  { preScanActiv = setTFTProgMode(ScanActiv, leftLCDView, rightLCDView, preScanActiv); }
                  else { preFixtureActiv = setTFTfixture(FixtureActiv, leftLCDView, rightLCDView, preFixtureActiv, ScanSpdMove); }           
                  setpixelsfixture(FixtureActiv, NeoPixelBright);
                }
                setpixels4x4red();
                pixels.show();
              }
              
              kbd_msg = "PRESSED";
              break;
        
            case HOLD:
              if ( UnitsView == 1 ) {
                if (ProgMode == false) { // switch scanner active ----------------------------------------
                  leftnewPos = 0; leftEnc.write(leftnewPos * 4);
                  tft.setFont();
                  tft.setTextSize(_ts);
                  tft.setTextColor(TFT_LightGray, TFT_Black);
                  tft.setCursor(_tw-_ts*36, _tw-_th*2+_ts*3);
                  
                  if (shift == false) { tft.print(" Pan  "); } // blind out shift
                  switch(keypad.key[i].kchar + keypad_shift) {
                    case 65: // A
                      bitSet(ScanActiv,0); ScanSelected = 1;
                      lastScanActivPressed = 0;
                      rightnewPos = ScanActivFixture[0*8]; rightEnc.write(rightnewPos * 4);
                      pixels.setPixelColor(16,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 0));
                      break;
                    case 66: // B
                      bitSet(ScanActiv,2); ScanSelected = 3;
                      lastScanActivPressed = 2;
                      rightnewPos = ScanActivFixture[2*8]; rightEnc.write(rightnewPos * 4);
                      pixels.setPixelColor(22,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 0));
                      break;
                    case 67: // C
                      bitSet(ScanActiv,4); ScanSelected = 5;
                      lastScanActivPressed = 4;
                      rightnewPos = ScanActivFixture[4*8]; rightEnc.write(rightnewPos * 4);
                      pixels.setPixelColor(28,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 0));
                      break;
                    case 68: // D
                      bitSet(ScanActiv,6); ScanSelected = 7;
                      lastScanActivPressed = 6;
                      rightnewPos = ScanActivFixture[6*8]; rightEnc.write(rightnewPos * 4);
                      pixels.setPixelColor(34,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 0));
                      break;
    
                    case 97: // a
                      bitSet(ScanActiv,1); ScanSelected = 2;
                      lastScanActivPressed = 1;
                      rightnewPos = ScanActivFixture[1*8]; rightEnc.write(rightnewPos * 4);
                      pixels.setPixelColor(21,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 0));
                      break;
                    case 98: // b
                      bitSet(ScanActiv,3); ScanSelected = 4;
                      lastScanActivPressed = 3;
                      rightnewPos = ScanActivFixture[3*8]; rightEnc.write(rightnewPos * 4);
                      pixels.setPixelColor(27,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 0));
                      break;
                    case 99: // c
                      bitSet(ScanActiv,5); ScanSelected = 6;
                      lastScanActivPressed = 5;
                      rightnewPos = ScanActivFixture[5*8]; rightEnc.write(rightnewPos * 4);
                      pixels.setPixelColor(33,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 0));
                      break;
                    case 100: // d
                      bitSet(ScanActiv,7); ScanSelected = 8;
                      lastScanActivPressed = 7;
                      rightnewPos = ScanActivFixture[7*8]; rightEnc.write(rightnewPos * 4);
                      pixels.setPixelColor(39,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 0));
                      break;
                  }
                  setTFTscanner(ScanActiv, rightLCDView, leftLCDView, ScanActivFixture);
                  drawFixtureSelected(ScanSelected, leftnewPos);
                  setpixelsscanner(ScanActiv, NeoPixelBright);
                  setpixels4x4red();
                  pixels.show();
                }
              }
              
              kbd_msg = "HOLD";
              break;
        
            case RELEASED:
              if (keypad.key[i].kchar == 115 || keypad.key[i].kchar == 83) { shift = false; }

              if ( UnitsView == 0 ) {
//              usbMIDI.sendControlChange(keypad.key[i].kchar + MIDIBaseAdr - 1 + keypad_shift, 0, MIDIChannel & 0b00001111); // Send CC (control, value, channel)
//              MIDI.sendControlChange(keypad.key[i].kchar + MIDIBaseAdr - 1 + keypad_shift, 0, MIDIChannel & 0b00001111); // Send CC (control, value, channel)
                usbMIDI.sendNoteOff(keypad.key[i].kchar + MIDIBaseAdr - 1 + keypad_shift, 0, MIDIChannel & 0b00001111); // Stop note (pitch, velocity, channel)
//                MIDI.sendNoteOff(keypad.key[i].kchar + MIDIBaseAdr - 1 + keypad_shift, 0, MIDIChannel & 0b00001111); // Stop note (pitch, velocity, channel)
              }
              else if ( UnitsView == 1 && ProgMode == false && kbd_msg == "HOLD" && ScanSelected > 0 ) {
                drawFixtures(ScanActiv, ScanActivFixture);
                setTFTscanner(ScanActiv, rightLCDView, leftLCDView, ScanActivFixture);
                
                tft.setFont();
                tft.setTextSize(_ts);        
                tft.setTextColor(TFT_LightGray, TFT_Black);
                tft.setCursor(_tw-_ts*36, _tw-_th*2+_ts*3);
                rightEnc.write(ScanMotion * 4);
                rightPos = ScanMotion;
                if      (rightLCDView == 0 ) { tft.print("LftRgt"); }
                else if (rightLCDView == 1 ) { tft.print("UpDown"); }
                else if (rightLCDView == 2 ) { tft.print("CircRt"); }
                else if (rightLCDView == 3 ) { tft.print("CircLt"); }
                else if (rightLCDView == 4 ) { tft.print("Swing "); }
                else if (rightLCDView == 5 ) { tft.print(" Wave "); }
                else if (rightLCDView == 6 ) { tft.print("DiagLu"); }
                else if (rightLCDView == 7 ) { tft.print("DiagRu"); }
                
                tft.setTextColor(TFT_Yellow, TFT_Black);
                tft.setCursor(_tw-_ts*27, _tw-_th+_ts*2);
                tft.setFont(A18n);
                TFTnumber(ScanMotion);
              }

              if ( kbd_msg == "HOLD") { // EEprom save here

              }

              ScanSelected = 0;
              kbd_msg = "RELEASED";
              break;

            case IDLE:
              kbd_msg = "IDLE";
          }
        }
        else // keys 4x4
        {
          switch (keypad.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
            
            case PRESSED:
              FSR_low = analogRead(A8);
              key_ana[i] = FSR_low;
              if ( UnitsView == 0 ) {
                usbMIDI.sendNoteOn(keypad.key[i].kchar + MIDIBaseAdr - 1 + keypad_shift, 127, MIDIChannel & 0b00001111); // Send Note (pitch, velocity, channel)
//                MIDI.sendNoteOn(keypad.key[i].kchar + MIDIBaseAdr - 1 + keypad_shift, 127, MIDIChannel & 0b00001111); // Send Note (pitch, velocity, channel)
              }
              if ( UnitsView == 1 ) {
                if (ProgMode == false) { // read scanner fixture -----------------------------------------
                  setpixels4x4red();
                  switch(keypad.key[i].kchar + keypad_shift) {
                    case 1:  pixels.setPixelColor(35,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 2:  pixels.setPixelColor(36,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 3:  pixels.setPixelColor(37,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 4:  pixels.setPixelColor(38,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 5:  pixels.setPixelColor(29,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 6:  pixels.setPixelColor(30,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 7:  pixels.setPixelColor(31,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 8:  pixels.setPixelColor(32,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 9:  pixels.setPixelColor(23,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 10: pixels.setPixelColor(24,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 11: pixels.setPixelColor(25,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 12: pixels.setPixelColor(26,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 13: pixels.setPixelColor(17,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 14: pixels.setPixelColor(18,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 15: pixels.setPixelColor(19,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 16: pixels.setPixelColor(20,pixels.Color(0, 2+NeoPixelBright, 0)); break;
                    case 17: pixels.setPixelColor(35,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 18: pixels.setPixelColor(36,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 19: pixels.setPixelColor(37,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 20: pixels.setPixelColor(38,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 21: pixels.setPixelColor(29,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 22: pixels.setPixelColor(30,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 23: pixels.setPixelColor(31,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 24: pixels.setPixelColor(32,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 25: pixels.setPixelColor(23,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 26: pixels.setPixelColor(24,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 27: pixels.setPixelColor(25,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 28: pixels.setPixelColor(26,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 29: pixels.setPixelColor(17,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 30: pixels.setPixelColor(18,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 31: pixels.setPixelColor(19,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 32: pixels.setPixelColor(20,pixels.Color(0, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                  }
                  // read fixtures
                  for (int s = 0; s < 8; s++ ) {
                    FixtureActiv = EEPROM.read(FixtureBaseEE + ( 8 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72));
                    if (bitRead(ScanActiv, s) == 1) { 
                      if (bitRead(FixtureActiv, 0) == 1) { ScanActivFixture[0+s*8] = EEPROM.read(FixtureBaseEE + ( 0 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72 )); 
                                                           DMXset(SCANNER_BASE_ADR+s*8+0, ScanActivFixture[0+s*8]); }
                      if (bitRead(FixtureActiv, 1) == 1) { ScanActivFixture[1+s*8] = EEPROM.read(FixtureBaseEE + ( 1 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72 ));
                                                           DMXset(SCANNER_BASE_ADR+s*8+1, ScanActivFixture[1+s*8]); }
                      if (bitRead(FixtureActiv, 2) == 1) { ScanActivFixture[2+s*8] = EEPROM.read(FixtureBaseEE + ( 2 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72 ));
                                                           DMXset(SCANNER_BASE_ADR+s*8+2, ScanActivFixture[2+s*8]); }
                      if (bitRead(FixtureActiv, 3) == 1) { ScanActivFixture[3+s*8] = EEPROM.read(FixtureBaseEE + ( 3 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72 ));
                                                           DMXset(SCANNER_BASE_ADR+s*8+3, ScanActivFixture[3+s*8]); }
                      if (bitRead(FixtureActiv, 4) == 1) { ScanActivFixture[4+s*8] = EEPROM.read(FixtureBaseEE + ( 4 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72 ));
                                                           DMXset(SCANNER_BASE_ADR+s*8+4, ScanActivFixture[4+s*8]); }
                      if (bitRead(FixtureActiv, 5) == 1) { ScanActivFixture[5+s*8] = EEPROM.read(FixtureBaseEE + ( 5 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72 ));
                                                           DMXset(SCANNER_BASE_ADR+s*8+5, ScanActivFixture[5+s*8]); }
                      if (bitRead(FixtureActiv, 6) == 1) { ScanActivFixture[6+s*8] = EEPROM.read(FixtureBaseEE + ( 6 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72 ));
                                                           DMXset(SCANNER_BASE_ADR+s*8+6, ScanActivFixture[6+s*8]); }
                      if (bitRead(FixtureActiv, 7) == 1) { ScanActivFixture[7+s*8] = EEPROM.read(FixtureBaseEE + ( 7 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72 ));
                                                           DMXset(SCANNER_BASE_ADR+s*8+7, ScanActivFixture[7+s*8]); }
                                                           ScanActivFixture[64+s]  = EEPROM.read(FixtureBaseEE + ( 8 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72 ));
                    }
                  }
                }
                else { // write scanner fixture ..........................................................
                  setpixels4x4red();
                  switch(keypad.key[i].kchar + keypad_shift) {
                    case 1:  pixels.setPixelColor(35,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 2:  pixels.setPixelColor(36,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 3:  pixels.setPixelColor(37,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 4:  pixels.setPixelColor(38,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 5:  pixels.setPixelColor(29,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 6:  pixels.setPixelColor(30,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 7:  pixels.setPixelColor(31,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 8:  pixels.setPixelColor(32,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 9:  pixels.setPixelColor(23,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 10: pixels.setPixelColor(24,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 11: pixels.setPixelColor(25,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 12: pixels.setPixelColor(26,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 13: pixels.setPixelColor(17,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 14: pixels.setPixelColor(18,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 15: pixels.setPixelColor(19,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 16: pixels.setPixelColor(20,pixels.Color(2+NeoPixelBright, 0, 2+NeoPixelBright)); break;
                    case 17: pixels.setPixelColor(35,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 18: pixels.setPixelColor(36,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 19: pixels.setPixelColor(37,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 20: pixels.setPixelColor(38,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 21: pixels.setPixelColor(29,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 22: pixels.setPixelColor(30,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 23: pixels.setPixelColor(31,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 24: pixels.setPixelColor(32,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 25: pixels.setPixelColor(23,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 26: pixels.setPixelColor(24,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 27: pixels.setPixelColor(25,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 28: pixels.setPixelColor(26,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 29: pixels.setPixelColor(17,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 30: pixels.setPixelColor(18,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 31: pixels.setPixelColor(19,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                    case 32: pixels.setPixelColor(20,pixels.Color(2+NeoPixelBright, 2+NeoPixelBright, 2+NeoPixelBright)); break;
                  }
                  // write fixtures
                  for (int s = 0; s < 8; s++ ) {
                    if (bitRead(ScanActiv, s) == 1) {
                      if(bitRead(FixtureActiv, 0) == 1 ) { EEPROM.write(FixtureBaseEE + ( 0 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72), ScanPan); delay(5); }
                      if(bitRead(FixtureActiv, 1) == 1 ) { EEPROM.write(FixtureBaseEE + ( 1 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72), ScanTilt); delay(5); }
                      if(bitRead(FixtureActiv, 2) == 1 ) { EEPROM.write(FixtureBaseEE + ( 2 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72), ScanColor); delay(5); }
                      if(bitRead(FixtureActiv, 3) == 1 ) { EEPROM.write(FixtureBaseEE + ( 3 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72), ScanStrobe); delay(5); }
                      if(bitRead(FixtureActiv, 4) == 1 ) { EEPROM.write(FixtureBaseEE + ( 4 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72), ScanGobo); delay(5); }
                      if(bitRead(FixtureActiv, 5) == 1 ) { EEPROM.write(FixtureBaseEE + ( 5 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72), ScanRotate); delay(5); }
                      if(bitRead(FixtureActiv, 6) == 1 ) { EEPROM.write(FixtureBaseEE + ( 6 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72), ScanPrisma); delay(5); }
                      if(bitRead(FixtureActiv, 7) == 1 ) { EEPROM.write(FixtureBaseEE + ( 7 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72), ScanFocus); delay(5); }
                                                           EEPROM.write(FixtureBaseEE + ( 8 + s*9 + (keypad.key[i].kchar + keypad_shift-1)*72), FixtureActiv); delay(5);
                    }
                  } 
                }
                pixels.show();
              }

              kbd_msg = "PRESSED";
              break;
        
            case HOLD:
              kbd_msg = "HOLD";
              break;
        
            case RELEASED:
              if ( UnitsView == 0 ) {
                usbMIDI.sendNoteOff(keypad.key[i].kchar + MIDIBaseAdr - 1 + keypad_shift, 0, MIDIChannel & 0b00001111); // Stop note (pitch, velocity, channel)
//                MIDI.sendNoteOff(keypad.key[i].kchar + MIDIBaseAdr - 1 + keypad_shift, 0, MIDIChannel & 0b00001111); // Stop note (pitch, velocity, channel)
              }
              else if ( UnitsView == 1 ) {
                if (ProgMode == false) { // Scanner
                  drawFixtures(ScanActiv, ScanActivFixture);
                  setTFTscanner(ScanActiv, rightLCDView, leftLCDView, ScanActivFixture);
                }
              }
              
              kbd_msg = "RELEASED";
              break;
            
            case IDLE:
              kbd_msg = "IDLE";
          }        
        }
        Serial.print(kbd_msg);
        Serial.print("  Key ");
        Serial.println(keypad.key[i].kchar + keypad_shift, DEC);
      }
    }
  }



/// Keypad ################################################################
