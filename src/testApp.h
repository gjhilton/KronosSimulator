#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class testApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();
	
private:
	void onFramerateChanged(int & rate);
	void onOpenClicked(bool & pressed);
	void onSaveClicked(bool & pressed);
	void processOpenFileSelection(ofFileDialogResult openFileResult);
	void saveFileToSelection(ofFileDialogResult saveFileResult);
	
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
	
	ofxButton saveButton, openButton;
	ofxIntSlider frameRateSlider;
	
};
