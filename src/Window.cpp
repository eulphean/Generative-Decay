#include "Window.h"

Window::Window(){
}

void Window::setup(glm::vec2 pos) {
	origin = pos;
	isTorn = false; // Keeps track if this window is torn.
	color = ofColor::fromHsb(ofRandom(255), ofRandom(255), ofRandom(255), 255);
	textureId = ofRandom(VideoBank::instance().getVideoCount()); // Assign a default texture id.
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
	if (isTorn) {
		ofPushStyle();
			auto player = VideoBank::instance().getVideoPlayer(textureId);
			player.update();
			player.getTexture().setCompression(	OF_COMPRESS_ARB);		///< ARB compression.)
			player.getTexture().drawSubsection(origin.x, origin.y, windowProp.x, windowProp.y, origin.x, origin.y);
			//ofDrawRectangle(origin.x, origin.y, windowProp.x, windowProp.y);
		ofPopStyle();
	}
}

void Window::drawBody(bool debug) {
	if (debug) {
		// Don't bind texture
		body.draw(true);
	} else {
		body.draw(false);
	}
}

void Window::setupSoftBody(ofxBox2d &box2d, SoftBodyProperties softBodyProps) {
	// Setup soft body mesh. 
	isTorn = true;
	// Use the current texture id and send it across the SoftBody to be used for the texture.
	// Maybe we use the pixels since using a video might be more heavy lifting.
	body.setup(box2d, origin, softBodyProps);
	textureId = ofRandom(VideoBank::instance().getVideoCount());
	auto player = VideoBank::instance().getVideoPlayer(textureId);
	player.play();
}

void Window::clean(ofxBox2d &box2d) {
	body.clean(box2d); 
}
