// KlingTile 144 ###################################################################

    byte TILE_BASE_ADR = DMXBase+30;

    // big number counting
    for ( COLOR=0; COLOR<3; COLOR++) {
      if (COLOR==1 && (Count_DMX % 32) < 16) { DMX_LED = DMXBright; }
      else if (COLOR==2 && (Count_DMX % 32) > 15 && (Count_DMX % 32) < 24) { DMX_LED = DMXBright; }
      else if (COLOR==0 && (Count_DMX % 32) > 23 && (Count_DMX % 32) < 32) { DMX_LED = DMXBright; }
      else { DMX_LED = 0; }

      for (int j=0; j<12; j++) {
        for (int i=0; i<8; i++) { // first 8 bits
          DMXset((j*12+(7-i))*3 + COLOR + TILE_BASE_ADR,
          bitRead(pgm_read_byte_near(num_8 + (Count_DMX % 32)*12 + j),i)*DMX_LED); // 1st
        }
        for (int i=0; i<4; i++) { // rest of 4 bits
          if (j % 2) {
            DMXset((j*12+8+(3-i))*3 + COLOR + TILE_BASE_ADR,
            bitRead(pgm_read_byte_near(num_4 + (Count_DMX % 32)*6 + j/2),i)*DMX_LED); } // 1st
          else {
            DMXset((j*12+8+(3-i))*3 + COLOR + TILE_BASE_ADR,
            bitRead(pgm_read_byte_near(num_4 + (Count_DMX % 32)*6 + j/2),i+4)*DMX_LED); } // 1st
        }
      }

    // only 8x6 upper left
      for (int j=0; j<6; j++) {
        for (int i=0; i<8; i++) {
          DMXset((j*12+(7-i))*3 + COLOR + TILE_BASE_ADR,
          bitRead(pgm_read_byte_near(num_ + ((Count_8x8 % (CountLenght+1))+1) * 8 + j), i) * DMX_LED); // 1st
        }
      }
    }

/// KlingTile 144 ###################################################################
