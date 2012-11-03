#include <stdio.h>

int (*animation_ptr)();

struct colour {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

/*
struct colour red = {255,0,0};
const struct colour anim[1] = {{255,0,0}};
struct colour frames[1][1];

struct colour colours[1];

struct colour *leds;*/

/*
struct colour numbers[1][1];
struct frame{
	struct colour pixels[1];
};

const struct frame f1 = {{255,0,0}};
const struct frame* sequence[1] = {&f1};


struct frame animation[1] = {{{255,0,0}}};
*/


/*
const char frame_0[1] = {255};
const char* frames[1] = {frame_0};
*/

const struct colour frame_0[1] = {{255,0,0}};
const struct colour* frames[1] = {frame_0};
 
void init(){
	//sequence[0] = f1;
}

int animationA() {
	return 255;
}

int animationB() {
	return 255;
}

typedef int (*fn)();
int lerp(fn oldAnimation, fn newAnimation){
	return (*oldAnimation)() + (*newAnimation)() ;
}

int main(int argc, const char * argv[]){

	//animation_ptr = animationA;
	//printf("%d",(*animation_ptr)());
	
	printf("%hhu\n", frames[0][0].r);
	
	//int result = lerp(animationA, animationB);
	//printf("%d",result);
	
	
    return 0;
}