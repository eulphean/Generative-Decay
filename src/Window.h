#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "SoftBody.h"

// Defines a class for each subsection.
class Window {
  public:
    Window();
    void setup(glm::vec2 pos);
    void update(ofxBox2d &box2d);
    void drawWindow(bool debug, ofPoint windowProp);
    void drawBody(bool debug);
	
    void setupSoftBody(ofxBox2d &box2d, SoftBodyProperties softBodyProps);
    void clean(ofxBox2d &box2d);
	
		// Debug
    ofColor color;

		SoftBody body; // Mesh + Box2D body removed.
		bool isTorn;
		glm::vec2 origin;
};
