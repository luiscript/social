#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);
    ofSetWindowTitle("Music in math - Simple Harmonic Motion");
    ofEnableDepthTest();
    ofSetLineWidth(2);
    ofSetColor(200);
    midiOut.openPort("Driver IAC Bus 1");
    numDots = 25;
    start = false;
    for(int i = 0; i < numDots; i++) active[i] = false;
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    ofEnableLighting();
    light.enable();
    light.setPosition(0,100,100);
    light.setDiffuseColor(ofColor(200));
    light.setAmbientColor(ofColor(128));
    
    if(start){
        for(int a=0; a <= numDots; a++){
            
            ofPushMatrix();
            ofTranslate(0, ofGetHeight()/2);
            
            int x = a * ofGetWidth()/numDots;
            int rad = ofGetHeight()/2;
            float time = ofGetElapsedTimef() - time0;
            
            //this line of code does the magic
            ofPoint p1(x, rad * cos((48 + a) * time * 0.025 + PI/2), 0);
            ofPoint p2(x,0,0);
            
            ofDrawCylinder(p1.x, (p1.y - p2.y)/2, 2, p1.distance(p2));
            ofDrawSphere(p1, 7);
            ofDrawSphere(p2, p1.distance(p2) < 7 ? 15 : 7);
            
            //send midi note on when p2 is near p1
            if(p1.distance(p2) < 11 && !active[a]){
                midiOut.sendNoteOn(1, 40 + a);
                active[a] = true;
            }
            
            //send midi note off when p2 is not near p1
            if(p1.distance(p2) >= 11 && active[a]){
                midiOut.sendNoteOff(1, 40 + a);
                active[a] = false;
            }
            
            ofPopMatrix();
        }
    } else {
        for(int a=0; a <= numDots; a++){
            ofPushMatrix();
            ofTranslate(0, ofGetHeight()/2);
            int x = a * ofGetWidth()/numDots;
            ofPoint p2(x,0,0);
            ofDrawSphere(p2, 7);
        }
    }
    
    light.disable();
    ofDisableLighting();

}


void ofApp::keyPressed(int key) {
    start = !start;
    time0 = ofGetElapsedTimef();
};

