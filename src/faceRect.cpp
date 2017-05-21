//
//  faceRect.cpp
//  1010-face-proto
//
//  Created by A. K. Williams on 5/16/17.
//
//

#include <stdio.h>
#include "faceRect.h"

void faceRect::setup(string fName){
    // open file and read to buffer
    ofFile file;
    file.open(fName);
    
    ofBuffer buffer = file.readToBuffer();
    
    // create ofXml object from file buffer
    faceData.loadFromBuffer( buffer.getText() ) ;
    // start by setting the xml to the parent node - for whatever reason it doesn't work for me when I try to set by path
    faceData.setToParent() ; // you need to set this to the parent - this is almost always the way to start
    
    windowHeight = faceData.getIntValue("opencv_storage/cascade/height") ;
    windowWidth = faceData.getIntValue("opencv_storage/cascade/width") ;
    
    faceData.setTo("opencv_storage/cascade/features");
    // now set to the feature data and get the number of features
    // NOTE: you have to redo this, just look at the features node, and findout how long it is
    featureCount = faceData.getNumChildren() ;
    
    // traverse down to the child elements of the features
    faceData.setToChild(0); // maybe there's a better way to select the correct elements
    currentFeatureIndex = 0;
}


void faceRect::update(){
    // if we're at the level of the rects, drill up to the higher feature level so that we can just move to siblings
    if(!faceData.exists("rects")){
        faceData.setToParent();
    }
    // set to the next sibling of the feature index
    if(currentFeatureIndex < featureCount){
        faceData.setToSibling();
        currentFeatureIndex +=1;
    } else {
        faceData.setToParent();
        faceData.setToChild(0);
        currentFeatureIndex = 0;
    }
    faceData.setTo("rects"); // down to the rect level of the current value
}

vector<vector<int>> faceRect::getRects(){
    int n = faceData.getNumChildren();
    vector<vector<int>> retVector(n); // init the size of
    
    // reserve space for all of the vector space
    // YES !!!! this was the solution
    for(int k = 0; k < n; k++){
        retVector[k].reserve(5);
    }
    /* because this ^^^ is a 2d vector, you need to allocate space for the vectors that will be
     * must allocate memory space for the int vectors that you are storing
     *
     * Otherwise, the 2d vecotr will be pointing to a memory space that it doesn't own / is empty (acc. to stackoverflow)
     */
    
    // for all of the rect's children,
    
    for(int i = 0; i < n; i++){
        // get the rect data as a string
        string currIndex ="_[" + ofToString(i) + "]";
        string intVal = faceData.getValue(currIndex);
        // convert the string into an vector<int>
        vector<string> strIntArr = ofSplitString(intVal, " ", true, true);
        // create an int vector from the split string
        vector<int> intArr(strIntArr.size());
        for(int j = 0; j < strIntArr.size(); j++){
            retVector[i].push_back( ofToInt(strIntArr[j]) );
        }
        
    }
    return retVector;
}

