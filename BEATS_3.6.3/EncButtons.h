void EncValueTFT() {
  
}

void EncButtonTFT() {
// byte MenuDepth, byte UnitsView, byte ProgMode, byte shift, byte leftEncPressed, byte leftLCDView, 
// byte leftnewPos, byte rightEncPressed, byte rightLCDView, byte rightnewPos, byte MIDIBaseAdr
// MenuDepth - shift - UnitsView - ProgMode - leftLCDView & rightLCDView

  switch(MenuDepth) {
    case 0: // no menu
      // Encoder LED's
      digitalWrite(leftENC_RED, HIGH);  // red LED off
      digitalWrite(leftENC_GREEN, HIGH);  // green LED off
      digitalWrite(rightENC_RED, HIGH);  // red LED off
      digitalWrite(rightENC_GREEN, HIGH);  // green LED off
      
      tft.setFont();
      tft.setTextSize(_ts);
      tft.setTextColor(TFT_White, TFT_Black);
      tft.setCursor((_tw/2 - strlen("Program") * 3 * _ts), _tw-_th*2+_ts*3);
      tft.print("        ");
      tft.setTextColor(TFT_Cyan, TFT_Black);
      tft.setCursor(_tw/2-_ts*24, _tw-_th+_ts*2);
      
      switch(UnitsView) {
        
        case 0: // MIDI ===============================================================================
          tft.setCursor((_tw/2 - strlen("  MIDI  ") * 3 * _ts), _tw-_th+_ts*2);
          tft.print("  MIDI  "); 
          
          pixels.setPixelColor(16,pixels.Color(0,1,0));
          pixels.setPixelColor(17,pixels.Color(0,0,1));
          pixels.setPixelColor(18,pixels.Color(0,0,1));
          pixels.setPixelColor(19,pixels.Color(0,0,1));
          pixels.setPixelColor(20,pixels.Color(0,0,1));
          pixels.setPixelColor(21,pixels.Color(1,0,0));
          
          pixels.setPixelColor(22,pixels.Color(0,1,0));
          pixels.setPixelColor(23,pixels.Color(0,0,1));
          pixels.setPixelColor(24,pixels.Color(0,0,1));
          pixels.setPixelColor(25,pixels.Color(0,0,1));
          pixels.setPixelColor(26,pixels.Color(0,0,1));
          pixels.setPixelColor(27,pixels.Color(1,0,0));
          
          pixels.setPixelColor(28,pixels.Color(0,1,0));
          pixels.setPixelColor(29,pixels.Color(0,0,1));
          pixels.setPixelColor(30,pixels.Color(0,0,1));
          pixels.setPixelColor(31,pixels.Color(0,0,1));
          pixels.setPixelColor(32,pixels.Color(0,0,1));
          pixels.setPixelColor(33,pixels.Color(1,0,0));
          
          pixels.setPixelColor(34,pixels.Color(0,1,0));
          pixels.setPixelColor(35,pixels.Color(0,0,1));
          pixels.setPixelColor(36,pixels.Color(0,0,1));
          pixels.setPixelColor(37,pixels.Color(0,0,1));
          pixels.setPixelColor(38,pixels.Color(0,0,1));
          pixels.setPixelColor(39,pixels.Color(1,0,0));
                
//          if ( RUN == true ) { tft.fillRect(_clx, _cly, _clw, _clh, LCD_bck_Color); } // clear

          tft.setTextColor(TFT_Black);
          tft.setCursor(2, _tw-_th*2+_ts*3);
          if (ProgMode == false) { //------------------------------------------------------------------
            if (leftLCDView > 2 ) { leftLCDView = 0; } // toggle through 3 points
            
            tft.setCursor(2, _tw-_th*2+_ts*3);
            switch(leftLCDView) {
              case 0:
                tft.fillRect(0, _tw-_th*2+_ts*2, _ts*38, _ts*9, TFT_Red);
                tft.print("cc ");
                tft.print(0+MIDIBaseAdr-1);
                if((0+MIDIBaseAdr-1) < 10) tft.print(" ");
                if((0+MIDIBaseAdr-1) < 100) tft.print(" ");
                leftEnc.write(leftEncMIDI_A * 4);
                leftPos = leftEncMIDI_A;
                break;

              case 1:
                tft.fillRect(0, _tw-_th*2+_ts*2, _ts*38, _ts*9, TFT_Green);
                tft.print("cc ");
                tft.print(1+MIDIBaseAdr-1);
                if((1+MIDIBaseAdr-1) < 10) tft.print(" "); 
                if((1+MIDIBaseAdr-1) < 100) tft.print(" ");
                leftEnc.write(leftEncMIDI_B * 4);
                leftPos = leftEncMIDI_B;
                break;

              case 2:
                tft.fillRect(0, _tw-_th*2+_ts*2, _ts*38, _ts*9, TFT_Blue);
                tft.print("cc ");
                tft.print(2+MIDIBaseAdr-1);
                if((2+MIDIBaseAdr-1) < 10) tft.print(" "); 
                if((2+MIDIBaseAdr-1) < 100) tft.print(" ");
                leftEnc.write(leftEncMIDI_C * 4);
                leftPos = leftEncMIDI_C;
                break;
            }
            
            if (rightLCDView > 2 ) { rightLCDView = 0; } // toggle through 3 points
            tft.setCursor(_tw-_ts*36, _tw-_th*2+_ts*3);
            switch(rightLCDView) {
              case 0:
                tft.fillRect(_tw-_ts*36-4, _tw-_th*2+_ts*2, _ts*38, _ts*9, TFT_Magenta);
                tft.print("cc ");
                tft.print(3+MIDIBaseAdr-1);
                if((3+MIDIBaseAdr-1) < 10) tft.print(" ");
                if((3+MIDIBaseAdr-1) < 100) tft.print(" ");
                rightEnc.write(rightEncMIDI_D * 4);
                rightPos = rightEncMIDI_D;
                break;

              case 1:
                tft.fillRect(_tw-_ts*36-4, _tw-_th*2+_ts*2, _ts*38, _ts*9, TFT_Yellow);
                tft.print("cc ");
                tft.print(4+MIDIBaseAdr-1);
                if((4+MIDIBaseAdr-1) < 10) tft.print(" ");
                if((4+MIDIBaseAdr-1) < 100) tft.print(" ");
                rightEnc.write(rightEncMIDI_E * 4);
                rightPos = rightEncMIDI_E;
                break;

              case 2:
                tft.fillRect(_tw-_ts*36-4, _tw-_th*2+_ts*2, _ts*38, _ts*9, TFT_Cyan);
                tft.print("cc ");
                tft.print(5+MIDIBaseAdr-1);
                if((5+MIDIBaseAdr-1) < 10) tft.print(" ");
                if((5+MIDIBaseAdr-1) < 100) tft.print(" ");
                rightEnc.write(rightEncMIDI_F * 4);
                rightPos = rightEncMIDI_F;
                break;
            }
          }
          
          else { // MIDI programming mode .............................................................
            
            tft.fillRect(_clx, _cly, _clw, _clh, TFT_Black); // clear

            tft.fillRect(0, _tw-_th*2+_ts*2, _ts*38, _ts*9, TFT_Black);
            tft.setTextColor(TFT_LightGray);
            tft.setCursor(2, _tw-_th*2+_ts*3);
            tft.print("Coarse");
            
            tft.fillRect(_tw-_ts*36-4, _tw-_th*2+_ts*2, _ts*38, _ts*9, TFT_Black);
            tft.setTextColor(TFT_LightGray);
            tft.setCursor(_tw-_ts*34, _tw-_th*2+_ts*3);
            tft.print(" Fine");
            
            tft.setTextColor(TFT_Green, TFT_Black);
            tft.setCursor((_tw/2 - strlen("Metronom") * 3 * _ts + _ts*3 ), _tw-_th*2+_ts*3);
            tft.print("Metronom");
            
            leftEnc.write(bpm * 4);
            leftPos = bpm;
            rightEnc.write(0);
            rightPos = 0;
            
            TFT_Draw_BPM(bpm);
            
            if (leftLCDView > 1 ) { leftLCDView = 0; } // toggle
            switch(leftLCDView) {
              case 0:
                RUN = false;
                break;

              case 1:
                RUN = true;
                break;
            }
            switch(rightLCDView) {
              case 0:
                RUN = false;
                break;

              case 1:
                RUN = true;
                break;
            }
          }
          break;
          
        case 1: // Scanner ============================================================================
          tft.setCursor((_tw/2 - strlen("Scanner") * 3 * _ts), _tw-_th+_ts*2);
          tft.print("Scanner");
          tft.fillRect(0, _tw-_th*2+_ts*2, _ts*38, _ts*9, TFT_Black);
          tft.fillRect(_tw-_ts*36-4, _tw-_th*2+_ts*2, _ts*38, _ts*9, TFT_Black);

          setpixels4x4red();
          pixels.setPixelColor(16,pixels.Color(0,0,1)); pixels.setPixelColor(21,pixels.Color(0,0,1));
          pixels.setPixelColor(22,pixels.Color(0,0,1)); pixels.setPixelColor(27,pixels.Color(0,0,1));
          pixels.setPixelColor(28,pixels.Color(0,0,1)); pixels.setPixelColor(33,pixels.Color(0,0,1));
          pixels.setPixelColor(34,pixels.Color(0,0,1)); pixels.setPixelColor(39,pixels.Color(0,0,1));
         
          tft.setTextColor(TFT_LightGray, TFT_Black);
          if (ProgMode == false) { //------------------------------------------------------------------
            if ( leftLCDView > 2 ) { leftLCDView = 0; } // toggle trough 3 points
            tft.setCursor(2, _tw-_th*2+_ts*3);
            switch(leftLCDView) {
              case 0:
                tft.print("Beats ");
                if ( (ScanSpdMove & 0b00011111) > 10 ) { ScanSpdMove = ScanSpdMove & 0b11100000; }
                leftEnc.write((ScanSpdMove & 0b00011111) * 4);
                leftPos = (ScanSpdMove & 0b00011111);
                break; 
                
              case 1:
                tft.print(" Free ");
                if ( (ScanSpdMove & 0b00011111) < 12 ) { ScanSpdMove = (ScanSpdMove & 0b11100000)+11 ; }
                leftEnc.write(((ScanSpdMove & 0b00011111)-11) * 4);
                leftPos = (ScanSpdMove & 0b00011111)-11; 
                break;

              case 2:
                tft.print(" Run  ");
                leftEnc.write(ScanRun * 4);
                leftPos = ScanRun; 
                break;
            }
            
            if (rightLCDView > 7 ) { rightLCDView = 0; } // toggle through 8 points
            tft.setCursor(_tw-_ts*36, _tw-_th*2+_ts*3);
            switch(rightLCDView) {
              case 0: tft.print("LftRgt"); break;
              case 1: tft.print("UpDown"); break;
              case 2: tft.print("Circ R"); break;
              case 3: tft.print("Circ L"); break;
              case 4: tft.print("Swing "); break;
              case 5: tft.print(" Wave "); break;
              case 6: tft.print("DiagLU"); break;
              case 7: tft.print("DiagRU"); break;
            }
            rightEnc.write(ScanMotion * 4);
            rightPos = ScanMotion;
            
            drawFixtures(ScanActiv, ScanActivFixture);
            setTFTscanner(ScanActiv, rightLCDView, leftLCDView, ScanActivFixture);
            setpixelsscanner(ScanActiv, NeoPixelBright);
            
            
/*            
            if (ScanSelected == 0) {
              if (leftLCDView == 0) { ScanSpdMove = (rightLCDView << 5) + (ScanSpdMove & 0b11100000); } 
              else if (leftLCDView == 1) { 
                if ((ScanSpdMove & 0b11100000) == 0) { ScanSpdMove = rightLCDView << 5; } 
                else { ScanSpdMove = (rightLCDView << 5) + (ScanSpdMove & 0b11100000) + 10; } 
              }
              
              tft.setCursor(_tw-_ts*36, _tw-_th*2+_ts*3);
//              rightLCDView = (ScanSpdMove>>5);

              if ( bitRead(ScanActiv,0) == 1 ) { ScanAngle[0] = ScanMotion; ScanMove[0] = rightLCDView; }
              if ( bitRead(ScanActiv,1) == 1 ) { ScanAngle[1] = ScanMotion; ScanMove[1] = rightLCDView; }
              if ( bitRead(ScanActiv,2) == 1 ) { ScanAngle[2] = ScanMotion; ScanMove[2] = rightLCDView; }
              if ( bitRead(ScanActiv,3) == 1 ) { ScanAngle[3] = ScanMotion; ScanMove[3] = rightLCDView; }
              if ( bitRead(ScanActiv,4) == 1 ) { ScanAngle[4] = ScanMotion; ScanMove[4] = rightLCDView; }
              if ( bitRead(ScanActiv,5) == 1 ) { ScanAngle[5] = ScanMotion; ScanMove[5] = rightLCDView; }
              if ( bitRead(ScanActiv,6) == 1 ) { ScanAngle[6] = ScanMotion; ScanMove[6] = rightLCDView; }
              if ( bitRead(ScanActiv,7) == 1 ) { ScanAngle[7] = ScanMotion; ScanMove[7] = rightLCDView; }
            }
*/            
            
          }
          
          else { // Scanner programming mode ..........................................................
            if (leftLCDView > 4 ) { leftLCDView = 0; } // toggle through 5 points
            tft.setCursor(2, _tw-_th*2+_ts*3);
            switch(leftLCDView) {
              case 0:
                tft.print(" Pan  ");
                leftEnc.write(ScanPan * 4);
                leftPos = ScanPan;
                break;

              case 1:
                tft.print("Color ");
                leftEnc.write(ScanColor * 4);
                leftPos = ScanColor;
                break;

              case 2:
                tft.print(" Gobo ");
                leftEnc.write(ScanGobo * 4);
                leftPos = ScanGobo;
                break;

              case 3:
                tft.print("Prisma");
                leftEnc.write(ScanPrisma * 4);
                leftPos = ScanPrisma;
                break;

              case 4:
                if ((ScanSpdMove & 0b00011111) > 10) { 
                  tft.print(" Free ");
                  leftEnc.write(((ScanSpdMove & 0b00011111)-11) * 4);
                  leftPos = (ScanSpdMove & 0b00011111)-11; 
                } 
                else { 
                  tft.print("Beats ");
                  leftEnc.write(((ScanSpdMove & 0b00001111)) * 4);
                  leftPos = (ScanSpdMove & 0b00001111); 
                }
                break;
            }
            if (rightLCDView > 4 ) { rightLCDView = 0; } // toggle through 5 points
            tft.setCursor(_tw-_ts*36-2, _tw-_th*2+_ts*3);
            switch(rightLCDView) {
              case 0:
                tft.print(" Tilt ");
                rightEnc.write(ScanTilt * 4);
                rightPos = ScanTilt;
                break;

              case 1:
                tft.print("Strobe");
                rightEnc.write(ScanStrobe * 4);
                rightPos = ScanStrobe;
                break;

              case 2:
                tft.print("Rotate");
                rightEnc.write(ScanRotate * 4);
                rightPos = ScanRotate;
                break;

              case 3:
                tft.print(" Focus");
                rightEnc.write(ScanFocus * 4);
                rightPos = ScanFocus;
                break;

              case 4:
                tft.print("Motion");
                if (shift==true) { // select scanner
                  rightLCDView = 0;
                  leftLCDView = 0;
                  ScanPan    = ScanActivFixture[0+lastScanActivPressed*8];
                  ScanTilt   = ScanActivFixture[1+lastScanActivPressed*8];
                  ScanColor  = ScanActivFixture[2+lastScanActivPressed*8];
                  ScanStrobe = ScanActivFixture[3+lastScanActivPressed*8];
                  ScanGobo   = ScanActivFixture[4+lastScanActivPressed*8];
                  ScanRotate = ScanActivFixture[5+lastScanActivPressed*8];
                  ScanPrisma = ScanActivFixture[6+lastScanActivPressed*8];
                  ScanFocus  = ScanActivFixture[7+lastScanActivPressed*8];              
                  FixtureActiv = ScanActivFixture[64+lastScanActivPressed];
                  leftnewPos = ScanPan;
                  leftEnc.write(leftnewPos * 4);
                }
                rightEnc.write(ScanMotion * 4);
                rightPos = ScanMotion;
                break;
            }
            
            tft.fillRect(_clx, _cly, _clw, _clh, TFT_Black); // clear
            tft.setTextColor(TFT_Green, TFT_Black);
            tft.setCursor((_tw/2 - strlen("Program") * 3 * _ts), _tw-_th*2+_ts*3);
            tft.print("Program");
            
            preScanActiv = ~ScanActiv; // bitwise not (force to execute)
            preFixtureActiv = ~FixtureActiv; // bitwise not (force to execute)
            preScanSpdMove = ~preScanSpdMove; // bitwise not (force to execute)
            preScanActiv = setTFTProgMode(ScanActiv, leftLCDView, rightLCDView, preScanActiv);
            preFixtureActiv = setTFTfixture(FixtureActiv, leftLCDView, rightLCDView, preFixtureActiv, ScanSpdMove);
            setpixelsfixture(FixtureActiv, NeoPixelBright);            
          }
          
          if ( bitRead(ScanActiv,0) == 1 ) { ScanAngle[0] = ScanMotion; ScanMove[0] = rightLCDView; }
          if ( bitRead(ScanActiv,1) == 1 ) { ScanAngle[1] = ScanMotion; ScanMove[1] = rightLCDView; }
          if ( bitRead(ScanActiv,2) == 1 ) { ScanAngle[2] = ScanMotion; ScanMove[2] = rightLCDView; }
          if ( bitRead(ScanActiv,3) == 1 ) { ScanAngle[3] = ScanMotion; ScanMove[3] = rightLCDView; }
          if ( bitRead(ScanActiv,4) == 1 ) { ScanAngle[4] = ScanMotion; ScanMove[4] = rightLCDView; }
          if ( bitRead(ScanActiv,5) == 1 ) { ScanAngle[5] = ScanMotion; ScanMove[5] = rightLCDView; }
          if ( bitRead(ScanActiv,6) == 1 ) { ScanAngle[6] = ScanMotion; ScanMove[6] = rightLCDView; }
          if ( bitRead(ScanActiv,7) == 1 ) { ScanAngle[7] = ScanMotion; ScanMove[7] = rightLCDView; }
          
          break;
          
        case 2: // COB ================================================================================
          tft.setCursor((_tw/2 - strlen("  COB  ") * 3 * _ts), _tw-_th+_ts*2);
          tft.print("  COB  ");

          pixels.setPixelColor(16,pixels.Color(0,0,1));
          pixels.setPixelColor(17,pixels.Color(0,1,0));
          pixels.setPixelColor(18,pixels.Color(0,1,0));
          pixels.setPixelColor(19,pixels.Color(0,1,0));
          pixels.setPixelColor(20,pixels.Color(0,1,0));
          pixels.setPixelColor(21,pixels.Color(0,0,1));
          
          pixels.setPixelColor(22,pixels.Color(0,0,1));
          pixels.setPixelColor(23,pixels.Color(0,1,0));
          pixels.setPixelColor(24,pixels.Color(0,1,0));
          pixels.setPixelColor(25,pixels.Color(0,1,0));
          pixels.setPixelColor(26,pixels.Color(0,1,0));
          pixels.setPixelColor(27,pixels.Color(0,0,1));
          
          pixels.setPixelColor(28,pixels.Color(0,0,1));
          pixels.setPixelColor(29,pixels.Color(0,1,0));
          pixels.setPixelColor(30,pixels.Color(0,1,0));
          pixels.setPixelColor(31,pixels.Color(0,1,0));
          pixels.setPixelColor(32,pixels.Color(0,1,0));
          pixels.setPixelColor(33,pixels.Color(0,0,1));
          
          pixels.setPixelColor(34,pixels.Color(0,0,1));
          pixels.setPixelColor(35,pixels.Color(0,1,0));
          pixels.setPixelColor(36,pixels.Color(0,1,0));
          pixels.setPixelColor(37,pixels.Color(0,1,0));
          pixels.setPixelColor(38,pixels.Color(0,1,0));
          pixels.setPixelColor(39,pixels.Color(0,0,1));
                  
          tft.setTextColor(TFT_LightGray, TFT_Black);

          tft.fillRect(0, _tw-_th*2+_ts*2, _ts*38, _ts*9, TFT_Black);
          tft.fillRect(_tw-_ts*36-4, _tw-_th*2+_ts*2, _ts*38, _ts*9, TFT_Black);
          if (ProgMode == false) { //------------------------------------------------------------------
            if (leftLCDView > 3 ) { leftLCDView = 0; } // toggle through 4 points
            tft.setCursor(2, _tw-_th*2+_ts*3);
            switch(leftLCDView) {
              case 0:
                tft.print(" dmx8 ");
                leftEnc.write(DMXPixbar * 4);
                leftPos = DMXPixbar;
                break;
  
              case 1:
                tft.print("Bckbrt");
                leftEnc.write(DMXBackBright * 4);
                leftPos = DMXBackBright; 
                break;
  
              case 2:
                tft.print(" Red  ");
                leftEnc.write(leftEncRED * 4);
                leftPos = leftEncRED;
                break;
                
              case 3:
                tft.print(" Blue ");
                leftEnc.write(leftEncBlue * 4);
                leftPos = leftEncBlue;
                break;
            }

            if (rightLCDView > 3 ) { rightLCDView = 0; } // toggle through 4 points
            tft.setCursor(_tw-_ts*36, _tw-_th*2+_ts*3);
            switch(rightLCDView) {
              case 0:
                tft.print(" dmx64");
                rightEnc.write(DMXPattern * 4);
                rightPos = DMXPattern;
                break;
  
              case 1:
                tft.print("Bright");
                rightEnc.write(DMXBright * 4);
                rightPos = DMXBright;
                break;
  
              case 2:
                tft.print(" Green");
                rightEnc.write(rightEncGreen * 4);
                rightPos = rightEncGreen;
                break;

              case 3:
                tft.print("Bright");
                rightEnc.write(rightEncBright * 4);
                rightPos = rightEncBright;
                break;
            }
          }
          else { // COB programming mode ..............................................................
            if (leftLCDView > 3 ) { leftLCDView = 0; } // toggle through 4 points
            tft.setCursor(2, _tw-_th*2+_ts*3);
            switch(leftLCDView) {
              case 0:
                tft.print("Bright");
                break;
                
              case 1:
                tft.print("Bright");
                break;
                
              case 2:
                tft.print("Bright");
                break;
                
              case 3:
                tft.print("Bright");
                break;
            }
            if (rightLCDView > 2 ) { rightLCDView = 0; } // toggle through 3 points
            tft.fillRect(_clx, _cly, _clw, _clh, TFT_Black); // clear
            TFT_Draw8x8grid();
            tft.setCursor(_tw-_ts*36, _tw-_th*2+_ts*3);
            switch(rightLCDView) {
              case 0:
                tft.print("  Red ");
                break;
                
              case 1:
                tft.print(" Green");
                break;
                
              case 2:
                tft.print(" Blue ");
                break;
            }
            tft.setTextColor(TFT_Green, TFT_Black);
            tft.setCursor((_tw/2 - strlen("Program") * 3 * _ts), _tw-_th*2+_ts*3);
            tft.print("Program");
            break;
          }
        }
        
        tft.setTextColor(TFT_Yellow, TFT_Black);
        tft.setFont(A18n);

        tft.setCursor(_tw-_ts*27, _tw-_th+_ts*2);
        TFTnumber(rightPos);

        tft.setCursor(_ts*9, _tw-_th+_ts*2);
        if (UnitsView == 1 && leftLCDView == 1 && ((ScanSpdMove & 0b00011111)-11) == 0 ) { 
          tft.setFont(A14n); tft.print("Stop "); 
        }
        else if ( UnitsView == 1 && leftLCDView == 0 ) {
          if (rightLCDView > 10 ) { rightLCDView = 10; } // stop after 11 points
          switch(leftPos) {
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
            case 10: tft.print(" 1/2"); break;
          }
        }
        else {
          TFTnumber(leftPos);
        }
      
      pixels.show();
      break; // MenuDepth
    
    case 1:
      digitalWrite(leftENC_RED, HIGH);  // red LED off
      digitalWrite(leftENC_GREEN, HIGH);  // green LED off
      digitalWrite(rightENC_RED, HIGH);  // red LED off
      digitalWrite(rightENC_GREEN, LOW);  // green LED on
      break; // MenuDepth
    
    case 2:
      digitalWrite(rightENC_RED, LOW);  // red LED on
      digitalWrite(rightENC_GREEN, LOW);  // green LED on
      break; // MenuDepth
    
    case 9:
      // Encoder LED's
      digitalWrite(leftENC_RED, HIGH);  // red LED off
      digitalWrite(leftENC_GREEN, LOW);  // green LED on
      digitalWrite(rightENC_RED, HIGH);  // red LED off
      digitalWrite(rightENC_GREEN, HIGH);  // green LED off
      break; // MenuDepth
    
    case 10:
      // Encoder LED's
      digitalWrite(leftENC_RED, LOW);  // red LED on
      digitalWrite(leftENC_GREEN, LOW);  // green LED on
      break; // MenuDepth
  }
}
