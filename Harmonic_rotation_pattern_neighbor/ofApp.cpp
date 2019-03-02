#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    delta = PI/16;
    connectionDistance = 200;
    for(float angle = 0; angle <= TWO_PI; angle+=delta)
        angles.push_back(0);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    meshLines.setMode(OF_PRIMITIVE_LINES);
    meshLines.enableIndices();
}

//--------------------------------------------------------------
void ofApp::update(){
    mesh.clear();
    meshLines.clear();
    
    int radius = ofGetWidth()/4;
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    int index = 0;
    for(float angle = 0; angle <= TWO_PI; angle+=delta)
    {
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        
        float x1 = x + radius * cos(angles[index]);
        float y1 = y + radius * sin(angles[index]);
        
        float x2 = x + radius * cos(angles[index] + PI);
        float y2 = y + radius * sin(angles[index] + PI);
        
        mesh.addVertex(ofPoint(x1, y1));
        mesh.addVertex(ofPoint(x2, y2));
        
        meshLines.addVertex(ofPoint(x1, y1));
        meshLines.addVertex(ofPoint(x2, y2));
        
        angles[index] += index * PI/5000;
        index++;
    }
    
    for (int v=0; v<mesh.getNumVertices(); v++) {
        ofVec3f point1 = mesh.getVertex(v);
        for (int vv=v+1; vv<mesh.getNumVertices(); vv++) {
            ofVec3f point2 = mesh.getVertex(vv);
            float distance = point1.distance(point2);
            if(distance <= connectionDistance)
            {
                meshLines.addIndex(v);
                meshLines.addIndex(vv);
            }
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofSetLineWidth(2);
    glPointSize(10);
    meshLines.draw();
    mesh.draw();
}

