#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face_mesh.clear();
	this->frame_mesh.clear();

	auto R = 200;
	auto r = 50;
	auto v_span = 2;
	auto u_span = 3;


	int index = 0;
	for (auto v = 0; v < 360; v += v_span) {

		for (auto u = 0; u < 360; u += u_span) {

			vector<glm::vec3> vertices;
			vertices.push_back(this->make_point(R, r, u, v));
			vertices.push_back(this->make_point(R, r, u + u_span, v));
			vertices.push_back(this->make_point(R, r, u + u_span, v + v_span));
			vertices.push_back(this->make_point(R, r, u, v + v_span));

			float noise_value, height;

			noise_value = ofNoise(glm::vec4(vertices[0] * 0.015, ofGetFrameNum() * 0.05));
			height = noise_value < 0.5 ? 0 : ofMap(noise_value, 0.5, 1, 0, 50);
			vertices.push_back(this->make_point(R, r + height, u, v));

			noise_value = ofNoise(glm::vec4(vertices[1] * 0.015, ofGetFrameNum() * 0.05));
			height = noise_value < 0.5 ? 0 : ofMap(noise_value, 0.5, 1, 0, 50);
			vertices.push_back(this->make_point(R, r + height, u + u_span, v));

			noise_value = ofNoise(glm::vec4(vertices[2] * 0.015, ofGetFrameNum() * 0.05));
			height = noise_value < 0.5 ? 0 : ofMap(noise_value, 0.5, 1, 0, 50);
			vertices.push_back(this->make_point(R, r + height, u + u_span, v + v_span));

			noise_value = ofNoise(glm::vec4(vertices[3] * 0.015, ofGetFrameNum() * 0.05));
			height = noise_value < 0.5 ? 0 : ofMap(noise_value, 0.5, 1, 0, 50);
			vertices.push_back(this->make_point(R, r + height, u, v + v_span));

			int index = this->face_mesh.getNumVertices();
			this->face_mesh.addVertices(vertices);
			this->frame_mesh.addVertices(vertices);

			// Face Index

			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 2);
			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 3);

			this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 5); this->face_mesh.addIndex(index + 6);
			this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 6); this->face_mesh.addIndex(index + 7);

			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 5);
			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 5); this->face_mesh.addIndex(index + 1);

			this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 5); this->face_mesh.addIndex(index + 6);
			this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 6); this->face_mesh.addIndex(index + 2);

			this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 6); this->face_mesh.addIndex(index + 7);
			this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 7); this->face_mesh.addIndex(index + 3);

			this->face_mesh.addIndex(index + 3); this->face_mesh.addIndex(index + 7); this->face_mesh.addIndex(index + 4);
			this->face_mesh.addIndex(index + 3); this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 0);

			// Frame Index

			this->frame_mesh.addIndex(index + 0); this->frame_mesh.addIndex(index + 1);
			this->frame_mesh.addIndex(index + 1); this->frame_mesh.addIndex(index + 2);
			this->frame_mesh.addIndex(index + 2); this->frame_mesh.addIndex(index + 3);
			this->frame_mesh.addIndex(index + 3); this->frame_mesh.addIndex(index + 0);

			this->frame_mesh.addIndex(index + 4); this->frame_mesh.addIndex(index + 5);
			this->frame_mesh.addIndex(index + 5); this->frame_mesh.addIndex(index + 6);
			this->frame_mesh.addIndex(index + 6); this->frame_mesh.addIndex(index + 7);
			this->frame_mesh.addIndex(index + 7); this->frame_mesh.addIndex(index + 4);

			this->frame_mesh.addIndex(index + 0); this->frame_mesh.addIndex(index + 4);
			this->frame_mesh.addIndex(index + 1); this->frame_mesh.addIndex(index + 5);
			this->frame_mesh.addIndex(index + 2); this->frame_mesh.addIndex(index + 6);
			this->frame_mesh.addIndex(index + 3); this->frame_mesh.addIndex(index + 7);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.44);

	ofSetColor(0);
	this->face_mesh.drawFaces();

	ofSetColor(96);
	this->frame_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// ���w�f�b�T������ �`���Ċy���ސ��w�����@P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}