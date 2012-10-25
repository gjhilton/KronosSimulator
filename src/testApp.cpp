#include "testApp.h"

#define UI_HEIGHT 100
#define UI_BUTTON_NAME_LOAD "LOAD IMAGE"

void testApp::setup(){
	
	// initialise gui
    gui = new ofxUICanvas(0,ofGetHeight()-UI_HEIGHT,ofGetWidth(),UI_HEIGHT);
	gui->setFont("GUI/Inconsolata.ttf", false, true, false, 300);
    gui->setFontSize(OFX_UI_FONT_LARGE, 10);
	gui->setFontSize(OFX_UI_FONT_MEDIUM, 6);
    gui->setFontSize(OFX_UI_FONT_SMALL, 4);
	gui->addLabelButton(UI_BUTTON_NAME_LOAD, false);
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
	
	ofBackgroundHex(0x000000);
}

void testApp::update(){}

//--------------------------------------------------------------
void testApp::draw() {	
	
	for (int i=0; i<loadedImages.size(); i++){
		loadedImages[i].draw(0, 20);
	}
	
	for (int i=0; i<processedImages.size(); i++){
		processedImages[i].draw(processedImages[i].getWidth(), 20);
	}
	
}

//Sort function for stl::sort http://www.cplusplus.com/reference/algorithm/sort/
bool sortColorFunction (ofColor i,ofColor j) { 
	return (i.getBrightness()<j.getBrightness()); 
}


void testApp::processOpenFileSelection(ofFileDialogResult openFileResult){
	
	ofLogVerbose("getName(): "  + openFileResult.getName());
	ofLogVerbose("getPath(): "  + openFileResult.getPath());
	
	ofFile file (openFileResult.getPath()); 
	
	if (file.exists()){
		//Limiting this example to one image so we delete previous ones
		processedImages.clear();
		loadedImages.clear();
		
		ofLogVerbose("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());
		
		//We only want images
		if (fileExtension == "JPG" || fileExtension == "PNG") {
			
			//Save the file extension to use when we save out
			originalFileExtension = fileExtension;
			
			//Load the selected image
			ofImage image;
			image.loadImage(openFileResult.getPath());
			if (image.getWidth()>ofGetWidth() || image.getHeight() > ofGetHeight()) 
			{
				image.resize(image.getWidth()/2, image.getHeight()/2);
			}
			loadedImages.push_back(image);
			
			//Make some short variables 
			int w = image.getWidth();
			int h = image.getHeight();
			
			//Make a new image to save manipulation by copying the source
			ofImage processedImage = image;
			
			//Walk through the pixels
			for (int y = 0; y < h; y++){
				
				//Create a vector to store and sort the colors
				vector<ofColor> colorsToSort;
				
				for (int x = 0; x < w; x++){
					
					//Capture the colors for the row
					ofColor color = image.getColor(x, y); 
					colorsToSort.push_back(color);					
				}
				
				//Sort the colors for the row
				sort (colorsToSort.begin(), colorsToSort.end(), sortColorFunction);
				
				for (int x = 0; x < w; x++)
				{
					//Put the sorted colors back in the new image
					processedImage.setColor(x, y, colorsToSort[x]);
				}
			}
			//Store the processed image
			processedImages.push_back(processedImage);
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