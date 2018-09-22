#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class ofApp : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    bool start;
    bool active[100];
    int numDots;
    float time0;
    ofLight light;
    ofxMidiOut midiOut;
};
