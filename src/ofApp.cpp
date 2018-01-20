#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetBackgroundAuto(false);
    
    gridSize = ofVec3f(40, 40, 40);
    cellSize = ofVec3f(20, 20, 20);
    boxSize = cellSize * gridSize;
    snake.setup(gridSize, cellSize);
    
    camera.setupPerspective(false, 60, 0.1, 10000);
    camera.setPosition(ofVec3f(0, 1000, 0));
    camera.lookAt(ofVec3f(0, 0, 0));
    
    keys[OF_KEY_LEFT] = ofVec3f(-1, 0, 0);
    keys[OF_KEY_RIGHT] = ofVec3f(1, 0, 0);
    keys[OF_KEY_DOWN] = ofVec3f(0, 0, 1);
    keys[OF_KEY_UP] = ofVec3f(0, 0, -1);
    keys['a'] = ofVec3f(0, 0, -1);
    keys['d'] = ofVec3f(0, 0, 1);
    keys['w'] = ofVec3f(1, 0, 0);
    keys['s'] = ofVec3f(-1, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update() {
    if (rotationTarget.asVec3().match(rotation.asVec3(), 0.001f)) {
        rotation = rotationTarget;
        snake.update();
    }
    else {
        rotation += (rotationTarget - rotation) * rotationSpeed;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    
    camera.begin();
    
    ofPushMatrix();
    
    float angle;
    ofVec3f axis;
    rotation.getRotate(angle, axis);
    ofRotate(angle, axis.x, axis.y, axis.z);
    
    ofPushStyle();
    
    ofNoFill();
    ofSetColor(0);
    ofDrawBox(0, 0, 0, boxSize.x, boxSize.y, boxSize.z);
    
    ofPopStyle();
    
    snake.draw();
    
    ofPopMatrix();
    
    camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (rotation != rotationTarget) {
        return;
    }
    switch (key) {
        case OF_KEY_LEFT:
        case OF_KEY_RIGHT:
        case OF_KEY_DOWN:
        case OF_KEY_UP:
            if (abs(lastArrowKey - key) != 2) {
                snake.dir = keys[key];
                lastArrowKey = key;
            }
            break;
        case 'w':
        case 's':
        case 'a':
        case 'd': {
            rotationTarget *= ofQuaternion(90, keys[key]);
            ofVec3f axis = -keys[key] * rotationTarget.inverse();
            snake.dir.rotate(90, axis);
            keys[OF_KEY_LEFT].rotate(90, axis);
            keys[OF_KEY_RIGHT].rotate(90, axis);
            keys[OF_KEY_DOWN].rotate(90, axis);
            keys[OF_KEY_UP].rotate(90, axis);
            break;
        }
        case '-':
            snake.setSpeed(snake.getSpeed() - 1);
            break;
        case '=':
        case '+':
            snake.setSpeed(snake.getSpeed() + 1);
            break;
        case '[':
            snake.setFrames(snake.getFrames() - 1);
            break;
        case ']':
            snake.setFrames(snake.getFrames() + 1);
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
