#include <Adafruit_NeoPixel.h>

#define PIN 2
#define NUM_LEDS 6
#define NUM_COLORS 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// This is run once at the beginning
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

// This main loop is looped over and over
void loop() {  
  setColorAll(0,0,0); // Turn all the pixels off
  setColor(0, 255,0,0); // Set the first pixel (pixel 0) to red
  delay(2000); // Delay in milliseconds. 1000ms = 1 second
  setColor(0, 0,0,0); // Turn off the second pixel

// -----------------EXAMPLE 1--------------------------------------
  // This shows a static rainbow

  setColor(0, 255,0,0); //Pixel 0 to Red
  setColor(1, 255,255,0); //Pixel 1 to Yellow
  setColor(2, 0,255,0); //Pixel 2 to Green
  setColor(3, 0,255,255); //Pixel 3 to Cyan
  setColor(4, 0,0,255); //Pixel 4 to Blue
  setColor(5, 255,0,255); //Pixel 5 to Magenta
  delay(3000);

  setColorAll(0,0,0); // Turn all the pixels off
  setColor(1, 255,0,0); // Set the second pixel (pixel 1) to red
  delay(2000); // Delay in milliseconds. 1000ms = 1 second
  setColor(1, 0,0,0); // Turn off the second pixel

// -----------------EXAMPLE 2--------------------------------------
  // This is a rainbow where all the pixels are the same color, 
  // and changes are abrupt between colors

  int ms=500;
  setColorAll(255,0,0); //Pixel 0 to Red
  delay(ms);
  setColorAll(255,255,0); //Pixel 1 to Yellow
  delay(ms);
  setColorAll(0,255,0); //Pixel 2 to Green
  delay(ms);
  setColorAll(0,255,255); //Pixel 3 to Cyan
  delay(ms);
  setColorAll(0,0,255); //Pixel 4 to Blue
  delay(ms);
  setColorAll(255,0,255); //Pixel 5 to Magenta
  delay(ms);

  setColorAll(0,0,0); // Turn all the pixels off
  setColor(2, 255,0,0); // Set the third pixel (pixel 2) to red
  delay(2000); // Delay in milliseconds. 1000ms = 1 second
  setColor(2, 0,0,0); // Turn off the third pixel

// -----------------EXAMPLE 3--------------------------------------
  // This is a rainbow where all the pixels are the same color,
  // and changes fade between colors
  
  for(int j=0; j<256; j++) {
    for(int i=0; i<NUM_LEDS; i++) {
      strip.setPixelColor(i, Wheel(j));
    }
    strip.show();
    delay(20); //in milliseconds
  }

  setColorAll(0,0,0); // Turn all the pixels off
  setColor(3, 255,0,0); // Set the fourth pixel (pixel 3) to red
  delay(2000); // Delay in milliseconds. 1000ms = 1 second
  setColor(3, 0,0,0); // Turn off the fourth pixel

// -----------------EXAMPLE 4--------------------------------------
  // Fading rainbow where each pixel is a different color
  
  for(int j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(int i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) % 255));
    }
    strip.show();
    delay(2); //in milliseconds
  }

  setColorAll(0,0,0); // Turn all the pixels off
  setColor(4, 255,0,0); // Set the fifth pixel (pixel 4) to red
  delay(2000); // Delay in milliseconds. 1000ms = 1 second
  setColor(4, 0,0,0); // Turn off the fifth pixel

// -----------------EXAMPLE 5--------------------------------------
  // nifty "falling and stacking in different colors" effect
  for(int color=0; color<255; color+= 50){ // "wheel()" takes values from 0 to 255. This loop does color 0, 50, 100, 200, and 250
    for(int lightsThatAreAlreadyOn = 0; lightsThatAreAlreadyOn < NUM_LEDS; lightsThatAreAlreadyOn++){
      for(int lightThatIsOn = 0; lightThatIsOn < NUM_LEDS - lightsThatAreAlreadyOn; lightThatIsOn++){
       setColor(lightThatIsOn, Wheel(color));
       delay(75);
       setColor(lightThatIsOn, 0,0,0);
      }
      setColor(NUM_LEDS - lightsThatAreAlreadyOn - 1, Wheel(color)); // after a color falls, set it to the farthest LED that doesn't already have a color
    }
    setColorAll(0,0,0);
  }
} // End of main loop



// HELPER FUNCTIONS

// Sets pixel i to an RGB color and then shows the strip
void setColor(int i, byte red, byte green, byte blue) {
  strip.setPixelColor(i, red,green,blue);
  strip.show();
} // End of setColor

void setColor(int i, uint32_t wheelColor){
  strip.setPixelColor(i, wheelColor);
  strip.show();
}

// Sets all the pixels to an RGB color and then shows the strip
void setColorAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    strip.setPixelColor(i, red,green,blue);
  }
  strip.show();
} // End of setColorAll

void setColorAll(uint32_t wheelColor){
  for(int i = 0; i < NUM_LEDS; i++ ) {
    strip.setPixelColor(i, wheelColor);
  }
  strip.show();
}


// Causes num pixels to light up as red, one at a time
void countdown(int num, byte red, byte green, byte blue) {
  setColorAll(0,0,0);
  for (int i=0; i<num; i++) {
    setColor(i, red,green,blue);
    delay(500);
    setColor(i, 0,0,0);
  }
} // End of countdown


// This returns a value that can be used to set a color of a pixel
uint32_t Wheel(byte WheelPos) {
  
  if(WheelPos < 85) {
    //As position goes from 0 to 84, red lowers and blue rises by 3
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  
  else if(WheelPos < 170) {
    //As position goes from 85 to 169, green rises and blue lowers by 3
    WheelPos -= 85; //To get a value between 0 and 84
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } 
  
  else if(WheelPos < 256) {
    //As position goes from 170-255, red rises and green lowers by 3
    WheelPos -= 170; //To get a value between 0 and 84
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
} // End of Wheel

