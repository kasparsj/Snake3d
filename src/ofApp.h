#pragma once

#include "ofMain.h"
#include "Snake3d.h"
#include "ofCamera.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    Snake3d snake;
    ofCamera camera;
    ofQuaternion rotation;
    ofQuaternion rotationTarget;
    ofVec3f gridSize;
    ofVec3f cellSize;
    ofVec3f boxSize;
    float rotationSpeed = 0.1f;
    std::map<int, ofVec3f> keys;
    int lastArrowKey;
};
