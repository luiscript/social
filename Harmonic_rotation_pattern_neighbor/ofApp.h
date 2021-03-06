#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    float delta;
    vector<float> angles;
    ofMesh mesh;
    ofMesh meshLines;
    float connectionDistance;
};
