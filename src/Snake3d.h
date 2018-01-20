#pragma once

#include "ofVec3f.h"

#define MAX_LENGTH 1000

class Snake3d {
    
public:
    ofVec3f snake[MAX_LENGTH];
    vector<ofVec3f> apples;
    ofVec3f dir;
    int speed[2] = {1, 5}; // cells to move, per frames
    int currentFrame = -1;
    int length;
    int initLength;
    ofVec3f minPos;
    ofVec3f maxPos;
    ofVec3f cellSize;

    void setup(ofVec3f gridSize, ofVec3f cellSize, int length = 10);
    void update();
    void draw();
    void addApple();
    bool checkCollision(const ofVec3f &p);
    bool checkApple(const ofVec3f &p);
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
    
};
