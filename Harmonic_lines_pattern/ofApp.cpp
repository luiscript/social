#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    delta = PI/32;
    numLines = 15;
    connectionDistance = ofGetWidth()/5;
    for(int l=0; l<numLines; l++)
        angles.push_back(0);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    meshLines.setMode(OF_PRIMITIVE_LINES);
    meshLines.enableIndices();

    colors.push_back(ofColor(128, 200));
    colors.push_back(ofColor(200,200));
    colors.push_back(ofColor(255, 200));
}

//--------------------------------------------------------------
void ofApp::update(){
    mesh.clear();
    meshLines.clear();
    
    int radius = ofGetHeight()/2;
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    int index = 0;
    float width =(ofGetWidth()/2)/numLines;

    for(int l=0; l<numLines; l++)
    {

        float x = width * l;
        float y = radius * sin(angles[index]);
        angles[index] += index * PI/1500;
        index++;
        int colorIndex = index % 3;
        if(l == 0)
        {
            mesh.addVertex(ofPoint(x,0,0));
            mesh.addVertex(ofPoint(x,y,0));
            mesh.addColor(colors[colorIndex]);
            mesh.addColor(colors[colorIndex]);
            
            meshLines.addVertex(ofPoint(x,0,0));
            meshLines.addVertex(ofPoint(x,y,0));
            meshLines.addColor(colors[colorIndex]);
            meshLines.addColor(colors[colorIndex]);
            
        } else {
            mesh.addVertex(ofPoint(x,0,0));
            mesh.addVertex(ofPoint(x,y,0));
            mesh.addColor(colors[colorIndex]);
            mesh.addColor(colors[colorIndex]);
            
            meshLines.addVertex(ofPoint(x,0,0));
            meshLines.addVertex(ofPoint(x,y,0));
            meshLines.addColor(colors[colorIndex]);
            meshLines.addColor(colors[colorIndex]);
            
            mesh.addVertex(ofPoint(-x,0,0));
            mesh.addVertex(ofPoint(-x,y,0));
            mesh.addColor(colors[colorIndex]);
            mesh.addColor(colors[colorIndex]);
            
            meshLines.addVertex(ofPoint(-x,0,0));
            meshLines.addVertex(ofPoint(-x,y,0));
            meshLines.addColor(colors[colorIndex]);
            meshLines.addColor(colors[colorIndex]);
        }
   
    }
    
    for (int v=0; v<mesh.getNumVertices(); v++) {
        ofVec3f point1 = mesh.getVertex(v);
        for (int vv=v+1; vv<mesh.getNumVertices(); vv++) {
            ofVec3f point2 = mesh.getVertex(vv);
            float distance = point1.distance(point2);
            if(distance <= connectionDistance )
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
    glPointSize(8);
    meshLines.draw();
    mesh.draw();
}

