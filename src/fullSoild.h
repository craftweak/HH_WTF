#pragma once

#include "ofMain.h"
#include "ofxTweenzor.h"

class fullSoild : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void fadeSoildIn01();
    void fadeSoildEnd01(float* arg);
    void fadeSoildIn02();
    void fadeSoildEnd02(float* arg);
    void fadeSoildIn03();
    void fadeSoildEnd03(float* arg);
    void fadeSoildIn04();
    void fadeSoildEnd04(float* arg);

    
    
    ofPoint pos[4];
    ofPoint wh[4];
    ofPoint col[4];

};