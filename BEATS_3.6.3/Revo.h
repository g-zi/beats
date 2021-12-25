// DMX REVO IV; 1-256 lower left 1, upper right 256 ############################################

    byte REVO_BASE_ADR = DMXBase+30; // 256 channels

    // number counting
    for ( COLOR=1; COLOR<5; COLOR++) {
      DMX_LED = 0;
      if (COLOR==2 && (Count_DMX % 32) < 16) { DMX_LED = 255; }
      else if (COLOR==3 && (Count_DMX % 32) > 15 && (Count_DMX % 32) < 24) { DMX_LED = 255; }
      else if (COLOR==1 && (Count_DMX % 32) > 23 && (Count_DMX % 32) < 32) { DMX_LED = 255; }
      else { DMX_LED = 0; }
      for (int j=0; j<6; j++) {
        for (int i=0; i<8; i++) {
          DMXset(((7-j)*8+(7-i))*4 + COLOR + REVO_BASE_ADR,
          bitRead(pgm_read_byte_near(num_ + (Count_DMX % (CountLenght+1)+1)*8 + j),i)*DMX_LED); // >127 on
        }
      }
    }
    // bar counting
    // flashing
    DMX_LED = 255;
    if (Counter > 11 && (Count_DMX % 32) > 23) {DMX_LED = 0;}
    COLOR = 4;
    for (int i=0; i<8; i++) {
      DMXset((1*8+(7-i))*4 + COLOR + REVO_BASE_ADR, bitRead(pgm_read_byte_near(BAR_8 + (Count_DMX >> 2) % 8 ),i)*DMX_LED);
    }
    COLOR = 1;
    for (int i=0; i<8; i++) {
      DMXset((1*8+(7-i))*4 + COLOR + REVO_BASE_ADR, bitRead(pgm_read_byte_near(BAR_2 + (Count_DMX >> 4) % 2 ),i)*DMX_LED);
    }
    // every beat
    DMX_LED = 255;
    COLOR = 3;
    for (int i=0; i<8; i++) {
      DMXset((0*8+(7-i))*4 + COLOR + REVO_BASE_ADR, bitRead(pgm_read_byte_near(BAR_4 + (Count_DMX % 4)),i)*DMX_LED);
    }

/// DMX REVO IV; 1-256 lower left 1, upper right 256 ############################################

  /*
    // TEST
    COLOR = 4;
    REVO = (Count_DMX % (CountLenght+1))+1;
    for (int j=0; j<6; j++) {
      for (int i=0; i<8; i++) {
        DMXset(((7-j)*8+(7-i))*4 + COLOR, pgm_read_byte_near(BAR_4 + (Count_DMX % 2))*255); // >127 on
      }
    }
  */
