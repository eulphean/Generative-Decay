#include "Window.h"

Window::Window(){

}

void Window::setup(glm::vec2 pos) {
	origin = pos;
	isTorn = false; // Keeps track if this window is torn.
	color = ofColor::fromHsb(ofRandom(255), ofRandom(255), ofRandom(255), 255);
}

void Window::update(ofxBox2d &box2d) {
	// Update soft body. 
	body.update(box2d);
}

void Window::drawWindow(bool debug, ofPoint windowProp) {
	// Show raw windows.
	if (debug) {
		ofPushStyle();
			ofSetColor(color);
			ofDrawRectangle(origin.x, origin.y, windowProp.x, windowProp.y);
		ofPopStyle();
	}
	
	// Black for now, if this section is torn.
	// [TODO] It should be pointing to the video stack in reality;
	if (isTorn) {
		ofPushStyle();
			ofSetColor(ofColor::black);
			ofDrawRectangle(origin.x, origin.y, windowProp.x, windowProp.y);
		ofPopStyle();
	}
}

void Window::drawBody(bool debug, ofImage img) {
	if (debug) {
		// Don't bind texture
		body.draw(true);
	} else {
		//img.getTexture().bind();
			body.draw(false);
		//img.getTexture().unbind();
	}
}

void Window::setupSoftBody(ofxBox2d &box2d, SoftBodyProperties softBodyProps) {
	// Setup soft body mesh. 
	isTorn = true;
	body.setup(box2d, origin, softBodyProps);
}

void Window::clean(ofxBox2d &box2d) {
	body.clean(box2d); 
}
