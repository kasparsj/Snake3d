#include "Snake3d.h"
#include "ofGraphics.h"
#include "of3dGraphics.h"

void Snake3d::setup(ofVec3f gridSize, ofVec3f cellSize, int length) {
    this->gridSize = gridSize;
    this->cellSize = cellSize;
    this->boxSize = cellSize * gridSize;
    this->length = length;
    initLength = length;
    
    apple.loadModel("apple.3ds");
    ofVec3f sceneSize = apple.getSceneMax() - apple.getSceneMin();
    float scale = .5f / MAX(MAX(sceneSize.x, sceneSize.y), sceneSize.z);
    apple.setScale(scale, scale, scale);
    glShadeModel(GL_SMOOTH);
    addApple();
    
    keys[OF_KEY_LEFT] = ofVec3f(-1, 0, 0);
    keys[OF_KEY_RIGHT] = ofVec3f(1, 0, 0);
    keys[OF_KEY_DOWN] = ofVec3f(0, 0, 1);
    keys[OF_KEY_UP] = ofVec3f(0, 0, -1);
    keys['a'] = ofVec3f(0, 0, -1);
    keys['d'] = ofVec3f(0, 0, 1);
    keys['w'] = ofVec3f(1, 0, 0);
    keys['s'] = ofVec3f(-1, 0, 0);
}

void Snake3d::update() {
    if (rotationTarget.asVec3().match(rotation.asVec3(), 0.001f)) {
        rotation = rotationTarget;
    }
    else {
        rotation += (rotationTarget - rotation) * rotationSpeed;
    }
    rotation.getRotate(rotAngle, rotAxis);
    
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
        
        ofVec3f minPos = getMinPos();
        ofVec3f maxPos = getMaxPos();

        if (snake[0].x > maxPos.x) {
            holePos[0] = snake[0];
            holePos[1] = ofVec3f(minPos.x, snake[0].y, snake[0].z);
            holeAxis = ofVec3f(0, 1, 0);
            snake[0].x = minPos.x;
        }
        else if(snake[0].x < minPos.x) {
            holePos[0] = snake[0];
            holePos[1] = ofVec3f(maxPos.x, snake[0].y, snake[0].z);
            holeAxis = ofVec3f(0, 1, 0);
            snake[0].x = maxPos.x;
        }
        if (snake[0].y > maxPos.y) {
            holePos[0] = snake[0];
            holePos[1] = ofVec3f(snake[0].x, minPos.y, snake[0].z);
            holeAxis = ofVec3f(1, 0, 0);
            snake[0].y = minPos.y;
        }
        else if (snake[0].y < minPos.y) {
            holePos[0] = snake[0];
            holePos[1] = ofVec3f(snake[0].x, maxPos.y, snake[0].z);
            holeAxis = ofVec3f(1, 0, 0);
            snake[0].y = maxPos.y;
        }
        if (snake[0].z > maxPos.z) {
            holePos[0] = snake[0];
            holePos[1] = ofVec3f(snake[0].x, snake[0].y, minPos.z);
            holeAxis = ofVec3f(0, 0, 1);
            snake[0].z = minPos.z;
        }
        else if (snake[0].z < minPos.z) {
            holePos[0] = snake[0];
            holePos[1] = ofVec3f(snake[0].x, snake[0].y, maxPos.z);
            holeAxis = ofVec3f(0, 0, 1);
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
    ofVec3f minPos = getMinPos();
    ofVec3f maxPos = getMaxPos();
    int x = round(ofRandom(minPos.x, maxPos.x));
    int y = round(ofRandom(minPos.y, maxPos.y));
    int z = round(ofRandom(minPos.z, maxPos.z));
    apples.push_back(ofVec3f(x, y, z));
}

bool Snake3d::checkApple(const ofVec3f &p) {
    for (int i=0; i<apples.size(); i++) {
        if (apples[i].match(p, 0.01f)) {
            snake[length] = snake[length-1] + dir;
            length++;
            apples.erase(apples.begin() + i);
            return true;
        }
    }
    return false;
}

void Snake3d::draw() {
    ofPushMatrix();
    
    ofRotate(rotAngle, rotAxis.x, rotAxis.y, rotAxis.z);
    
    ofPushStyle();
    
    drawBox();
    drawApple();
    drawSnake();
    drawHoles();
    
    ofPopStyle();
    
    ofPopMatrix();
}

void Snake3d::drawBox() {
    ofNoFill();
    ofSetColor(ofColor::black);
    ofDrawBox(0, 0, 0, boxSize.x, boxSize.y, boxSize.z);
}

void Snake3d::drawApple() {
    ofSetColor(ofColor::white);
    for (int i=0; i<apples.size(); i++) {
        ofPoint point = (apples[i] + 0.5) * cellSize;
        apple.setPosition(point.x, point.y, point.z);
        apple.drawFaces();
        
        if (false) {
            point = apples[i] * cellSize;
            float minZ = gridSize.z * cellSize.z / -2.f;
            float maxZ = gridSize.z * cellSize.z / 2.f;
            ofDrawLine(point.x, point.y, minZ, point.x, point.y, maxZ);
            ofDrawLine(point.x + cellSize.x, point.y, minZ, point.x + cellSize.x, point.y, maxZ);
            ofDrawLine(point.x, point.y + cellSize.y, minZ, point.x, point.y + cellSize.y, maxZ);
            ofDrawLine(point.x + cellSize.x, point.y + cellSize.y, minZ, point.x + cellSize.x, point.y + cellSize.y, maxZ);
        }
    }
}

void Snake3d::drawSnake() {
    ofSetColor(ofColor::black);
    ofFill();
    for (int i=0; i<length; i++) {
        ofPoint point = (snake[i] + 0.5) * cellSize;
        ofDrawBox(point, cellSize.x, cellSize.y, cellSize.z);
    }
}

void Snake3d::drawHoles() {
    ofNoFill();
    if (holePos[0] != ofVec3f() || holePos[1] != ofVec3f()) {
        ofPushMatrix();
        
        ofRotate(90, -holeAxis.x, -holeAxis.y, -holeAxis.z);
        ofDrawCircle((holePos[0] + 0.5).getRotated(90, holeAxis) * cellSize, 40);
        ofDrawCircle((holePos[1] + 0.5).getRotated(90, holeAxis) * cellSize, 40);
        
        ofPopMatrix();
    }
}

void Snake3d::keyPressed(int key) {
    std::map<int, int> inverseKeys = {{OF_KEY_LEFT, OF_KEY_RIGHT}, {OF_KEY_RIGHT, OF_KEY_LEFT}, {OF_KEY_UP, OF_KEY_DOWN}, {OF_KEY_DOWN, OF_KEY_UP}};
    std::map<int, int> similarKeys = {{OF_KEY_LEFT, 'a'}, {OF_KEY_RIGHT, 'd'}, {OF_KEY_UP, 'w'}, {OF_KEY_DOWN, 's'}};
    switch (key) {
        case OF_KEY_LEFT:
        case OF_KEY_RIGHT:
        case OF_KEY_DOWN:
        case OF_KEY_UP:
            if (lastArrowKey == key || lastArrowKey == inverseKeys[key]) {
                rotate(similarKeys[key]);
            }
            else {
                turn(key);
            }
            lastArrowKey = key;
            break;
//        case 'w':
//        case 's':
//        case 'a':
//        case 'd': {
//            rotate(key);
//            break;
//        }
    }
}

void Snake3d::turn(int key) {
    dir = keys[key];
}

void Snake3d::rotate(int key) {
    rotationTarget *= ofQuaternion(90, keys[key]);
    ofVec3f axis = -keys[key] * rotationTarget.inverse();
    dir.rotate(90, axis);
    keys[OF_KEY_LEFT].rotate(90, axis);
    keys[OF_KEY_RIGHT].rotate(90, axis);
    keys[OF_KEY_DOWN].rotate(90, axis);
    keys[OF_KEY_UP].rotate(90, axis);
}
