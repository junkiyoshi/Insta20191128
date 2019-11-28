#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofNoFill();
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh_list.clear();
	this->frame_list.clear();

	int span = 100;
	for (int x = -100; x <= 100; x += span) {

		for (int y = -100; y <= 100; y += span) {

			for (int z = -100; z <= 100; z += span) {

				ofMesh mesh, frame;
				frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
				auto base = glm::vec3(x, y, z);
				auto param = glm::vec3();
				switch ((int)ofRandom(3)) {
				case 0:
					param = glm::vec3(5, 0, 0);
					break;
				case 1:
					param = glm::vec3(0, 5, 0);
					break;
				case 2:
					param = glm::vec3(0, 0, 5);
					break;
				}
				
				auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

				for (int i = 0; i < 100; i++) {
				
					auto location = glm::vec3(
						ofMap(ofNoise(noise_seed.x, (i + ofGetFrameNum()) * 0.01), 0, 1, span * -0.35, span * 0.35),
						ofMap(ofNoise(noise_seed.y, (i + ofGetFrameNum()) * 0.01), 0, 1, span * -0.35, span * 0.35),
						ofMap(ofNoise(noise_seed.z, (i + ofGetFrameNum()) * 0.01), 0, 1, span * -0.35, span * 0.35));

					mesh.addVertex(base + location + param);
					mesh.addVertex(base + location - param);

					frame.addVertex(base + location + param);
					frame.addVertex(base + location - param);

					if (i > 0) {

						mesh.addIndex(i * 2); mesh.addIndex(i * 2 - 1); mesh.addIndex(i * 2 - 2);
						mesh.addIndex(i * 2); mesh.addIndex(i * 2 + 1); mesh.addIndex(i * 2 - 1);

						frame.addIndex(i * 2); frame.addIndex(i * 2 - 2);
						frame.addIndex(i * 2 + 1); frame.addIndex(i * 2 - 1);
					}
				}

				frame.addIndex(0); frame.addIndex(1);
				frame.addIndex(frame.getNumVertices() - 1); frame.addIndex(frame.getNumVertices() - 2);

				this->mesh_list.push_back(mesh);
				this->frame_list.push_back(frame);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.25);

	ofSetColor(39, 128);
	int span = 100;
	for (int x = -100; x <= 100; x += span) {

		for (int y = -100; y <= 100; y += span) {

			for (int z = -100; z <= 100; z += span) {

				ofDrawBox(glm::vec3(x, y, z), span);
			}
		}
	}

	for (int i = 0; i < this->mesh_list.size(); i++) {

		ofSetColor(39);
		this->mesh_list[i].draw();

		ofSetColor(239);
		this->frame_list[i].drawWireframe();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}