#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    clicker.setApp(this);
    clicker.setClickFrequency(1.0);
    clicker.setClickRegion(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    clicker.setClicksMaxNum(5);
    clicker.setClickLengthInFramesMin(1);
    clicker.setClickLengthInFramesMax(10);
    clicker.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    clicker.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    clicker.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    //
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    //
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    cout << "mouseDragged - " << button << " - (" << x << ", " << y << ")" << endl;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    cout << "mousePressed - " << button << " - (" << x << ", " << y << ")" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    cout << "mouseRelease - " << button << " - (" << x << ", " << y << ")" << endl;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}