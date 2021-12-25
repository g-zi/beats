/*
  BEATS - MIDI Beat Counter Version 1.3
  Based on Teensy 3.6 or higher, runs from 48 Mhz 

  MIDI -> show MIDI note and pressure value above MIDI

  Reset EEprom: press Shift, left and right encoder at the same time, power up and hold for at least 2 sec.
*/

// https://platformio.org/lib/show/70/Audio
// https://gammon.com.au/forum/?id=14175
// https://github.com/Circuito-io/Basic-Circuits/tree/master/ledbar_mic
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/

/*
https://github.com/bblanchon/ArduinoTrace
https://www.codeproject.com/Articles/1037057/Debugger-for-Arduino
http://visualmicro.blogspot.com/
https://mcuoneclipse.com/2014/08/09/hacking-the-teensy-v3-1-for-swd-debugging/
https://docs.platformio.org/en/latest/plus/debugging.html#piodebug
*/

// which version?
#define MBC_361 // Teensy 3.6 version with two shift buttons included in the keypad matrix
//#define MBC_36 // Teensy 3.6 version with one shift button


// which display? TFT or OLED could be used with LED in parallel
//#define Adafruit_TFT128   // https://www.adafruit.com/products/2088
#define Adafruit_TFT240   // https://www.aafruit.com/product/3787 or https://www.berrybase.de/neu/1.3-240x240-ips-hd-lcd-display-modul-spi-interface
//#define Adafruit_OLED  // runs only with cpu speed overclock https://www.adafruit.com/products/1431 
//or https://www.berrybase.de/neu/1.5-128x128-oled-display-modul-rgb-spi-interface?c=123
//#define LED_8x8matrix // Adafruit i2c LED 8x8 matrix display


#if defined(LED_8x8matrix)
//  #define LED_8x8_info // information output on LED 8x8 matrix
  #include "Adafruit_LEDBackpack.h" // LED_8x8; modified for use i2c_t3
//  Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix(); // with I2C
  Adafruit_8x8matrix matrix = Adafruit_8x8matrix(); // with I2C
#endif


// which serial port for MIDI-DIN? No definition switch off MIDI-DIN
#define MIDI_SERIAL_2
//#define MIDI_SERIAL_3

#include "HardwareSerial.h"

#include <Encoder.h>
//#define ENCODER_DO_NOT_USE_INTERRUPTS
#define ENCODER_OPTIMIZE_INTERRUPTS

// keypad and encoder buttons
#include <Keypad.h>
#if defined(MBC_361)
  Encoder rightEnc(28, 24); // use pin 28 & 29
  long rightPos  = -999;
  Encoder leftEnc(31, 32); // use pin 31 & 32
  long leftPos  = -999;
  #define rightENC_BTN 27
  #define rightENC_RED 35
  #define rightENC_GREEN 36
  #define rightENC_BLUE 29
  #define leftENC_BTN 39
  #define leftENC_RED 38
  #define leftENC_GREEN 37
  #define leftENC_BLUE 30
  #define iLED 29     // LED pin on Teensy board; 11 for Teensy2.0; 13 for Teensy3.1/2/6 (30 = enc_bl)
  const byte ROWS = 6; // 6x5 keys 
  const byte COLS = 5; // cols and rows exchanged because of diodes direction
  char keys[ROWS][COLS] = {
    { 'A', 'B', 'C', 'D', 'x' },
    { 13,   9,   5,   1,  'S' },
    { 14,  10,   6,   2,  's' },
    { 15,  11,   7,   3,  'x' },
    { 16,  12,   8,   4,  'x' },
    { 'a', 'b', 'c', 'd', 'x' }  
  };
  byte colPins[COLS] = { 14, 15, 16, 17, 12 }; //connect to the row pinouts of the keypad
  byte rowPins[ROWS] = { 20, 33, 34, 25, 26, 21 }; //connect to the column pinouts of the keypad
#elif defined(MBC_36)
  Encoder rightEnc(28, 29); // use pin 28 & 29
  long rightPos  = -999;
  Encoder leftEnc(31, 32); // use pin 31 & 32
  long leftPos  = -999;
  #define Shift_BTN 12
  #define rightENC_BTN 27
  #define rightENC_RED 24
  #define rightENC_GREEN 25
  #define rightENC_BLUE 26
  #define leftENC_BTN 39
  #define leftENC_RED 38
  #define leftENC_GREEN 37
  #define leftENC_BLUE 30
  #define iLED 26     // LED pin on Teensy board; 11 for Teensy2.0; 13 for Teensy3.1/2/6 (30 = enc_bl)
  const byte ROWS = 4; // 6x4 keys
  const byte COLS = 6;
  char keys[ROWS][COLS] = {
    { 'A', 13, 14, 15, 16, 'a' },
    { 'B',  9, 10, 11, 12, 'b' },
    { 'C',  5,  6,  7,  8, 'c' },
    { 'D',  1,  2,  3,  4, 'd' }
  //{  '','S','s', '', '',  '' }   
  };
  byte rowPins[ROWS] = { 14, 15, 16, 17 }; //connect to the row pinouts of the keypad
  byte colPins[COLS] = { 20, 33, 34, 35, 36, 21 }; //connect to the column pinouts of the keypad
#endif
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


unsigned long loopCount;
unsigned long startTime;
unsigned long ticker;
unsigned long bpm_ms = 1800 ; // set to 120 bpm
unsigned long bpm = 120 ; // set to 120 bpm
String kbd_msg = "";
byte keypad_shift = 0;
bool shift = false;
byte key_ana[ROWS*COLS]; // analog key


#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

#include <EEPROM.h>
//#include <SD.h>
#include <SPI.h>
#include "SdFat.h" // https://github.com/greiman/SdFat
#include <TimerThree.h>


byte DMXbuffer[516]; // Minimum size = number of channels + 1. Add more channels if the last light flickers. This seems reliable: size = number of channels + 4.
// Send at least 24 channels (25 bytes) to keep time between breaks above 1.2 milliseconds. Some DMX hardware may not be able to handle faster refresh times.
//int serial1TXbuffersizeminus1;

// TeensyDMX needs to be included before ST7735_t3.h https://github.com/ssilverman/TeensyDMX
#include <TeensyDMX.h>
namespace teensydmx = ::qindesign::teensydmx;
constexpr uint8_t kTXPin = 2; // Pin for enabling or disabling the transmitter
teensydmx::Sender dmxTx{Serial1}; // Create the DMX sender on Serial1


#include "Adafruit_GFX.h" // graphic library
float p = 3.1415926;

// TFT Adafruit_ST77xx   FEDCBA9876543210    #####################################
// Color definitions     RRRRRggggggBBBBB
#define TFT_Black 0x0000
#define TFT_Gray       0b0111101111101111
#define TFT_LightGray  0b1011110111110111
#define TFT_DarkGray   0b0001100011100011
#define TFT_DarkerGray 0b0000100001100001
#define TFT_Blue 0x001F
#define TFT_DarkBlue   0b0000000000010111
#define TFT_Red 0xF800
#define TFT_DarkRed    0b1001100000000000
#define TFT_Orange 0xFA00
#define TFT_Green 0x07E0
#define TFT_DarkGreen   0b0000010000000000
#define TFT_DarkerGreen 0b0000000011100000
#define TFT_Cyan 0x07FF
#define TFT_LightCyan 0b0000011110011100
//                      RRRRRggggggBBBBB
#define TFT_MENU_1UP  0b1111111111111111
#define TFT_MENU_2UP  0b0000011000011000
#define TFT_Magenta 0xF81F
#define TFT_Yellow 0xFFE0
#define TFT_White 0xFFFF
#define TFT_MenuBack 0x0004

#define TFT_SCLK 13  // SCLK can also use pin 14
//#define TFT_MISO 12  // used as key row5
#define TFT_MOSI 11  // MOSI can also use pin 7
#define TFT_CS   6   // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_RST  5   // RST can use any pin or set to -1 and connect to RESET pin
#define TFT_DC   4   // but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22

// Adafruit TFT displays
#if defined(Adafruit_TFT128)
  // This SPI Teensy3 native optimized version requires specific pins
  #if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
  #endif
  #include <ST7735_t3.h> // TFT Hardware-specific library
  ST7735_t3 tft = ST7735_t3(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
#elif defined(Adafruit_TFT240)
  #include <ST7789_t3.h> // Hardware-specific library
  #include <ST7735_t3_font_Arial.h>
  #include <ST7735_t3_font_ArialBold.h>
  ST7789_t3 tft = ST7789_t3(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
#elif defined(Adafruit_OLED) // Adafruit OLED display
  #include <Adafruit_SSD1351.h> // OLED Hardware-specific library
//  Adafruit_SSD1351 tft = Adafruit_SSD1351(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
  Adafruit_SSD1351 tft = Adafruit_SSD1351(TFT_CS, TFT_DC, TFT_RST);
#endif

// https://learn.adafruit.com/creating-custom-symbol-font-for-adafruit-gfx-library/overview
// getTextBounds() Adafruit_GFX_Button, GFXcanvas1, GFXcanvas8, GFXcanvas16, GFXfont
// tft.getTextBounds(string, x, y, &x1, &y1, &w, &h);

//#include <Fonts/FreeMonoBoldOblique24pt7b.h>
//#include <Fonts/FreeMono9pt7b.h>
//#include <Fonts/FreeMono12pt7b.h>
//#include <Fonts/FreeMono24pt7b.h>
//#include <Fonts/FreeSerif9pt7b.h>

//#include <Fonts/FreeMono18pt7b.h>
//#include <Fonts/FreeMonoBold18pt7b.h>

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>


#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 104 // How many NeoPixels? 16 + 24 + 64
#define PIN 23 // NeoPixel data port
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


//#include <RGBLed.h>
//RGBLed LE_led( 38, 37, 30, COMMON_ANODE); // left encoder LED
//RGBLed RE_led( 24, 25, 26, COMMON_ANODE); // right encoder LED
//LE_led.setColor(255, 0, 0);
//LE_led.flash(255, 0, 0, 250, 100); // Interval 250/100ms


unsigned long current_ms_left = millis();
unsigned long current_ms_right = millis();
unsigned long previous_ms_left = 0; 
unsigned long previous_ms_right = 0; 

// Menu for TFT
#define leftTFT_MenuLines 6
const char* leftTFT_Menu[] = {
  "Back Color", // -2
  "Text Font", // -1
  "Count Lengt",
  "MIDI Channel",
  "MIDI Address",
  "Text Color",
  "Back Color",
  "Text Font",
  "Count Lengt", // +1
  "MIDI Channel"  // +2
};

const char* leftTFT_LongMenu[] = {
  "Beat Count Length",
  "MIDI Channel",
  "MIDI Base Address",
  "TFT Text Color",
  "TFT Back Color",
  "TFT Text Font"
};

#define rightTFT_MenuLines 6
const char* rightTFT_Menu[] = {
  "Display 64", // -2
  "Neo Bright", // -1
  "DMX Address", // Scan View
  "DMX Units",
  "COB Pattern",
  "Brightness",
  "Display 64",
  "Neo Bright",
  "DMX Address", // +1
  "DMX Units"  // +2
};

const char* rightTFT_LongMenu[] = {
  "DMX Base Address",
  "DMX Units Selection",
  "DMX COB Pattern",
  "DMX Brightness",
  "HAT for 64 Pattern",
  "Neopixel Brightness"
};

const byte DMXBaseEE = 0; // DMX base address
const byte DMXUnitsEE = 1; // DMX units selection BSxCCSPP = Beats/Bars, Scanner Prog, xx, COB, Scanner, Pixbar
const byte DMXPatternEE = 2; // DMX COB pattern
const byte DMXBrightEE = 3; // DMX brightness for Pixbar and COB
const byte HATPatternEE = 4; // Select which HAT to use, Waveshare or Unicorn
const byte NeoPixelBrightEE = 5; // Neopixel brightness
const byte rightEncoderStartEE = 9; // Encoder start point, not used for menu

// section 10 - 19 used for secondary encoder, needs to be at same single position as main encoder (bright 3 = back 13, count 20 = start = 10 etc.)
const byte CountLenghtEE = 10; // beats-1, 256= 255, 128=127, 64=63, 32=31, 16=15
const byte DMXPixbarEE = 12; // DMX pattern for Cameo COB 8x LED
const byte DMXBackBrightEE = 13; // DMX backlight

const byte BeatStartEE = 20; // Beat start
const byte MIDIChannelEE = 21; // MIDI Channel
const byte MIDIBaseAdrEE = 22; // MIDI Base Address
const byte LCDTextColorEE = 23; // LCD text color            FEDCBA9876543210 -> 76543210  LCD_Red, LCD_Green, LCD_Blue, LCD_Bright
const byte LCDBackColorEE = 24; // LCD background color     RRRRRggggggBBBBB -> hhRRggBB    
const byte LCDTextFontEE = 25; // LCD text font
const byte leftEncoderStartEE = 29; // Encoder start point, not used for menu

const word FixtureBaseEE = 1024; // scanner fixture base address 

byte leftEncMIDI_A = 0;
byte leftEncMIDI_B = 0;
byte leftEncMIDI_C = 0;
byte rightEncMIDI_D = 0;
byte rightEncMIDI_E = 0;
byte rightEncMIDI_F = 0;
byte leftEncRED = 0;
byte leftEncBlue = 0;
byte rightEncGreen = 0;
byte rightEncBright = 0;

byte DMXBase = EEPROM.read(DMXBaseEE);
byte DMXUnits = EEPROM.read(DMXUnitsEE);
byte DMXPattern = EEPROM.read(DMXPatternEE);
byte DMXBright = EEPROM.read(DMXBrightEE);
byte HATPattern = EEPROM.read(HATPatternEE);
byte NeoPixelBright = EEPROM.read(NeoPixelBrightEE);
byte rightEncoderStart = EEPROM.read(rightEncoderStartEE);

byte CountLenght = EEPROM.read(CountLenghtEE);
byte DMXPixbar = EEPROM.read(DMXPixbarEE);
byte DMXBackBright = EEPROM.read(DMXBackBrightEE);

byte BeatStart = EEPROM.read(BeatStartEE);
byte MIDIChannel = EEPROM.read(MIDIChannelEE); // <- Beat/Bar bit7 set here, upper nipple unused
byte MIDIBaseAdr = EEPROM.read(MIDIBaseAdrEE);
byte LCDTextColor = EEPROM.read(LCDTextColorEE);
byte LCDBackColor = EEPROM.read(LCDBackColorEE);
byte LCDTextFont = EEPROM.read(LCDTextFontEE)-1;
byte leftEncoderStart = EEPROM.read(leftEncoderStartEE);

// read first scanner values
byte ScanPan = EEPROM.read(FixtureBaseEE);
byte ScanTilt = EEPROM.read(FixtureBaseEE+1);
byte ScanColor = EEPROM.read(FixtureBaseEE+2);
byte ScanStrobe = EEPROM.read(FixtureBaseEE+3);
byte ScanGobo = EEPROM.read(FixtureBaseEE+4);
byte ScanRotate = EEPROM.read(FixtureBaseEE+5);
byte ScanPrisma = EEPROM.read(FixtureBaseEE+6);
byte ScanFocus = EEPROM.read(FixtureBaseEE+7);

//byte ScanBeats = 0;
//byte ScanFree = 0;

byte ScanMoveMode = 0;
byte ScanMoveDir = 0;

byte ScanMotion = 0;
byte ScanSpeed = 0;
byte ScanSpdMove = 0b01000000; // 7.6.5. = move (2 = move circle right), < 10 speed 
byte preScanSpdMove = 0;
byte ScanRun = 0;
byte ScanBPM = 0;

byte ScanSelected = 0;

byte leftLCDView = 0;
byte rightLCDView = 0;
byte MenuDepth = 0;
byte UnitsView = 0;
bool leftEncPressed = false;
bool rightEncPressed = false;

bool ProgMode = false;

byte leftLastEncoder = 1;
byte rightLastEncoder = 1;
byte KEYS = 0; 
byte DMX_LED = 0;
byte DMX_BG = 0;
byte COLOR = 0;

byte FSR = 0;
byte FSR_low = 0;
byte FSR_read = 0;

byte Counter = 0; // MIDI Beat Clock (1-24)
byte Count_Beats = (BeatStart & 0b00000011) ;
byte Count_8x8 = BeatStart;
byte Count_DMX = BeatStart;
byte NeoPixelFastCounter = 0;
byte RED = 0;
byte GREEN = 0;
byte BLUE = 0;
long RGB = 0;
long leftnewPos = 0;
long rightnewPos = 0;
String left_str = "";
String right_str = "";
byte left_half_bound = 0;
byte right_half_bound = 0;
int16_t txtX, txtY;
uint16_t txtW, txtH;

byte CAMEO_BASE_ADR = 0 ;
byte SCANNER_BASE_ADR = 0 ;
byte COB_BASE_ADR = 0 ;

const byte SPP = 242; // Song Position Pointer
const byte CLOCK = 248;
const byte START = 250;
const byte CONTINUE = 251;
const byte STOP = 252;
bool RUN = false; // used to identify song running or stopped

byte incomingByte;
byte miditype = 0;
byte usbMIDIdata1 = 0;
byte usbMIDIdata2 = 0;
uint32_t songPositionPointer = 0;

/*
usbMIDI.NoteOff  0x80  Note Off
usbMIDI.NoteOn  0x90  Note On
usbMIDI.AfterTouchPoly  0xA0  Polyphonic AfterTouch
usbMIDI.ControlChange 0xB0  Control Change / Channel Mode
usbMIDI.ProgramChange 0xC0  Program Change
usbMIDI.AfterTouchChannel 0xD0  Channel (monophonic) AfterTouch
usbMIDI.PitchBend 0xE0  Pitch Bend
usbMIDI.SystemExclusive 0xF0  System Exclusive
usbMIDI.TimeCodeQuarterFrame  0xF1  System Common - MIDI Time Code Quarter Frame
usbMIDI.SongPosition  0xF2  System Common - Song Position Pointer
usbMIDI.SongSelect  0xF3  System Common - Song Select
usbMIDI.TuneRequest 0xF6  System Common - Tune Request
usbMIDI.Clock 0xF8  System Real Time - Timing Clock
usbMIDI.Start 0xFA  System Real Time - Start
usbMIDI.Continue  0xFB  System Real Time - Continue
usbMIDI.Stop  0xFC  System Real Time - Stop
usbMIDI.ActiveSensing 0xFE  System Real Time - Active Sensing
usbMIDI.SystemReset 0xFF  System Real Time - System Reset
 */

byte pixbar[24]; // Array for 8 RGB LEDs (24)
byte ScanActiv = 0; // Scanner activ
byte lastScanActivPressed = 0; // last scanner activ pressed
byte preScanActiv = 255; // Scanner activ
byte FixtureActiv = 0; // Fixture activ
byte preFixtureActiv = 255; // pre Fixture activ
byte ScanActivFixture[72]; // Array for Scanner fixture and activ (0-8 fixtures, 9 active)
bool ScanDir[8] = {true,true,true,true,true,true,true,true};
unsigned int ScanCnt[8]; // up/down counter
int  ScanCalc[8];
byte ScanAngle[8]; 
byte ScanSpd[8]; 
byte ScanMove[8];
byte scanmv;


#include "Shapes.h" // contains all shapes for 8x8 and 12x12 (Klingtile) matrix and display fonts
#if defined(Adafruit_TFT240)
  static const uint8_t * TFT_ = TFT_240_ ;
#else
  static const uint8_t * TFT_ = TFT_128_ ;
#endif

word LCD_Color(int EE_value) {
/*
 F E D C B A 9 8 7 6 5 4 3 2 1 0
 R R R R R G G G G G G B B B B B
 x x . . . x x . . . . x x . . .

 7  6  5  4  3  2  1  0
 R1 R0 G1 G0 B1 B0 h1 h0

 (R5-1) + (h1*2) + 2
 (G6+5) + (h1*2) + 2
*/ 
  byte _LCD_bright = EE_value & 0b00000011      ; // 0-1-2-3       0b......xx
  byte _LCD_blue   = EE_value & 0b00001100      ; // 0-8-16-24     0b...xx...
  byte _LCD_green  = EE_value & 0b00110000      ; // 0-8-16-24-48  0b..xx....
  byte _LCD_red    = EE_value & 0b11000000      ; // 0-8-16-24     0b...xx...
  if(_LCD_blue  > 0) _LCD_blue  = (_LCD_blue*2 + _LCD_bright * 2 + 1)  ;
  if(_LCD_green > 0) _LCD_green = ((_LCD_green + _LCD_bright * 4 + 3)) ;
  if(_LCD_red   > 0) _LCD_red   = ((_LCD_red/8 + _LCD_bright * 2 + 1)) ;
  word LCD_Col = _LCD_blue + (_LCD_green << 5) + (_LCD_red << 11) ;
return LCD_Col;
}
word LCD_txt_Color = LCD_Color(LCDTextColor);
word LCD_bck_Color = LCD_Color(LCDBackColor);


#include "sub.h" // Subroutines
#include "EncButtons.h" // Subroutines



// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
void setup() {
/*
// https://github.com/PaulStoffregen/SD
  if (!(SD.begin(BUILTIN_SDCARD))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
*/

  Timer3.initialize(100000);
  Timer3.attachInterrupt(BPM); // 

// keypad
  keypad.setDebounceTime(20); // Default is 50mS
  keypad.setHoldTime(250);    // Default is 1000mS
  loopCount = 0;
  startTime = millis();
  ticker = millis();
  
  usbMIDI.setHandleRealTimeSystem(RealTimeSystem);
//  usbMIDI.setHandleSongPosition(songPositionPointer);

// MIDI 5pol DIN
#if defined(MIDI_SERIAL_2) || defined(MIDI_SERIAL_3)
  Serial.begin(115200);
  MIDI.begin(); // start MIDI via 5pol DIN
#endif


/*/ DMX with UART
  Serial1.begin(250000);
  // Increase serial1 buffer size to send more channels.
  // open file: hardware/teensy/avr/cores/teensy3/serial3.c
  // edit line: #define TX_BUFFER_SIZE 40
  serial1TXbuffersizeminus1 = Serial1.availableForWrite();
*/// DMX with UART

// TeensyDMX
  pinMode(kTXPin, OUTPUT); // Set the pin that enables the transmitter
  digitalWriteFast(kTXPin, HIGH);
  dmxTx.begin();
  
  pinMode(iLED, OUTPUT); // internal LED

//  pinMode(Shift_BTN, INPUT_PULLUP);  // Shift (MISO)
  pinMode(rightENC_RED, OUTPUT); // right Encoder LED red
  pinMode(rightENC_GREEN, OUTPUT); // right Encoder LED green
  pinMode(rightENC_BLUE, OUTPUT); // right Encoder LED blue
  pinMode(rightENC_BTN, INPUT);  // right Encoder Switch (active +)
  
  pinMode(leftENC_RED, OUTPUT); // left Encoder LED red
  pinMode(leftENC_GREEN, OUTPUT); // left Encoder LED green
  pinMode(leftENC_BLUE, OUTPUT); // left Encoder LED blue
  pinMode(leftENC_BTN, INPUT);  // left Encoder Switch (active +)
  
  digitalWrite(rightENC_RED, HIGH); // right Encoder LED red off
  digitalWrite(rightENC_GREEN, HIGH); // right Encoder LED green off
  digitalWrite(rightENC_BLUE, HIGH); // right Encoder LED blue off

  digitalWrite(leftENC_RED, HIGH); // left Encoder LED red off
  digitalWrite(leftENC_GREEN, HIGH); // left Encoder LED green off
  digitalWrite(leftENC_BLUE, HIGH); // left Encoder LED blue off


// TFT Adafruit_ST7735
#if defined(Adafruit_TFT128)
  pinMode(SD_CS, INPUT_PULLUP);  // keep SD CS high when not using SD card
  tft.initR(INITR_GREENTAB);     // for TFT; initialize a ST7735R chip, green tab
#elif defined(Adafruit_TFT240)
  tft.init(240, 240, SPI_MODE0); // Init ST7789 240x240, SPI_MODE3 for display without CS
#elif defined(Adafruit_OLED)
  tft.begin(); // for OLED
#endif


  tft.setRotation(1); // rotate 90°
  tft.setTextWrap(false); // no text wrap
  tft.fillScreen(TFT_Black);
  tft.setCursor((_tw - strlen("Beats by DJ Yoi") * 6 * _ts) / 2, 0);
  tft.setTextColor(TFT_Gray);
  tft.setTextSize(_ts);
  tft.println("Beats by DJ Yoi"); // status line top
  
  tft.setTextSize(1);
  tft.setFont(Arial_28_Bold);
  tft.setTextColor(TFT_White);
  tft.setCursor(_ttx, _c1);
  tft.println("   BEATS");
  tft.setFont(Arial_28);
  tft.setTextColor(TFT_Gray);
  tft.setCursor(_ttx, _c2);
  tft.println("Beat Clock");
  tft.setCursor(_ttx, _c3);
  tft.println("Counter by");
  tft.setFont(Arial_28_Bold);
  tft.setTextColor(TFT_White);
  tft.setCursor(_ttx, _c4);
  tft.println("   DJ Yoi");
  
  tft.setFont();
  tft.setTextColor(TFT_Gray,TFT_Black);
  tft.setCursor((_tw - strlen("Version: 1.3") * 6 * _ts) / 2, _tw-_th);
  tft.setTextSize(_ts);
  tft.print("Version: 1.3");
//  delay(1200);
  tft.setCursor((_tw - strlen("Version: 1.3") * 6 * _ts) / 2, _tw-_th);
  tft.print("            ");

  
// Reset EEprom: press Shift, left and right encoder at the same time, power up and hold for at least 2 sec.
//  if (digitalRead(rightENC_BTN) == HIGH && digitalRead(leftENC_BTN) == HIGH && digitalRead(Shift_BTN) == LOW)
  if (digitalRead(rightENC_BTN) == HIGH && digitalRead(leftENC_BTN) == HIGH)
  {
    if (millis() > 100)  // -> Reset EEprom
    {
      tft.setTextColor(TFT_Yellow);
      tft.fillRect(0, 0, _tw, _tw, TFT_Black);
#if defined(Adafruit_TFT240)
      tft.setTextSize(6);
      tft.setCursor(11, 41);
      tft.println("Erase");
      tft.setCursor(11, 106);
      tft.println("EEprom");
#else 
      tft.setTextSize(3);
      tft.setCursor(11, 55);
      tft.println("Erase");
      tft.setCursor(11, 82);
      tft.println("EEprom");
#endif

      EEPROM.write(CountLenghtEE,31);
      CountLenght = 31;
      delay(10);
      EEPROM.write(BeatStartEE,0);
      BeatStart = 0;
      delay(10);
      EEPROM.write(MIDIChannelEE,0);
      MIDIChannel = 0;
      delay(10);
      EEPROM.write(MIDIBaseAdrEE,36); // C+1
      MIDIBaseAdr = 36;
      delay(10);
      EEPROM.write(DMXBaseEE,1);
      DMXBase = 1;
      delay(10);
      EEPROM.write(DMXUnitsEE,0);
      DMXUnits = 0;
      delay(10);
      EEPROM.write(DMXPixbarEE,0);
      DMXPixbar = 0;
      delay(10);
      EEPROM.write(DMXPatternEE,0);
      DMXPattern = 0;
      delay(10);
      EEPROM.write(HATPatternEE,0);
      HATPattern = 0;
      delay(10);
      EEPROM.write(DMXBrightEE,100);
      DMXBright = 100;
      delay(10);
      EEPROM.write(DMXBackBrightEE,10);
      DMXBackBright = 10;
      delay(10);
      EEPROM.write(LCDTextColorEE,246);
      LCDTextColor = 246;
      delay(10);
      EEPROM.write(LCDBackColorEE,10);
      LCDBackColor = 10;
      delay(10);
      EEPROM.write(LCDTextFontEE,8);
      LCDTextFont = 8;
      delay(10);
      EEPROM.write(NeoPixelBrightEE,25);
      NeoPixelBright = 25;
      delay(10);
      EEPROM.write(rightEncoderStartEE, 2); // menu pointer
      rightEncoderStart = 2;
      delay(10);
      EEPROM.write(leftEncoderStartEE, 2); // menu pointer
      leftEncoderStart = 2;
      delay(10);
      
      for (int i = 0; i < 2305; i = i + 9 ) {
        EEPROM.write(FixtureBaseEE+i, 0);
        EEPROM.write(FixtureBaseEE+i+1, 0);
        EEPROM.write(FixtureBaseEE+i+2, 0);
        EEPROM.write(FixtureBaseEE+i+3, 255); // Shutter open
        EEPROM.write(FixtureBaseEE+i+4, 0);
        EEPROM.write(FixtureBaseEE+i+5, 0);
        EEPROM.write(FixtureBaseEE+i+6, 0);
        EEPROM.write(FixtureBaseEE+i+7, 127); // Focus
        EEPROM.write(FixtureBaseEE+i+8, 0);
        delay(5);
      }

      tft.setTextColor(TFT_Magenta);
      tft.fillRect(0, 0, _tw, _tw, TFT_Black);
#if defined(Adafruit_TFT240)
      tft.setTextSize(6);
      tft.setCursor(11, 41);
      tft.println("EEprom");
      tft.setCursor(11, 106);
      tft.println("erased");
#else 
      tft.setTextSize(3);
      tft.setCursor(11, 55);
      tft.println("EEprom");
      tft.setCursor(11, 82);
      tft.println("erased");
#endif
    }
  }
 
  
// NeoPixel #############################################################################

  pixels.begin(); // Initialize NeoPixel
/*
  for (int i = 16; i < 40; i++ ) {
//    pixels.setPixelColor(i, pixels.Color(DMXbuffer[i*3], DMXbuffer[i*3+1], DMXbuffer[i*3+2]));
    pixels.setPixelColor(i, pixels.Color(0, 1, 0));
  }
*/

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
  
  pixels.show();


#if defined(LED_8x8matrix) // start LED 8x8 matrix
  matrix.begin(0x70);  // pass in the address <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  matrix.setTextWrap(false);  // scroll text
  matrix.setTextSize(1);
  matrix.setTextColor(LED_GREEN);
#endif


#if defined(LED_8x8_info) // Info output ################################################

    for (int8_t x=7; x>=-100; x--) {
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print("BEATS by DJ Yoi");
      matrix.writeDisplay();
      delay(35); // 50
    }

    for (int8_t x=7; x>=-15; x--) { // MIDI Channel
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print("Ch");
      matrix.writeDisplay();
      delay(35); // 50
    }
    matrix.clear();
    matrix.drawBitmap(0, 1, num_+(MIDIChannel & 0b00001111)*8, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    delay(500);

    for (int8_t x=7; x>=-20; x--) { // MIDI Address
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print("Adr");
      matrix.writeDisplay();
      delay(35); // 50
    }
    matrix.clear();
    matrix.drawBitmap(0, 1, num_+(MIDIBaseAdr)*8, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    delay(500);

    for (int8_t x=7; x>=-30; x--) { // Start beats
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print("Start");
      matrix.writeDisplay();
      delay(35); // 50
    }
    matrix.clear();
    matrix.drawBitmap(0, 1, num_+(BeatStart+1)*8, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    delay(500);

    for (int8_t x=7; x>=-30; x--) { // Beats count
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print("Beats");
      matrix.writeDisplay();
      delay(35); // 50
    }
    matrix.clear();
    matrix.drawBitmap(0, 1, num_+(CountLenght+1)*8, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    delay(500);

    for (int8_t x=7; x>=-20; x--) { // DMX Base Address
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print("DMX");
      matrix.writeDisplay();
      delay(35); // 50
    }
    matrix.clear();
    matrix.drawBitmap(0, 1, num_+(DMXBase)*8, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    delay(500);

    for (int8_t x=7; x>=-30; x--) { // DMX Light
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print("Light");
      matrix.writeDisplay();
      delay(35); // 50
    }
    matrix.clear();
    matrix.drawBitmap(0, 1, num_+(DMXBright)*8, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    delay(500);

    for (int8_t x=7; x>=-40; x--) { // DMX Pattern
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print("Pattern");
      matrix.writeDisplay();
      delay(35); // 50
    }
    matrix.clear();
    matrix.drawBitmap(0, 1, num_+(DMXPattern)*8, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    delay(500);

    matrix.clear();
    matrix.drawBitmap(0, 1, chr_Yoi, 8, 8, LED_YELLOW);
    matrix.writeDisplay();

  /// Info output ####################################################

#endif

// set initial value of encoders
//  rightEnc.write(DMXBright * 4);
//  leftEnc.write(DMXBright * 4);


// load init for all scanner from position 1, ignore ScanActiv
  for (int s = 0; s < 8; s++ ) {
    ScanActivFixture[0+s*8] = EEPROM.read(FixtureBaseEE + ( 0 + s*9 ));
    ScanActivFixture[1+s*8] = EEPROM.read(FixtureBaseEE + ( 1 + s*9 ));
    ScanActivFixture[2+s*8] = EEPROM.read(FixtureBaseEE + ( 2 + s*9 ));
    ScanActivFixture[3+s*8] = EEPROM.read(FixtureBaseEE + ( 3 + s*9 ));
    ScanActivFixture[4+s*8] = EEPROM.read(FixtureBaseEE + ( 4 + s*9 ));
    ScanActivFixture[5+s*8] = EEPROM.read(FixtureBaseEE + ( 5 + s*9 ));
    ScanActivFixture[6+s*8] = EEPROM.read(FixtureBaseEE + ( 6 + s*9 ));
    ScanActivFixture[7+s*8] = EEPROM.read(FixtureBaseEE + ( 7 + s*9 ));
    ScanActivFixture[64+s]  = EEPROM.read(FixtureBaseEE + ( 8 + s*9 ));
  }


// read the unique MAC address from Teensy
#include "mac.h"



/*
// the following code should be placed at the end of setup() since the watchdog starts right after this
WDOG_UNLOCK = WDOG_UNLOCK_SEQ1;
WDOG_UNLOCK = WDOG_UNLOCK_SEQ2;
delayMicroseconds(1); // Need to wait a bit..
WDOG_STCTRLH = 0x0001; // Enable WDG
WDOG_TOVALL = 1200; // The next 2 lines sets the time-out value. This is the value that the watchdog timer compare itself to.
WDOG_TOVALH = 0;
WDOG_PRESC = 0; // This sets prescale clock so that the watchdog timer ticks at 1kHZ instead of the default 1kHZ/4 = 200 HZ
*/
}


        

// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL

void loop() {
#if defined(MBC_36)
  if (digitalRead(Shift_BTN) == LOW) { shift = true; } else { shift = false; }
#endif

// debug
//  viewStatus(UnitsView, ProgMode, shift, leftEncPressed, leftLCDView, leftnewPos, rightEncPressed, rightLCDView, rightnewPos);

/*
// use the following 4 lines to kick the dog
noInterrupts();
WDOG_REFRESH = 0xA602;
WDOG_REFRESH = 0xB480;
interrupts()
// if you don't refresh the watchdog timer before it runs out, the system will be rebooted
*/
  
  CAMEO_BASE_ADR = DMXBase;
  SCANNER_BASE_ADR = DMXBase + (DMXUnits & 0b00000011) * 30;
  COB_BASE_ADR = DMXBase + (DMXUnits & 0b00000011) * 30 + ((DMXUnits & 0b00000100) >> 2) * 64 ;
  
  if (RUN==false) bpm_ms = millis();

/*  
  if ((millis()-ticker) > 100) { // update every 100ms

    ticker = millis();
  }
*/

//  Serial.print(" Mic: ");
//  Serial.println(analogRead(A11));

  loopCount++;

  if ( (millis()-startTime) > 50 && keypad.key[0].kstate > 0) {
    if(FSR_low > 0) {
      FSR = analogRead(A8) - FSR_low ;
      if(FSR > 127) { FSR = 127; }

      Serial.print(" FSR: ");
      Serial.print(FSR);
      Serial.print("   FSR_low: ");
      Serial.print(FSR_low);
      Serial.print("         Average loops per second = ");
      Serial.println(loopCount/5);

      usbMIDI.sendAfterTouch(FSR, MIDIChannel & 0b00001111); // Send aftertouch (pressure, channel)
//      MIDI.sendAfterTouch(FSR, MIDIChannel & 0b00001111); // Send aftertouch (pressure, channel)
    }
    startTime = millis();
    loopCount = 0;
  }
  if(keypad.key[0].kstate == 0) { FSR_low=0; FSR=0; }

  #include "Keys.h" // Keypad
  #include "EncLeft.h" // Encoder
  #include "EncRight.h" // Encoder

  // DMX ################################################################################
  #include "Cameo.h" // Cameo Pixbar 650
  #include "COB_4x4x4.h" // Eurolight LED PMC-16x30W, 4x4 COB LED 16x30W
  dmxTx.set(0, DMXbuffer, 512);
/*
  for (int i = 0; i < 64; i++) { 
    Serial.print(DMXbuffer[i],HEX);
    if(DMXbuffer[i] < 15 ) Serial.print(" ");
    Serial.print(" ");
  }
  Serial.println();
*/
  /// DMX ################################################################################

  if (usbMIDI.read()) // USB MIDI receive
  {
    miditype = usbMIDI.getType();
    usbMIDIdata1 = usbMIDI.getData1();
    usbMIDIdata2 = usbMIDI.getData2();
/*
    Serial.print("usbMIDItype:");
    Serial.print(miditype);
    Serial.print(" 1:");
    Serial.print(usbMIDIdata1);
    Serial.print(" 2:");
    Serial.print(usbMIDIdata2);
    Serial.print(" SPP:");
    Serial.println(songPositionPointer);
*/    
    if (miditype == SPP) { 
      songPositionPointer = usbMIDIdata2 * 128 + usbMIDIdata1;
      Count_Beats = (songPositionPointer & 0b00000011) ;
      Count_DMX = songPositionPointer / 4 + BeatStart ;
      if (bitRead(MIDIChannel,7)==0) { Count_8x8 = Count_DMX; }
      else { Count_8x8 = songPositionPointer / 16 + BeatStart; }
      SPPupdate();
      if ( MenuDepth == 0  && songPositionPointer % 4 == 0 && RUN == true && UnitsView != 1 ) { TFT_Draw_Count(); }
      else if ( MenuDepth == 0 && UnitsView != 1 ) { TFT_Draw_Count(); }
      for (int i = 0; i < 16; i++) pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // clear neopixel ring  
      ClearCounter();
      NeoPixelFastCounter = songPositionPointer * 6 % 96 ;
      Counter = songPositionPointer * 6  % 24 -1 ;
      ClockCounter();
    }
  }


#if defined(MIDI_SERIAL_2)
  if (Serial2.available() > 0) { 
    incomingByte = Serial2.read();
    CheckClock(); }
#endif

#if defined(MIDI_SERIAL_3)
  if (Serial3.available() > 0) {
    incomingByte = Serial3.read();
    CheckClock(); }
#endif

//    Serial.print("MIDI-DIN incoming Byte: ");
//    Serial.println(incomingByte, DEC);


#if defined(LED_8x8matrix) // LED matrix 8x8 ############################################

// number counting
  if (keypad.key[0].kstate == 0) { // no button pressed
    matrix.clear();
    if ((Count_8x8 % 32) < 16) {
      matrix.drawBitmap(0, 0, num_ + ((Count_8x8 % (CountLenght + 1)) + 1) * 8, 8, 8, LED_GREEN);
    }
    else if ((Count_8x8 % 32) < 24) {
      matrix.drawBitmap(0, 0, num_ + ((Count_8x8 % (CountLenght + 1)) + 1) * 8, 8, 8, LED_YELLOW);
    }
    else {
      matrix.drawBitmap(0, 0, num_ + ((Count_8x8 % (CountLenght + 1)) + 1) * 8, 8, 8, LED_RED);
    }
  }

  // bar counting
  matrix.drawBitmap(0, 6, BAR_8 + ((Count_8x8 >> 2) % 8), 8, 1, LED_YELLOW);
  matrix.drawBitmap(0, 6, BAR_2 + ((Count_8x8 >> 4) % 2), 8, 1, LED_RED);

  // blink LED
  if ((Count_8x8 % 32) > 23 && Counter > 11) matrix.drawBitmap(0, 6, BAR_8 + 7, 8, 1, LED_OFF);

  // every beat
  matrix.drawBitmap(0, 7, BAR_8 + 7, 8, 1, LED_OFF); // clear last row
  matrix.drawBitmap(0, 7, BAR_4 + (Count_8x8 % 4), 8, 1, LED_GREEN);

  matrix.writeDisplay();
 
#endif /// LED matrix 8x8 ###############################################################

}
/// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL


void RealTimeSystem(byte realtimebyte) {
  incomingByte = realtimebyte;          // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//    Serial.print("MIDI-USB incoming Byte: ");
//    Serial.println(incomingByte, DEC);
  CheckClock();
}

/*
void songPositionPointer(uint16_t songPosition) {
  Serial.print ("Song position: ");
  Serial.print (songPosition);
  Serial.print ("   Counter: ");
  Serial.println (Counter);

  Count_8x8 = songPosition/4 ;
  Count_DMX = songPosition/4 ;
  NeoPixelFastCounter = 0;
  incomingByte = SPP;
//  CheckClock();
}
*/

void CheckClock() {

  switch (incomingByte) {

    case CLOCK:
      ClockCounter();
//        Serial.print("Clock: ");
//        Serial.println(incomingByte, DEC);
        RUN = true;
      break;

    case START:
//      ClearCounter();
//      Serial.print("Start: ");
//      Serial.println(incomingByte, DEC);
//      if (keypad.key[0].kstate == 0 && digitalRead(rightENC_GREEN) == HIGH) { // no button pressed and green encoder LED off
//        TFT_Counter(); // write 1st beat to TFT
//      } 
        RUN = true;
      break;

    case CONTINUE:
//      ClearCounter();
//      Serial.print("Continue: ");
//      Serial.println(incomingByte, DEC);
//      if (keypad.key[0].kstate == 0 && digitalRead(rightENC_GREEN) == HIGH) { // no button pressed and green encoder LED off
//        TFT_Counter(); // write 1st beat to TFT
//      } 
        RUN = true;
      break;

    case STOP:
//      Serial.print("Stop: ");
//      Serial.println(incomingByte, DEC);
      RUN = false;
      break;

    case SPP:
      break;

    default:
      break;
  }
}


void ClockCounter() {

  Counter++;
  switch(Counter) {
    case 4:
      digitalWrite(iLED, HIGH);
      break;
    case 6:
      songPositionPointer++;
      if (RUN==true) { SPPupdate(); }
      break;
    case 12:
      songPositionPointer++;
      if (RUN==true) { SPPupdate(); }
      break;
    case 18:
      songPositionPointer++;
      if (RUN==true) { SPPupdate(); }
      break;
    case 20:
      Count_DMX++;  // shifts DMX out
      if(bitRead(MIDIChannel, 7)==0) { Count_8x8++; }
      else { Count_Beats++; if(Count_Beats > 3) { Count_Beats=0; Count_8x8++; }}    
      break;
    case 24:
      Counter = 0;
      songPositionPointer++;
      if (RUN==true) { SPPupdate(); }
      digitalWrite(iLED, LOW);
      break;
  }

  NeoPixelFastCounter++;
  if (NeoPixelFastCounter == 96) {
    NeoPixelFastCounter = 0;
    if (RUN == true && MenuDepth == 0) {
      tft.setFont();
      tft.setTextSize(_ts);
      tft.setTextColor(TFT_LightGray, TFT_Black);
      tft.setCursor(_tw/2+_ts*20, _ty+_ts*2);
      bpm = (bpm + 78692*pow(millis()-bpm_ms,-0.8662)+1) / 2 ;
//      tft.print(bpm);
      tft.setTextColor(TFT_Gray, TFT_Black);
      tft.setCursor(_tw/2+_ts*40, _ty+_ts*2);
//      tft.print("bpm");
    }
//    Serial.print(" BPM_ms: ");
//    Serial.println(millis()-bpm_ms);
    bpm_ms = millis();
  }

  // NeoPixel ###########################################################################
  
  // 2nd view DMX 8 pixbar[24] ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if ((leftLCDView & 0b00001111) == 0 && UnitsView == 2) { // view DMX 8 pixbar[24]
    // 15 = 1st, 0 = 16th
    int bright8 = 4;
    for (int i = 0; i < 24; i = i+3) {
        // count from 12:00 to 6:00 
      pixels.setPixelColor(15-i/3, pixels.Color(pixbar[i]/bright8, pixbar[i+1]/bright8, pixbar[i+2]/bright8));
      pixels.setPixelColor(7-i/3, pixels.Color(pixbar[i]/bright8, pixbar[i+1]/bright8, pixbar[i+2]/bright8));
        // count from 9:00 to 3:00 
//      pixels.setPixelColor((27-i/3) & 0b00001111, pixels.Color(pixbar[i]/bright8, pixbar[i+1]/bright8, pixbar[i+2]/bright8));
//      pixels.setPixelColor((19-i/3) & 0b00001111, pixels.Color(pixbar[i]/bright8, pixbar[i+1]/bright8, pixbar[i+2]/bright8));
    }
  }

  // 1st view, normal counting ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  else { // normal counting

    // clear last fast counter LED
    if ((NeoPixelFastCounter / 6 % 16) == 0) pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    else pixels.setPixelColor(16 - NeoPixelFastCounter / 6 % 16, pixels.Color(0, 0, 0));

    // clear last beat counter LED
    if (Count_DMX % 16 == 0) pixels.setPixelColor(0, pixels.Color(0, 0, 0));  
    else pixels.setPixelColor(16 - (Count_DMX % 16), pixels.Color(0, 0, 0));

    // count beats
    if (((Count_DMX) % 32) < 16) {
      RED = 28 - Counter * 2; // 28 off
      GREEN = 0;
      BLUE = 28 - Counter * 2;
    }
    else {
      RED = 56 - Counter * 4; // 56 off
      GREEN = 0;
      BLUE = 0;
    }
  
    if ((Count_DMX % 4) == 0 && Counter < 15 && RUN == true) {
      for (int i = 1; i < 5; i++) {
        pixels.setPixelColor(15 - (Count_DMX % 16) - i, pixels.Color(RED, GREEN, BLUE)); } // next 4 LEDs on
  
      if ((Count_DMX % 32) == 0 && RUN == true) {
        for (int i = 0; i < 16 - 4; i++) {
          pixels.setPixelColor(i, pixels.Color(RED, GREEN, BLUE)); }} // all LEDs on, 1st beat
    }
    
    if ((Count_DMX % 32) > 27 && Counter < 15 && RUN == true) {
      for (int i = 0; i < 4; i++) {
        pixels.setPixelColor(i, pixels.Color(RED, GREEN, BLUE)); }} // last 4 beats

    // fast counter 1 circle every beat
    pixels.setPixelColor(15 - NeoPixelFastCounter / 6 % 16, pixels.Color(0, 5, 0));
  
    if (RUN == false) { pixels.setPixelColor(15, pixels.Color(5, 5, 0)); } // top LED orientation
    
    pixels.setPixelColor( 15 - (Count_DMX % 16), pixels.Color(0, 0, 100)); // 0,0,80  blue
    if ((Count_DMX % 32) > 15) pixels.setPixelColor( 15 - (Count_DMX % 16), pixels.Color(50, 0, 50)); // 60,0,40   magenta

    if ((Count_DMX % 1) == 0 && Counter < 15 && RUN == true) {
      pixels.setPixelColor(15, pixels.Color(58 - Counter * 4, 58 - Counter * 4, 0)); } // top LED (56 off)
       
  }

/*    
    Serial.print("Cameo: ");
    for (int i = 0; i < 24; i++) { Serial.print(pixbar[i]); }
    Serial.println("");
    
    Serial.print("Calc: ");
    for (int i = 0; i < 24; i++) { Serial.print(15-i/3); }
    Serial.println("");
*/

  // copy COB 4x4x4 DMX to NeoPixel 8x8 matrix ++++++++++++++++++++++++++++++++++++++++++
  int bright64 = 4;
  int count64 = 40; // 16 + 24 neopixels before
  int j = 0;
  for (int i = 0; i < 64; i++ ) { // convert 4x4x4 COB to 8x8 NeoPixel
    // linear output 
    if(HATPattern==1) {
      switch (i) {
        case 0:  j =   0; break;
        case 4:  j =  36; break;
        case 8:  j = -12; break;
        case 12: j =  24; break;
        case 16: j = -24; break;
        case 20: j =  12; break;
        case 24: j = -36; break;
        case 28: j =   0; break;
        case 32: j =   0; break;
        case 36: j =  36; break;
        case 40: j = -12; break;
        case 44: j =  24; break;
        case 48: j = -24; break;
        case 52: j =  12; break;
        case 56: j = -36; break;
        case 60: j =   0; break; }
    }
    else { // Pimoroni Unicorn Hat for Raspi
      switch (i) {
        case  0: j =  57; break;
        case  1: j =  51; break;
        case  2: j =  45; break;
        case  3: j =  39; break;
        case  4: j =  -3; break;
        case  5: j =  -9; break;
        case  6: j = -15; break;
        case  7: j = -21; break;
        case  8: j = -12; break;
        case 12: j =  24; break;
        case 16: j =  33; break;
        case 17: j =  27; break;
        case 18: j =  21; break;
        case 19: j =  15; break;
        case 20: j = -27; break;
        case 21: j = -33; break;
        case 22: j = -39; break;
        case 23: j = -45; break;
        case 24: j = -36; break;
        case 28: j =   0; break;
        case 32: j =  57; break;
        case 33: j =  51; break;
        case 34: j =  45; break;
        case 35: j =  39; break;
        case 36: j =  -3; break;
        case 37: j =  -9; break;
        case 38: j = -15; break;
        case 39: j = -21; break;
        case 40: j = -12; break;
        case 44: j =  24; break;
        case 48: j =  33; break;
        case 49: j =  27; break;
        case 50: j =  21; break;
        case 51: j =  15; break;
        case 52: j = -27; break;
        case 53: j = -33; break;
        case 54: j = -39; break;
        case 55: j = -45; break;
        case 56: j = -36; break;
        case 60: j =   0; break;
      }
    }
    pixels.setPixelColor(count64, pixels.Color(DMXbuffer[COB_BASE_ADR+i*3+j]/bright64, DMXbuffer[COB_BASE_ADR+i*3+j+1]/bright64, DMXbuffer[COB_BASE_ADR+i*3+j+2]/bright64));
    count64++;
  }  
  /// copy COB 4x4x4 DMX to NeoPixel 8x8 matrix +++++++++++++++++++++++++++++++++++++++++


  // rescale brightness
  for(int i = 0; i < 16; i++) {
     RGB = pixels.getPixelColor(i);
     RED = RGB >> 16, GREEN = RGB >> 8, BLUE = RGB;
     pixels.setPixelColor(i, RED*float(NeoPixelBright*0.05), GREEN*float(NeoPixelBright*0.05), BLUE*float(NeoPixelBright*0.05)); }
  for(int i = 40; i < pixels.numPixels(); i++) {
     RGB = pixels.getPixelColor(i);
     RED = RGB >> 16, GREEN = RGB >> 8, BLUE = RGB;
     pixels.setPixelColor(i, RED*float(NeoPixelBright*0.05), GREEN*float(NeoPixelBright*0.05), BLUE*float(NeoPixelBright*0.05)); }
  
  pixels.show();
  
  // TFT ####################   FEDCBA9876543210    #####################################
  //                            RRRRRggggggBBBBB
  if ( MenuDepth == 0 && Counter == 20 && UnitsView != 1 ) { 
    TFT_Counter();
  }

  // DMX ################################################################################
  #include "Scanner.h" // SC-X50 MKII LED Scanner 

}


void TFT_Counter() {

  if(bitRead(MIDIChannel,7)==1) {  
    tft.fillRect(0, _ty, _tw, _th, TFT_Black);
    switch(Count_Beats) {
      case 0:
        tft.fillRect(0, _ty, _tw/4, _th, TFT_Orange);
        break;
      case 1:
        tft.fillRect(_tw/4, _ty, _tw/4, _th, TFT_Orange);
        break;
      case 2:
        tft.fillRect(_tw/2, _ty, _tw/4, _th, TFT_Orange);
        break;
      case 3:
        tft.fillRect(_tw/2+_tw/4, _ty, _tw/4, _th, TFT_Orange);
        break;
    }
  }

  if(bitRead(MIDIChannel,7)==0 || Count_Beats==0) {  

    if (Count_8x8 % (CountLenght + 1) + 1 == 1)  {
      tft.fillRect(_clx, _cly, _clw, _clh, LCD_bck_Color); // clear
    }
    int i = _ncx1;
    if (Count_8x8 % (CountLenght + 1) + 1 >= 10)  {
      i = _i2;
    }
    if (Count_8x8 % (CountLenght + 1) + 1 >= 100) {
      i = _i3;
    }
  
    tft.fillRect(i,   _ncy, _ncw, _nch, LCD_bck_Color); // 1-9 clear area
    tft.drawBitmap(i, _ncy, TFT_ + ((Count_8x8 % (CountLenght + 1) + 1) % 10 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color); // 1-9 320 ( char 64x40 )
  
    if (i == _i2 && (Count_8x8 % (CountLenght + 1) + 1) % 10 == 0 ) {
      tft.fillRect(  _ncx10, _ncy, _ncw, _nch, LCD_bck_Color); // clear area
      tft.drawBitmap(_ncx10, _ncy, TFT_ + (((Count_8x8 % (CountLenght + 1) + 1) / 10) % 10 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color);
    } // 10-99
  
    if (i == _i3  && (Count_8x8 % (CountLenght + 1) + 1) % 100 == 0 ) {
      tft.fillRect(  _ncx100, _ncy, _ncw, _nch, LCD_bck_Color); // clear area
      tft.drawBitmap(_ncx100, _ncy, TFT_ + (((Count_8x8 % (CountLenght + 1) + 1) / 100) % 10 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color);
    } // > 99
    
    if (i == _i3 && (Count_8x8 % (CountLenght + 1) + 1) % 10 == 0 ) {
      tft.fillRect(  _ncx1, _ncy, _ncw, _nch, LCD_bck_Color); // clear area
      tft.drawBitmap(_ncx1, _ncy, TFT_ + (((Count_8x8 % (CountLenght + 1) + 1) / 10) % 10 + LCDTextFont*10) * _ncp , _ncw , _nch, LCD_txt_Color);
    } // 0-9
  }  
/*
  Serial.print("i");
  Serial.print(i);
  Serial.print(" Count_8x8:");
  Serial.print(Count_8x8);
  Serial.print(" CountLenght:");
  Serial.println(CountLenght);
*/
}


void leftTFT_MenuSelect(int i) {
  tft.setFont();
  tft.fillRect(_tx, _ty, _tw, _th, TFT_Blue); // titel
  tft.setTextSize(_ts);
  tft.setCursor((_tw - strlen("Select MIDI Function") * 6 * _ts) / 2, _tty);
  tft.setTextColor(TFT_Yellow);
  tft.println("Select MIDI Function");

  tft.setFont(A24b);
  tft.setTextSize(1);
  tft.setTextColor(TFT_Black);
  tft.setCursor(_cy, _c3);
  tft.fillRect(_mx, _m3, _tw, _ms, TFT_Yellow);
  tft.println(leftTFT_Menu[i]); // selected

  tft.setFont(A24n);
  tft.setTextColor(TFT_MENU_1UP);
  tft.setCursor(_cy, _c2);
  tft.fillRect(_mx, _m2, _tw, _ms, TFT_MenuBack);
  tft.println(leftTFT_Menu[i - 1]); // one above
  tft.setCursor(_cy, _c4);
  tft.fillRect(_mx, _m4, _tw, _ms, TFT_MenuBack);
  tft.println(leftTFT_Menu[i + 1]); // one below

  tft.setTextColor(TFT_MENU_2UP);
  tft.setCursor(_cy, _c1);
  tft.fillRect(_mx, _m1, _tw, _ms, TFT_MenuBack);
  tft.println(leftTFT_Menu[i - 2]); // two above
  tft.setCursor(_cy, _c5);
  tft.fillRect(_mx, _m5, _tw, _ms+_ts, TFT_MenuBack);
  tft.println(leftTFT_Menu[i + 2]); // two below
}

void rightTFT_MenuSelect(int i) {
  tft.setFont();
  tft.fillRect(_tx, _ty, _tw, _th, TFT_Blue); // titel
  tft.setTextSize(_ts);
  tft.setCursor((_tw - strlen("Select DMX Function") * 6 * _ts) / 2, _tty);
  tft.setTextColor(TFT_Yellow);
  tft.println("Select DMX Function");

  tft.setFont(A24b);
  tft.setTextSize(1);
  tft.setTextColor(TFT_Black);
  tft.setCursor(_cy, _c3);
  tft.fillRect(_mx, _m3, _tw, _ms, TFT_Yellow);
  tft.println(rightTFT_Menu[i]); // selected

  tft.setFont(A24n);
  tft.setTextColor(TFT_MENU_1UP);
  tft.setCursor(_cy, _c2);
  tft.fillRect(_mx, _m2, _tw, _ms, TFT_MenuBack);
  tft.println(rightTFT_Menu[i - 1]); // one above
  tft.setCursor(_cy, _c4);
  tft.fillRect(_mx, _m4, _tw, _ms, TFT_MenuBack);
  tft.println(rightTFT_Menu[i + 1]); // one below

  tft.setTextColor(TFT_MENU_2UP);
  tft.setCursor(_cy, _c1);
  tft.fillRect(_mx, _m1, _tw, _ms, TFT_MenuBack);
  tft.println(rightTFT_Menu[i - 2]); // two above
  tft.setCursor(_cy, _c5);
  tft.fillRect(_mx, _m5, _tw, _ms+_ts, TFT_MenuBack);
  tft.println(rightTFT_Menu[i + 2]); // two below
  
}


void TFT_Color(int i) {
/*
 F E D C B A 9 8 7 6 5 4 3 2 1 0
 R R R R R G G G G G G B B B B B
 x x . . . x x . . . . x x . . .

  7  6  5  4  3  2  1  0
  R1 R0 G1 G0 B1 B0 h1 h0

 (R5-1) + (h1*2) + 2
 (G6+5) + (h1*2) + 2
*/ 
byte _LCD_bright = i & 0b00000011      ; // 0-1-2-3       0b......xx
byte _LCD_blue   = i & 0b00001100      ; // 0-8-16-24     0b...xx...
byte _LCD_green  = i & 0b00110000      ; // 0-8-16-24-48  0b..xx....
byte _LCD_red    = i & 0b11000000      ; // 0-8-16-24     0b...xx...

  if(_LCD_blue  > 0) _LCD_blue  = (_LCD_blue*2 + _LCD_bright * 2 + 1)  ;
  if(_LCD_green > 0) _LCD_green = ((_LCD_green + _LCD_bright * 4 + 3)) ;
  if(_LCD_red   > 0) _LCD_red   = ((_LCD_red/8 + _LCD_bright * 2 + 1)) ;
word  LCDColor = _LCD_blue + (_LCD_green << 5) + (_LCD_red << 11) ;

  tft.fillRect(_mx, _my, _tw, _cry-_m1-_ts*4, LCDColor);
  tft.fillRect(_mx, _my+_cry-_m1-_ts*4, _tw, _mh-_my+_cry-_m1-_ts*4, TFT_Black);

  tft.setFont(A32n);
  tft.setTextSize(1);
  tft.setCursor(_nxc1, _nyc);
  if (i >= 10)  {
    tft.setCursor(_nxc10, _nyc);
  }
  if (i >= 100) {
    tft.setCursor(_nxc100, _nyc);
  }
  tft.setTextColor(TFT_Yellow);
  tft.println(i);
 
  tft.setFont();
  tft.setTextSize(_ts);
  tft.setCursor(_crgbx, _cry);
  tft.print("   Red: ");
  tft.println(_LCD_red);
  tft.setCursor(_crgbx, _cgy);
  tft.print(" Green: ");
  tft.println(_LCD_green/2);
  tft.setCursor(_crgbx, _cby);
  tft.print("  Blue: ");
  tft.println(_LCD_blue);
  tft.setCursor(_crgbx, _chy);
//  tft.print("Bright: ");
//  tft.println(_LCD_bright);
/*
  tft.print(" Bright: ");
  tft.println(_LCD_bright);
  tft.setTextSize(1);
  tft.setCursor(30, 90);
  tft.println(LCDColor, BIN);
  tft.setCursor(30, 100);
  tft.println("FEDCBA9876543210");
*/
}


void TFT_MenuValue(int i) {
  
  tft.fillRect(_mx, _my, _tw, _mh, TFT_Black); // clear area

  tft.setFont(A96n);
  tft.setCursor(_nx1, 45*_ts);
  if (i >= 10)  {
    tft.setCursor(_nx10, 45*_ts);
  }
  if (i >= 100) {
    tft.setFont(A96n);
    tft.setCursor(_nx100, 45*_ts);
  }
  tft.setTextColor(TFT_Yellow);
  tft.println(i);
}


void TFT_2_MenuValue() {
  
  tft.fillRect(_mx, _my, _tw, _mh, TFT_Black); // clear area

  tft.setFont(A24n);
  tft.setTextColor(TFT_White);
  tft.setCursor(left_half_bound, _c2);
  tft.print(left_str);
  tft.setCursor(_tw/2+right_half_bound, _c2);
  tft.print(right_str);

  tft.setFont(A60n);
  tft.setCursor(_ts*18, 65*_ts);
  if (leftnewPos >= 10)  {
    tft.setCursor(_ts*7, 65*_ts);
  }
  if (leftnewPos >= 100) {
    tft.setFont(A48n);
    tft.setCursor(_ts*2, 68*_ts);
  }
  tft.setTextColor(TFT_Yellow);
  tft.println(leftnewPos);
  
  tft.drawLine(_tw/2-_ts, _tw/3, _tw/2-_ts, _tw-_ts*15, TFT_Green);

  tft.setFont(A60n);
  tft.setTextSize(_ts);
  tft.setCursor(_tw/2+_ts*18, 65*_ts);
  if (rightnewPos >= 10)  {
    tft.setCursor(_tw/2+_ts*7, 65*_ts);
  }
  if (rightnewPos >= 100) {
    tft.setFont(A48n);
    tft.setCursor(_tw/2+_ts*2, 68*_ts);
  }
  tft.setTextColor(TFT_Yellow);
  tft.println(rightnewPos);
  
}


void TFT_UpperTextandNumber(String Text, int i) {
  tft.setFont();
  tft.fillRect(_tx, _ty, _tw, _th, TFT_Blue); // clear area
  tft.setTextSize(_ts); // 10 for 2 digit; 6 for 3 digits
  tft.setCursor((128 - Text.length() * 6) / 2, 9);
  tft.setTextColor(TFT_Yellow);
  tft.println(Text);
  TFT_MenuValue(i);
}


void ClearCounter() {
  Counter = 0;

  NeoPixelFastCounter = (24 * (BeatStart) % 96); // define start count
  Count_Beats = BeatStart  & 0b00000011; // define start count
  Count_8x8 = BeatStart; // define start count
  Count_DMX = BeatStart; // define start count

  if ( songPositionPointer > 0 ) {
    Count_Beats = (songPositionPointer & 0b00000011) ;
    Count_DMX = songPositionPointer / 4 + BeatStart ;
    if (bitRead(MIDIChannel,7)==0) { Count_8x8 = Count_DMX; }
    else { Count_8x8 = songPositionPointer / 16 + BeatStart; }
  }
}


void SPPupdate() {
  tft.setFont();
  tft.setTextSize(_ts);
  tft.setCursor((_tw/2 - strlen("SPP:1234.1.1 123 bpm") * 3 * _ts), 0);
  tft.setTextColor(TFT_Gray, TFT_Black);
  if (songPositionPointer /16 +1 > 999) {     tft.print("SPP:"); }
  else if (songPositionPointer /16 +1 > 99) { tft.print(" SPP:"); }
  else if (songPositionPointer /16 +1 > 9) {  tft.print("  SPP:"); }
  else {                                      tft.print("   SPP:"); }
  tft.setTextColor(TFT_Cyan, TFT_Black);
  tft.print(songPositionPointer/16+1);
  tft.print(".");
  tft.print((songPositionPointer/4) %4 +1);
  tft.setTextColor(0x05DD, TFT_Black);
  tft.print(".");
  tft.print(songPositionPointer %4 +1);
  tft.print("  ");

  tft.setTextColor(TFT_LightGray, TFT_Black);
  tft.setCursor(_tw/2+_ts*20, 0);
  tft.print(bpm);
  tft.setTextColor(TFT_Gray, TFT_Black);
  tft.setCursor(_tw/2+_ts*40,0);
  tft.print("bpm");

}


void BPM() {
//  Serial.println("0.1 second timer");
  Timer3.setPeriod(100000);
}
