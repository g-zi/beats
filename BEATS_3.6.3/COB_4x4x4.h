// COB 4x4x4 direct ###################################################################
// 48 channel mode 4x4 RGB
// COB_BASE_ADR = DMXBase + (DMXUnits & 0b00000011) * 30 + ((DMXUnits & 0b00000100) >> 2) * 64 ;

if(((DMXUnits & 0b00011000) >> 3) > 0) {
  
  if (DMXPattern == 0 || DMXPattern == 4 || DMXPattern == 5 || DMXPattern == 6 || DMXPattern == 10 || DMXPattern == 11 || DMXPattern == 12 || DMXPattern >= 14) 
  {
    for ( COLOR = 0; COLOR < 3; COLOR++) {

      // background color
      if (COLOR == 2 && (Count_DMX % 32) < 16) {
        DMX_BG = DMXBackBright;  // 1-16
      }
      else if (COLOR == 2 && (Count_DMX % 32) > 15 && (Count_DMX % 32) < 24) {
        DMX_BG = DMXBackBright;  // 17-24
      }
      else if ((COLOR == 1 || COLOR == 2) && (Count_DMX % 32) > 23 && (Count_DMX % 32) < 32) {
        DMX_BG = DMXBackBright;  // 25-32
      }
      else {
        DMX_BG = 0;
      }

      // number counting
      if (COLOR == 1 && (Count_DMX % 32) < 16) {
        DMX_LED = DMXBright;  // 1-16
      }
      else if ((COLOR == 0 || COLOR == 1) && (Count_DMX % 32) > 15 && (Count_DMX % 32) < 24) {
        DMX_LED = DMXBright;  // 17-24
      }
      else if (COLOR == 0 && (Count_DMX % 32) > 23 && (Count_DMX % 32) < 32) {
        DMX_LED = DMXBright;  // 25-32
      }
      else {
        DMX_LED = 0;
      }
      
      for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
          if (bitRead(pgm_read_byte_near(num_ + ((Count_DMX % (CountLenght + 1)) + 1) * 8 + j), (7 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR, DMX_BG);
          }

          if (bitRead(pgm_read_byte_near(num_ + ((Count_DMX % (CountLenght + 1)) + 1) * 8 + j), (3 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 48, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 48, DMX_BG);
          }
        }
      }
      for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 4; i++) {
          if (bitRead(pgm_read_byte_near(num_ + ((Count_DMX % (CountLenght + 1)) + 1) * 8 + j + 4), (7 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 96, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 96, DMX_BG);
          }

          if (bitRead(pgm_read_byte_near(num_ + ((Count_DMX % (CountLenght + 1)) + 1) * 8 + j + 4), (3 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 144, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 144, DMX_BG);
          }
        }
      }
    }

    // bar counting
    DMX_LED = DMXBright;
    if (Counter > 11 && (Count_DMX % 32) > 23) {
      DMX_LED = 0; // flashing
    }

    for (int i = 0; i < 4; i++) {
      COLOR = 0; // red
      DMXset((COB_BASE_ADR) + (11 - i) * 3 + COLOR + 96, bitRead(pgm_read_byte_near(BAR_8 + (Count_DMX >> 2) % 8 ), i + 4)*DMX_LED);
      DMXset((COB_BASE_ADR) + (11 - i) * 3 + COLOR + 144, bitRead(pgm_read_byte_near(BAR_8 + (Count_DMX >> 2) % 8 ), i)*DMX_LED);
      DMXset((COB_BASE_ADR) + (15 - i) * 3 + COLOR + 96, 0); // every beat
      DMXset((COB_BASE_ADR) + (15 - i) * 3 + COLOR + 144, 0); // every beat
      COLOR = 1; // green
      DMXset((COB_BASE_ADR) + (11 - i) * 3 + COLOR + 96, bitRead(pgm_read_byte_near(BAR_8 + (Count_DMX >> 2) % 8 ), i + 4)*DMX_LED);
      DMXset((COB_BASE_ADR) + (11 - i) * 3 + COLOR + 144, bitRead(pgm_read_byte_near(BAR_8 + (Count_DMX >> 2) % 8 ), i)*DMX_LED);
      DMXset((COB_BASE_ADR) + (15 - i) * 3 + COLOR + 96, bitRead(pgm_read_byte_near(BAR_4 + (Count_DMX % 4)), i + 4)*DMX_LED); // every beat
      DMXset((COB_BASE_ADR) + (15 - i) * 3 + COLOR + 144, bitRead(pgm_read_byte_near(BAR_4 + (Count_DMX % 4)), i)*DMX_LED); // every beat
      COLOR = 2; // blue
      DMXset((COB_BASE_ADR) + (11 - i) * 3 + COLOR + 96, 0);
      DMXset((COB_BASE_ADR) + (11 - i) * 3 + COLOR + 144, 0);
      DMXset((COB_BASE_ADR) + (15 - i) * 3 + COLOR + 96, bitRead(pgm_read_byte_near(BAR_4 + (Count_DMX % 4)), i + 4)*DMX_LED); // every beat
      DMXset((COB_BASE_ADR) + (15 - i) * 3 + COLOR + 144, bitRead(pgm_read_byte_near(BAR_4 + (Count_DMX % 4)), i)*DMX_LED); // every beat
    }
  }


  if (DMXPattern == 1 || DMXPattern == 4 || DMXPattern == 7 || DMXPattern == 9 || DMXPattern == 10 || DMXPattern == 12 || DMXPattern == 13 || DMXPattern == 14) 
  {
    for ( COLOR = 0; COLOR < 3; COLOR++) {

      // background color
      if (COLOR == 1 && (Count_DMX % 32) < 16) {
        DMX_BG = DMXBackBright;  // 1-16
      }
      else if (COLOR == 2 && (Count_DMX % 32) > 15 && (Count_DMX % 32) < 24) {
        DMX_BG = DMXBackBright;  // 17-24
      }
      else if ((COLOR == 0 || COLOR == 2) && (Count_DMX % 32) > 23 && (Count_DMX % 32) < 32) {
        DMX_BG = DMXBackBright;  // 25-32
      }
      else {
        DMX_BG = 0;
      }
      //      if ((COLOR==0 || COLOR==2) && (Count_DMX % 32 > 23) && (Count_DMX % 32 < 32)) { DMX_BG = (24-Counter)*DMXBackBright/24 ; } // flash last 4 beats

      // counting shp_256_
      if (COLOR == 0 && (Count_DMX % 5) == 0) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 0 && (Count_DMX % 5) == 3) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 0 && (Count_DMX % 5) == 5) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 1 && (Count_DMX % 5) == 1) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 1 && (Count_DMX % 5) == 3) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 1 && (Count_DMX % 5) == 4) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 2 && (Count_DMX % 5) == 2) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 2 && (Count_DMX % 5) == 4) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 2 && (Count_DMX % 5) == 5) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else {
        DMX_LED = 0;
      }

      for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
          if (bitRead(pgm_read_byte_near(shp_256_ + ((Count_DMX % (CountLenght + 1)) + 1) * 8 + j), (7 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR, DMX_BG);
          }

          if (bitRead(pgm_read_byte_near(shp_256_ + ((Count_DMX % (CountLenght + 1)) + 1) * 8 + j), (3 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 48, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 48, DMX_BG);
          }
        }
      }
      for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
          if (bitRead(pgm_read_byte_near(shp_256_ + ((Count_DMX % (CountLenght + 1)) + 1) * 8 + j + 4), (7 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 96, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 96, DMX_BG);
          }

          if (bitRead(pgm_read_byte_near(shp_256_ + ((Count_DMX % (CountLenght + 1)) + 1) * 8 + j + 4), (3 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 144, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 144, DMX_BG);
          }
        }
      }
    }
  }


  if (DMXPattern == 2 || DMXPattern == 5 || DMXPattern == 7 || DMXPattern == 8 || DMXPattern == 10 || DMXPattern == 11 || DMXPattern == 13 || DMXPattern == 14) 
  {
    for ( COLOR = 0; COLOR < 3; COLOR++) {

      // background color
      if (COLOR == 2 && (Count_DMX % 32) < 16) {
        DMX_BG = DMXBackBright;  // 1-16
      }
      else if (COLOR == 1 && (Count_DMX % 32) > 15 && (Count_DMX % 32) < 24) {
        DMX_BG = DMXBackBright;  // 17-24
      }
      else if ((COLOR == 0 || COLOR == 2) && (Count_DMX % 32) > 23 && (Count_DMX % 32) < 32) {
        DMX_BG = DMXBackBright;  // 25-32
      }
      else {
        DMX_BG = 0;
      }
      //      if ((COLOR==0 || COLOR==2) && (Count_DMX % 32 > 23) && (Count_DMX % 32 < 32)) { DMX_BG = (24-Counter)*DMXBackBright/24 ; } // flash last 4 beats

      // counting shp_321_
      if (COLOR == 1 && (Count_DMX % 5) == 0) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 1 && (Count_DMX % 5) == 3) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 1 && (Count_DMX % 5) == 5) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 2 && (Count_DMX % 5) == 1) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 2 && (Count_DMX % 5) == 3) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 2 && (Count_DMX % 5) == 4) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 0 && (Count_DMX % 5) == 2) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 0 && (Count_DMX % 5) == 4) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 0 && (Count_DMX % 5) == 5) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else {
        DMX_LED = 0;
      }

      for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
          if (bitRead(pgm_read_byte_near(shp_321_ + ((Count_DMX % (CountLenght + 1)) + 1) * 8 + j), (7 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR, DMX_BG);
          }

          if (bitRead(pgm_read_byte_near(shp_321_ + ((Count_DMX % (CountLenght + 1)) + 1) * 8 + j), (3 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 48, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 48, DMX_BG);
          }
        }
      }
      for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
          if (bitRead(pgm_read_byte_near(shp_321_ + ((Count_DMX % (CountLenght + 1)) + 1) * 8 + j + 4), (7 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 96, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 96, DMX_BG);
          }

          if (bitRead(pgm_read_byte_near(shp_321_ + ((Count_DMX % (CountLenght + 1)) + 1) * 8 + j + 4), (3 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 144, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 144, DMX_BG);
          }
        }
      }
    }
  }


  if (DMXPattern == 3 || DMXPattern == 6 || DMXPattern == 8 || DMXPattern == 9 || DMXPattern == 11 || DMXPattern == 12 || DMXPattern == 13 || DMXPattern == 14) 
  {
    for ( COLOR = 0; COLOR < 3; COLOR++) {

      // background color
      if (COLOR == 2 && (Count_DMX % 32) < 16) {
        DMX_BG = DMXBackBright;  // 1-16
      }
      else if (COLOR == 1 && (Count_DMX % 32) > 15 && (Count_DMX % 32) < 24) {
        DMX_BG = DMXBackBright;  // 17-24
      }
      else if ((COLOR == 0 || COLOR == 2) && (Count_DMX % 32) > 23 && (Count_DMX % 32) < 32) {
        DMX_BG = DMXBackBright;  // 25-32
      }
      else {
        DMX_BG = 0;
      }
      //      if ((COLOR==0 || COLOR==2) && (Count_DMX % 32 > 23) && (Count_DMX % 32 < 32)) { DMX_BG = (24-Counter)*DMXBackBright/24 ; } // flash last 4 beats

      // counting shp_beat_
      if (COLOR == 2 && (Count_DMX % 5) == 0) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 2 && (Count_DMX % 5) == 3) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 2 && (Count_DMX % 5) == 5) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 0 && (Count_DMX % 5) == 1) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 0 && (Count_DMX % 5) == 3) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 0 && (Count_DMX % 5) == 4) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 1 && (Count_DMX % 5) == 2) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 1 && (Count_DMX % 5) == 4) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else if (COLOR == 1 && (Count_DMX % 5) == 5) {
        DMX_LED = (24 - Counter) * DMXBright / 24;
      }
      else {
        DMX_LED = 0;
      }

      for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
          if (bitRead(pgm_read_byte_near(shp_beat_ + ((Count_DMX % 32 ) + 1) * 8 + j), (7 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR, DMX_BG);
          }

          if (bitRead(pgm_read_byte_near(shp_beat_ + ((Count_DMX % 32 ) + 1) * 8 + j), (3 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 48, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 48, DMX_BG);
          }
        }
      }
      for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
          if (bitRead(pgm_read_byte_near(shp_beat_ + ((Count_DMX % 32 ) + 1) * 8 + j + 4), (7 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 96, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 96, DMX_BG);
          }

          if (bitRead(pgm_read_byte_near(shp_beat_ + ((Count_DMX % 32 ) + 1) * 8 + j + 4), (3 - i)) == 1 ) {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 144, DMX_LED);
          }
          else {
            DMXset((COB_BASE_ADR) + (i + (j * 4)) * 3 + COLOR + 144, DMX_BG);
          }
        }
      }
    }
  }
}
  /// COB 4x4x4 direct ###################################################################
