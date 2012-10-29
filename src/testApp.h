#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class testApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();
	
private:
	void framerateChanged(int & rate);
	void presentFileChooser(bool & pressed);
	void processOpenFileSelection(ofFileDialogResult openFileResult);
	//void saveFileToSelection(ofFileDialogResult saveFileResult);
	void saveFileToSelection();
	
	ofImage loadedImage;
	int num_leds;
	int num_frames;
	int current_frame;
	int led_w;
	int led_h;
	int led_spacing;
	bool image_loaded;
	int currentFramerate;
	string loaded_image_name;
	
	ofxButton openButton;
	ofxIntSlider frameRateSlider;
	
};
