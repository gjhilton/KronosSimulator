#pragma once

#include "ofMain.h"
#include "ofxUI.h"




class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyReleased(int key);
	
		void processOpenFileSelection(ofFileDialogResult openFileResult);
		//bool sortColorFunction (ofColor i,ofColor j);
	vector<ofImage>loadedImages;
	vector<ofImage>processedImages;
	string originalFileExtension;
	
	ofxUICanvas *gui; 
};
