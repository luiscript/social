// luiscript 2018
// Hypercube
// https://www.instagram.com/p/BoMSuk3lgZa/

#pragma once

#include "ofMain.h"
//#include "ofxAbletonLink.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        void connect(int, int , int , ofVec3f[]);
        vector<ofVec4f> points;
        float angle;
    
        //ofxAbletonLink link;
        ofLight light;
};
