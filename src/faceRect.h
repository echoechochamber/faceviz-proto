//
//  faceRect.h
//  1010-face-proto
//
//  Created by A. K. Williams on 5/16/17.
//
//

#ifndef faceRect_h
#define faceRect_h
#include "ofMain.h"

class faceRect{
public:
    void setup(string fName);
    void update();
    vector<vector<int>> getRects();
    
    void draw(int xOffset, int yOffset, float scale);
    
    int numStages();
    
    bool re; 
    
    ofXml faceData;
    
private:
    int featureCount;
    int windowHeight;
    int windowWidth;
    int currentFeatureIndex; 
    
    string currentFeatures; 
};

#endif /* faceRect_h */
