// Encoder Left #################################################################################

  leftnewPos = leftEnc.read() / 4;
  if (leftnewPos != leftPos || bitRead(leftLCDView, 5) == 1)
  {
    bitClear(leftLCDView, 5);

    if (MenuDepth == 2 || MenuDepth == 10 ) { // sub menues
      if (shift == true) {
        if (leftnewPos < leftPos) { leftnewPos = leftnewPos -9; leftEnc.write(leftnewPos * 4); }
        if (leftnewPos > leftPos) { leftnewPos = leftnewPos +9; leftEnc.write(leftnewPos * 4); } }
        if (leftnewPos < 1 ) { leftnewPos = 0; leftEnc.write(leftnewPos * 4); }
        if (leftnewPos > 254 ) { leftnewPos = 255; leftEnc.write(leftnewPos * 4); }
    }
      
    if (MenuDepth%2 == 1) { // main menue
      bitSet(MenuDepth, 3); // left menu on
      if (leftnewPos > leftTFT_MenuLines + 1) {
        leftnewPos = 2; leftEnc.write(leftnewPos * 4);
      }
      if (leftnewPos < 2) {
        leftnewPos = leftTFT_MenuLines + 1; leftEnc.write(leftnewPos * 4);
      }
      EncButtonTFT(); // update Encoder LED's
      leftTFT_MenuSelect(leftnewPos);
    }
    
    else if (MenuDepth == 2) { // sub menue right encoder
      switch (rightLastEncoder+8) {
        if (leftnewPos < 1 ) { leftnewPos = 0; leftEnc.write(leftnewPos * 4); }
        if (leftnewPos > 254 ) { leftnewPos = 255; leftEnc.write(leftnewPos * 4); }
        case DMXPixbarEE: // DMX DMX pattern for 8x8 COB
          DMXPixbar = leftnewPos;
          TFT_2_MenuValue();
          break;
        case DMXBackBrightEE: // DMX back brightness
          if (leftnewPos < leftPos && shift == false) { leftnewPos = leftnewPos -4; leftEnc.write(leftnewPos * 4); }
          if (leftnewPos > leftPos && shift == false) { leftnewPos = leftnewPos +4; leftEnc.write(leftnewPos * 4); }           
          DMXBackBright = leftnewPos;
          TFT_2_MenuValue();
          break;
      }
      switch (rightLastEncoder-2) {
        case DMXUnitsEE: // DMX units selection
          tft.setTextSize(1);
          tft.setFont(A24n);
          tft.setTextColor(TFT_Gray, TFT_Black);
          if (rightnewPos == 1) { // Pixbar
            if (leftnewPos < 1 ) { leftnewPos = 3; leftEnc.write(leftnewPos * 4); }
            if (leftnewPos > 3 ) { leftnewPos = 1; leftEnc.write(leftnewPos * 4); }
            DMXUnits = (DMXUnits & 0b11111100) + leftnewPos-1;
            tft.setCursor(_i3-_ts*2, _c2);
            if ((DMXUnits & 0b00000011) == 0) tft.print("off     ");
            else {
              tft.setTextColor(TFT_Yellow, TFT_Black);
              tft.print(DMXUnits & 0b00000011);
              tft.print("   ");
              tft.setTextColor(TFT_Gray, TFT_Black);
              tft.print((DMXUnits & 0b00000011) * 30);
            }
          }
          if (rightnewPos == 2) { // Scanner
            if (bitRead(DMXUnits, 2) == 0) bitSet(DMXUnits, 2);
            else bitClear(DMXUnits, 2); // toggle
            tft.setCursor(_i3-_ts*2, _c3);

            if (bitRead(DMXUnits, 2) == 0) tft.print("off     ");
            else {
              tft.setTextColor(TFT_Yellow, TFT_Black);
              tft.print("on");
              tft.print(" ");
              tft.setTextColor(TFT_Gray, TFT_Black);
              tft.print("64");
            }
/*            
            if ((DMXUnits & 0b11100000) >> 5 == 0) tft.print("off     ");
            else {
              tft.setTextColor(TFT_Yellow, TFT_Black);
              tft.print((DMXUnits & 0b11100000) >> 5);
              tft.print(" ");
              tft.setTextColor(TFT_Gray, TFT_Black);
              tft.print(((DMXUnits & 0b11100000) >> 5) * 8);
            }            
*/            
          }
      
          if (rightnewPos == 3) { // 64 COB
            if (leftnewPos < 1 ) { leftnewPos = 3; leftEnc.write(leftnewPos * 4); }
            if (leftnewPos > 3 ) { leftnewPos = 1; leftEnc.write(leftnewPos * 4); }
            DMXUnits = (DMXUnits & 0b11100111) + ((leftnewPos-1)<<3);
            tft.setCursor(_i3-_ts*2, _c4);
            if ((DMXUnits & 0b00011000) >> 3 == 0) tft.print("off     ");
            else {
              tft.setTextColor(TFT_Yellow, TFT_Black);
              tft.print((DMXUnits & 0b00011000) >> 3);
              tft.print(" ");
              tft.setTextColor(TFT_Gray, TFT_Black);
              tft.print(((DMXUnits & 0b00011000) >> 3) * 192);
            }            
          }
          
          if(DMXUnits > 0) {
            tft.setTextColor(TFT_Gray, TFT_Black);
            tft.setCursor(_cy+_ts*3, _c5);
            if (rightnewPos == 4) {
              tft.setTextColor(TFT_White, TFT_Black);
              if (leftnewPos < 1 ) { leftnewPos = 0; leftEnc.write(leftnewPos * 4); }
              if (leftnewPos > 254 ) { leftnewPos = 255; leftEnc.write(leftnewPos * 4); }
              DMXBase = leftnewPos;
            }
            tft.print("Adr. ");
            tft.setTextColor(TFT_Yellow, TFT_Black);
            tft.print(DMXBase);
            tft.setTextColor(TFT_Gray, TFT_Black);
            tft.print(" - ");
            if(DMXBase + (DMXUnits & 0b00000011) * 30 + ((DMXUnits & 0b00000100) >> 2) * 64 + ((DMXUnits & 0b00011000) >> 3) * 192 > 512) {
              tft.setTextColor(TFT_Red,TFT_Black); }
            tft.print(DMXBase + (DMXUnits & 0b00000011) * 30 + ((DMXUnits & 0b00000100) >> 2) * 64 + ((DMXUnits & 0b00011000) >> 3) * 192);
            tft.print("      ");
          }

          break;
        
      }
    }
    
    
    else if (MenuDepth == 10) { // sub menue left encoder

      switch (leftLastEncoder+18) {  //
        
        case BeatStartEE: // beats-1, 256=255, 128=127, 64=63, 32=31, 16=15
          if (leftnewPos < 1 ) { leftnewPos = 0; leftEnc.write(leftnewPos * 4); }
          if (leftnewPos > 254 ) { leftnewPos = 255; leftEnc.write(leftnewPos * 4); }
          BeatStart = leftnewPos;
          left_str = "Start";
          left_half_bound = _ts*11 ;
          right_str = "Length";
          right_half_bound = _ts*6 ;
          rightnewPos++;
          TFT_2_MenuValue();
          rightnewPos--;
          tft.setFont(A24n);
          tft.setTextColor(TFT_Cyan);        
          if(bitRead(MIDIChannel, 7)==0) {
            tft.setCursor(_tw/2+_ts*6, _c1+_ts);
            tft.print("Beats"); }
          else {
            tft.setCursor(_tw/2+_ts*12, _c1+_ts);
            tft.print("Bars"); }
          break;

        case MIDIChannelEE: // MIDI Channel
          if (leftnewPos < 1 ) { leftnewPos = 1; leftEnc.write(leftnewPos * 4); }
          if (leftnewPos > 16 ) { leftnewPos = 16; leftEnc.write(leftnewPos * 4); }
          MIDIChannel = (MIDIChannel & 0b11110000) + leftnewPos;
          TFT_MenuValue(leftnewPos);
          break;

        case MIDIBaseAdrEE: // MIDI Base Address
          if (leftnewPos < 1 ) { leftnewPos = 0; leftEnc.write(leftnewPos * 4); }
          if (leftnewPos > 131 ) { leftnewPos = 131; leftEnc.write(leftnewPos * 4); }
          MIDIBaseAdr = leftnewPos;
          tft.fillRect(_mx, _my, _tw, _mh, TFT_Black); // clear area
          tft.setFont(A60b);
          tft.setCursor(_ts*5, _ts*55);
          tft.setTextColor(TFT_Yellow, TFT_Black);

          pixels.setPixelColor(35,pixels.Color(20,20,0));
          pixels.show();

          switch(MIDIBaseAdr) {
            case 0:   tft.print(" C -2"); break;
            case 1:   tft.print(" C#-2"); break;
            case 2:   tft.print(" D -2"); break;
            case 3:   tft.print(" D#-2"); break;
            case 4:   tft.print(" E -2"); break;
            case 5:   tft.print(" F -2"); break;
            case 6:   tft.print(" F#-2"); break;
            case 7:   tft.print(" G -2"); break;
            case 8:   tft.print(" G#-2"); break;
            case 9:   tft.print(" A -2"); break;
            case 10:  tft.print(" A#-2"); break;
            case 11:  tft.print(" B -2"); break;
            case 12:  tft.print(" C -1"); break;
            case 13:  tft.print(" C#-1"); break;
            case 14:  tft.print(" D -1"); break;
            case 15:  tft.print(" D#-1"); break;
            case 16:  tft.print(" E -1"); break;
            case 17:  tft.print(" F -1"); break;
            case 18:  tft.print(" F#-1"); break;
            case 19:  tft.print(" G -1"); break;
            case 20:  tft.print(" G#-1"); break;
            case 21:  tft.print(" A -1"); break;
            case 22:  tft.print(" A#-1"); break;
            case 23:  tft.print(" B -1"); break;
            case 24:  tft.print(" C   "); break;
            case 25:  tft.print(" C#  "); break;
            case 26:  tft.print(" D   "); break;
            case 27:  tft.print(" D#  "); break;
            case 28:  tft.print(" E   "); break;
            case 29:  tft.print(" F   "); break;
            case 30:  tft.print(" F#  "); break;
            case 31:  tft.print(" G   "); break;
            case 32:  tft.print(" G#  "); break;
            case 33:  tft.print(" A   "); break;
            case 34:  tft.print(" A#  "); break;
            case 35:  tft.print(" B   "); break;
            case 36:  tft.setTextColor(TFT_White, TFT_Black); tft.print(" C +1"); break;
            case 37:  tft.print(" C#+1"); break;
            case 38:  tft.print(" D +1"); break;
            case 39:  tft.print(" D#+1"); break;
            case 40:  tft.print(" E +1"); break;
            case 41:  tft.print(" F +1"); break;
            case 42:  tft.print(" F#+1"); break;
            case 43:  tft.print(" G +1"); break;
            case 44:  tft.print(" G#+1"); break;
            case 45:  tft.print(" A +1"); break;
            case 46:  tft.print(" A#+1"); break;
            case 47:  tft.print(" B +1"); break;
            case 48:  tft.print(" C +2"); break;
            case 49:  tft.print(" C#+2"); break;
            case 50:  tft.print(" D +2"); break;
            case 51:  tft.print(" D#+2"); break;
            case 52:  tft.print(" E +2"); break;
            case 53:  tft.print(" F +2"); break;
            case 54:  tft.print(" F#+2"); break;
            case 55:  tft.print(" G +2"); break;
            case 56:  tft.print(" G#+2"); break;
            case 57:  tft.print(" A +2"); break;
            case 58:  tft.print(" A#+2"); break;
            case 59:  tft.print(" B +2"); break;
            case 60:  tft.print(" C +3"); break;
            case 61:  tft.print(" C#+3"); break;
            case 62:  tft.print(" D +3"); break;
            case 63:  tft.print(" D#+3"); break;
            case 64:  tft.print(" E +3"); break;
            case 65:  tft.print(" F +3"); break;
            case 66:  tft.print(" F#+3"); break;
            case 67:  tft.print(" G +3"); break;
            case 68:  tft.print(" G#+3"); break;
            case 69:  tft.print(" A +3"); break;
            case 70:  tft.print(" A#+3"); break;
            case 71:  tft.print(" B +3"); break;
            case 72:  tft.print(" C +4"); break;
            case 73:  tft.print(" C#+4"); break;
            case 74:  tft.print(" D +4"); break;
            case 75:  tft.print(" D#+4"); break;
            case 76:  tft.print(" E +4"); break;
            case 77:  tft.print(" F +4"); break;
            case 78:  tft.print(" F#+4"); break;
            case 79:  tft.print(" G +4"); break;
            case 80:  tft.print(" G#+4"); break;
            case 81:  tft.print(" A +4"); break;
            case 82:  tft.print(" A#+4"); break;
            case 83:  tft.print(" B +4"); break;
            case 84:  tft.print(" C +5"); break;
            case 85:  tft.print(" C#+5"); break;
            case 86:  tft.print(" D +5"); break;
            case 87:  tft.print(" D#+5"); break;
            case 88:  tft.print(" E +5"); break;
            case 89:  tft.print(" F +5"); break;
            case 90:  tft.print(" F#+5"); break;
            case 91:  tft.print(" G +5"); break;
            case 92:  tft.print(" G#+5"); break;
            case 93:  tft.print(" A +5"); break;
            case 94:  tft.print(" A#+5"); break;
            case 95:  tft.print(" B +5"); break;
            case 96:  tft.print(" C +6"); break;
            case 97:  tft.print(" C#+6"); break;
            case 98:  tft.print(" D +6"); break;
            case 99:  tft.print(" D#+6"); break;
            case 100: tft.print(" E +6"); break;
            case 101: tft.print(" F +6"); break;
            case 102: tft.print(" F#+6"); break;
            case 103: tft.print(" G +6"); break;
            case 104: tft.print(" G#+6"); break;
            case 105: tft.print(" A +6"); break;
            case 106: tft.print(" A#+6"); break;
            case 107: tft.print(" B +6"); break;
            case 108: tft.print(" C +7"); break;
            case 109: tft.print(" C#+7"); break;
            case 110: tft.print(" D +7"); break;
            case 111: tft.print(" D#+7"); break;
            case 112: tft.print(" E +7"); break;
            case 113: tft.print(" F +7"); break;
            case 114: tft.print(" F#+7"); break;
            case 115: tft.print(" G +7"); break;
            case 116: tft.print(" G#+7"); break;
            case 117: tft.print(" A +7"); break;
            case 118: tft.print(" A#+7"); break;
            case 119: tft.print(" B +7"); break;
            case 120: tft.print(" C +8"); break;
            case 121: tft.print(" C#+8"); break;
            case 122: tft.print(" D +8"); break;
            case 123: tft.print(" D#+8"); break;
            case 124: tft.print(" E +8"); break;
            case 125: tft.print(" F +8"); break;
            case 126: tft.print(" F#+8"); break;
            case 127: tft.print(" G +8"); break;
            case 128: tft.print(" G#+8"); break;
            case 129: tft.print(" A +8"); break;
            case 130: tft.print(" A#+8"); break;
            case 131: tft.print(" B +8"); break; }
          tft.setFont();
          tft.setTextSize(_ts);
          tft.setCursor(_cy, _cly+_clh);
          tft.print(leftnewPos);
          break;

        case LCDTextColorEE: // LCD text color
          if (leftnewPos < 1 ) { leftnewPos = 0; leftEnc.write(leftnewPos * 4); }
          if (leftnewPos > 254 ) { leftnewPos = 255; leftEnc.write(leftnewPos * 4); }
          LCDTextColor = leftnewPos;
          LCD_txt_Color = LCD_Color(LCDTextColor);
          TFT_Color(leftnewPos);
          break;
          
        case LCDBackColorEE: // LCD background color
          if (leftnewPos < 1 ) { leftnewPos = 0; leftEnc.write(leftnewPos * 4); }
          if (leftnewPos > 254 ) { leftnewPos = 255; leftEnc.write(leftnewPos * 4); }
          LCDBackColor = leftnewPos;
          LCD_bck_Color = LCD_Color(LCDBackColor);
          TFT_Color(leftnewPos);
          break;
          
        case LCDTextFontEE: // LCD text font ( DSEG7, DSEG7 bold, Helvetica, Swiss, Machine, Bernard, Wave, Marker, Asimov, Calligraphy, Brush, Harlow, Christmas )
          if (leftnewPos < 1 ) { leftnewPos = 13; leftEnc.write(leftnewPos * 4); }
          if (leftnewPos > 13 ) { leftnewPos = 1; leftEnc.write(leftnewPos * 4); }
          LCDTextFont = leftnewPos-1;
          
          tft.fillRect(_mx, _my, _tw, _mh, LCD_bck_Color); // clear area
          tft.drawBitmap(_ncx100, _ncy, TFT_ + (1 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color);
          tft.drawBitmap(_ncx1, _ncy, TFT_ + (2 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color);
          tft.drawBitmap(_ncx1 * 2, _ncy, TFT_ + (3 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color);
          
          tft.setFont();
          tft.setTextSize(_ts);
          tft.setCursor(_ts*7, _cly+_clh);
          tft.setTextColor(TFT_Yellow, LCD_bck_Color);
          
          switch(LCDTextFont) {
            case 0:  tft.print(" DSEG7"); break;
            case 1:  tft.print(" DSEG7 bold"); break;
            case 2:  tft.print(" Helvetica"); break;
            case 3:  tft.print(" Swiss"); break;
            case 4:  tft.print(" Machine"); break;
            case 5:  tft.print(" Bernard"); break;
            case 6:  tft.print(" Wave"); break;
            case 7:  tft.print(" Marker"); break;
            case 8:  tft.print(" Asimov"); break;
            case 9:  tft.print(" Calligraphy"); break;
            case 10: tft.print(" Brush"); break;
            case 11: tft.print(" Harlow"); break;
            case 12: tft.print(" Christmas"); break;
          }
          break;
      }
    }
        
    
    else if (MenuDepth == 0) { // no menue
    
      // map active UnitsView to encoder
      if (shift == true) {
        if (leftnewPos < leftPos) { leftnewPos = leftnewPos - 9 ; leftEnc.write(leftnewPos * 4 + 3); }
        if (leftnewPos > leftPos) { leftnewPos = leftnewPos + 9 ; leftEnc.write(leftnewPos * 4); }
      }
/*      
      else if (UnitsView == 0 && leftLCDView == 1) {
        if (leftnewPos < leftPos && digitalRead(leftENC_BTN) == LOW) { leftnewPos = leftnewPos - 4 ; leftEnc.write(leftnewPos * 4); }
        if (leftnewPos > leftPos && digitalRead(leftENC_BTN) == LOW) { leftnewPos = leftnewPos + 4 ; leftEnc.write(leftnewPos * 4); }
      }
*/      
      if (leftnewPos < 1 ) { leftnewPos = 0; leftEnc.write(leftnewPos * 4); }
      if (leftnewPos > 254 ) { leftnewPos = 255; leftEnc.write(leftnewPos * 4); }
      tft.setFont();
      tft.setTextSize(_ts);
      tft.setTextColor(TFT_Yellow, TFT_Black);
      tft.setFont(A18n);
      tft.setCursor(_ts*9, _tw-_th+_ts*2);
      switch(UnitsView) { // unit views encoder mappings
        case 0: // MIDI
          if ( ProgMode == false ) { // --------------------------------------------------------------
            if (leftLCDView == 0 ) {
              if (leftnewPos > 127 ) { leftnewPos = 127; leftEnc.write(leftnewPos * 4); }
              leftEncMIDI_A = leftnewPos;
              usbMIDI.sendControlChange(0 + MIDIBaseAdr - 1, leftnewPos, MIDIChannel & 0b00001111); // Send Control (control, value, channel)
//              MIDI.sendControlChange(0 + MIDIBaseAdr - 1, leftnewPos, MIDIChannel & 0b00001111); // Send Control (control, value, channel)
              }
            else if (leftLCDView == 1 ) { 
              if (leftnewPos > 127 ) { leftnewPos = 127; leftEnc.write(leftnewPos * 4); }
              leftEncMIDI_B = leftnewPos;
              usbMIDI.sendControlChange(1 + MIDIBaseAdr - 1, leftnewPos, MIDIChannel & 0b00001111); // Send Control (control, value, channel)
//              MIDI.sendControlChange(1 + MIDIBaseAdr - 1, leftnewPos, MIDIChannel & 0b00001111); // Send Control (control, value, channel)
              }
            else if (leftLCDView == 2 ) {
              if (leftnewPos > 127 ) { leftnewPos = 127; leftEnc.write(leftnewPos * 4); }
              leftEncMIDI_C = leftnewPos;
              usbMIDI.sendControlChange(2 + MIDIBaseAdr - 1, leftnewPos, MIDIChannel & 0b00001111); // Send Control (control, value, channel)
//              MIDI.sendControlChange(2 + MIDIBaseAdr - 1, leftnewPos, MIDIChannel & 0b00001111); // Send Control (control, value, channel)
            }
            TFTnumber(leftnewPos);
            break;
          }
          else { // ..................................................................................
            bpm = leftnewPos;
            TFT_Draw_BPM(bpm);
            TFTnumber(leftnewPos);
            rightEnc.write(0);
            rightPos = 0;
            tft.setTextColor(TFT_Yellow, TFT_Black);
            tft.setCursor(_tw-_ts*27, _tw-_th+_ts*2);
            tft.setFont(A18n);
            TFTnumber(rightPos);
            break;
        }

        case 1: // Scanner
          if ( ProgMode == false ) { // --------------------------------------------------------------
            if (ScanSelected > 0) {
              if (leftnewPos < 1 ) { leftnewPos = 0; leftEnc.write(leftnewPos * 4); }
              if (leftnewPos > 6 ) { leftnewPos = 7; leftEnc.write(leftnewPos * 4); }
              drawFixtures(ScanActiv, ScanActivFixture);
              setTFTscanner(ScanActiv, rightLCDView, leftLCDView, ScanActivFixture);
              drawFixtureSelected(ScanSelected, leftnewPos);
              rightnewPos = ScanActivFixture[leftnewPos+(ScanSelected-1)*8]; rightEnc.write(rightnewPos * 4);
              tft.setFont();
              tft.setTextColor(TFT_LightGray, TFT_Black);
              tft.setCursor(_tw-_ts*36, _tw-_th*2+_ts*3);
              switch(leftnewPos) {
                case 0: tft.print(" Pan  "); break;
                case 1: tft.print(" Tilt "); break;
                case 2: tft.print("Color "); break;
                case 3: tft.print("Strobe"); break;
                case 4: tft.print(" Gobo "); break;
                case 5: tft.print("Rotate"); break;
                case 6: tft.print("Prisma"); break;
                case 7: tft.print(" Focus"); break;
              }
            }
            else {
              tft.setTextColor(TFT_Yellow, TFT_Black);
              tft.setFont(A18n);
              tft.setCursor(_ts*9, _tw-_th+_ts*2);
              if (leftLCDView == 0) { 
                if (leftnewPos > 10 ) { leftnewPos = 10; leftEnc.write(leftnewPos * 4); }
                ScanSpdMove = (rightLCDView << 5) + leftnewPos;
                switch(leftnewPos) {
                  case 0:  tft.setFont(A14n); tft.print("Stop "); break;
                  case 1:  tft.print("256  "); break;  // 256
                  case 2:  tft.print("128  "); break;
                  case 3:  tft.print(" 64  "); break;
                  case 4:  tft.print(" 32  "); break;
                  case 5:  tft.print(" 16  "); break;
                  case 6:  tft.print("  8  "); break;
                  case 7:  tft.print("  4  "); break; // speed 1 bar
                  case 8:  tft.print("  2  "); break;
                  case 9:  tft.print("  1  "); break; 
                  case 10: tft.print(" 1/2 "); break;
                }
                if ( bitRead(ScanActiv,0) == 1 ) { ScanSpd[0] = leftnewPos; }
                if ( bitRead(ScanActiv,1) == 1 ) { ScanSpd[1] = leftnewPos; }
                if ( bitRead(ScanActiv,2) == 1 ) { ScanSpd[2] = leftnewPos; }
                if ( bitRead(ScanActiv,3) == 1 ) { ScanSpd[3] = leftnewPos; }
                if ( bitRead(ScanActiv,4) == 1 ) { ScanSpd[4] = leftnewPos; }
                if ( bitRead(ScanActiv,5) == 1 ) { ScanSpd[5] = leftnewPos; }
                if ( bitRead(ScanActiv,6) == 1 ) { ScanSpd[6] = leftnewPos; }
                if ( bitRead(ScanActiv,7) == 1 ) { ScanSpd[7] = leftnewPos; }  
//Serial.println(ScanSpdMove);
              }
              else if (leftLCDView == 1 ) {
                if (leftnewPos > 21 ) { leftnewPos = 21; leftEnc.write(leftnewPos * 4); }
                ScanSpdMove = (rightLCDView << 5) + leftnewPos + 10;
                if (leftnewPos == 0 ) { tft.setFont(A14n); tft.print("Stop "); }
                else { TFTnumber(leftnewPos); }
              }
              else if (leftLCDView == 2 ) { // Run
                ScanRun = leftnewPos;
                TFTnumber(leftnewPos);
              }
            }
          }
          else { // Scanner programming mode .........................................................
            if      (leftLCDView == 0 ) { ScanPan    = leftnewPos; TFTnumber(leftnewPos); SetScannerFixture(ScanActiv, 0, ScanPan,    SCANNER_BASE_ADR); }
            else if (leftLCDView == 1 ) { ScanColor  = leftnewPos; TFTnumber(leftnewPos); SetScannerFixture(ScanActiv, 2, ScanColor,  SCANNER_BASE_ADR); }
            else if (leftLCDView == 2 ) { ScanGobo   = leftnewPos; TFTnumber(leftnewPos); SetScannerFixture(ScanActiv, 4, ScanGobo,   SCANNER_BASE_ADR); }
            else if (leftLCDView == 3 ) { ScanPrisma = leftnewPos; TFTnumber(leftnewPos); SetScannerFixture(ScanActiv, 6, ScanPrisma, SCANNER_BASE_ADR); }
            else if (leftLCDView == 4  && shift == false ) { 
              tft.setTextColor(TFT_Yellow, TFT_Black);
              tft.setFont(A18n);
              tft.setCursor(_ts*9, _tw-_th+_ts*2);
              if ((ScanSpdMove & 0b00011111) < 11) { 
                if (leftnewPos > 10 ) { leftnewPos = 10; leftEnc.write(leftnewPos * 4); }
                ScanSpdMove = (rightLCDView << 5) + leftnewPos;
                switch(leftnewPos) {
                  case 0:  tft.setFont(A14n); tft.print("Stop "); break;
                  case 1:  tft.print("256  "); break; // 256
                  case 2:  tft.print("128  "); break;
                  case 3:  tft.print(" 64  "); break;
                  case 4:  tft.print(" 32  "); break;
                  case 5:  tft.print(" 16  "); break;
                  case 6:  tft.print("  8  "); break;
                  case 7:  tft.print("  4  "); break; // speed 1 bar
                  case 8:  tft.print("  2  "); break;
                  case 9:  tft.print("  1  "); break; 
                  case 10: tft.print(" 1/2"); break;
                }
                if ( bitRead(ScanActiv,0) == 1 ) { ScanSpd[0] = leftnewPos; }
                if ( bitRead(ScanActiv,1) == 1 ) { ScanSpd[1] = leftnewPos; }
                if ( bitRead(ScanActiv,2) == 1 ) { ScanSpd[2] = leftnewPos; }
                if ( bitRead(ScanActiv,3) == 1 ) { ScanSpd[3] = leftnewPos; }
                if ( bitRead(ScanActiv,4) == 1 ) { ScanSpd[4] = leftnewPos; }
                if ( bitRead(ScanActiv,5) == 1 ) { ScanSpd[5] = leftnewPos; }
                if ( bitRead(ScanActiv,6) == 1 ) { ScanSpd[6] = leftnewPos; }
                if ( bitRead(ScanActiv,7) == 1 ) { ScanSpd[7] = leftnewPos; }
//Serial.println(ScanSpdMove);
              }
              else {
                if (leftnewPos > 21 ) { leftnewPos = 21; leftEnc.write(leftnewPos * 4); }
                TFTnumber(leftnewPos);
              }
            }
            else if (leftLCDView == 4 && shift == true ) {
              tft.setFont();
              tft.setTextSize(_ts);
              tft.setTextColor(TFT_LightGray, TFT_Black);
              tft.setCursor(2, _tw-_th*2+_ts*3);
              if ( (ScanSpdMove & 0b00011111) > 10 ) { 
                ScanSpdMove = (ScanSpdMove & 0b11100000) ; 
                tft.print("Beats ");
              } 
              else { 
                ScanSpdMove = (ScanSpdMove & 0b11100000)+11 ; 
                tft.print(" Free ");
              } 
            }
            if(bitRead(FixtureActiv, leftLCDView*2) == 0 && shift == false) { 
              bitSet(FixtureActiv, leftLCDView*2);
              pixels.setPixelColor(16+leftLCDView*6,pixels.Color(0,2+NeoPixelBright,0));
              pixels.show();
            }
            preFixtureActiv = setTFTfixture(FixtureActiv, leftLCDView, rightLCDView, preFixtureActiv, ScanSpdMove);
          }
          break;
          
        case 2: // COB
          if      (leftLCDView == 0 ) { DMXPixbar = leftnewPos; }
          else if (leftLCDView == 1 ) { 
            if (shift == false) {
              if (leftnewPos < leftPos) { leftnewPos = leftnewPos - 1 ; leftEnc.write(leftnewPos * 4); } // this is not correct
              if (leftnewPos > leftPos) { leftnewPos = leftnewPos + 4 ; leftEnc.write(leftnewPos * 4); }
            }
            DMXBackBright = leftnewPos; }
          else if (leftLCDView == 2 ) { leftEncRED = leftnewPos; }
          else if (leftLCDView == 3 ) { leftEncBlue = leftnewPos; }
          TFTnumber(leftnewPos);
          break;
      }
    }
    
    if (MenuDepth < 10) { // exit sub-menue
      if ( leftLastEncoder+18 == MIDIBaseAdrEE ) {
        pixels.setPixelColor(35,pixels.Color(0,0,1)); // clear mark C for drum pad
        pixels.show();
      }
    }
    
    if ( leftnewPos > 254 || leftnewPos < 1 || MenuDepth > 0 ) { leftEnc.write(leftnewPos * 4); }
    leftPos = leftnewPos;
  }

// Encoder Button ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
  current_ms_left = millis();

  if (digitalRead(leftENC_BTN) == HIGH)
  {
    if (leftEncPressed == false) { // pressed left encoder button
      Serial.print("left Enc pressed ");
      Serial.print(leftEncPressed);
      Serial.print("  millis ");
      Serial.print(current_ms_left - previous_ms_left);
      Serial.print("   UnitsView ");
      Serial.print(UnitsView);
      Serial.print("   ProgMode ");
      Serial.print(ProgMode);
      Serial.print("   leftLCDView ");
      Serial.print(leftLCDView);
      Serial.print("   Shift ");
      Serial.print(shift);
      Serial.print("   leftnewPos ");
      Serial.println(leftnewPos);
    }
    leftEncPressed = true;
    
    if (current_ms_left - previous_ms_left >= 600 && current_ms_left - previous_ms_left < 650 ) // -> enter edit mode (600ms)
    {
      if (MenuDepth == 0) // enter menu
      {
        MenuDepth = 9;
        leftLastEncoder = EEPROM.read(leftEncoderStartEE);
        leftEnc.write(leftLastEncoder * 4);
        leftTFT_MenuSelect(leftLastEncoder);
      }
      else // exit menu
      {
        if (MenuDepth == 10) { // save value
          EEPROM.write(leftLastEncoder+18, leftnewPos);
          delay(10);
          
          if(leftLastEncoder+8 == CountLenghtEE) {
            EEPROM.write(leftLastEncoder+8, rightnewPos);
            delay(10);}
        }
        MenuDepth = 0;
        LCD_bck_Color = LCD_Color(LCDBackColor);
        tft.fillRect(_clx, _ty, _clw, _cly-_ty, TFT_Black); // clear
        tft.fillRect(_clx, _cly, _clw, _clh, LCD_bck_Color); // clear
        tft.fillRect(_clx, _clh+_cly, _clw, _clw-_clh, TFT_Black); // clear
        EEPROM.write(leftEncoderStartEE, leftLastEncoder);
        delay(10);
        TFT_Draw_Count();
        leftLCDView = leftLCDView - 1;
        tft.setFont();
        tft.setTextSize(_ts);        
      }
    }
  }
  
  else {
    if (leftEncPressed == true) { // released left encoder button (<500ms)
      Serial.print("left Enc released ");
      Serial.print(leftEncPressed);
      Serial.print("  millis ");
      Serial.println(current_ms_left - previous_ms_left);
    }
    
    if (leftEncPressed == true && current_ms_left - previous_ms_left < 500) {
      
      if (MenuDepth > 0) // Edit mode on (green LED on)
      {
        bitSet(leftLCDView, 5);
        
        if (MenuDepth == 9) // enter left 2nd level menu
        {
          MenuDepth = 10;  // 2 + bit3
          leftLastEncoder = leftnewPos;
          tft.fillRect(_tx, _ty, _tw, _th, TFT_Red); // titel
          tft.setFont();
          tft.setTextSize(_ts);
          tft.setCursor((_tw - strlen(leftTFT_LongMenu[leftLastEncoder-2]) * 6 * _ts) / 2, _tty);
          tft.setTextColor(TFT_Yellow);
          tft.println(leftTFT_LongMenu[leftLastEncoder-2]); //  
          int i = EEPROM.read(leftLastEncoder+18);
          leftEnc.write(i*4);
          leftPos = i;
          int j = EEPROM.read(leftLastEncoder+8);
          rightEnc.write(j*4);
          rightPos = j;
        }
        
        else if (MenuDepth == 10) // exit 2nd level menue
        {
          MenuDepth = 9;  // 1 + bit3
          EEPROM.write(leftLastEncoder+18, leftnewPos);
          delay(10);
          
          if(leftLastEncoder+8 == CountLenghtEE) {
            EEPROM.write(leftLastEncoder+8, rightnewPos);
            delay(10);}
          
          leftEnc.write(leftLastEncoder*4); // write back last menu point
          leftTFT_MenuSelect(leftLastEncoder);
        }
        
        else if (MenuDepth == 2) // 2nd level right menue, every push increase counter
        {
          leftPos++;
          leftEnc.write((leftPos) * 4);
          bitSet(leftLCDView, 5);
        }
      }
      
      else if (MenuDepth == 0) { // no menue selected
        if ( shift == false ) { leftLCDView++; } // toggle through active units view
        else {  // toggle trough views: MIDI - Scanner - COB
          ProgMode = false;
          UnitsView++;
          if (bitRead(DMXUnits, 2) == 0 && UnitsView == 1) { UnitsView++; } // move to next if no scanner is activated
          if ((DMXUnits & 0b00000011) + ((DMXUnits & 0b00011000) >> 3) == 0 && UnitsView == 2) { UnitsView++; } // move to next if no COB is activated
          if (UnitsView > 2 ) { UnitsView = 0; } // toggle
          TFT_Draw_Count();
        }
      }
    }
    if ( leftEncPressed == true ) { EncButtonTFT(); }
    leftEncPressed = false;
    previous_ms_left = current_ms_left;
  }

/// Encoder Left ##########################################################################
