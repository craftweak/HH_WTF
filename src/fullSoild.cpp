#include "fullSoild.h"

//--------------------------------------------------------------
void fullSoild::setup(){
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_SCREEN);
    
    pos[0].set(0,0);
    pos[1].set(ofGetWindowWidth(),0);
    pos[2].set(0,ofGetWindowHeight());
    pos[3].set(0,0);
    
    for (int i = 0; i<4; i++) {
        wh[i].set(0.f,0.f);
    }
    
    for (int i = 0; i<4; i++) {
        col[i].set(0.f,0.f);
    }
    
    
}

//--------------------------------------------------------------
void fullSoild::update(){
    
    
    
}
//--------------------------------------------------------------
void fullSoild::draw(){
    
    
    for (int i = 0; i<4; i++) {
        ofSetColor(col[i].x,col[i].x,col[i].x,col[i].y);
        ofRect(pos[i],wh[i].x,wh[i].y);
    }
}
//--------------------------------------------------------------
void fullSoild::fadeSoildIn01(){
    
    wh[0].y =ofGetWindowHeight();
    Tweenzor::add(&col[0].x, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[0].x, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[0].y, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[0].y, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&wh[0].x, 0.f, ofGetWindowWidth(), 0.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&pos[0].x, 0.f, ofGetWindowWidth(), 1.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&col[0].y), this, &fullSoild::fadeSoildEnd01);
    
}
//--------------------------------------------------------------
void fullSoild::fadeSoildEnd01(float *arg){
    pos[0].set(0,0);
    wh[0].set(0.f,0.f);
    
}
//--------------------------------------------------------------
void fullSoild::fadeSoildIn02(){
    wh[1].y =ofGetWindowHeight();
    wh[1].x =ofGetWindowWidth();
    Tweenzor::add(&col[1].x, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[1].x, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[1].y, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[1].y, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&wh[1].x,ofGetWindowWidth() ,0.f, 1.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&pos[1].x, ofGetWindowWidth(), 0.f, 0.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&col[1].y), this, &fullSoild::fadeSoildEnd02);
    
    
}
//--------------------------------------------------------------
void fullSoild::fadeSoildEnd02(float *arg){
    pos[1].set(ofGetWindowWidth(),0);
    wh[1].set(0.f,0.f);
    
    
}
//--------------------------------------------------------------
void fullSoild::fadeSoildIn03(){
    wh[2].y =ofGetWindowHeight();
    wh[2].x =ofGetWindowWidth();
    Tweenzor::add(&col[2].x, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[2].x, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[2].y, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[2].y, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&wh[2].y,ofGetWindowHeight() ,0.f, 1.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&pos[2].y, ofGetWindowHeight(), 0.f, 0.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&col[2].y), this, &fullSoild::fadeSoildEnd03);
}
//--------------------------------------------------------------
void fullSoild::fadeSoildEnd03(float *arg){
    pos[2].set(0,ofGetWindowHeight());
    wh[2].set(0.f,0.f);
    
    
}
//--------------------------------------------------------------
void fullSoild::fadeSoildIn04(){
    
    wh[3].x =ofGetWindowWidth();
    Tweenzor::add(&col[3].x, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[3].x, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[3].y, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[3].y, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&wh[3].y,0.f,ofGetWindowHeight() , 0.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&pos[3].y, 0.f,ofGetWindowHeight(), 1.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&col[3].y), this, &fullSoild::fadeSoildEnd04);
    
    
}
//--------------------------------------------------------------
void fullSoild::fadeSoildEnd04(float *arg){
    pos[3].set(0,0);
    wh[3].set(ofGetWindowWidth(),0.f);
    
    
}