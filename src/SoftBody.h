#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

struct SoftBodyProperties {
  ofPoint meshDimensions;
  ofPoint subsectionSize;
  ofPoint vertexPhysics;
  ofPoint jointPhysics;
  ofPoint textureDimensions;
  float meshVertexRadius;
};


class SoftBody {
  public:
  	SoftBody() {}; 
    void setup(ofxBox2d &box2d, glm::vec2 meshOrigin, SoftBodyProperties softBodyProperties);
    void update(ofxBox2d &box2d);
    void draw(bool showSoftBody);
    void clean(ofxBox2d &box2d);
	
    // Filter index to define which texture the subsection body should bind to.
//    int filterIdx = 1;
    bool isOutside; // Set this to true if all the vertices of this soft body are removed.
	
  private:
    void setupMeshPlane(glm::vec2 meshOrigin, SoftBodyProperties softBodyProperties);
    void createBox2DSprings(ofxBox2d &box2d, SoftBodyProperties softBodyProperties);
    void addForce();
	
    std::vector<std::shared_ptr<ofxBox2dCircle>> vertices; // Every vertex in the mesh is a circle.
    std::vector<std::shared_ptr<ofxBox2dJoint>> joints; // Joints connecting those vertices.
    ofMesh mesh;
};
