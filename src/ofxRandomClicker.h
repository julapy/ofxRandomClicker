//
//  ofxRandomClicker.h
//  example
//
//  Created by Lukasz Karluk on 7/01/2015.
//
//

#include "ofMain.h"

//--------------------------------------------------------------
class ofxRandomClick : public ofMouseEventArgs {

public:
    
    ofxRandomClick() {
        clickCount = 0;
        clickLengthInFrames = 1;
    }
    
    int clickCount;
    int clickLengthInFrames;
    ofVec2f clickPosStart;
    ofVec2f clickPosEnd;
};

//--------------------------------------------------------------
class ofxRandomClicker {
    
public:
    
    ofxRandomClicker();
    ~ofxRandomClicker();
    
    void setApp(ofBaseApp * appPtr);
    void setClickRegion(const ofRectangle & value);
    void setClicksMaxNum(int value);
    void setClickFrequency(float value);
    void setClickLengthInFramesMin(int value);
    void setClickLengthInFramesMax(int value);
    void setup();
    
    void update();
    void draw();
    
    ofBaseApp * app;
    ofRectangle clickRegion;
    vector<ofxRandomClick> clicks;
    int clicksMaxNum;
    int clickLengthInFramesMin;
    int clickLengthInFramesMax;
    float clickFrequency;
};