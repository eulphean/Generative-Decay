#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxGui.h"
#include "Window.h"
#include "SoftBody.h"

class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    void exit() override;
  
    // Mesh helper methods.
    void createWindows();
    void windowSizeUpdated(int &num); // Recreate image subsections with new width or height.
		void createSoftBody();
    
    void clear();
    void updateSoftBodyProps();
  
    // Interactive flags.
    bool hideGui = true;
    bool debug = false;
	
		// Physics engine.
    ofxBox2d box2d;
  
    // Each is a window. 
    vector<Window> windows; // Pool of original subsections.
  
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
	
		// TODO: Don't use this for too long. 
		// Come up with a better algorithm honestly.
		vector<int> tornWindows;
	
		ofImage img; 
};

