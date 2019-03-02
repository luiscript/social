#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    delta = PI/32;
    for(float angle = 0; angle <= TWO_PI; angle+=delta)
        angles.push_back(0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    int radius = ofGetWidth()/4;
    ofSetLineWidth(4);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    int index = 0;
    for(float angle = 0; angle <= TWO_PI; angle+=delta)
    {
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        
        ofPushMatrix();
        
        ofTranslate(x, y);
        ofRotateZRad(angle);
        
        float x1 = radius * cos(angles[index]);
        float z1 = radius * sin(angles[index]);
        
        float x2 = radius * cos(angles[index] + PI);
        float z2 = radius * sin(angles[index] + PI);

        ofPolyline p;
        glm::vec3 v1(x1, z1, 0.0);
        glm::vec3 v2(x2, z2, 0.0);
        p.lineTo(v1);
        p.lineTo(v2);
        
        p.draw();
        ofPopMatrix();
        
        angles[index] += PI/500 + index * PI/3500;
        index++;
    }
}

