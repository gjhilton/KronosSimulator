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
      int colour = frames[frame][pixel];
      int r = (colour >> 16) & 0xff;
      int g = (colour >> 8) & 0xff;
      int b = (colour >> 0) & 0xff;
      
      leds[pixel].r = r;
      leds[pixel].g = g;
      leds[pixel].b = b;
    }
    FastSPI_LED.show();
    delay(10);
  }  
}


/*

// example image data format

#define N_FRAMES 2
#define N_PIXELS 4

const int frames[N_FRAMES][N_PIXELS] = {{1,2,3,4},{5,6,7,8}};

*/

/*
int toHex(int r, int g, int b){
	return
	((0xff & (unsigned char) r) << 16) |
	((0xff & (unsigned char) g) << 8) |
	((0xff & (unsigned char) b));
}
*/
