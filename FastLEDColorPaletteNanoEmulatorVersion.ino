#include <FastLED.h>
//apa102:
#define DATA_PIN 2 //D2 for D1Mini, 2 for ESP-01
#define CLOCK_PIN 0 //D1 for D1Mini, 0 for ESP-01

#define LED_PIN     D6 //for ws2812
#define NUM_LEDS    37
#define BRIGHTNESS  20 //change to 200 for shows!!!!
#define LED_TYPE    APA102
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

boolean upDown = true;
boolean lines = true;

#define UPDATES_PER_SECOND 30000

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.



CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

int paletteVar = 1;

int motionSpeed = 1;
int maxStartIndex = 70;
int minStartIndex = 0;
volatile int setting = 2;
int stripeIndex2 = 0;
int stripeVar = 2;
boolean backwards = false;


boolean emulated = true;


/****Variables needed for sending to Processing. */
uint16_t sendDelay = 10;    // [Milliseconds] To slow stuff down if needed.
boolean testing = false;  // Default is false. [Ok to change for testing.]
// Can temporarily change testing to true to check output in serial monitor.
// Must set back to false to allow Processing to connect and receive data.

boolean linkedUp = true;  // Initially set linkup status false. [Do Not change.]
/****End of variables needed for sending Processing. */

void setup() {
//  delay( 3000 ); // power-up safety delay - for new hardware setups and such
 
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS); //DATA_RATE_MHZ(8)
  //  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  //currentPalette = RainbowStripeColors_p;
  currentBlending = NOBLEND;

  /****Stuff needed in setup() section for sending to Processing. */
  Serial.begin(115200);  // Allows serial output.
  if(emulated){
//  while (!Serial) {
//    ;  // Wait for serial connection. Only needed for Leonardo board.
//  }
  firstContact();  // Connect with Processing. Hello, is anyone out there?
  /****End of stuff to put in your setup() section for Processing. */
  }
}


void loop()
{
  
  // This tests if serial is connected.  Needed for sending to Processing. //
//  if (linkedUp == true) {  // Check to see if connected with Processing. //
/*
//    if (setting == 1) { //updown and diagonal stripes changing colour according to ChangePalettePeriodically3()

      if (lines == false) { //toggled in ChangePalettePeriodically3()
        //ChangePalettePeriodically2();
//        ChangePaletteEveryTime();
        //Serial.println(paletteVar);
        //PaletteSetup();
        //SetupVariablePalette(CRGB::Red, CRGB::Gray, CRGB::Blue, CRGB::Black);
        //SetupRandomVariablePalette(CRGB::Red, CRGB::Gray, CRGB::Blue, CRGB::Black);
        ChangePalettePeriodically3();
        static uint8_t startIndex = 0;
        if (upDown == true) {
          startIndex = startIndex + motionSpeed; // motion speed 
          FillLEDsFromPaletteColors( startIndex);
          //Serial.println(startIndex);
          if (startIndex == maxStartIndex) {
            upDown = false;
          }
        }
        else {
          startIndex = startIndex - motionSpeed; // motion speed /
          FillLEDsFromPaletteColors( startIndex);
          //Serial.println(startIndex);
          if (startIndex == minStartIndex) {
            upDown = true;
          }
        }

        //add_glitter();

        FastLED.show();
        if(emulated){
        SendToProcessing();
        FastLED.delay(1000 / UPDATES_PER_SECOND);
      }
        
//          motionSpeed++;
//          if(motionSpeed == 10){
//          motionSpeed = 1;
//          }
//
//          minStartIndex++;
//          if(minStartIndex == 20){
//          minStartIndex = 0;
//          }
//          maxStartIndex--;
//          if(maxStartIndex == 30){
//          maxStartIndex = 70;
//          }
        
      }//end if(lines)
      else {
        //ChangePalettePeriodically2();
        //ChangePaletteEveryTime();
        //Serial.println(paletteVar);
        //PaletteSetup();
        //SetupVariablePalette(CRGB::Red, CRGB::Gray, CRGB::Blue, CRGB::Black);
        //SetupRandomVariablePalette(CRGB::Red, CRGB::Gray, CRGB::Blue, CRGB::Black);
        ChangePalettePeriodically3();
        static uint8_t startIndex = 0;
        startIndex = startIndex + motionSpeed; // motion speed 
        FillLEDsFromPaletteColors( startIndex);
        //Serial.println(startIndex);
        if (startIndex == maxStartIndex) {
          startIndex = 0;
        }
        //add_glitter();
        //add_glitter from https://gist.github.com/kriegsman/ccffc81a74bc03636ce1
        FastLED.show(); 
      if(emulated){
        SendToProcessing();
        FastLED.delay(1000 / UPDATES_PER_SECOND);
      }
       
//          motionSpeed++;
//          if(motionSpeed == 10){
//          motionSpeed = 1;
//          }
//
//          minStartIndex++;
//          if(minStartIndex == 20){
//          minStartIndex = 0;
//          }
//          maxStartIndex--;
//          if(maxStartIndex == 30){
//          maxStartIndex = 70;
//          }
       

      }//end else(lines)
//    }//end if(setting ==1)
*/

//    else if (setting == 2) //full colour stripes on/off
//    {
/*
      ChangeStripesPeriodically();
      static uint8_t stripeIndex = 0;
      stripeIndex = stripeIndex + 1;
      FillStripesFromPaletteColors( stripeIndex);
      //Serial.println(startIndex);
      if (stripeIndex > 15) {
        stripeIndex = 0;
      }
      //add_glitter();
      //add_glitter from https://gist.github.com/kriegsman/ccffc81a74bc03636ce1
      FastLED.show(); SendToProcessing();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
      */
//    }//end if(setting == 2)
//    else
//    {
//if(setting == 1){

EVERY_N_SECONDS(2) {
//    backwards = !backwards;
  }
  


      ChangeStripesPeriodically();      
      stripeIndex2 = stripeIndex2 + PI;
//      FillPatternStripesFromPaletteColors(stripeIndex2, stripeVar);
if(!backwards){
FillHalf(stripeIndex2, stripeVar, 0, 18);
} else{
  FillHalfBackwards(stripeIndex2, stripeVar, 0, 18);
}
     
      
      //Serial.println(startIndex);
//      int happy = random(1, 37);
      if (stripeIndex2 > NUM_LEDS*4) {
        stripeIndex2 = 0;
        backwards = !backwards;
//        stripeVar ++;
//        stripeVar = random8(0, 37);
      }
      stripeVar = -stripeVar;
      if(!backwards){
      FillHalf(stripeIndex2, stripeVar, 18, NUM_LEDS);
      }else{
        FillHalfBackwards(stripeIndex2, stripeVar, 18, NUM_LEDS);
      }
//      FillPatternStripesFromPaletteColors(stripeIndex2, stripeVar);
      stripeVar = -stripeVar;
//}else{
//  ChangeStripesPeriodically();      
//      stripeIndex2 = stripeIndex2 - 1;
////      stripeVar = random8(0, 37);
//      FillPatternStripesFromPaletteColors(stripeIndex2, stripeVar);
//
//      
//      
//      
//      //Serial.println(startIndex);
////      int happy = random(1, 37);
//      if (stripeIndex2 > -NUM_LEDS) {
//        stripeVar = random8(0, 37);
//        stripeIndex2 = NUM_LEDS;
//      }
//      stripeVar = -stripeVar;
//}
      //add_glitter();
      //add_glitter from https://gist.github.com/kriegsman/ccffc81a74bc03636ce1
      FastLED.show(); 
      if(emulated){
        SendToProcessing();
        FastLED.delay(1000 / UPDATES_PER_SECOND);
      }

//    }//end else 3

    
//  }
}//end loop





/****The below two functions are needed for sending to Processing. */
// Copy from here to the bottom.
//--------------------
// Waits for Processing to respond and then sends the number of pixels.
void firstContact() {
  uint16_t nLEDS = NUM_LEDS;  // Number to send to Processing.  (Allows up to 65,535 pixels)
  if (testing == true) {
    linkedUp = true;  // If testing, pretend we are already connected to Processing.
    Serial.print("NUM_LEDS: "); Serial.println(nLEDS);  // Number of pixels in our LED strip.
    Serial.print("  High Byte = "); Serial.print(highByte(nLEDS));  // The high byte.
    Serial.print(" x 256 = "); Serial.println(highByte(nLEDS) * 256);
    Serial.print("  Low Byte  = "); Serial.println(lowByte(nLEDS));  // The low byte.
    delay(3000);
  }
  else {
    while (Serial.available() <= 0) {  // Repeats until Processing responds. Hello?
      Serial.print('A');  // send an ASCII A (byte of value 65)
      delay(100);
    }
    // Once Processing responds send the number of pixels as two bytes.
    Serial.write(highByte(nLEDS));  // Send the high byte to Processing.
    Serial.write(lowByte(nLEDS));  // Send the low byte to Processing.
    Serial.print('#');  // send an ASCII # (byte of value 35) as a flag for Processing.
    linkedUp = true;  // Now that Processing knows number of pixels set linkedUp to true.
    delay(500);
  }
}

//--------------------
// This function sends ALL the pixel data to Processing.
void SendToProcessing() {
  if (testing == true) { // Print pixel data. If NUM_LEDS is large this will be a lot of data!
    Serial.println("-------------------------------------------------------");
    for (uint16_t d = 0; d < NUM_LEDS; d++) {
      Serial.print("p: "); Serial.print(d);
      Serial.print("\tr: "); Serial.print(leds[d].g);
      Serial.print("\tg: "); Serial.print(leds[d].b);
      Serial.print("\tb: "); Serial.println(leds[d].r);
    }
    Serial.println(" ");
    delay(500);  // Add some extra delay while testing.
  }
  else {  // Send ALL the pixel data to Processing!
    for (uint16_t d = 0; d < NUM_LEDS; d++) {
      Serial.write(d);          // Pixel number
      Serial.write(leds[d].g);  // Red channel data
      Serial.write(leds[d].b);  // Green channel data
      Serial.write(leds[d].r);  // Blue channel data
    }
    delay(sendDelay);  // Delay to slow things down if needed.
  }
}

//--------------------
/****End of the functions needed for sending to Processing.*/


// Additionl notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.
