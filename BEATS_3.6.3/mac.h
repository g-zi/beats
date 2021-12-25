// read the unique MAC address from Teensy 

  uint8_t maccheck[6] = { 0x4, 0xE9, 0xE5, 0x9, 0x1B, 0x69 }; // enter valid MAC address here
  uint8_t mac[6];
  
  #if defined(HW_OCOTP_MAC1) && defined(HW_OCOTP_MAC0)
//    Serial.println("using HW_OCOTP_MAC* - see https://forum.pjrc.com/threads/57595-Serial-amp-MAC-Address-Teensy-4-0");
    for(uint8_t by=0; by<2; by++) mac[by]=(HW_OCOTP_MAC1 >> ((1-by)*8)) & 0xFF;
    for(uint8_t by=0; by<4; by++) mac[by+2]=(HW_OCOTP_MAC0 >> ((3-by)*8)) & 0xFF;
  #else
    mac[0] = 0x04;
    mac[1] = 0xE9;
    mac[2] = 0xE5;
    uint32_t SN=0;
    __disable_irq();
    
    #if defined(HAS_KINETIS_FLASH_FTFA) || defined(HAS_KINETIS_FLASH_FTFL)
//      Serial.println("using FTFL_FSTAT_FTFA - vis teensyID.h - see https://github.com/sstaub/TeensyID/blob/master/TeensyID.h");  
      FTFL_FSTAT = FTFL_FSTAT_RDCOLERR | FTFL_FSTAT_ACCERR | FTFL_FSTAT_FPVIOL;
      FTFL_FCCOB0 = 0x41;
      FTFL_FCCOB1 = 15;
      FTFL_FSTAT = FTFL_FSTAT_CCIF;
      while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF)) ; // wait
      SN = *(uint32_t *)&FTFL_FCCOB7;
      
    #elif defined(HAS_KINETIS_FLASH_FTFE)
//      Serial.println("using FTFL_FSTAT_FTFE - vis teensyID.h - see https://github.com/sstaub/TeensyID/blob/master/TeensyID.h");
      kinetis_hsrun_disable();
      FTFL_FSTAT = FTFL_FSTAT_RDCOLERR | FTFL_FSTAT_ACCERR | FTFL_FSTAT_FPVIOL;
      *(uint32_t *)&FTFL_FCCOB3 = 0x41070000;
      FTFL_FSTAT = FTFL_FSTAT_CCIF;
      while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF)) ; // wait
      SN = *(uint32_t *)&FTFL_FCCOBB;
      kinetis_hsrun_enable();
    #endif
    
    __enable_irq();
    for(uint8_t by=0; by<3; by++) mac[by+3]=(SN >> ((2-by)*8)) & 0xFF;
  #endif

  if (memcmp(mac, maccheck, sizeof(mac)) != 0) {
    tft.setFont(Arial_14);
    tft.setTextColor(TFT_Yellow);
    tft.setCursor(_tx, _c5);
    tft.print(mac[0] < 16 ? "   0" : "   ");
    tft.print(mac[0], HEX);
    tft.print(" : ");
    tft.print(mac[1] < 16 ? "0" : "");
    tft.print(mac[1], HEX);
    tft.print(" : ");
    tft.print(mac[2] < 16 ? "0" : "");
    tft.print(mac[2], HEX);
    tft.print(" : ");
    tft.print(mac[3] < 16 ? "0" : "");
    tft.print(mac[3], HEX);
    tft.print(" : ");
    tft.print(mac[4] < 16 ? "0" : "");
    tft.print(mac[4], HEX);
    tft.print(" : ");
    tft.print(mac[5] < 16 ? "0" : "");
    tft.println(mac[5], HEX);      
    tft.setFont(Arial_12);
    tft.setTextColor(TFT_Gray);
    tft.setCursor(_ttx, _c5+18);
    tft.println("   Contact g.zi@gmx.de");
    while(1) {}; // stop executing if MAC is not valid
  }
      
