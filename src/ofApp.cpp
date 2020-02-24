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
  
    // Default values.
    showSoftBody = false;
    hideGui = true;
    showTexture = true;
    showImageSubsections = false; 
  
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
    subsectionWidth.addListener(this, &ofApp::subsectionSizeUpdated);
    subsectionHeight.addListener(this, &ofApp::subsectionSizeUpdated);
  
    gui.loadFromFile("ReproductiveFeedback.xml");
  
    // Load a single image.
    img.load("bg.jpg");
    img.resize(ofGetWidth(), ofGetHeight());
    
    // Create subsection properties.
    createSubsectionProperties();
  
    // Create all the subsections of the image.
    createImageSubsections();
}

void ofApp::update()
{
    // Update subsection properties every time.
    createSubsectionProperties();
  
    // Update box2d
    box2d.update();
  
    // Erase this element if it's outside the box2d bounds.
    ofRemove(subsectionBodies, [&](SubsectionBody &b) {
      b.update(box2d);
      return b.isOutside;
    });
}

void ofApp::draw()
{
  if (showImageSubsections) {
    for (auto i : imageSubsections) {
      i.draw(ofPoint(subsectionWidth, subsectionHeight));
    }
  } else {
    ofPushMatrix();
      // Draw the base image.
      img.draw(0, 0, ofGetWidth(), ofGetHeight());
      // Draw any subsections that have been torn apart as black rectangles.
      for (auto &sub : imageSubsections) {
        if (sub.isTorn) {
          ofPushStyle();
            ofSetColor(ofColor::black);
            ofDrawRectangle(sub.origin.x, sub.origin.y, subsectionWidth, subsectionHeight);
          ofPopStyle();
        }
      }

      // Draw all subsection bodies that are torn away.
      for (auto b: subsectionBodies) {
        ofPushStyle();
          if (showTexture) {
            img.getTexture().bind();
              b.draw(showSoftBody);
            img.getTexture().unbind();
          } else {
            b.draw(showSoftBody);
          }
        ofPopStyle();
      }
    ofPopMatrix();
  }
  if (!hideGui) {
    gui.draw();
  }
}

// Recreate image subsections.
void ofApp::subsectionSizeUpdated(int &num) {
  createImageSubsections();
}

void ofApp::createSubsectionProperties() {
  // Create Soft Body payload to create objects.
  softBodyProperties.meshDimensions = ofPoint(meshRows, meshColumns);
  softBodyProperties.vertexPhysics = ofPoint(vertexBounce, vertexDensity, vertexFriction); // x (bounce), y (density), z (friction)
  softBodyProperties.jointPhysics = ofPoint(jointFrequency, jointDamping); // x (frequency), y (damping)
  softBodyProperties.meshVertexRadius = meshVertexRadius;
  softBodyProperties.subsectionSize = ofPoint(subsectionWidth, subsectionHeight); // x (width), y(height)
  softBodyProperties.textureDimensions = ofPoint(ofGetWidth(), ofGetHeight());
}

void ofApp::createImageSubsections() {
  // Clear previous subsections.
  imageSubsections.clear();
  
  // Build a collection of image subsections.
  for (int x = 0; x < ofGetWidth(); x+=subsectionWidth) {
    for (int y = 0; y < ofGetHeight(); y+=subsectionHeight) {
      Subsection s = Subsection(glm::vec2(x, y)); // Store the starting point of each subsection.
      imageSubsections.push_back(s);
    }
  }
}

void ofApp::createSubsectionBody() {
  int idx = ofRandom(imageSubsections.size());
  
  // Keep looking for a random subsection.
  while (ofContains(tornIndices, idx)) {
    idx = ofRandom(imageSubsections.size());
  }
  
  // Save the index and create a subsection.
  tornIndices.push_back(idx);
  Subsection &s = imageSubsections[idx];
  s.isTorn = true;
  
  // Create a subsection body to tear.
  SubsectionBody body;
  body.setup(box2d, s.origin, softBodyProperties);
  subsectionBodies.push_back(body);
}

void ofApp::clear() {
  // Clear all bodies from space.
  ofRemove(subsectionBodies, [&](SubsectionBody &b) {
    b.clean(box2d);
    return true;
  });
}

void ofApp::keyPressed(int key) {
    switch (key) {
      case 'n': {
        createSubsectionBody();
        break;
      }
      
      case 's': {
        showSoftBody = !showSoftBody;
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
      
      case 't': {
        showTexture = !showTexture;
        break;
      }
      
      case 'i': {
        showImageSubsections = !showImageSubsections;
      }
      
      default: {
        break;
      }
    }
}

void ofApp::exit() {
  gui.saveToFile("ReproductiveFeedback.xml");
}
