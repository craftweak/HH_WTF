#pragma once
#include "ofMain.h"
#include "ofxSvg.h"
#include "ofxTweenzor.h"

class circle {
    
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void circleline();
    void circlelineEnd(float* arg);
    
    ofxSVG svg;
    float step;
    
    float pst;
    
    vector<ofPolyline> outlines;
    
    bool drawcircleline;
    
    float xx,yy,rr;
    
};
