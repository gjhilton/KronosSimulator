#include "testApp.h"

#define MAX_LEDS 96
#define UI_HEIGHT 100

void testApp::setup(){
	
	currentFramerate = 8;
	ofSetFrameRate(currentFramerate);
	
	// alternative gui
	int guih = ofGetHeight() - 30;
	openButton.setup("open animation",300);
	openButton.setPosition(10,guih);
	openButton.addListener(this,&testApp::onOpenClicked);

	saveButton.setup("save",300);
	saveButton.setPosition(150,guih);
	saveButton.addListener(this,&testApp::onSaveClicked);
	
	frameRateSlider.setup("framerate", currentFramerate, 1, 60);
	frameRateSlider.setPosition(500,guih);
	frameRateSlider.addListener(this,&testApp::onFramerateChanged);
	
	ofBackgroundHex(0x000000);
	image_loaded = false;
	
	saveFileToSelection();
}

void testApp::update(){}

void testApp::draw() {
	
	// draw gui - persistent
	openButton.draw();
	
	// draw animation
	if (image_loaded){
		
		// draw gui - widgets shown only with anim loaded
		saveButton.draw();
		frameRateSlider.draw();
		
		// draw info string
		stringstream s;
		s
		<< loaded_image_name
		<< "\n"
		<< "using " << num_leds << " leds. "
		<< "frame " << current_frame << "/" << num_frames;
		ofSetHexColor(0x666666);
		ofDrawBitmapString(s.str(), 10, 20);
		
		
		ofPushMatrix();
		ofTranslate(10, 80);
	
		for(int pixel = 0; pixel < num_leds; pixel++) {
			ofSetColor(loadedImage.getColor(pixel,current_frame));
			ofRect(0,0,led_w,led_h);
			ofTranslate(led_w + led_spacing, 0);
		}
	
		ofPopMatrix();
	
		// wind on counter
		current_frame++;
		if (current_frame >= num_frames) current_frame = 0;
	}
}

bool ofShader::setupShaderFromFile(GLenum type, string filename) {
	ofBuffer buffer = ofBufferFromFile(filename);
	if(buffer.size()) {
		return setupShaderFromSource(type, buffer.getText());
	} else {
		ofLog(OF_LOG_ERROR, "Could not load shader of type " + nameForType(type) + " from file " + filename);
		return false;
	}
}

void testApp::saveFileToSelection(){
//void testApp::saveFileToSelection(ofFileDialogResult saveFileResult){
	
	// step 1 - build a string representation of the image data
	string imgdata = "/*           IMAGE DATA           */";
	
	// step 2 - load a boilerplate arduino sketch
	
	ofBuffer buffer = ofBufferFromFile("arduino_template/arduino_template.ino");
	if(buffer.size()) {
		string arduino_template = buffer.getText();
		ofLog(OF_LOG_WARNING, "SUCCESS!");
		// step 3 - insert the image data into the arduino sketch
	
		// step 4 - save the file
		// ofFile file (saveFileResult.getPath());
	} else {
		ofLog(OF_LOG_ERROR, "Save failed: couldn't open template file");
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
				if (num_leds <= 32){
					led_spacing = 3;
					led_h = 30;
					led_w = 30;
				}
				if (num_leds > 32){
					led_spacing = 2;
					led_h = 16;
					led_w = 16;
				}
				if (num_leds > 64){
					led_spacing = 1;
					led_h = 11;
					led_w = 11;
				}
				num_frames = loadedImage.getHeight();
				current_frame = 0;
				image_loaded = true;
			}
		}
	}
	
}

void testApp::onOpenClicked(bool & pressed){
	if (pressed == false) return;
	ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a jpg or png");
	processOpenFileSelection(openFileResult);
}

void testApp::onSaveClicked(bool & pressed){
	if (pressed == false) return;
	ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a jpg or png");
	processOpenFileSelection(openFileResult);
}

void testApp::onFramerateChanged(int & rate){
	ofSetFrameRate(rate);
}
