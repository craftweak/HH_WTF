#include "circle.h"

void circle::setup() {
    
    svg.load("circle.svg");
    
    
	for (int i = 0; i < svg.getNumPath(); i++){
		ofPath p = svg.getPathAt(i);
		// svg defaults to non zero winding which doesn't look so good as contours
		p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        
		vector<ofPolyline>& lines = p.getOutline();
        
        
		for(int j=0;j<(int)lines.size();j++){
			outlines.push_back(lines[j].getResampledBySpacing(1));
		}
	}
    
    drawcircleline = false;
    
    
    
    
    
}
//------------------------------------------------------------------------------------------
void circle::update() {
    
    
    
    
    
    
}
//------------------------------------------------------------------------------------------
void circle::draw() {
    
    ofPushMatrix();
    ofPushStyle();
    ofSetLineWidth(2);
    ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
    
    ofRotateZ(rr);
    ofTranslate(-svg.getWidth()/2, -svg.getHeight()/2);
    ofNoFill();
    for (int i = 0; i < (int)outlines.size(); i++){
        ofPolyline & line = outlines[i];
        int num = pst * line.size();
        ofBeginShape();
        for (int j = 0; j < num; j++){
            ofVertex(line[j]);
        }
        ofEndShape();
    }
    
	ofPushStyle();
	ofPopMatrix();
    
    
    
    
}
//------------------------------------------------------------------------------------------
void circle::exit() {
    
    
    
    
    
    
}
//------------------------------------------------------------------------------------------
void circle::circleline() {
    
    
    Tweenzor::add(&pst, 0.f, 1.f, 0.f, 1.2f,EASE_IN_OUT_CUBIC);
    Tweenzor::add(&rr, 0.f, 360.f, 0.f, 1.f,EASE_IN_OUT_CUBIC);
    Tweenzor::addCompleteListener( Tweenzor::getTween(&pst), this, &circle::circlelineEnd);
    
    //drawcircleline = false;
    
    
    
    
    
}
//------------------------------------------------------------------------------------------
void circle::circlelineEnd(float *arg) {
    
    Tweenzor::add(&pst, 1.f, 0.f, 0.f, 1.2f,EASE_IN_OUT_CUBIC);
    Tweenzor::add(&rr, 360.f, 0.f, 0.2f, 1.f,EASE_IN_OUT_CUBIC);
    
    
    
    
}
//------------------------------------------------------------------------------------------
