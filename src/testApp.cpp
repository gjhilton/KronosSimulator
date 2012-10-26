#include "testApp.h"

#define MAX_LEDS 32
#define UI_HEIGHT 100
#define UI_BUTTON_NAME_LOAD "LOAD ANIMATION"

void testApp::setup(){
	
	ofSetFrameRate(10);
	
	// initialise gui
    gui = new ofxUICanvas(0,ofGetHeight()-UI_HEIGHT,ofGetWidth(),UI_HEIGHT);
	gui->setFont("GUI/Inconsolata.ttf", false, true, false, 300);
    gui->setFontSize(OFX_UI_FONT_LARGE, 10);
	gui->setFontSize(OFX_UI_FONT_MEDIUM, 6);
    gui->setFontSize(OFX_UI_FONT_SMALL, 4);
	gui->addLabelButton(UI_BUTTON_NAME_LOAD, false);
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
	
	ofBackgroundHex(0x000000);
	image_loaded = false;
}

void testApp::update(){}

void testApp::draw() {
	if (image_loaded){
		
		// draw info string
		stringstream s;
		s
		<< loaded_image_name
		<< "\n"
		<< "using " << num_leds << " leds. "
		<< "frame " << current_frame << "/" << num_frames;
		ofSetHexColor(0x666666);
		ofDrawBitmapString(s.str(), 40, 40);
		
		
		ofPushMatrix();
		ofTranslate(40, 80);
	
		for(int pixel = 0; pixel < num_leds; pixel++) {
			ofSetColor(loadedImage.getColor(current_frame, pixel));
			ofRect(0,0,led_w,led_h);
			ofTranslate(led_w + led_spacing, 0);
		}
	
		ofPopMatrix();
	
		// wind on counter
		current_frame++;
		if (current_frame >= num_frames) current_frame = 0;
	}
}

void testApp::processOpenFileSelection(ofFileDialogResult openFileResult){
	
	ofFile file (openFileResult.getPath()); 
	
	if (file.exists()){
		image_loaded = false;
		loaded_image_name = file.getFileName();
		string fileExtension = ofToUpper(file.getExtension());
		if (fileExtension == "JPG" || fileExtension == "PNG") {
			loadedImage.loadImage(openFileResult.getPath());
			num_leds = loadedImage.getWidth();
			if (num_leds <= MAX_LEDS){
				num_frames = loadedImage.getHeight();
				led_spacing = 4;
				led_h = 30;
				led_w = 30;
				current_frame = 0;
				image_loaded = true;
			}
		}
	}
	
}

void testApp::presentFileChooser(){
	ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a jpg or png");
	processOpenFileSelection(openFileResult);
}

void testApp::guiEvent(ofxUIEventArgs &e) {
	string name = e.widget->getName();
	if(name == UI_BUTTON_NAME_LOAD) {
        ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue()==0) presentFileChooser();
	}
}