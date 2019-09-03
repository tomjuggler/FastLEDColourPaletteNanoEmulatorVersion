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





CRGBPalette16 currentPalette;
TBlendType    currentBlending;

int paletteVar = 1;

int motionSpeed = 1;
int maxStartIndex = 70;
int minStartIndex = 0;
volatile int setting = 2;
int stripeIndex2 = 0;
int stripeVar = 4;
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

  currentBlending = NOBLEND;

  /****Stuff needed in setup() section for sending to Processing. */
  Serial.begin(115200);  // Allows serial output.
  if (emulated) {
    //  while (!Serial) {
    //    ;  // Wait for serial connection. Only needed for Leonardo board.
    //  }
    firstContact();  // Connect with Processing. Hello, is anyone out there?
    /****End of stuff to put in your setup() section for Processing. */
  }
}


void loop()
{  
  EVERY_N_SECONDS(5) {
    //so something here?
  }
  ChangeStripesPeriodically(); //or try built in palette:  // currentPalette = RainbowStripeColors_p; //super awesome rainbows!
  stripeIndex2 = stripeIndex2 + PI*2;
  if (!backwards) {
    FillHalf(stripeIndex2, stripeVar, 0, 18);
  } else {
    FillHalfBackwards(stripeIndex2, stripeVar, 0, 18);
  }

  if (stripeIndex2 > NUM_LEDS * 4) {
    stripeIndex2 = 0;
    backwards = !backwards;

  }
  stripeVar = -stripeVar;
  if (!backwards) {
    FillHalf(stripeIndex2, stripeVar, 18, NUM_LEDS);
  } else {
    FillHalfBackwards(stripeIndex2, stripeVar, 18, NUM_LEDS);
  }
  stripeVar = -stripeVar;
  FastLED.show();
  if (emulated) {
    SendToProcessing();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
  }

}//end loop





/****The below two functions are needed for sending to Processing. */

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
