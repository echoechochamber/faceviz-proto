#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    finder.setup("haarcascade_frontalface_default.xml");
    face.setup("haarcascade_frontalface_default.xml");
    finder.setPreset(ObjectFinder::Fast);
    finder.getTracker().setSmoothingRate(.8);

    cam.setup(640, 480);
    drawFinder = false;
    drawFeatRect = true;
    rectRadius = 0.0;
    ofBackground(255,255,255);
    re = false;
}

void ofApp::update() {
    cam.update();
    if(cam.isFrameNew()) {
        finder.update(cam);
        
    }
    if(finder.size() > 0){
        face.update();
    }
}

void ofApp::draw() {
    cam.draw(0, 0);
    

    // draw the finder if I say so
    if(drawFinder){
        ofPushStyle();
        ofSetColor(0,0,255);
        ofSetLineWidth(3.0);
        finder.draw();
        ofPopStyle();
    }
    if(drawFeatRect){
        // get the intarrays for the current feature
        vector<vector<int>> intArr = face.getRects();

        for(int j = 0; j < finder.size(); j++){
            // get the finder object to scale and offest the feature rectangles
            ofRectangle object = finder.getObjectSmoothed(j);
            float scaleX = object.width / 24.;
            float scaleY= object.height / 24.;
            
            
            for(int i = 0; i < intArr.size(); i ++){
                ofPushMatrix();
                ofTranslate(object.x , object.y );
                ofScale(scaleX, scaleY);

                ofPushStyle();
                if(intArr[i][4] > 0){
                    ofFill();
                } else {
                    ofNoFill();
                }
                ofSetColor(0);
                ofSetLineWidth(2.0);
                ofDrawRectRounded(float(intArr[i][0]) , float(intArr[i][1]) , float(intArr[i][2]) , float(intArr[i][3]) , rectRadius);
                ofPopStyle();
                
                ofPopMatrix();
            }
        }
    }
  

    ofDrawBitmapString(ofToString(rectRadius, 4), ofGetWidth() - 100, ofGetHeight() - 100);
}

void ofApp::keyPressed(int key){
    switch(key){
        case 't':
            drawFinder = !drawFinder;
            break;
        case 'f':
            drawFeatRect = !drawFeatRect;
            break;
        case OF_KEY_UP:
            rectRadius = rectRadius + 0.05;
            break;
        case OF_KEY_DOWN:
            if (rectRadius > 0.1){
                rectRadius = rectRadius - 0.05;
            }
            break;
    }
}
