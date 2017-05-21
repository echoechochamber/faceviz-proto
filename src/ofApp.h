#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "faceRect.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	    bool re;
    
    bool drawFinder;
    bool drawFeatRect;
    float     rectRadius; 
	ofVideoGrabber cam;
	ofxCv::ObjectFinder finder;


    void keyPressed(int key);
    faceRect face;
};
