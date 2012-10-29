#include "testApp.h"

#define MAX_LEDS 96
#define UI_HEIGHT 100
#define TEMPLATE_PLACEHOLDER "$INSERT_IMAGE_DATA_HERE$"

void testApp::setup(){
	
	currentFramerate = 8;
	ofSetFrameRate(currentFramerate);
	
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

void testApp::saveFileToSelection(ofFileDialogResult saveFileResult){
	
	// step 1 - build a string representation of the image data
	string imgdata = "/*           IMAGE DATA           */";
	// TODO
	
	// step 2 - load a boilerplate arduino sketch
	ofBuffer buffer = ofBufferFromFile("arduino_template/arduino_template.ino");
	if(buffer.size()) {
		// step 3 - insert the image data into the arduino sketch
		string arduino_template = buffer.getText();
		ofStringReplace(arduino_template,TEMPLATE_PLACEHOLDER,imgdata);
		buffer.set(arduino_template);
		// step 4 - save the file
		ofBufferToFile(saveFileResult.getPath(), buffer);
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
	ofFileDialogResult saveFileResult = ofSystemSaveDialog("saved.ino", "Save to file");
	if (saveFileResult.bSuccess) saveFileToSelection(saveFileResult);
}

void testApp::onFramerateChanged(int & rate){
	ofSetFrameRate(rate);
}
