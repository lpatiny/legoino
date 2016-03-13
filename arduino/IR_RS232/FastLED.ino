#include <FastLED.h>

#define NUM_LEDS    400
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];


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


extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
extern const TProgmemPalette16 blackPalette PROGMEM;
extern const TProgmemPalette16 blueRedPalette PROGMEM;
extern const TProgmemPalette16 blueGreenRedPalette PROGMEM;
extern const TProgmemPalette16 blueDarkVioletPalette PROGMEM;


void setupFastLED() {
  //  delay( 1000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );

  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
}


void loopFastLED()
{
  FastLED.setBrightness(  getIntensity() );

  if (getParameter(PARAM_POWER)==0) {
    currentPalette=blackPalette;
  } 
  else {
    getPalette();
  }
  static uint8_t startIndex = 0;
  startIndex = startIndex + getParameter(PARAM_SPEED); /* motion speed */
  FillLEDsFromPaletteColors( startIndex);

  FastLED.show();
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, 255, currentBlending);
    colorIndex += getParameter(PARAM_CHANGE);
  }
}

// RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
void getPalette() {
  switch (getParameter(PARAM_COLOR_MODEL)) {
  case 0:
    currentPalette=RainbowColors_p;
    break;
  case 1:
    currentPalette=RainbowStripeColors_p;
    break;
  case 2:
    currentPalette=OceanColors_p;
    break;
  case 3:
    currentPalette=CloudColors_p;
    break;
  case 4:
    currentPalette=LavaColors_p;
    break;
  case 5:
    currentPalette=ForestColors_p;
    break;
  case 6:
    currentPalette=PartyColors_p;
    break;
     case 7:
    currentPalette=blueRedPalette;
    break;
     case 8:
    currentPalette=blueGreenRedPalette;
    break;
         case 9:
    currentPalette=blueDarkVioletPalette;
    break;
  }
}

// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically()
{
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;

  if( lastSecond != secondHand) {
    lastSecond = secondHand;
    if( secondHand ==  0)  { 
      currentPalette = RainbowColors_p;         
      currentBlending = LINEARBLEND; 
    }
    if( secondHand == 10)  { 
      currentPalette = RainbowStripeColors_p;   
      currentBlending = NOBLEND;  
    }
    if( secondHand == 15)  { 
      currentPalette = RainbowStripeColors_p;   
      currentBlending = LINEARBLEND; 
    }
    if( secondHand == 20)  { 
      SetupPurpleAndGreenPalette();             
      currentBlending = LINEARBLEND; 
    }
    if( secondHand == 25)  { 
      SetupTotallyRandomPalette();              
      currentBlending = LINEARBLEND; 
    }
    if( secondHand == 30)  { 
      SetupBlackAndWhiteStripedPalette();       
      currentBlending = NOBLEND; 
    }
    if( secondHand == 35)  { 
      SetupBlackAndWhiteStripedPalette();       
      currentBlending = LINEARBLEND; 
    }
    if( secondHand == 40)  { 
      currentPalette = CloudColors_p;           
      currentBlending = LINEARBLEND; 
    }
    if( secondHand == 45)  { 
      currentPalette = PartyColors_p;           
      currentBlending = LINEARBLEND; 
    }
    if( secondHand == 50)  { 
      currentPalette = myRedWhiteBluePalette_p; 
      currentBlending = NOBLEND;  
    }
    if( secondHand == 55)  { 
      currentPalette = myRedWhiteBluePalette_p; 
      currentBlending = LINEARBLEND; 
    }
  }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
  for( int i = 0; i < 16; i++) {
    currentPalette[i] = CHSV( random8(), 255, random8());
  }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;

}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;

  currentPalette = CRGBPalette16(
  green,  green,  black,  black,
  purple, purple, black,  black,
  green,  green,  black,  black,
  purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Gray, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black
};


const TProgmemPalette16 blackPalette PROGMEM =
{
  CRGB::Black,
  CRGB::Black, // 'white' is too bright compared to red and blue
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black
};


const TProgmemPalette16 blueRedPalette PROGMEM =
{
  CRGB::Blue,
  CRGB::Blue, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red
};

const TProgmemPalette16 blueGreenRedPalette PROGMEM =
{
  CRGB::Blue,
  CRGB::Blue, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Green,
  CRGB::Green,
  CRGB::Green,
  CRGB::Green,
  CRGB::Green,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red
};

const TProgmemPalette16 blueDarkVioletPalette PROGMEM =
{
  CRGB::Blue,
  CRGB::Blue, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet
};


