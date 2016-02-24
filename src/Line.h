#pragma once
#include "ofMain.h"
#include "ofxPlaylist.h"
#include "ofxTweenzor.h"
#include "ofxSvg.h"

class Line {
    
public:
    
    ofVec2f position;
    void setup(ofVec2f position);
    void update();
    void draw();
    
    void exit();
    //void trigger();
    void LineDrawing01();
    void LineDrawing02();
    void CircleDrawing();
    void CircleDrawing1End(float* arg);
    void CircleDrawing2();
    void CircleDrawing2End(float* arg);
    void twoPointLine00();
    void twoPointLine01();
    void twoPointLine02();
    void twoPointLineEnd(float* arg);
    void circleLine();
    void circleLineEnd(float* arg);
    
    //void onComplete(float* arg);
    
    ofxPlaylist mainPlaylist;
    ofxPlaylist linePlaylist;
	
	ofVec3f		rectPos;
    ofVec3f     rectScale;
	float		rectRotation;
    
    ofVec2f CircleScale;
    ofVec2f CirclePos;
    ofVec2f CircleCol;
    
    
    ofVec2f LineStart;
    ofVec2f LineEnd;
    float   LineRot;
    ofVec4f LineCol;
    
    int Dir;
    
    
    float RR;
    ofVec2f RRpos;
    ofVec4f CircleCol2;
    
    float Reso;
    
    ofPoint Pos2;
    float RR2;
    float Reso2;
    
    
    ofPoint p01,p02,p03,p04,p05,p06,p07,p08,p09,p10,p11,p12;
    
    
    
    ofxSVG svg;
    float step;
    
    float pst;
    
    vector<ofPolyline> outlines;
    
    bool drawcircleline;
    
    float xx,yy,rr;
};
