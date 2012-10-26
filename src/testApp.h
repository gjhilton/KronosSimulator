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
	
};
