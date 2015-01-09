//
//  ofxRandomClicker.cpp
//  example
//
//  Created by Lukasz Karluk on 7/01/2015.
//
//

#include "ofxRandomClicker.h"

//--------------------------------------------------------------
ofxRandomClicker::ofxRandomClicker() {
    setApp(NULL);
    setClicksMaxNum(1);
    setClickFrequency(0.1);
    setClickLengthInFramesMin(1);
    setClickLengthInFramesMax(1);
}

ofxRandomClicker::~ofxRandomClicker() {
    //
}

//--------------------------------------------------------------
void ofxRandomClicker::setApp(ofBaseApp * appPtr) {
    app = appPtr;
}

void ofxRandomClicker::setClickRegion(const ofRectangle & value) {
    clickRegion = value;
}

void ofxRandomClicker::setClicksMaxNum(int value) {
    clicksMaxNum = value;
}

void ofxRandomClicker::setClickFrequency(float value) {
    clickFrequency = value;
}

void ofxRandomClicker::setClickLengthInFramesMin(int value) {
    clickLengthInFramesMin = MAX(value, 1);
}

void ofxRandomClicker::setClickLengthInFramesMax(int value) {
    clickLengthInFramesMax = MAX(value, 1);
}

void ofxRandomClicker::setup() {
    if(clickRegion.isEmpty() == true) {
        clickRegion.width = ofGetWidth();
        clickRegion.height = ofGetHeight();
    }
}

//--------------------------------------------------------------
void ofxRandomClicker::update() {
    
    int numOfClicks = clicks.size();
    for(int i=0; i<numOfClicks; i++) {
        ofxRandomClick & click = clicks[i];
        
        if(click.type == ofMouseEventArgs::Released) {
            clicks.erase(clicks.begin() + i);
            --i;
            --numOfClicks;
            continue;
        }
        
        click.clickCount += 1;
        if(click.clickCount == click.clickLengthInFrames) {
            click.type = ofMouseEventArgs::Released;
        } else {
            click.type = ofMouseEventArgs::Dragged;
        }
        float p = ofMap(click.clickCount, 0, click.clickLengthInFrames, 0.0, 1.0, true);
        click.x = ofMap(p, 0.0, 1.0, click.clickPosStart.x, click.clickPosEnd.x);
        click.y = ofMap(p, 0.0, 1.0, click.clickPosStart.y, click.clickPosEnd.y);
    }
    
    //----------------------------------------------------------
    bool bAddClick = true;
    bAddClick = bAddClick && (clicks.size() < clicksMaxNum);
    bAddClick = bAddClick && (ofRandom(1.0) < clickFrequency);
    
    if(bAddClick == true) {
        
        vector<int> clickIDs;
        for(int i=0; i<clicksMaxNum; i++) {
            clickIDs.push_back(i);
        }
        
        for(int i=0; i<clicks.size(); i++) {
            ofxRandomClick & click = clicks[i];
            for(int j=0; j<clickIDs.size(); j++) {
                if(click.button == clickIDs[j]) {
                    clickIDs.erase(clickIDs.begin() + j);
                    break;
                }
            }
        }
        int button = clickIDs[0];
        
        clicks.push_back(ofxRandomClick());
        ofxRandomClick & click = clicks.back();
        click.type = ofMouseEventArgs::Pressed;
        click.button = button;
        click.clickLengthInFrames = ofRandom(clickLengthInFramesMin, clickLengthInFramesMax);
        click.x = click.clickPosStart.x = click.clickPosEnd.x = ofRandom(clickRegion.x, clickRegion.x + clickRegion.width);
        click.y = click.clickPosStart.y = click.clickPosEnd.y = ofRandom(clickRegion.y, clickRegion.y + clickRegion.height);
        if(click.clickLengthInFrames > 1) {
            click.clickPosEnd.x += ofRandom(-100, 100);
            click.clickPosEnd.y += ofRandom(-100, 100);
            click.clickPosEnd.x = MAX(click.clickPosEnd.x, clickRegion.getMinX());
            click.clickPosEnd.x = MIN(click.clickPosEnd.x, clickRegion.getMaxX());
            click.clickPosEnd.y = MAX(click.clickPosEnd.y, clickRegion.getMinY());
            click.clickPosEnd.y = MIN(click.clickPosEnd.y, clickRegion.getMaxY());
        }
    }
    
    //----------------------------------------------------------
    if(app != NULL) {
        for(int i=0; i<clicks.size(); i++) {
            ofxRandomClick & click = clicks[i];
            if(click.type == ofMouseEventArgs::Pressed) {
                app->mousePressed(click.x, click.y, click.button);
            } else if(click.type == ofMouseEventArgs::Dragged) {
                app->mouseDragged(click.x, click.y, click.button);
            } else if(click.type == ofMouseEventArgs::Released) {
                app->mouseReleased(click.x, click.y, click.button);
            } else if(click.type == ofMouseEventArgs::Moved) {
                app->mouseMoved(click.x, click.y);
            }
        }
    } else {
        ofLogError("ofxRandomClicker", "you must first call setApp()");
    }
}

//--------------------------------------------------------------
void ofxRandomClicker::draw() {
    for(int i=0; i<clicks.size(); i++) {
        ofxRandomClick & click = clicks[i];
        
        ofFill();
        ofSetColor(ofColor::grey);
        ofCircle(click.x, click.y, 10);
        ofNoFill();
        ofSetColor(ofColor::black);
        ofCircle(click.x, click.y, 10);
        ofFill();
        ofSetColor(ofColor::white);
    }
}
