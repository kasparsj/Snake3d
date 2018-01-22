#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    ofEnableDepthTest();
    
    snake.setup(ofVec3f(40, 40, 40), ofVec3f(20, 20, 20));
    
    camera.setupPerspective(false, 60, 0.1, 10000);
    camera.setPosition(ofVec3f(0, 1100, 0));
    camera.lookAt(ofVec3f(0, 0, 0));
}

//--------------------------------------------------------------
void ofApp::update() {
    snake.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    camera.begin();

    snake.draw();
    
    camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    snake.keyPressed(key);
    
    switch (key) {
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
