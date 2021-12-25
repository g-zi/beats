// DMX Cameo Pixbar ###################################################################
// CH1 Dimmer; CH2 Strobe; CH3 Red; CH4 Green; CH5 Blue...CH26; CH27 Macro; CH28 Temperature; CH29 Pattern; CH30 Sound
// Flash: 28-Counter*2 ; 56-Counter*4 ; 112-Counter*8 ; 224-Counter*16
// CAMEO_BASE_ADR = DMXBase;

if((DMXUnits & 0b00000011) > 0) {

  DMXset(CAMEO_BASE_ADR, DMXBright); // set dimmer
  /*
    Serial.print("Count: ");
    Serial.print(Count_8x8, DEC);
    Serial.print("  ");
    Serial.print(Count_8x8 % 32, DEC);
    Serial.print("  ");
    Serial.print((Count_8x8>>2)%8, DEC);
    Serial.print("  ");
    Serial.print((Count_8x8>>2)%8, DEC);
  */

  if (((Count_8x8 % 32) == 0) && (Counter < 1)) { // clear all
    for (int i = 0; i < 24; i++) {
      pixbar[i] = 0;
    }
  }
  DMXset(CAMEO_BASE_ADR + 1, 0); // Strobe open

// color change, pattern and sound control
  if (DMXPixbar == 13)
  { // x0D Color change CH27
    DMXset((CAMEO_BASE_ADR + 26), (Count_8x8 % 32) * 2 + 6);
  }
  else DMXset((CAMEO_BASE_ADR + 26), 0); // Color off

  if (DMXPixbar == 14)
  { // x0E Color pattern CH29
    DMXset((CAMEO_BASE_ADR + 28), DMXPattern / 5 + 8);
  }
  else DMXset((CAMEO_BASE_ADR + 28), 0); // Pattern off

  if (DMXPixbar == 15)
  { // x0F Sound control CH30
    DMXset((CAMEO_BASE_ADR + 29), DMXPattern);
  }
  else DMXset((CAMEO_BASE_ADR + 29), 0); // Sound off
/// color change, pattern and sound control


  // complex counter
  if (DMXPixbar > 5 && DMXPixbar < 13)
  {
    if ((Count_8x8 % 1) == 0 && (Counter < 15)) { // Yellow, every beat

      if (Count_8x8 % 4 > 0) { // switch off last
        pixbar[((Count_8x8) % 4) * 6 - 6] = 0; // RED
        pixbar[((Count_8x8) % 4) * 6 - 5] = 0; // GREEN
        pixbar[((Count_8x8) % 4) * 6 - 4] = 0; // BLUE
        pixbar[((Count_8x8) % 4) * 6 - 3] = 0; // RED
        pixbar[((Count_8x8) % 4) * 6 - 2] = 0; // GREEN
        pixbar[((Count_8x8) % 4) * 6 - 1] = 0; // BLUE
      }
      else {
        pixbar[18] = 0; // RED
        pixbar[19] = 0; // GREEN
        pixbar[20] = 0; // BLUE
        pixbar[21] = 0; // RED
        pixbar[22] = 0; // GREEN
        pixbar[23] = 0; // BLUE
      }

      if (((Count_8x8 % 32) == 0) && (Counter < 1)) { // clear
        for (int i = 0; i < 24; i++) {
          pixbar[i] = 0;
        }
      }

      RED = 0;
      GREEN = 255;
      BLUE = 0;
      if ((Count_8x8 % 32) >= 0 && Counter < 15 ) { // 1st bar
        pixbar[0] = RED;
        pixbar[1] = GREEN;
        pixbar[2] = BLUE;
      }
      if ((Count_8x8 % 32) > 3 && Counter < 15 ) { // 2nd bar
        pixbar[3] = RED;
        pixbar[4] = GREEN;
        pixbar[5] = BLUE;
      }
      if ((Count_8x8 % 32) > 7 && Counter < 15 ) { // 3rd bar
        pixbar[6] = RED;
        pixbar[7] = GREEN;
        pixbar[8] = BLUE;
      }
      if ((Count_8x8 % 32) > 11 && Counter < 15 ) { // 4th bar
        pixbar[9] = RED;
        pixbar[10] = GREEN;
        pixbar[11] = BLUE;
      }
      RED = 0;
      GREEN = 255;
      BLUE = 255;
      if ((Count_8x8 % 32) > 15 && Counter < 15 ) { // 5th bar
        pixbar[12] = RED;
        pixbar[13] = GREEN;
        pixbar[14] = BLUE;
      }
      if ((Count_8x8 % 32) > 19 && Counter < 15 ) { // 6th bar
        pixbar[15] = RED;
        pixbar[16] = GREEN;
        pixbar[17] = BLUE;
      }
      if ((Count_8x8 % 32) > 23 && Counter < 15 ) { // 7th bar
        pixbar[18] = RED;
        pixbar[19] = GREEN;
        pixbar[20] = BLUE;
      }
      if ((Count_8x8 % 32) > 27 && Counter < 15 ) { // 8th bar
        pixbar[21] = RED;
        pixbar[22] = GREEN;
        pixbar[23] = BLUE;
      }

      // Yellow flashing, every beat
      if (DMXPixbar > 6)
      {
        pixbar[0] = 224 - Counter * 16;
        pixbar[1] = 224 - Counter * 16;
        pixbar[2] = 0;
        if ((Count_8x8 % 32) > 15 && (DMXPixbar > 6)) { // 16 beats +
          pixbar[12] = 224 - Counter * 16;
          pixbar[13] = 224 - Counter * 16;
          pixbar[14] = 0;
        }
      }

      if (DMXPixbar > 8)
      {
        if (((Count_8x8) % 32) < 16 ) { // flashing
          RED = 112 - Counter * 8;
          GREEN = 0;
          BLUE = 112 - Counter * 8;
        }
        else {
          RED = 224 - Counter * 16;
          GREEN = 0;
          BLUE = 0;
        }
      }

      if (((Count_8x8 % 32) > 27 || (Count_8x8 % 32) == 0) && DMXPixbar > 10) 
      { // all 8 LED's
        for (int i = 0; i < 8; i++) {
          pixbar[i * 3] = RED;
          pixbar[i * 3 + 1] = GREEN;
          pixbar[i * 3 + 2] = BLUE;
        }
      }

      if (DMXPixbar < 9 || DMXPixbar == 12) 
      { // Blue, every beat
        byte RED1 = 0; if ((Count_8x8 % 32) > 15) RED1 = 224 - Counter * 16;
        pixbar[((Count_8x8) % 4) * 6] = RED1;           // RED
        pixbar[((Count_8x8) % 4) * 6 + 1] = 0;          // GREEN
        pixbar[((Count_8x8) % 4) * 6 + 2] = 224 - Counter * 16; // BLUE

        pixbar[((Count_8x8) % 4) * 6 + 3] = RED1;       // RED
        pixbar[((Count_8x8) % 4) * 6 + 4] = 0;          // GREEN
        pixbar[((Count_8x8) % 4) * 6 + 5] = 224 - Counter * 16; // BLUE
      }

      if ((Count_8x8 % 4) == 0 && DMXPixbar > 9) 
      { // 4 LED's right
        for (int i = 4; i < 8; i++) {
          pixbar[i * 3] = RED;
          pixbar[i * 3 + 1] = GREEN;
          pixbar[i * 3 + 2] = BLUE;
        }
      }
      
      if (Count_8x8 % 32 == 26 && DMXPixbar > 9) 
      { // 4 LED's left
        for (int i = 0; i < 4; i++) {
          pixbar[i * 3] = RED;
          pixbar[i * 3 + 1] = GREEN;
          pixbar[i * 3 + 2] = BLUE;
        }
      }
    }

    if (Counter < 5) {
      DMXset(CAMEO_BASE_ADR, (16 - Counter) * DMXBright / 8);  // flash beats
    }
      
  }
  /// complex counter



  // medium counter
  if ((DMXPixbar == 3) || (DMXPixbar == 4) || (DMXPixbar == 5)) 
  { // 3 = static + 4 = last count flash + 5 = 1st beat flash yellow
    if (Count_8x8 % 4 > 0) { // switch off last
      pixbar[((Count_8x8) % 4) * 6 - 6] = 0; // RED
      pixbar[((Count_8x8) % 4) * 6 - 5] = 0; // GREEN
      pixbar[((Count_8x8) % 4) * 6 - 4] = 0; // BLUE
      pixbar[((Count_8x8) % 4) * 6 - 3] = 0; // RED
      pixbar[((Count_8x8) % 4) * 6 - 2] = 0; // GREEN
      pixbar[((Count_8x8) % 4) * 6 - 1] = 0; // BLUE
    }
    else {
      pixbar[18] = 0; // RED
      pixbar[19] = 0; // GREEN
      pixbar[20] = 0; // BLUE
      pixbar[21] = 0; // RED
      pixbar[22] = 0; // GREEN
      pixbar[23] = 0; // BLUE
    }

    if (((Count_8x8 % 32) == 0) && (Counter < 1)) { // clear
      for (int i = 0; i < 24; i++) {
        pixbar[i] = 0;
      }
    }

    RED = 255; // flash last 4 beats
    if (((Count_8x8 % 32) > 27 || (Count_8x8 % 32) == 24 || (Count_8x8 % 32) == 26) && (DMXPixbar == 4 || DMXPixbar == 5)) 
    {
      RED = 224 - Counter * 8;
    }
    for (int i = 0; i < (Count_8x8 >> 2) % 8; i++) { // count bars
      pixbar[i * 3] = RED;
      pixbar[i * 3 + 1] = 0;
      pixbar[i * 3 + 2] = 0;
    }

    byte RED1 = 0; // blue counting 4/4th
    byte RED2 = 0;
    if ((Count_8x8 >> 2) % 8 > (Count_8x8) % 4 * 2) {
      RED1 = 224 - Counter * 8;
    }
    if ((Count_8x8 >> 2) % 8 > (Count_8x8) % 4 * 2 + 1) {
      RED2 = 224 - Counter * 8;
    }
    pixbar[((Count_8x8) % 4) * 6] = RED1; // RED
    pixbar[((Count_8x8) % 4) * 6 + 1] = 0; // GREEN
    pixbar[((Count_8x8) % 4) * 6 + 2] = 224 - Counter * 8; // BLUE
    pixbar[((Count_8x8) % 4) * 6 + 3] = RED2; // RED
    pixbar[((Count_8x8) % 4) * 6 + 4] = 0; // GREEN
    pixbar[((Count_8x8) % 4) * 6 + 5] = 224 - Counter * 8; // BLUE

    if (Counter < 5) {
      DMXset(CAMEO_BASE_ADR, (16 - Counter)*DMXBright / 8);  // flash beats
    }

  }
  /// medium counter



  // easy counter
  if ((DMXPixbar == 1) || (DMXPixbar == 2)) 
  { // 1 = static; 2 = last count flash
    if (((Count_8x8) % 32) < 8 ) { //
      RED = 0;
      GREEN = 255;
      BLUE = 0;
    }
    else if (((Count_8x8) % 32) < 16 ) {
      RED = 255;
      GREEN = 0;
      BLUE = 255;
    }
    else if (((Count_8x8) % 32) < 24 ) {
      RED = 255;
      GREEN = 255;
      BLUE = 0;
    }
    else if (((Count_8x8) % 32) < 32 ) {
      RED = 255;
      GREEN = 0;
      BLUE = 0;
    }

    if (Counter < 5) {
      DMXset(CAMEO_BASE_ADR, (16 - Counter)*DMXBright / 8);  // flash beats via master dimmer
    }

    if (((Count_8x8 % 32) > 27 || (Count_8x8 % 32) == 24 || (Count_8x8 % 32) == 26) && (DMXPixbar == 2)) 
    { // last count flash via master dimmer
      if (Counter < 5) {
        DMXset(CAMEO_BASE_ADR, 0);  // set dimmer
      }
    }

    pixbar[(((Count_8x8) >> 2) % 8) * 3] = RED; // RED
    pixbar[(((Count_8x8) >> 2) % 8) * 3 + 1] = GREEN; // GREEN
    pixbar[(((Count_8x8) >> 2) % 8) * 3 + 2] = BLUE; // BLUE
  }
  /// easy counter


  if ((Count_8x8 % 32) == 0 && Counter < 15) { // 1st beat flash, color yellow
    RED = 224 - Counter * 16;
    GREEN = 224 - Counter * 16;
    BLUE = 0;
    for (int i = 0; i < 8; i++) { // write all LEDs
      pixbar[i * 3] = RED;
      pixbar[i * 3 + 1] = GREEN;
      pixbar[i * 3 + 2] = BLUE;
    }
  }

  for (int i = 0; i < 24; i++) { // write to Cameo 8 LED Pixbar
    DMXset((CAMEO_BASE_ADR + 2) + i, pixbar[i]);
  }
  
}    
/// DMX Cameo Pixbar ###################################################################
