#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    float delta;
    int numLines;
    vector<float> angles;
    vector<ofColor> colors;
    ofMesh mesh;
    ofMesh meshLines;
    float connectionDistance;
};
