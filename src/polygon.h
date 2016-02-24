#pragma once
#include "ofMain.h"

class polygon : public ofBaseApp{
public:
    void setup(int size);
    void update(int size , float noise);
    void draw();
    void clear();
    
    void random(float range);
    
    vector<ofVec3f> points;
    vector<ofVec3f> points_temp;


};