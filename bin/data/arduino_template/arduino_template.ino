#include <FastSPI_LED.h>

#define PIN 4

$INSERT_IMAGE_DATA_HERE$

struct CRGB { unsigned char r; unsigned char g; unsigned char b; };
struct CRGB *leds;

void setup() {
  FastSPI_LED.setLeds(N_PIXELS);
  FastSPI_LED.setChipset(CFastSPI_LED::SPI_WS2801);
  FastSPI_LED.setDataRate(3);
  FastSPI_LED.setPin(PIN);  
  FastSPI_LED.init();
  FastSPI_LED.start();

  leds = (struct CRGB*)FastSPI_LED.getRGBData(); 
}

void loop() {
  memset(leds, 0, N_PIXELS * 3);
  for(int frame=0; frame<N_FRAMES; frame++){
    for(int pixel=0; pixel<N_PIXELS; pixel++){
      leds[pixel].r = frames[frame][pixel][0];
      leds[pixel].g = frames[frame][pixel][1];
      leds[pixel].b = frames[frame][pixel][2];
    }
    FastSPI_LED.show();
    delay(50);
  }  
}


/*

green wire	- pin 13
red wire	- pin 11
yellow wire	- v in
white wire	- gnd

*/

/*
int toHex(int r, int g, int b){
	return
	((0xff & (unsigned char) r) << 16) |
	((0xff & (unsigned char) g) << 8) |
	((0xff & (unsigned char) b));
}
*/
