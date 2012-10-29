/*
 
quick test app as example of colour conversion
 
*/


#include <stdio.h>

#define N_FRAMES 3
#define N_PIXELS 2

const int frames[N_FRAMES][N_PIXELS] = {{16777215,0},{0,16777215},{16777215,0}};

int toHex(int r, int g, int b){
	return
	((0xff & (unsigned char) r) << 16) |
	((0xff & (unsigned char) g) << 8) |
	((0xff & (unsigned char) b));
}

int main(int argc, const char * argv[]){
	
	for(int frame=0; frame<N_FRAMES; frame++){
		printf("frame %d ----- \n", frame);
		for(int pixel=0; pixel<N_PIXELS; pixel++){
			int colour = frames[frame][pixel];
			int r = (colour >> 16) & 0xff;
			int g = (colour >> 8) & 0xff;
			int b = (colour >> 0) & 0xff;
			printf("pixel %d r:%d g:%d b:%d \n", pixel, r,g,b);
		}
	}
    return 0;
}