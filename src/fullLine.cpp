#include "fullLine.h"

//--------------------------------------------------------------
void fullLine::setup(int num){
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_SCREEN);
    
    num = 10;
    
    for (int i = 0; i<4; i++) {
        pos00[i].set(0.f,0.f);
        pos01[i].set(0.f,0.f);
    }
    
    for (int i = 0; i<4; i++) {
        col[i].set(255.f,0.f);
    }
}
//--------------------------------------------------------------
void fullLine::update(){
    
}
//--------------------------------------------------------------
void fullLine::draw(int num ){
    
    int numn = num;
    
    ofPushStyle();
    
    ofSetLineWidth(3);
    
//    ofSetColor(col[0].x,col[0].x,col[0].x,col[0].y);
//    for (int i = 0 ; i < numn; i++) {
//         ofLine(pos00[0].x,pos00[0].y+i*(ofGetWindowHeight()/numn),pos01[0].x,pos01[0].y+i*(ofGetWindowHeight()/numn));
//    }
//    ofSetColor(col[1].x,col[1].x,col[1].x,col[1].y);
//    for (int i = 0 ; i < numn; i++) {
//        ofLine(pos00[1].x,pos00[1].y+i*(ofGetWindowHeight()/numn),pos01[1].x,pos01[1].y+i*(ofGetWindowHeight()/numn));
//    }
//    
//    ofSetColor(col[2].x,col[2].x,col[2].x,col[2].y);
//    for (int i = 0 ; i < numn; i++) {
//        ofLine(pos00[2].x+i*(ofGetWindowWidth()/numn),pos00[2].y,pos01[2].x+i*(ofGetWindowWidth()/numn),pos01[2].y);
//    }
//    ofSetColor(col[3].x,col[3].x,col[3].x,col[3].y);
//    for (int i = 0 ; i < numn; i++) {
//        ofLine(pos00[3].x+i*(ofGetWindowWidth()/numn),pos00[3].y,pos01[3].x+i*(ofGetWindowWidth()/numn),pos01[3].y);
//    }
    ofSetColor(col[0].x,col[0].x,col[0].x,col[0].y);
    for (int i = 0 ; i < numn; i++) {
        ofLine(pos00[0].x,pos00[0].y+i*80,pos01[0].x,pos01[0].y+i*80);
    }
    ofSetColor(col[1].x,col[1].x,col[1].x,col[1].y);
    for (int i = 0 ; i < numn; i++) {
        ofLine(pos00[1].x,pos00[1].y+i*80,pos01[1].x,pos01[1].y+i*80);
    }
    
    ofSetColor(col[2].x,col[2].x,col[2].x,col[2].y);
    for (int i = 0 ; i < numn; i++) {
        ofLine(pos00[2].x+i*80,pos00[2].y,pos01[2].x+i*80,pos01[2].y);
    }
    ofSetColor(col[3].x,col[3].x,col[3].x,col[3].y);
    for (int i = 0 ; i < numn; i++) {
        ofLine(pos00[3].x+i*80,pos00[3].y,pos01[3].x+i*80,pos01[3].y);
    }
    
    ofPopStyle();
}
//--------------------------------------------------------------
void fullLine::fadeLineIn01(){
    
    //pos01[0].y =ofGetWindowHeight();
    
    Tweenzor::add(&col[0].x, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[0].x, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[0].y, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[0].y, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&pos01[0].x, 0.f, ofGetWindowWidth(), 0.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&pos00[0].x, 0.f, ofGetWindowWidth(), 1.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&col[0].y), this, &fullLine::fadeLineEnd01);
    
}
//--------------------------------------------------------------
void fullLine::fadeLineEnd01(float *arg){
    pos00[0].set(0.f,0.f);
    pos01[0].set(0.f,0.f);
    
}
//--------------------------------------------------------------
void fullLine::fadeLineIn02(){
    pos00[1].x =ofGetWindowWidth();
    pos01[1].x =ofGetWindowWidth();
    Tweenzor::add(&col[1].x, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[1].x, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[1].y, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[1].y, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&pos00[1].x, ofGetWindowWidth(), 0.f, 0.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&pos01[1].x, ofGetWindowWidth(), 0.f, 1.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&col[1].y), this, &fullLine::fadeLineEnd02);
    
}
//--------------------------------------------------------------
void fullLine::fadeLineEnd02(float *arg){
    pos00[1].set(0.f,0.f);
    pos01[1].set(0.f,0.f);
    
}
//--------------------------------------------------------------
void fullLine::fadeLineIn03(){
//    pos00[2].x =ofGetWindowWidth();
//    pos01[2].x =ofGetWindowWidth();
    Tweenzor::add(&col[2].x, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[2].x, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[2].y, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[2].y, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&pos00[2].y, 0.f, ofGetWindowHeight(), 0.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&pos01[2].y, 0.f, ofGetWindowHeight(), 1.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&col[2].y), this, &fullLine::fadeLineEnd03);
    
}
//--------------------------------------------------------------
void fullLine::fadeLineEnd03(float *arg){
    pos00[2].set(0.f,0.f);
    pos01[2].set(0.f,0.f);
    
}
//--------------------------------------------------------------
void fullLine::fadeLineIn04(){
    pos00[3].y =ofGetWindowHeight();
    pos01[3].y =ofGetWindowHeight();
    
    Tweenzor::add(&col[3].x, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[3].x, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[3].y, 0.f, 200.f, 0.f, 0.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&col[3].y, 200.f, 0.f, 0.f, 2.5f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&pos00[3].y, ofGetWindowHeight(), 0.f, 0.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::add(&pos01[3].y, ofGetWindowHeight(), 0.f, 1.f, 1.f,EASE_IN_OUT_QUAD);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&col[3].y), this, &fullLine::fadeLineEnd04);
    
}
//--------------------------------------------------------------
void fullLine::fadeLineEnd04(float *arg){
    pos00[3].set(0.f,0.f);
    pos01[3].set(0.f,0.f);
    
}