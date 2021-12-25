// Scanner ################################################################
//  SCANNER_BASE_ADR = DMXBase + (DMXUnits & 0b00000011) * 30;

if((DMXUnits & 0b00000100) > 0) {
  
  for (int s = 0; s < 8; s++ )
  { 
    if ( ScanDir[s] == true ) { ScanCnt[s]++; } else { ScanCnt[s]--; } // up-down counter
    if ( ScanCnt[s] < 1 ) { ScanDir[s] = true; 
/*
      Serial.print("  Calc: ");
      Serial.print(ScanCalc[s]);
      Serial.print("  Angle: ");
      Serial.println(ScanAngle[s]);
*/        
    } 
    Serial.print("ScanSpd:");
    Serial.println(ScanSpd[s]);
    switch(ScanSpd[s]) {
      case 0:  ScanCnt[s] = 0; ScanCalc[s] = 0; break;
      case 1:  if ( ScanCnt[s] > 3071 ) { ScanDir[s] = false; ScanCnt[s] = 3072; } ScanCalc[s] = ScanCnt[s]*ScanAngle[s]*2.2/3072-ScanAngle[s]*1.1; break;
      case 2:  if ( ScanCnt[s] > 1535 ) { ScanDir[s] = false; ScanCnt[s] = 1536; } ScanCalc[s] = ScanCnt[s]*ScanAngle[s]*2.2/1536-ScanAngle[s]*1.1; break;
      case 3:  if ( ScanCnt[s] > 767  ) { ScanDir[s] = false; ScanCnt[s] = 768;  } ScanCalc[s] = ScanCnt[s]*ScanAngle[s]*2.2/768-ScanAngle[s]*1.1;  break;
      case 4:  if ( ScanCnt[s] > 383  ) { ScanDir[s] = false; ScanCnt[s] = 384;  } ScanCalc[s] = ScanCnt[s]*ScanAngle[s]*2.2/384-ScanAngle[s]*1.1;  break;
      case 5:  if ( ScanCnt[s] > 191  ) { ScanDir[s] = false; ScanCnt[s] = 192;  } ScanCalc[s] = ScanCnt[s]*ScanAngle[s]*2.202/192-ScanAngle[s]*1.101;  break;
      case 6:  if ( ScanCnt[s] > 95   ) { ScanDir[s] = false; ScanCnt[s] = 96;   } ScanCalc[s] = ScanCnt[s]*ScanAngle[s]*2.234/96-ScanAngle[s]*1.117;   break;
      case 7:  if ( ScanCnt[s] > 47   ) { ScanDir[s] = false; ScanCnt[s] = 48;   } ScanCalc[s] = ScanCnt[s]*ScanAngle[s]*2.284/48-ScanAngle[s]*1.142;   break;
      case 8:  if ( ScanCnt[s] > 23   ) { ScanDir[s] = false; ScanCnt[s] = 24;   } ScanCalc[s] = ScanCnt[s]*ScanAngle[s]*2.368/24-ScanAngle[s]*1.184;   break;
      case 9:  if ( ScanCnt[s] > 11   ) { ScanDir[s] = false; ScanCnt[s] = 12;   } ScanCalc[s] = ScanCnt[s]*ScanAngle[s]*2.582/12-ScanAngle[s]*1.291;   break;
      case 10: if ( ScanCnt[s] > 5    ) { ScanDir[s] = false; ScanCnt[s] = 6;    } ScanCalc[s] = ScanCnt[s]*ScanAngle[s]*3.18/6-ScanAngle[s]*1.59;    break;      
    }
    
    if(ProgMode==0) 
    {
      if ( ScanMove[s] == 0 ) { // Pan
        if ( ScanActivFixture[0+s*8] + ScanCalc[s] > 255 ) { scanmv = 255; }
        else if ( ScanActivFixture[0+s*8] + ScanCalc[s] < 0 ) { scanmv = 0; }
        else { scanmv = ScanActivFixture[0+s*8] + ScanCalc[s]; }
        DMXset(SCANNER_BASE_ADR+s*8+0, scanmv ); 
        DMXset(SCANNER_BASE_ADR+s*8+1, ScanActivFixture[1+s*8] ); 
      }
      else if ( ScanMove[s] == 1 ) {  // Tilt
        if ( ScanActivFixture[1+s*8] + ScanCalc[s] > 255 ) { scanmv = 255; }
        else if ( ScanActivFixture[1+s*8] + ScanCalc[s] < 0 ) { scanmv = 0; }
        else { scanmv = ScanActivFixture[1+s*8] + ScanCalc[s]; }
        DMXset(SCANNER_BASE_ADR+s*8+1, scanmv ); 
        DMXset(SCANNER_BASE_ADR+s*8+0, ScanActivFixture[0+s*8] ); 
      }
      else if ( ScanMove[s] == 2 ) { // Circle clockwise
        if ( ScanActivFixture[0+s*8] + ScanCalc[s] > 255 ) { scanmv = 255; }
        else if ( ScanActivFixture[0+s*8] + ScanCalc[s] < 0 ) { scanmv = 0; }
        else { scanmv = ScanActivFixture[0+s*8] + ScanCalc[s]; }
        DMXset(SCANNER_BASE_ADR+s*8+0, scanmv );
        if ( ScanDir[s] == true ) { ScanCalc[s] = abs(ScanCalc[s])-ScanAngle[s]; }
        else if ( ScanDir[s] == false ) { ScanCalc[s] = -(abs(ScanCalc[s])-ScanAngle[s]); }
        if ( ScanActivFixture[1+s*8] + ScanCalc[s] > 255 ) { scanmv = 255; }
        else if ( ScanActivFixture[1+s*8] + ScanCalc[s] < 0 ) { scanmv = 0; }
        else { scanmv = ScanActivFixture[1+s*8] + ScanCalc[s]; }
        DMXset(SCANNER_BASE_ADR+s*8+1, scanmv ); 
      }
      else if ( ScanMove[s] == 3 ) { // Circle anti-clockwise
        if ( ScanActivFixture[0+s*8] + ScanCalc[s] > 255 ) { scanmv = 255; }
        else if ( ScanActivFixture[0+s*8] + ScanCalc[s] < 0 ) { scanmv = 0; }
        else { scanmv = ScanActivFixture[0+s*8] + ScanCalc[s]; }
        DMXset(SCANNER_BASE_ADR+s*8+0, scanmv );
        if ( ScanDir[s] == true ) { ScanCalc[s] = -(abs(ScanCalc[s])-ScanAngle[s]); }
        else if ( ScanDir[s] == false ) { ScanCalc[s] = abs(ScanCalc[s])-ScanAngle[s]; }
        if ( ScanActivFixture[1+s*8] + ScanCalc[s] > 255 ) { scanmv = 255; }
        else if ( ScanActivFixture[1+s*8] + ScanCalc[s] < 0 ) { scanmv = 0; }
        else { scanmv = ScanActivFixture[1+s*8] + ScanCalc[s]; }
        DMXset(SCANNER_BASE_ADR+s*8+1, scanmv ); 
      }
      else if ( ScanMove[s] == 4 ) { // Swing
        if ( ScanActivFixture[0+s*8] + ScanCalc[s] > 255 ) { scanmv = 255; }
        else if ( ScanActivFixture[0+s*8] + ScanCalc[s] < 0 ) { scanmv = 0; }
        else { scanmv = ScanActivFixture[0+s*8] + ScanCalc[s]; }
        DMXset(SCANNER_BASE_ADR+s*8+0, scanmv );
        ScanCalc[s] = (abs(abs(ScanCalc[s])-ScanAngle[s])-ScanAngle[s]/2)*2 ;  // Swing =(ABS(ABS(AV69)-10)-5)*2
        if ( ScanActivFixture[1+s*8] + ScanCalc[s] > 255 ) { scanmv = 255; }
        else if ( ScanActivFixture[1+s*8] + ScanCalc[s] < 0 ) { scanmv = 0; }
        else { scanmv = ScanActivFixture[1+s*8] + ScanCalc[s]; }
        DMXset(SCANNER_BASE_ADR+s*8+1, scanmv ); 
      }    
      else if ( ScanMove[s] == 5 ) { // Wave
        if ( ScanActivFixture[0+s*8] + ScanCalc[s] > 255 ) { scanmv = 255; }
        else if ( ScanActivFixture[0+s*8] + ScanCalc[s] < 0 ) { scanmv = 0; }
        else { scanmv = ScanActivFixture[0+s*8] + ScanCalc[s]; }
        DMXset(SCANNER_BASE_ADR+s*8+0, scanmv );
        ScanCalc[s] = (abs(abs(ScanCalc[s])-ScanAngle[s])-ScanAngle[s]/2)*2 ;  // Swing =(ABS(ABS(AV69)-10)-5)*2
        ScanCalc[s] = (abs(abs(ScanCalc[s])-ScanAngle[s])-ScanAngle[s]/2)*2 ;  // Wave =(ABS(ABS(AV69)-10)-5)*2
        if ( ScanActivFixture[1+s*8] + ScanCalc[s] > 255 ) { scanmv = 255; }
        else if ( ScanActivFixture[1+s*8] + ScanCalc[s] < 0 ) { scanmv = 0; }
        else { scanmv = ScanActivFixture[1+s*8] + ScanCalc[s]; }
        DMXset(SCANNER_BASE_ADR+s*8+1, scanmv ); 
      }    
      else if ( ScanMove[s] == 6 ) { // DiagLU upper left to down right
        if ( ScanActivFixture[0+s*8] + ScanCalc[s] > 255 ) { scanmv = 255; }
        else if ( ScanActivFixture[0+s*8] + ScanCalc[s] < 0 ) { scanmv = 0; }
        else { scanmv= ScanActivFixture[0+s*8] + ScanCalc[s]; }
        DMXset(SCANNER_BASE_ADR+s*8+0, scanmv);
        if ( ScanActivFixture[1+s*8] + ScanCalc[s] > 255 ) { scanmv = 255; }
        else if ( ScanActivFixture[1+s*8] + ScanCalc[s] < 0 ) { scanmv = 0; }
        else { scanmv = ScanActivFixture[1+s*8] + ScanCalc[s]; }
        DMXset(SCANNER_BASE_ADR+s*8+1, scanmv ); 
      }
      else if ( ScanMove[s] == 7 ) { // DiagRU lower left to upper right 
        if ( ScanActivFixture[0+s*8] + ScanCalc[s] > 255 ) { scanmv = 255; }
        else if ( ScanActivFixture[0+s*8] + ScanCalc[s] < 0 ) { scanmv = 0; }
        else { scanmv = ScanActivFixture[0+s*8] + ScanCalc[s]; }
        DMXset(SCANNER_BASE_ADR+s*8+0, scanmv);
        if ( ScanActivFixture[1+s*8] - ScanCalc[s] > 255 ) { scanmv = 255; }
        else if ( ScanActivFixture[1+s*8] - ScanCalc[s] < 0 ) { scanmv = 0; }
        else { scanmv = ScanActivFixture[1+s*8] - ScanCalc[s]; }
        DMXset(SCANNER_BASE_ADR+s*8+1, scanmv ); 
      }      
    }    
  }
}

/// Scanner ################################################################
