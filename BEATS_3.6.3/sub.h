// Subroutines ################################################################

void TFT_ColorWheel(int f,int s, byte ScanActivFix) {
  tft.setFont(A16n);
  tft.setCursor(_tw/10*(f+1), _tw/10*(s+1)-_ts*s+_ts);
  switch(ScanActivFix) {
    case 0 ... 6:     tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_White); break;
    case 7 ... 13:    tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_Yellow); break;
    case 14 ... 20:   tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_Magenta); break;
    case 21 ... 27:   tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_DarkGreen); break;
    case 28 ... 34:   tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_Red); break;
    case 35 ... 41:   tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_Cyan); break;
    case 42 ... 48:   tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_Green); break;
    case 49 ... 55:   tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_Orange); break;
    case 56 ... 63:   tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_Blue); break;
    case 64 ... 70:   tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_White);
               tft.fillRect(_tw/10*(f+1)+_tw/20, _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_Yellow); break;
    case 71 ... 77:   tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_Yellow);
               tft.fillRect(_tw/10*(f+1)+_tw/20, _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_Magenta); break;
    case 78 ... 84:   tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_Magenta);
               tft.fillRect(_tw/10*(f+1)+_tw/20, _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_DarkGreen); break;
    case 85 ... 91:   tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_DarkGreen);
               tft.fillRect(_tw/10*(f+1)+_tw/20, _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_Red); break;
    case 92 ... 98:   tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_Red);
               tft.fillRect(_tw/10*(f+1)+_tw/20, _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_Cyan); break;
    case 99 ... 105:  tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_Cyan);
               tft.fillRect(_tw/10*(f+1)+_tw/20, _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_Green); break;
    case 106 ... 112: tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_Green);
               tft.fillRect(_tw/10*(f+1)+_tw/20, _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_Orange); break;
    case 113 ... 119: tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_Orange);
               tft.fillRect(_tw/10*(f+1)+_tw/20, _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_Blue); break;
    case 120 ... 127: tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_Blue);
               tft.fillRect(_tw/10*(f+1)+_tw/20, _tw/10*(s+1)-_ts*s, _tw/20, _tw/10-_ts*2, TFT_White); break;
    case 128 ... 191: tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_DarkRed);
                      if((ScanActivFix-128)*1.575 < 10) {tft.print(" ");} tft.print(byte((ScanActivFix-128)*1.575)); 
                      if((ScanActivFix-128)*1.575 < 10) {tft.print(" ");} break;
    case 192 ... 255: tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_DarkBlue); 
                      if((ScanActivFix-192)*1.575 < 10) {tft.print(" ");} tft.print(byte((ScanActivFix-192)*1.575)); 
                      if((ScanActivFix-128)*1.575 < 10) {tft.print(" ");} break;
  }
}


void TFT_Strobe(int f, int s, byte ScanActivFix) {
  tft.setFont(A16n);
  tft.setCursor(_tw/10*(f+1), _tw/10*(s+1)-_ts*s+_ts);
  tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts, TFT_Black); 
  switch(ScanActivFix) {
    case 0 ... 3:     tft.setCursor(_tw/10*(f+1)+_ts, _tw/10*(s+1)-_ts*s);
                      tft.setFont(A20b); tft.print("S"); break;
    case 4 ... 7:     tft.setCursor(_tw/10*(f+1)+_ts, _tw/10*(s+1)-_ts*s);
                      tft.setFont(A20b); tft.print("O"); break;
    case 8 ... 215:   if ((ScanActivFix-7)*0.48 < 10) { tft.print(" "); }
                      tft.print(byte((ScanActivFix-7)*0.48)); // scale 207 down to 99
                      if ((ScanActivFix-7)*0.48 < 10) { tft.print(" "); } break;
    case 216 ... 255: tft.setCursor(_tw/10*(f+1)+_ts, _tw/10*(s+1)-_ts*s);
                      tft.setFont(A20b); tft.print("O"); break;
  }
}


void TFT_GoboWheel(int f, int s, byte ScanActivFix) {
  tft.setFont(A16n);
  tft.setCursor(_tw/10*(f+1)+_ts, _tw/10*(s+1)-_ts*s); 
  if ((ScanActivFix > 63 && ScanActivFix < 120) || ScanActivFix > 127) {tft.setCursor(_tw/10*(f+1), _tw/10*(s+1)-_ts*s+_ts);}
  tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts, TFT_Black);
  switch(ScanActivFix) {
    case 0 ... 7:     tft.setFont(A20b); tft.print("O"); break;
    case 8 ... 15:    tft.setFont(A8n); tft.print(" "); tft.setFont(A20b); tft.print("1"); break;
    case 16 ... 23:   tft.setFont(A8n); tft.print(" "); tft.setFont(A20b); tft.print("2"); break;
    case 24 ... 31:   tft.setFont(A8n); tft.print(" "); tft.setFont(A20b); tft.print("3"); break;
    case 32 ... 39:   tft.setFont(A8n); tft.print(" "); tft.setFont(A20b); tft.print("4"); break;
    case 40 ... 47:   tft.setFont(A8n); tft.print(" "); tft.setFont(A20b); tft.print("5"); break;
    case 48 ... 55:   tft.setFont(A8n); tft.print(" "); tft.setFont(A20b); tft.print("6"); break;
    case 56 ... 63:   tft.setFont(A8n); tft.print(" "); tft.setFont(A20b); tft.print("7"); break;
    case 64 ... 71:   tft.print("7"); tft.setTextColor(TFT_Red,TFT_Black); tft.print(byte((ScanActivFix-64))); break;
    case 72 ... 79:   tft.print("6"); tft.setTextColor(TFT_Red,TFT_Black); tft.print(byte((ScanActivFix-72))); break;
    case 80 ... 87:   tft.print("5"); tft.setTextColor(TFT_Red,TFT_Black); tft.print(byte((ScanActivFix-80))); break;
    case 88 ... 95:   tft.print("4"); tft.setTextColor(TFT_Red,TFT_Black); tft.print(byte((ScanActivFix-88))); break;
    case 96 ... 103:  tft.print("3"); tft.setTextColor(TFT_Red,TFT_Black); tft.print(byte((ScanActivFix-96))); break;
    case 104 ... 111: tft.print("2"); tft.setTextColor(TFT_Red,TFT_Black); tft.print(byte((ScanActivFix-104))); break;
    case 112 ... 119: tft.print("1"); tft.setTextColor(TFT_Red,TFT_Black); tft.print(byte((ScanActivFix-112))); break;
    case 120 ... 127: tft.setFont(A20b); tft.print("O"); tft.setFont(A16n); break;
    case 128 ... 191: tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_DarkRed); 
                      tft.setTextColor(TFT_White); if((ScanActivFix-128)*1.575 < 10) {tft.print(" ");} 
                      tft.print(byte((ScanActivFix-128)*1.575)); break;
    case 192 ... 255: tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_DarkBlue); 
                      tft.setTextColor(TFT_White); if((ScanActivFix-192)*1.575 < 10) {tft.print(" ");} 
                      tft.print(byte((ScanActivFix-192)*1.575)); break;
  }
}


void TFT_GoboRotate(int f,int s, byte ScanActivFix) {
  tft.setFont(A16n);
  tft.setCursor(_tw/10*(f+1), _tw/10*(s+1)-_ts*s+_ts);
  tft.setTextColor(TFT_White); 
  switch(ScanActivFix) {
    case 0 ... 63:    break;
    case 64 ... 147:  tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_DarkRed); 
                      if((ScanActivFix-64)*1.198 < 10) {tft.print(" ");} tft.print(byte((ScanActivFix-64)*1.198)); break;
    case 148 ... 231: tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_DarkBlue); 
                      if((ScanActivFix-148)*1.198 < 10) {tft.print(" ");} tft.print(byte((ScanActivFix-148)*1.198)); break;
    case 232 ... 255: tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_DarkGray); 
                      if((ScanActivFix-232) < 10) {tft.print(" ");} tft.print(byte((ScanActivFix-232))); break;
  }
}


void TFT_Prisma(int f,int s, byte ScanActivFix) {
  tft.setFont(A16n);
  tft.setCursor(_tw/10*(f+1), _tw/10*(s+1)-_ts*s+_ts);
  tft.setTextColor(TFT_White);
  switch(ScanActivFix) {
    case 0 ... 3:     tft.setCursor(_tw/10*(f+1)+_ts, _tw/10*(s+1)-_ts*s); 
                      tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_Black);
                      tft.setFont(A20b); tft.print("O"); break;
    case 4 ... 127:   tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_DarkRed); 
                      if((ScanActivFix-4)*0.805 < 10) {tft.print(" ");} tft.print(byte((ScanActivFix-4)*0.805)); break;
    case 128 ... 251: tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_DarkBlue); 
                      if((ScanActivFix-128)*0.805 < 10) {tft.print(" ");} tft.print(byte((ScanActivFix-128)*0.805)); break;
    case 252 ... 255: tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_DarkGray); 
                      tft.setCursor(_tw/10*(f+1)+_ts, _tw/10*(s+1)-_ts*s);
                      tft.fillRect(_tw/10*(f+1), _tw/10*(s+1)-_ts*s, _tw/10, _tw/10-_ts*2, TFT_Black);
                      tft.setFont(A20b); tft.print("X"); break;
  }
}


void TFT_Focus(int f,int s, byte ScanActivFix) {
  tft.setFont(A16n);
  tft.setCursor(_tw/10*(f+1), _tw/10*(s+1)-_ts*s+_ts);
  if (ScanActivFix/2.565 < 10) { tft.print(" "); }
  tft.print(byte(ScanActivFix*0.39)); // scale 255 down to 99
  if (ScanActivFix/2.565 < 10) { tft.print(" "); }
}


void TFT_Draw8x8grid() {
  tft.drawLine(_tw/10, _tw/10  -_ts  , _tw/10*9, _tw/10  -_ts  , TFT_DarkGray);
  tft.drawLine(_tw/10, _tw/10*2-_ts*2, _tw/10*9, _tw/10*2-_ts*2, TFT_DarkGray);
  tft.drawLine(_tw/10, _tw/10*3-_ts*3, _tw/10*9, _tw/10*3-_ts*3, TFT_DarkGray);
  tft.drawLine(_tw/10, _tw/10*4-_ts*4, _tw/10*9, _tw/10*4-_ts*4, TFT_DarkGray);
  tft.drawLine(_tw/10, _tw/10*5-_ts*5, _tw/10*9, _tw/10*5-_ts*5, TFT_DarkGray);
  tft.drawLine(_tw/10, _tw/10*6-_ts*6, _tw/10*9, _tw/10*6-_ts*6, TFT_DarkGray);
  tft.drawLine(_tw/10, _tw/10*7-_ts*7, _tw/10*9, _tw/10*7-_ts*7, TFT_DarkGray);
  tft.drawLine(_tw/10, _tw/10*8-_ts*8, _tw/10*9, _tw/10*8-_ts*8, TFT_DarkGray);
  tft.drawLine(_tw/10, _tw/10*9-_ts*9, _tw/10*9, _tw/10*9-_ts*9, TFT_DarkGray);
  
  tft.drawLine(_tw/10  , _tw/10  -_ts, _tw/10  , _tw/10*9-_ts*9, TFT_DarkGray);
  tft.drawLine(_tw/10*2, _tw/10*1-_ts, _tw/10*2, _tw/10*9-_ts*9, TFT_DarkGray);
  tft.drawLine(_tw/10*3, _tw/10*1-_ts, _tw/10*3, _tw/10*9-_ts*9, TFT_DarkGray);
  tft.drawLine(_tw/10*4, _tw/10*1-_ts, _tw/10*4, _tw/10*9-_ts*9, TFT_DarkGray);
  tft.drawLine(_tw/10*5, _tw/10*1-_ts, _tw/10*5, _tw/10*9-_ts*9, TFT_DarkGray);
  tft.drawLine(_tw/10*6, _tw/10*1-_ts, _tw/10*6, _tw/10*9-_ts*9, TFT_DarkGray);
  tft.drawLine(_tw/10*7, _tw/10*1-_ts, _tw/10*7, _tw/10*9-_ts*9, TFT_DarkGray);
  tft.drawLine(_tw/10*8, _tw/10*1-_ts, _tw/10*8, _tw/10*9-_ts*9, TFT_DarkGray);
  tft.drawLine(_tw/10*9, _tw/10*1-_ts, _tw/10*9, _tw/10*9-_ts*9, TFT_DarkGray);
}


void DMXset(unsigned int channel, byte Value) {
  if (channel >= 0 && channel < sizeof(DMXbuffer)) {
    DMXbuffer[channel] = Value;
//    if(Value > 0) { Serial.print(ScanActiv); Serial.print(" "); Serial.print(channel); Serial.print(" "); Serial.print(Value); Serial.print(" = "); Serial.println(DMXbuffer[channel]); }
  }
}


void SetScannerFixture(byte ScanActiv, byte Fixture, byte Value, byte SCANNER_BASE_ADR) {
  if bitRead(ScanActiv,0) { DMXset(SCANNER_BASE_ADR+0*8+Fixture, Value); }
  if bitRead(ScanActiv,1) { DMXset(SCANNER_BASE_ADR+1*8+Fixture, Value); }
  if bitRead(ScanActiv,2) { DMXset(SCANNER_BASE_ADR+2*8+Fixture, Value); }
  if bitRead(ScanActiv,3) { DMXset(SCANNER_BASE_ADR+3*8+Fixture, Value); }
  if bitRead(ScanActiv,4) { DMXset(SCANNER_BASE_ADR+4*8+Fixture, Value); }
  if bitRead(ScanActiv,5) { DMXset(SCANNER_BASE_ADR+5*8+Fixture, Value); }
  if bitRead(ScanActiv,6) { DMXset(SCANNER_BASE_ADR+6*8+Fixture, Value); }
  if bitRead(ScanActiv,7) { DMXset(SCANNER_BASE_ADR+7*8+Fixture, Value); }  
}


void setpixels4x4red() {
  pixels.setPixelColor(17,pixels.Color(1,0,0));
  pixels.setPixelColor(18,pixels.Color(1,0,0));
  pixels.setPixelColor(19,pixels.Color(1,0,0));
  pixels.setPixelColor(20,pixels.Color(1,0,0));
  pixels.setPixelColor(23,pixels.Color(1,0,0));
  pixels.setPixelColor(24,pixels.Color(1,0,0));
  pixels.setPixelColor(25,pixels.Color(1,0,0));
  pixels.setPixelColor(26,pixels.Color(1,0,0));
  pixels.setPixelColor(29,pixels.Color(1,0,0));
  pixels.setPixelColor(30,pixels.Color(1,0,0));
  pixels.setPixelColor(31,pixels.Color(1,0,0));
  pixels.setPixelColor(32,pixels.Color(1,0,0));
  pixels.setPixelColor(35,pixels.Color(1,0,0));
  pixels.setPixelColor(36,pixels.Color(1,0,0));
  pixels.setPixelColor(37,pixels.Color(1,0,0));
  pixels.setPixelColor(38,pixels.Color(1,0,0));
}


void setpixelsfixture(byte FixtureActiv, byte NeoPixelBright) {
  if(bitRead(FixtureActiv,0)==1) { pixels.setPixelColor(16,pixels.Color(0,2+NeoPixelBright,0)); } else { pixels.setPixelColor(16,pixels.Color(0,0,1)); }
  if(bitRead(FixtureActiv,2)==1) { pixels.setPixelColor(22,pixels.Color(0,2+NeoPixelBright,0)); } else { pixels.setPixelColor(22,pixels.Color(0,0,1)); }
  if(bitRead(FixtureActiv,4)==1) { pixels.setPixelColor(28,pixels.Color(0,2+NeoPixelBright,0)); } else { pixels.setPixelColor(28,pixels.Color(0,0,1)); }
  if(bitRead(FixtureActiv,6)==1) { pixels.setPixelColor(34,pixels.Color(0,2+NeoPixelBright,0)); } else { pixels.setPixelColor(34,pixels.Color(0,0,1)); }
  if(bitRead(FixtureActiv,1)==1) { pixels.setPixelColor(21,pixels.Color(0,2+NeoPixelBright,0)); } else { pixels.setPixelColor(21,pixels.Color(0,0,1)); }
  if(bitRead(FixtureActiv,3)==1) { pixels.setPixelColor(27,pixels.Color(0,2+NeoPixelBright,0)); } else { pixels.setPixelColor(27,pixels.Color(0,0,1)); }
  if(bitRead(FixtureActiv,5)==1) { pixels.setPixelColor(33,pixels.Color(0,2+NeoPixelBright,0)); } else { pixels.setPixelColor(33,pixels.Color(0,0,1)); }
  if(bitRead(FixtureActiv,7)==1) { pixels.setPixelColor(39,pixels.Color(0,2+NeoPixelBright,0)); } else { pixels.setPixelColor(39,pixels.Color(0,0,1)); }
}


void setpixelsscanner(byte ScanActiv, byte NeoPixelBright) {
  if(bitRead(ScanActiv,0)==1) { pixels.setPixelColor(16,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); } else { pixels.setPixelColor(16,pixels.Color(0,0,1)); }
  if(bitRead(ScanActiv,2)==1) { pixels.setPixelColor(22,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); } else { pixels.setPixelColor(22,pixels.Color(0,0,1)); }
  if(bitRead(ScanActiv,4)==1) { pixels.setPixelColor(28,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); } else { pixels.setPixelColor(28,pixels.Color(0,0,1)); }
  if(bitRead(ScanActiv,6)==1) { pixels.setPixelColor(34,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); } else { pixels.setPixelColor(34,pixels.Color(0,0,1)); }
  if(bitRead(ScanActiv,1)==1) { pixels.setPixelColor(21,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); } else { pixels.setPixelColor(21,pixels.Color(0,0,1)); }
  if(bitRead(ScanActiv,3)==1) { pixels.setPixelColor(27,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); } else { pixels.setPixelColor(27,pixels.Color(0,0,1)); }
  if(bitRead(ScanActiv,5)==1) { pixels.setPixelColor(33,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); } else { pixels.setPixelColor(33,pixels.Color(0,0,1)); }
  if(bitRead(ScanActiv,7)==1) { pixels.setPixelColor(39,pixels.Color(2+NeoPixelBright,2+NeoPixelBright,0)); } else { pixels.setPixelColor(39,pixels.Color(0,0,1)); }
}


void drawFixtures(byte ScanActiv, byte ScanActivFixture[72]) {
  
  tft.fillRect(_clx, _cly, _clw, _clh, TFT_Black); // clear
  tft.fillRect(0, _tw/10*9-_ts*9, _tw, _ts*2, TFT_Black); // only for the last row to delete the square selection  

  tft.setRotation(0); // rotate 0°
  tft.setTextColor(TFT_Gray);
  tft.setCursor(_ms+_ts, _tw/10*1+_ts); tft.setFont(A18n); tft.println("Pan");
  tft.setCursor(_ms+_ts, _tw/10*2+_ts); tft.setFont(A18n); tft.println("Tilt");
  tft.setCursor(_ms+_ts, _tw/10*3+_ts); tft.setFont(A18n); tft.println("Color");
  tft.setCursor(_ms+_ts, _tw/10*4+_ts); tft.setFont(A18n); tft.println("Strobe");
  tft.setCursor(_ms+_ts, _tw/10*5+_ts); tft.setFont(A18n); tft.println("Gobo");
  tft.setCursor(_ms+_ts, _tw/10*6+_ts); tft.setFont(A18n); tft.println("Rotate");
  tft.setCursor(_ms+_ts, _tw/10*7+_ts); tft.setFont(A18n); tft.println("Prisma");
  tft.setCursor(_ms+_ts, _tw/10*8+_ts); tft.setFont(A18n); tft.println("Focus");
  tft.setRotation(1); // rotate 90°
  
  tft.setTextColor(TFT_Gray);
  for (int s = 0; s < 8; s++ ) {
    for (int f = 0; f < 8; f++ ) {
      if (bitRead(ScanActiv, s) == 1 || s < 4) {
        if (bitRead(ScanActivFixture[64+s], f) == 1) { 
          if (f==1||f==4||f==6) { tft.setTextColor(TFT_LightCyan); } 
          else { tft.setTextColor(TFT_Yellow); }
        }
        else { 
          if (f==1||f==4||f==6) { tft.setTextColor(TFT_LightGray); } 
          else { tft.setTextColor(TFT_Gray); }
        }
        if (f==2) { TFT_ColorWheel(f, s, ScanActivFixture[f+s*8]); }
        else if (f==3) { TFT_Strobe(f, s, ScanActivFixture[f+s*8]); }
        else if (f==4) { TFT_GoboWheel(f, s, ScanActivFixture[f+s*8]); }
        else if (f==5) { TFT_GoboRotate(f, s, ScanActivFixture[f+s*8]); }
        else if (f==6) { TFT_Prisma(f, s, ScanActivFixture[f+s*8]); }
        else { TFT_Focus(f, s, ScanActivFixture[f+s*8]); } // f=0 Pan, f=1 Tilt, f=7 Focus
      }
    }
  }
  TFT_Draw8x8grid();
  
}


void setTFTscanner(byte ScanActiv, byte rightLCDView, byte leftLCDView, byte ScanActivFixture[72]) {
  int16_t txtX; int16_t txtY; uint16_t txtW; uint16_t txtH;

  if(bitRead(ScanActiv,0)==1) {tft.setTextColor(TFT_Yellow);} else {tft.setTextColor(TFT_Gray);}
  tft.setCursor(0, _c1-_ts*11);
  tft.setFont(A20b); tft.print("1");

  if(bitRead(ScanActiv,2)==1) {tft.setTextColor(TFT_Yellow);} else {tft.setTextColor(TFT_Gray);}
  tft.setCursor(0, _c2-_ts*9);
  tft.setFont(A20b); tft.print("3");

  if(bitRead(ScanActiv,4)==1) {tft.setTextColor(TFT_Yellow);} else {tft.setTextColor(TFT_Gray);}
  tft.setCursor(0, _c3-_ts*7);
  tft.setFont(A20b); tft.print("5");

  if(bitRead(ScanActiv,6)==1) {tft.setTextColor(TFT_Yellow);} else {tft.setTextColor(TFT_Gray);}
  tft.setCursor(0, _c4-_ts*5);
  tft.setFont(A20b); tft.print("7");

  if(bitRead(ScanActiv,1)==1) {tft.setTextColor(TFT_Yellow);} else {tft.setTextColor(TFT_Gray);}
  tft.setTextWrap(false);
  tft.getTextBounds(" 2", 0, 0, &txtX, &txtY, &txtW, &txtH);
  tft.setCursor(_tw-txtW, _c1);
  tft.setFont(A20n); tft.print(" ");
  tft.setFont(A20b); tft.print("2");

  if(bitRead(ScanActiv,3)==1) {tft.setTextColor(TFT_Yellow);} else {tft.setTextColor(TFT_Gray);}
  tft.getTextBounds(" 4", 0, 0, &txtX, &txtY, &txtW, &txtH);
  tft.setCursor(_tw-txtW, _c2+_ts*2);
  tft.setFont(A20n); tft.print(" ");
  tft.setFont(A20b); tft.print("4");

  if(bitRead(ScanActiv,5)==1) {tft.setTextColor(TFT_Yellow);} else {tft.setTextColor(TFT_Gray);}
  tft.getTextBounds(" 6", 0, 0, &txtX, &txtY, &txtW, &txtH);
  tft.setCursor(_tw-txtW, _c3+_ts*4);
  tft.setFont(A20n); tft.print(" ");
  tft.setFont(A20b); tft.print("6");

  if(bitRead(ScanActiv,7)==1) {tft.setTextColor(TFT_Yellow);} else {tft.setTextColor(TFT_Gray);}
  tft.getTextBounds(" 8", 0, 0, &txtX, &txtY, &txtW, &txtH);
  tft.setCursor(_tw-txtW, _c4+_ts*6);
  tft.setFont(A20n); tft.print(" ");
  tft.setFont(A20b); tft.print("8");
  
}


byte setTFTProgMode(byte ScanActiv, byte leftLCDView, byte rightLCDView, byte preScanActiv) {
// scanner 1
  if(bitRead(ScanActiv,0)!=bitRead(preScanActiv,0)) {
    if(bitRead(ScanActiv,0)==1) { tft.fillRect(0, _tty, _tw/10*1, _tw/8+_ts, TFT_Yellow); tft.setTextColor(TFT_Black); } 
    else { tft.fillRect(0, _tty, _tw/10*1, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    tft.setCursor(_ts*2, _tty+_ts*3);
    tft.setFont(A20b); tft.print("1"); }
// scanner 3  
  if(bitRead(ScanActiv,2)!=bitRead(preScanActiv,2)) {
    if(bitRead(ScanActiv,2)==1) { tft.fillRect(0, _tty+_tw/8+_ts*3, _tw/10*1, _tw/8+_ts, TFT_Yellow); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(0, _tty+_tw/8+_ts*3, _tw/10*1, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    tft.setCursor(_ts*2, _tty+_tw/8+_ts*6);
    tft.setFont(A20b); tft.print("3"); }
// scanner 5
  if(bitRead(ScanActiv,4)!=bitRead(preScanActiv,4)) {
    if(bitRead(ScanActiv,4)==1) { tft.fillRect(0, _tty+_tw/8*2+_ts*6, _tw/10*1, _tw/8+_ts, TFT_Yellow); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(0, _tty+_tw/8*2+_ts*6, _tw/10*1, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    tft.setCursor(_ts*2, _tty+_tw/8*2+_ts*9);
    tft.setFont(A20b); tft.print("5"); }
// scanner 7  
  if(bitRead(ScanActiv,6)!=bitRead(preScanActiv,6)) {
    if(bitRead(ScanActiv,6)==1) { tft.fillRect(0, _tty+_tw/8*3+_ts*9, _tw/10*1, _tw/8+_ts, TFT_Yellow); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(0, _tty+_tw/8*3+_ts*9, _tw/10*1, _tw/8+_ts, TFT_Black);  tft.setTextColor(TFT_Gray);}
    tft.setCursor(_ts*2, _tty+_tw/8*3+_ts*12);
    tft.setFont(A20b); tft.print("7"); }
// scanner 2 
  if(bitRead(ScanActiv,1)!=bitRead(preScanActiv,1)) {
    if(bitRead(ScanActiv,1)==1) { tft.fillRect(_tw-(_tw/10*1), _tty, _tw/10*1, _tw/8+_ts, TFT_Yellow); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(_tw-(_tw/10*1), _tty, _tw/10*1, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    tft.setCursor(_tw-_ts*10, _tty+_ts*3);
    tft.setFont(A20b); tft.print("2"); }
// scanner 4
  if(bitRead(ScanActiv,3)!=bitRead(preScanActiv,3)) {
    if(bitRead(ScanActiv,3)==1) { tft.fillRect(_tw-(_tw/10*1), _tty+_tw/8+_ts*3, _tw/10*1, _tw/8+_ts, TFT_Yellow); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(_tw-(_tw/10*1), _tty+_tw/8+_ts*3, _tw/10*1, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    tft.setCursor(_tw-_ts*10, _tty+_tw/8+_ts*6);
    tft.setFont(A20b); tft.print("4"); }
// scanner 6
  if(bitRead(ScanActiv,5)!=bitRead(preScanActiv,5)) {
    if(bitRead(ScanActiv,5)==1) { tft.fillRect(_tw-(_tw/10*1), _tty+_tw/8*2+_ts*6, _tw/10*1, _tw/8+_ts, TFT_Yellow); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(_tw-(_tw/10*1), _tty+_tw/8*2+_ts*6, _tw/10*1, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    tft.setCursor(_tw-_ts*10, _tty+_tw/8*2+_ts*9);
    tft.setFont(A20b); tft.print("6"); }
// scanner 8
  if(bitRead(ScanActiv,7)!=bitRead(preScanActiv,7)) {
    if(bitRead(ScanActiv,7)==1) { tft.fillRect(_tw-(_tw/10*1), _tty+_tw/8*3+_ts*9, _tw/10*1, _tw/8+_ts, TFT_Yellow); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(_tw-(_tw/10*1), _tty+_tw/8*3+_ts*9, _tw/10*1, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    tft.setCursor(_tw-_ts*10, _tty+_tw/8*3+_ts*12);
    tft.setFont(A20b); tft.print("8"); }
    
  preScanActiv = ScanActiv;
  return preScanActiv;
}


byte setTFTfixture(byte FixtureActiv, byte leftLCDView, byte rightLCDView, byte preFixtureActiv, byte ScanSpdMove) {
  int16_t txtX; int16_t txtY; uint16_t txtW; uint16_t txtH; String ScanMotionText;

// fixture 1
  if(bitRead(FixtureActiv,0)!=bitRead(preFixtureActiv,0)) {
    if(bitRead(FixtureActiv,0)==1) { tft.fillRect(_tw/10*1, _tty, _tw/10*4-_ts, _tw/8+_ts, TFT_DarkGreen); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(_tw/10*1, _tty, _tw/10*4-_ts, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    if(leftLCDView==0) {tft.setTextColor(TFT_White);}
    tft.setCursor(_tw/10+_ts*2, _tty+_ts*3);
    tft.setFont(A20n); tft.print("Pan"); }
// fixture 3  
  if(bitRead(FixtureActiv,2)!=bitRead(preFixtureActiv,2)) {
    if(bitRead(FixtureActiv,2)==1) { tft.fillRect(_tw/10*1, _tty+_tw/8+_ts*3, _tw/10*4-_ts, _tw/8+_ts, TFT_DarkGreen); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(_tw/10*1, _tty+_tw/8+_ts*3, _tw/10*4-_ts, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    if(leftLCDView==1) {tft.setTextColor(TFT_White);}
    tft.setCursor(_tw/10+_ts*2, _tty+_tw/8+_ts*6);
    tft.setFont(A20n); tft.print("Color"); }
// fixture 5
  if(bitRead(FixtureActiv,4)!=bitRead(preFixtureActiv,4)) {
    if(bitRead(FixtureActiv,4)==1) { tft.fillRect(_tw/10*1, _tty+_tw/8*2+_ts*6, _tw/10*4-_ts, _tw/8+_ts, TFT_DarkGreen); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(_tw/10*1, _tty+_tw/8*2+_ts*6, _tw/10*4-_ts, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    if(leftLCDView==2) {tft.setTextColor(TFT_White);}
    tft.setCursor(_tw/10+_ts*2, _tty+_tw/8*2+_ts*9);
    tft.setFont(A20n); tft.print("Gobo"); }
// fixture 7
  if(bitRead(FixtureActiv,6)!=bitRead(preFixtureActiv,6)) {
    if(bitRead(FixtureActiv,6)==1) { tft.fillRect(_tw/10*1, _tty+_tw/8*3+_ts*9, _tw/10*4-_ts, _tw/8+_ts, TFT_DarkGreen); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(_tw/10*1, _tty+_tw/8*3+_ts*9, _tw/10*4-_ts, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    if(leftLCDView==3) {tft.setTextColor(TFT_White);}
    tft.setCursor(_tw/10+_ts*2, _tty+_tw/8*3+_ts*12);
    tft.setFont(A20n); tft.print("Prisma"); }
// fixture 2
  if(bitRead(FixtureActiv,1)!=bitRead(preFixtureActiv,1)) {
    if(bitRead(FixtureActiv,1)==1) { tft.fillRect(_tw/2+_ts, _tty, _tw/10*4-_ts, _tw/8+_ts, TFT_DarkGreen); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(_tw/2+_ts, _tty, _tw/10*4-_ts, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    if(rightLCDView==0) {tft.setTextColor(TFT_White);}
    tft.setCursor(_tw/2, _tty+_ts*3);
    tft.setFont(A20n); tft.print("       Tilt"); }
// fixture 4
  if(bitRead(FixtureActiv,3)!=bitRead(preFixtureActiv,3)) {
    if(bitRead(FixtureActiv,3)==1) { tft.fillRect(_tw/2+_ts, _tty+_tw/8+_ts*3, _tw/10*4-_ts, _tw/8+_ts, TFT_DarkGreen); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(_tw/2+_ts, _tty+_tw/8+_ts*3, _tw/10*4-_ts, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    if(rightLCDView==1) {tft.setTextColor(TFT_White);}
    tft.setCursor(_tw/2, _tty+_tw/8+_ts*6);
    tft.setFont(A20n); tft.print(" Strobe"); }
// fixture 6
  if(bitRead(FixtureActiv,5)!=bitRead(preFixtureActiv,5)) {
    if(bitRead(FixtureActiv,5)==1) { tft.fillRect(_tw/2+_ts, _tty+_tw/8*2+_ts*6, _tw/10*4-_ts, _tw/8+_ts, TFT_DarkGreen); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(_tw/2+_ts, _tty+_tw/8*2+_ts*6, _tw/10*4-_ts, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    if(rightLCDView==2) {tft.setTextColor(TFT_White);}
    tft.setCursor(_tw/2, _tty+_tw/8*2+_ts*9);
    tft.setFont(A20n); tft.print(" Rotate"); }
// fixture 8
  if(bitRead(FixtureActiv,7)!=bitRead(preFixtureActiv,7)) {
    if(bitRead(FixtureActiv,7)==1) { tft.fillRect(_tw/2+_ts, _tty+_tw/8*3+_ts*9, _tw/10*4-_ts, _tw/8+_ts, TFT_DarkGreen); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(_tw/2+_ts, _tty+_tw/8*3+_ts*9, _tw/10*4-_ts, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    if(rightLCDView==3) {tft.setTextColor(TFT_White);}
    tft.setCursor(_tw/2, _tty+_tw/8*3+_ts*12);
    tft.setFont(A20n); tft.print("  Focus"); }

    
// scanner movements

  if ( ScanSpdMove != preScanSpdMove ) {  
    if ((ScanSpdMove & 0b00001111) > 0 || (ScanSpdMove & 0b00011111)-11 > 0) { tft.fillRect(0, _tty+_tw/8*4+_ts*12, _tw, _tw/8+_ts, TFT_DarkRed); tft.setTextColor(TFT_Black); }
    else { tft.fillRect(0, _tty+_tw/8*4+_ts*12, _tw, _tw/8+_ts, TFT_Black); tft.setTextColor(TFT_Gray); }
    tft.setFont(A20n);

    if(leftLCDView==4) { tft.setTextColor(TFT_White); }
    tft.setCursor(_ts*3, _tty+_tw/8*4+_ts*15);
    if ((ScanSpdMove & 0b00011111) > 10) { tft.print("Free"); } else { tft.print("Beats"); }

    if ( rightLCDView==4 ) { tft.setTextColor(TFT_White); }
    else { tft.setTextColor(TFT_Gray); }
    switch(ScanSpdMove>>5) {
      case 0: ScanMotionText = "Left-Right"; break;
      case 1: ScanMotionText = "Up-Down"; break;
      case 2: ScanMotionText = "Circle Right"; break;
      case 3: ScanMotionText = "Circle Left"; break;
      case 4: ScanMotionText = "Swing"; break;
      case 5: ScanMotionText = "Wave"; break;
      case 6: ScanMotionText = "Diagonal LU"; break;
      case 7: ScanMotionText = "Diagonal RU"; break;
    }
    tft.getTextBounds(ScanMotionText, 0, 0, &txtX, &txtY, &txtW, &txtH);
    tft.setCursor(_tw-txtW-_ts*4, _tty+_tw/8*4+_ts*15);
    tft.print(ScanMotionText);
  }
  
  preScanSpdMove = ScanSpdMove;
  preFixtureActiv = FixtureActiv;
  return preFixtureActiv;
}


void drawFixtureSelected(byte ScanSelected, byte leftnewPos) {
  if ( ScanSelected > 0) {
    tft.drawRect(_tw/10*(leftnewPos+1), _tw/10*ScanSelected-_ts*ScanSelected,   _tw/10+1, _tw/10-_ts+1, TFT_Magenta);
    tft.drawRect(_tw/10*(leftnewPos+1)-1, _tw/10*ScanSelected-_ts*ScanSelected-1, _tw/10+3, _tw/10-_ts+3, TFT_Magenta);
    tft.drawRect(_tw/10*(leftnewPos+1)-2, _tw/10*ScanSelected-_ts*ScanSelected-2, _tw/10+5, _tw/10-_ts+5, TFT_Magenta);
  }  
}


void TFTnumber(byte Number) {
  if (Number < 10) { tft.print(" "); }
  if (Number < 100) { tft.print(" "); }
  tft.print(Number);
  if (Number < 10) { tft.print(" "); }
  if (Number < 100) { tft.print(" "); }
}


void TFT_Draw_Count() {
  tft.fillRect(_clx, _cly, _clw, _clh, LCD_bck_Color); // clear
  
  int i = _ncx1;
  if (Count_8x8 % (CountLenght + 1) + 1 >= 100) {
    tft.drawBitmap(_ncx100, _ncy, TFT_ + (((Count_8x8 % (CountLenght + 1) + 1) / 100) % 10 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color);
    tft.drawBitmap(i, _ncy, TFT_ + (((Count_8x8 % (CountLenght + 1) + 1) / 10) % 10 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color);
    i = _i3;
  }
  else if (Count_8x8 % (CountLenght + 1) + 1 >= 10)  {
    tft.drawBitmap(_ncx10, _ncy, TFT_ + (((Count_8x8 % (CountLenght + 1) + 1) / 10) % 10 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color);
    i = _i2;
  }
  tft.drawBitmap(i, _ncy, TFT_ + ((Count_8x8 % (CountLenght + 1) + 1) % 10 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color); // 1-9 320 ( char 64x40 )
}


void TFT_Draw_BPM( unsigned long TFTbpm ) {
  tft.fillRect(_clx, _cly, _clw, _clh, LCD_bck_Color); // clear
  
  int i = _ncx1;
  if (TFTbpm >= 100) {
    tft.drawBitmap(_ncx100, _ncy, TFT_ + ((TFTbpm / 100) % 10 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color);
    tft.drawBitmap(i, _ncy, TFT_ + ((TFTbpm / 10) % 10 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color);
    i = _i3;
  }
  else if (TFTbpm >= 10)  {
    tft.drawBitmap(_ncx10, _ncy, TFT_ + ((TFTbpm / 10) % 10 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color);
    i = _i2;
  }
  tft.drawBitmap(i, _ncy, TFT_ + (TFTbpm % 10 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color); // 1-9 320 ( char 64x40 )
}


void viewStatus(byte UnitsView, byte ProgMode, byte shift, byte leftEncPressed, byte leftLCDView, 
                byte leftnewPos, byte rightEncPressed, byte rightLCDView, byte rightnewPos) {
  tft.setFont();
  tft.setCursor(0,0);
  tft.setTextSize(2);
  tft.setTextColor(TFT_LightGray, TFT_Black);
  tft.print("UV");
  tft.setTextColor(TFT_Yellow, TFT_Black);
  tft.print(UnitsView);
  tft.setTextColor(TFT_LightGray, TFT_Black);
  tft.print(" PM");
  tft.setTextColor(TFT_Yellow, TFT_Black);
  tft.print(ProgMode);
  tft.setTextColor(TFT_LightGray, TFT_Black);
  tft.print(" L");
  tft.setTextColor(TFT_Yellow, TFT_Black);
  tft.print(leftEncPressed);
  tft.setTextColor(TFT_LightGray, TFT_Black);
  tft.print(" lV");
  tft.setTextColor(TFT_Yellow, TFT_Black);
  tft.print(leftLCDView);
  tft.setTextColor(TFT_LightGray, TFT_Black);
  tft.print(" P");
  tft.setTextColor(TFT_Yellow, TFT_Black);
  TFTnumber(leftnewPos);

  tft.setCursor(0,22);
  tft.setTextColor(TFT_LightGray, TFT_Black);
  tft.print(" S");
  tft.setTextColor(TFT_Yellow, TFT_Black);
  tft.print(shift);
  tft.setTextColor(TFT_LightGray, TFT_Black);
  tft.print("   ");
  tft.setTextColor(TFT_Yellow, TFT_Black);
  tft.print(" ");
  tft.setTextColor(TFT_LightGray, TFT_Black);
  tft.print(" R");
  tft.setTextColor(TFT_Yellow, TFT_Black);
  tft.print(rightEncPressed);
  tft.setTextColor(TFT_LightGray, TFT_Black);
  tft.print(" rV");
  tft.setTextColor(TFT_Yellow, TFT_Black);
  tft.print(rightLCDView);
  tft.setTextColor(TFT_LightGray, TFT_Black);
  tft.print(" P");
  tft.setTextColor(TFT_Yellow, TFT_Black);
  TFTnumber(rightnewPos);
}

/*
  tft.setFont();
  tft.setCursor(0,44);
  tft.setTextSize(2);
  tft.setTextColor(TFT_LightGray, TFT_Black);
  tft.print("P");
  tft.setTextColor(TFT_Red, TFT_Black);
  tft.print(rightPos-rightnewPos);
  tft.print("-");
  tft.print(rightnewPos);
  tft.print("-");
  tft.print(rightEnc.read());
*/

/// Subroutines ###############################################################
