#include <Adafruit_NeoPixel.h>

#define PIN 0
#define NUM_LEDS 3
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
  strip.setBrightness(20);
  strip.show(); // Initialize all pixels to 'off'
}

// This main loop is looped over and over
void loop() {  

  // Jerky rainbow
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

  // Fading rainbow, all pixel the same color
  for(int j=0; j<256; j++) {
    for(int i=0; i<NUM_LEDS; i++) {
      strip.setPixelColor(i, Wheel(j));
    }
    strip.show();
    delay(20); //in milliseconds
  }

  // Fading rainbow, all pixels different color
  for(int j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(int i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) % 255));
    }
    strip.show();
    delay(2); //in milliseconds
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
