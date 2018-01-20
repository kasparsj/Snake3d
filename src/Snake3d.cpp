#include "Snake3d.h"
#include "ofGraphics.h"
#include "of3dGraphics.h"

void Snake3d::setup(ofVec3f gridSize, ofVec3f cellSize, int length) {
    this->minPos = ofVec3f(gridSize.x / -2.f, gridSize.y / -2.f, gridSize.z / -2.f);
    this->maxPos = ofVec3f(gridSize.x / 2.f, gridSize.y / 2.f, gridSize.z / 2.f);
    this->cellSize = cellSize;
    this->length = length;
    initLength = length;
    addApple();
}

void Snake3d::update() {
    currentFrame++;
    if (dir == ofVec3f(0, 0, 0) || currentFrame % speed[1] > 0) {
        return;
    }
    
    ofVec3f newPos = snake[0] + dir * speed[0];
    if (checkCollision(newPos)) {
        for (int i=1; i<length; i++) {
            snake[i] = snake[0];
        }
        length = initLength;
        dir = ofVec3f(0, 0, 0);
    }
    else {
        for (int i=(MAX_LENGTH-1); i>0; i--) {
            if ((i - speed[0]) >= 0) {
                snake[i] = snake[i - speed[0]];
            }
            else {
                snake[i] = newPos + dir * i;
            }
        }
        snake[0] = newPos;
        if (snake[0].x > maxPos.x) {
            snake[0].x = minPos.x;
        }
        else if(snake[0].x < minPos.x) {
            snake[0].x = maxPos.x;
        }
        if (snake[0].y > maxPos.y) {
            snake[0].y = minPos.y;
        }
        else if (snake[0].y < minPos.y) {
            snake[0].y = maxPos.y;
        }
        if (snake[0].z > maxPos.z) {
            snake[0].z = minPos.z;
        }
        else if (snake[0].z < minPos.z) {
            snake[0].z = maxPos.z;
        }
        if (checkApple(newPos)) {
            addApple();
        }
    }
}

bool Snake3d::checkCollision(const ofVec3f &p) {
    for (int i=0; i<length; i++) {
        if (snake[i].match(p)) {
            return true;
        }
    }
    return false;
}

void Snake3d::addApple() {
    int x = round(ofRandom(minPos.x, maxPos.x));
    int y = round(ofRandom(minPos.y, maxPos.y));
    int z = round(ofRandom(minPos.z, maxPos.z));
    apples.push_back(ofVec3f(x, y, z));
}

bool Snake3d::checkApple(const ofVec3f &p) {
    for (int i=0; i<apples.size(); i++) {
        if (apples[i].match(p)) {
            snake[length] = snake[length-1] + dir;
            length++;
            apples.erase(apples.begin() + i);
            return true;
        }
    }
    return false;
}

void Snake3d::draw() {
    ofPushStyle();
    ofSetColor(ofColor::red);
    ofFill();
    for (int i=0; i<apples.size(); i++) {
        ofPoint point = apples[i] * cellSize;
        ofDrawBox(point, cellSize.x, cellSize.y, cellSize.z);
    }
    ofSetColor(ofColor::black);
    ofFill();
    for (int i=0; i<length; i++) {
        ofPoint point = snake[i] * cellSize;
        ofDrawBox(point, cellSize.x, cellSize.y, cellSize.z);
    }
    ofPopStyle();
}
