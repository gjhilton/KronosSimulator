#pragma once

#include "ofMain.h"
#include "ofxUI.h"

class testApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();
	
private:
	void presentFileChooser();
	void processOpenFileSelection(ofFileDialogResult openFileResult);
	
	ofxUICanvas *gui;
	void guiEvent(ofxUIEventArgs &e);
	
	vector<ofImage>loadedImages;
	vector<ofImage>processedImages;
	string originalFileExtension;
	
	ofImage loadedImage;
	int num_leds;
	int num_frames;
	int current_frame;
	int led_w;
	int led_h;
	int led_spacing;
	bool image_loaded;
	string loaded_image_name;
	
};
