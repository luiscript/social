// luiscript 2018
// Hypercube
// https://www.instagram.com/p/BoMSuk3lgZa/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    points.push_back({-1,-1,-1, 1});
    points.push_back({ 1,-1,-1, 1});
    points.push_back({ 1, 1,-1, 1});
    points.push_back({-1, 1,-1, 1});
    
    points.push_back({-1,-1, 1, 1});
    points.push_back({ 1,-1, 1, 1});
    points.push_back({ 1, 1, 1, 1});
    points.push_back({-1, 1, 1, 1});
    
    points.push_back({-1,-1,-1,-1});
    points.push_back({ 1,-1,-1,-1});
    points.push_back({ 1, 1,-1,-1});
    points.push_back({-1, 1,-1,-1});
    
    points.push_back({-1,-1, 1,-1});
    points.push_back({ 1,-1, 1,-1});
    points.push_back({ 1, 1, 1,-1});
    points.push_back({-1, 1, 1,-1});
    
    angle = 0;
    
    ofSetLineWidth(4);
    
    //link.enableLink();
}

//--------------------------------------------------------------
void ofApp::update(){
    angle += 0.005;
    //angle = ofMap(link.getPhase()/link.getQuantum(), 0, 1, 0, PI);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotateX(-90);
    
    ofVec3f projected3d[16];
    
    ofEnableLighting();
    light.enable();
    light.setPosition(ofGetWidth()/2,0,100);
    light.setDiffuseColor(ofColor(255));
    light.setAmbientColor(ofColor(180));
    
    for (int i=0; i<points.size(); i++) {
        ofVec4f v = points[i];
        
        ofMatrix4x4 rotationXY;
        rotationXY.set(cos(angle), -sin(angle), 0, 0,
                       sin(angle), cos(angle), 0, 0 ,
                       0, 0, 1, 0,
                       0, 0, 0, 1 );
        
        
        ofMatrix4x4 rotationZW;
        rotationZW.set( 1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, cos(angle), -sin(angle),
                        0, 0, sin(angle), cos(angle) );
        
        ofVec4f rotated = rotationXY.postMult(v);
        rotated = rotationZW.postMult(rotated);
        
        
        float distance = 2;
        float w = 1 / (distance - rotated.w);
        
        ofMatrix4x4 projection;
        projection.set(w, 0, 0, 0,
                       0, w, 0, 0,
                       0, 0, w, 0,
                       0, 0, 0, 0);
        
        ofVec4f projected = projection.preMult(rotated);
        projected *= (ofGetHeight()/4);
        
        projected3d[i] = projected;
        
        ofDrawSphere(projected , 8);
        
    }
    
    for(int i=0; i < 4; i++){
        connect(0, i, (i+1) %4, projected3d);
        connect(0, i+4, ((i+1) % 4) + 4, projected3d);
        connect(0, i, i+4, projected3d);
    }

    for (int i = 0; i < 4; i++) {
        connect(8, i, (i+1) % 4, projected3d );
        connect(8, i+4, ((i+1) % 4)+4, projected3d);
        connect(8, i, i+4, projected3d);
    }

    for (int i = 0; i < 8; i++) {
        connect(0, i, i + 8, projected3d);
    }
    
    light.disable();
    ofDisableLighting();
}

void ofApp::connect(int offset, int i, int j, ofVec3f points[]){
    ofVec3f a = points[i + offset];
    ofVec3f b = points[j + offset];
    ofDrawLine(a.x, a.y, a.z, b.x, b.y, b.z);
}

