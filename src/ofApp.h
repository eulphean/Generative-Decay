#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "SubsectionBody.h"
#include "ofxGui.h"

class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    void exit() override;
  
    // Mesh helper methods.
    void createImageSubsections();
    void subsectionSizeUpdated(int &num); // Recreate image subsections with new width or height.
    void clear(); 
    void createSubsectionBody();
    void createSubsectionProperties();
    
    // Grabber stuff.
    ofVideoGrabber grabber;
  
    // Physics engine.
    ofxBox2d box2d;
  
    // Checks to keep track of updated box2d object.
    bool showSoftBody;
    bool hideGui;
    bool showTexture; 
  
    // Subsections
    vector<Subsection> imageSubsections; // Pool of original subsections.
    vector<SubsectionBody> subsectionBodies; // Mesh + Box2D body removed.
    vector<int> tornIndices; 
  
    // App GUI.
    ofxPanel gui;
    ofxFloatSlider meshVertexRadius;
    ofxIntSlider meshColumns;
    ofxIntSlider meshRows;
    ofxIntSlider subsectionWidth;
    ofxIntSlider subsectionHeight;
  
    // Physics.
    ofxFloatSlider vertexDensity;
    ofxFloatSlider vertexBounce;
    ofxFloatSlider vertexFriction;
    ofxFloatSlider jointFrequency;
    ofxFloatSlider jointDamping;
  
    // Soft body UI properties. 
    SoftBodyProperties softBodyProperties;
  
    // Background image.
    ofImage img;
  
    int numSubsections = 0; 
};

