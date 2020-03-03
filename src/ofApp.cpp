#include "ofApp.h"

void ofApp::setup()
{
    ofBackground(0);
    ofDisableArbTex();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
  
    // Setup box 2d.
    box2d.init();
    box2d.setGravity(0, 0.2);
    box2d.enableEvents();
    box2d.registerGrabbing(); // Enable grabbing the circles.
  
    // Setup GUI.
    gui.setup();
    gui.add(meshVertexRadius.setup("Mesh vertex radius", 5, 1, 30));
    gui.add(subsectionWidth.setup("Subsection width", 50, 10, 500));
    gui.add(subsectionHeight.setup("Subsection height", 50, 10, 500));
    gui.add(meshColumns.setup("Mesh columns", 20, 1, 100));
    gui.add(meshRows.setup("Mesh rows", 20, 1, 100));
    gui.add(vertexDensity.setup("Vertex density", 0.5, 0, 1));
    gui.add(vertexBounce.setup("Vertex bounce", 0.5, 0, 1));
    gui.add(vertexFriction.setup("Vertex friction", 0.5, 0, 1));
    gui.add(jointFrequency.setup("Joint frequency", 4.f, 0.f, 20.f ));
    gui.add(jointDamping.setup("Joint damping", 1.f, 0.f, 5.f));
    subsectionWidth.addListener(this, &ofApp::windowSizeUpdated);
    subsectionHeight.addListener(this, &ofApp::windowSizeUpdated);
    gui.loadFromFile("ReproductiveFeedback.xml");
  
    // Create all the subsections of the image.
    createWindows();
	
    // Load all videos or images or whatever is used to create the narrative.
    img.load("bg.jpg"); 
}

void ofApp::update()
{
    // Update props coming from GUI.
    updateSoftBodyProps();
	
    // Update box2d
    box2d.update();
	
    for (auto &w : windows) {
    	w.update(box2d); 
		}
}

void ofApp::draw()
{
	img.draw(0, 0, ofGetWidth(), ofGetHeight()); 
	
	// Draw windows.
	for (auto w : windows) {
		w.drawWindow(debug, ofPoint(subsectionWidth, subsectionHeight));
		w.drawBody(debug, img);
	}
	
	// Draw torn bodies.
	//img.getTexture().bind();
//	for (auto w : windows) {
//	}
	//img.getTexture().unbind();

  if (!hideGui) {
    gui.draw();
  }
	
  cout << ofGetFrameRate() << endl;
}

// Recreate image subsections.
void ofApp::windowSizeUpdated(int &num) {
  createWindows();
}

void ofApp::updateSoftBodyProps() {
  softBodyProperties.meshDimensions = ofPoint(meshRows, meshColumns);
  softBodyProperties.vertexPhysics = ofPoint(vertexBounce, vertexDensity, vertexFriction); // x (bounce), y (density), z (friction)
  softBodyProperties.jointPhysics = ofPoint(jointFrequency, jointDamping); // x (frequency), y (damping)
  softBodyProperties.meshVertexRadius = meshVertexRadius;
  softBodyProperties.subsectionSize = ofPoint(subsectionWidth, subsectionHeight); // x (width), y(height)
  softBodyProperties.textureDimensions = ofPoint(ofGetWidth(), ofGetHeight());
}

void ofApp::createWindows() {
  // Clear previous windows.
  windows.clear();
  
  // Build a collection of image subsections.
  for (int x = 0; x < ofGetWidth(); x+=subsectionWidth) {
    for (int y = 0; y < ofGetHeight(); y+=subsectionHeight) {
      Window w; // Start point.
      w.setup(glm::vec2(x, y));
      windows.push_back(w);
    }
  }
}

void ofApp::createSoftBody() {
	// Find a window which is not already torn
	// (PS: This logic will update in the future)
	int idx = ofRandom(windows.size());
  while (ofContains(tornWindows, idx)) {
    idx = ofRandom(windows.size());
  }
	
	tornWindows.push_back(idx);
  auto &w = windows[idx];
  w.setupSoftBody(box2d, softBodyProperties);
}

void ofApp::keyPressed(int key) {
    switch (key) {
      case 'n': {
        createSoftBody();
        break;
      }
      
      case 'd': {
        debug = !debug;
        break;
      }
      
      case 'h': {
        hideGui = !hideGui;
        break;
      }
      
      case 'c': {
        clear(); 
        break;
      }
      
      default: {
        break;
      }
    }
}

void ofApp::exit() {
  gui.saveToFile("ReproductiveFeedback.xml");
}


void ofApp::clear() {
  // Clear all bodies from space.
  for (auto & w : windows){
  	w.clean(box2d);
	}
}
