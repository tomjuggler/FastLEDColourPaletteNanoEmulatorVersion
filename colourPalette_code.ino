void FillHalf( uint8_t colorIndex, uint8_t var, int start, int finish)
{
  uint8_t brightness = 255;
  for ( int i = start; i < finish; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex = colorIndex + var; //change this to change pattern nicely!!
  }
}

void FillHalfBackwards( uint8_t colorIndex, uint8_t var, int start, int finish)
{
  uint8_t brightness = 255;
  for ( int i = start; i < finish; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex = colorIndex - var; //change this to change pattern nicely!!
  }
}

void FillPatternStripesFromPaletteColors( uint8_t colorIndex, uint8_t var)
{
  uint8_t brightness = 255;
  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex = colorIndex + var; //change this to change pattern nicely!!
  }
}

void ChangeStripesPeriodically()
{
  uint8_t secondHand = (millis() / 1000) % 60; //last number is number of seconds the whole thing lasts!
  static uint8_t lastSecond = 99;

  if ( lastSecond != secondHand) {
    lastSecond = secondHand;
    if ( secondHand == 1 )  {
      //      SetupVariablePalette6(CRGB::Red, CRGB::Green, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Blue);
      SetupVariablePalette(CRGB::Black, CRGB::Blue, CRGB::Black, CRGB::Green);
    }
    if ( secondHand == 10)  {
      SetupVariablePalette(CRGB::Yellow, CRGB::Black, CRGB::Blue, CRGB::Black);
    }
    if ( secondHand == 20)  {
      SetupVariablePalette(CRGB::Cyan, CRGB::Black, CRGB::Yellow, CRGB::Black);
    }
    if ( secondHand == 30)  {
      SetupVariablePalette(CRGB::Magenta, CRGB::Black, CRGB::Green, CRGB::Black); //was red and green but my screen won't show it now...
    }
    if ( secondHand == 40)  {
      SetupVariablePalette(CRGB::Cyan, CRGB::Black, CRGB::Magenta, CRGB::Black);
    }
    if ( secondHand == 50)  {
      SetupVariablePalette(CRGB::Green, CRGB::Black, CRGB::Blue, CRGB::Black);
    }
    if ( secondHand == 5)  {
//      stripeVar+=4; 
//      if (stripeVar > 12) {
//        stripeVar = 4;
//      }
    }
  }
}

void SetupVariablePalette(CRGB a, CRGB b, CRGB c, CRGB d)//4 colours default
{

  currentPalette = CRGBPalette16(a, b, c, d, a, b, c, d, a, b, c, d, a, b, c, d);
}
