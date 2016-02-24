#pragma once

#include "ofMain.h"
#include "fullLine.h"
#include "ofxTweenzor.h"

class fullLine : public ofBaseApp{
    
public:
    void setup(int num);
    void update();
    void draw(int num);
    
    void fadeLineIn01();
    void fadeLineEnd01(float* arg);
    void fadeLineIn02();
    void fadeLineEnd02(float* arg);
    void fadeLineIn03();
    void fadeLineEnd03(float* arg);
    void fadeLineIn04();
    void fadeLineEnd04(float* arg);
    
    
    
    ofPoint pos00[4];
    ofPoint pos01[4];
    ofPoint col[4];
    
};