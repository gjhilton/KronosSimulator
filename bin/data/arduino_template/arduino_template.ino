$INSERT_IMAGE_DATA_HERE$

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  for(int frame=0; frame<N_FRAMES; frame++){
		for(int pixel=0; pixel<N_PIXELS; pixel++){
			int colour = frames[frame][pixel];
			int r = (colour >> 16) & 0xff;
			int g = (colour >> 8) & 0xff;
			int b = (colour >> 0) & 0xff;
			//	TODO: do something with these values	
		}
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