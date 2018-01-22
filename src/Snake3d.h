#pragma once

#include "ofQuaternion.h"
#include "ofxAssimpModelLoader.h"

#define MAX_LENGTH 1000

class Snake3d {
    
public:
    ofVec3f snake[MAX_LENGTH];
    vector<ofVec3f> apples;
    ofVec3f dir;
    int speed[2] = {1, 6}; // cells to move, per frames
    int currentFrame = -1;
    int length;
    int initLength;
    ofVec3f gridSize;
    ofVec3f cellSize;
    ofVec3f boxSize;
    ofVec3f holePos[2];
    ofVec3f holeAxis;
    ofxAssimpModelLoader apple;
    std::map<int, ofVec3f> keys;
    int lastArrowKey;
    ofQuaternion rotation;
    ofQuaternion rotationTarget;
    float rotationSpeed = 0.1f;
    float rotAngle;
    ofVec3f rotAxis;


    void setup(ofVec3f gridSize, ofVec3f cellSize, int length = 5);
    void update();
    void draw();
    void addApple();
    bool checkCollision(const ofVec3f &p);
    bool checkApple(const ofVec3f &p);
    void keyPressed(int key);
    void turn(int key);
    void rotate(int key);
    
    int getSpeed() {
        return speed[0];
    }
    void setSpeed(int numCells) {
        speed[0] = MAX(numCells, 1);
    }
    int getFrames() {
        return speed[1];
    }
    void setFrames(int numFrames) {
        speed[1] = MAX(numFrames, 1);
    }
    ofVec3f getMinPos() {
        return ofVec3f(gridSize.x / -2.f, gridSize.y / -2.f, gridSize.z / -2.f);
    }
    ofVec3f getMaxPos() {
        return ofVec3f(gridSize.x / 2.f - 1.f, gridSize.y / 2.f - 1.f, gridSize.z / 2.f - 1.f);
    }
    
private:
    void drawBox();
    void drawApple();
    void drawSnake();
    void drawHoles();
    
};
