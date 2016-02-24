

#include "Line.h"

void Line::setup(ofVec2f _position){
    position = _position;
    
    // init
	rectRotation = 0.f;
	rectPos.set(ofRandomWidth(), ofRandomHeight());
    rectScale.set(1, 1);
    
    LineStart.set(0, 0);
    LineEnd.set(0, 0);
    LineCol.set(0,0,0,0);
    
    RR = 0.0;
    RRpos.set(ofGetWindowWidth()/2  ,ofGetWindowHeight()/2);
    Reso = 0;
    Pos2.set(0,0);
    
    //Tweenzor::init();
    
    
    p01.set(0, 0);
    p02.set(0, 0);
    p03.set(0, 0);
    p04.set(0, 0);
    
    
    
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
    
    //drawcircleline = false;
    
    xx =0;
    yy =0;
}

void Line::update(){
    mainPlaylist.update();
    linePlaylist.update();
    //ofSetCircleResolution(32);
    

    
}
void Line::draw(){
    ofSetHexColor(0x3399cc);
//    ofCircle(position, 10);
//    
//    
//    ofPushMatrix();
//    ofSetColor(255);
//	ofTranslate(rectPos);
//	ofRotateZ(rectRotation);
//    ofScale(rectScale.x,rectScale.y);
//    ofRect(0,0, 200, 100);
//	ofPopMatrix();
    
    ofPushMatrix();
    ofPushStyle();
    //ofsetar
    ofSetLineWidth(2.0);
    ofRotateZ(LineRot);
    ofSetColor(LineCol.x,LineCol.w);
    ofLine(LineStart, LineEnd);
    ofPopStyle();
    ofPopMatrix();
    
    ofSetColor(CircleCol2.x,CircleCol2.w);
    ofCircle(RRpos, RR);
    
    
    ofPushStyle();
    ofFill();
    ofSetColor(255, 255, 255,255);
    ofSetCircleResolution(Reso2);
    ofCircle(Pos2, RR2);
    ofPopStyle();
    
    
    //two
    ofSetColor(255,255);
    ofLine(p01,p02);
//    ofSetColor(0, 255, 0,255);
//    ofCircle(p01.x,p01.y,0, 2);
//    ofSetColor(0, 0, 255,255);
//    ofCircle(p02.x,p02.y,0, 2);
    
    
    
    
    

}
//--------------------------------------------------------------
void Line::exit() {
	Tweenzor::destroy();
}
//------------
void Line::CircleDrawing2(){
    
    Pos2.set(ofRandom(0,ofGetWindowWidth()), ofRandom(0, ofGetWindowHeight()));
    Tweenzor::add(&RR2, 0.f, 300.f, 0.f, 1.f);
    Tweenzor::add(&Reso2, 3.f, 16.f, 0.3f, 1.f);;
    Tweenzor::addCompleteListener(Tweenzor::getTween(&RR2), this, &Line::CircleDrawing2End);
}
//--------------------------------------------------------------
void Line::CircleDrawing2End(float* arg){
    
    using namespace Playlist;
    mainPlaylist.addKeyFrame(Action::tween(300.f, &RR2, 0,TWEEN_CUBIC,TWEEN_EASE_IN_OUT));
    mainPlaylist.addToKeyFrame(Action::tween(100.f, &Reso2, 0,TWEEN_CUBIC,TWEEN_EASE_IN_OUT));
}

//void Line::trigger(){
//    
//    using namespace Playlist;
//    
//    // this will move a rectangle to the mouse position.
//    // and then wobble sigthly.
//    
//    ofVec3f targetPosition = ofVec3f(ofGetMouseX(), ofGetMouseY());
//    ofVec3f targetScale = ofVec3f(ofRandom(2.0), ofRandom(2.0));
//    
//    // (1) take 1000ms to move to random target point on x axis,
//    // (2) wait 500ms, then take 500ms to move to random target point on y axis
//    
//    mainPlaylist.addKeyFrame(	Action::tween(500.f, &rectPos.x, targetPosition.x, TWEEN_BOUNCE, TWEEN_EASE_OUT));		// -- (1)
//    mainPlaylist.addToKeyFrame(	Action::tween(500.f, &rectPos.y, targetPosition.y, TWEEN_BOUNCE, TWEEN_EASE_OUT));		// -- (2)
//    mainPlaylist.addToKeyFrame(Action::pause(200.f));
//    mainPlaylist.addToKeyFrame(	Action::tween(1000.f, &rectScale.x, targetScale.x));		// -- (3)
//    mainPlaylist.addToKeyFrame(	Action::tween(1000.f, &rectScale.y, targetScale.y));		// -- (3)
//    
//    // pause for 200 ms - you will only notice this if you click repeatedly.
//    mainPlaylist.addKeyFrame(Action::pause(200.f));
//    
//    // wobble slightly once target position reached.
//    mainPlaylist.addKeyFrame(Action::tween(100.f, &rectRotation, ofRandomf()*90, TWEEN_BOUNCE, TWEEN_EASE_OUT));
//    
//    // --> try other TWEEN_ variations with the above- it's fun!
//    // --> try other TWEEN_EASE_ variations with the above - it's geeky!
//    
//}

void Line::LineDrawing01(){
    
        //LineStart.set(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight()));
    
        using namespace Playlist;
        
        ofVec2f targetPosStart   = ofVec2f(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight()));
        ofVec2f targetPosEnd   =  ofVec2f(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight()));
    
    
        int Rot = ofRandom(-30,45);
        int TargetCol01 =255;
        int TargetCol02 =0;
        
        
        //mainPlaylist.addKeyFrame(  Action::tween(0.f, &LineRot, Rot ));
        mainPlaylist.addKeyFrame(  Action::tween(50.f, &LineCol.w, TargetCol01,TWEEN_CUBIC,TWEEN_EASE_IN_OUT ));
        mainPlaylist.addToKeyFrame(  Action::tween(50.f, &LineCol.x, TargetCol01,TWEEN_CUBIC,TWEEN_EASE_IN_OUT));
        mainPlaylist.addToKeyFrame(  Action::tween(500.f, &LineEnd.x, targetPosEnd.x,TWEEN_CUBIC,TWEEN_EASE_IN_OUT));
        mainPlaylist.addToKeyFrame(  Action::tween(500.f, &LineEnd.y, targetPosEnd.y,TWEEN_CUBIC,TWEEN_EASE_IN_OUT));
        
        mainPlaylist.addToKeyFrame(  Action::tween(700.f, &LineStart.x, targetPosEnd.x,TWEEN_CUBIC,TWEEN_EASE_IN_OUT));
        mainPlaylist.addToKeyFrame(  Action::tween(700.f, &LineStart.y, targetPosEnd.y,TWEEN_CUBIC,TWEEN_EASE_IN_OUT));
        
        mainPlaylist.addKeyFrame(  Action::tween(50.f, &LineCol.w, TargetCol02 ));
        mainPlaylist.addKeyFrame(  Action::tween(0.f, &LineStart.x, 0));
        mainPlaylist.addKeyFrame(  Action::tween(0.f, &LineStart.y, 0));
        mainPlaylist.addKeyFrame(  Action::tween(0.f, &LineEnd.x, 0));
        mainPlaylist.addKeyFrame(  Action::tween(0.f, &LineEnd.y, 0));
        

        
}

void Line::LineDrawing02(){
        using namespace Playlist;
        
        ofVec2f targetPosStart   = ofVec2f(0,0);
        ofVec2f targetPosEnd   = ofVec2f(ofGetWindowWidth(), ofGetWindowHeight());
        int Rot = ofRandom(-30,45);
        int TargetCol01 =255;
        int TargetCol02 =0;

        mainPlaylist.addKeyFrame(  Action::tween(0.f, &LineStart.x, ofGetWindowWidth()));
        mainPlaylist.addKeyFrame(  Action::tween(0.f, &LineStart.y, ofGetWindowHeight()));
        mainPlaylist.addKeyFrame(  Action::tween(0.f, &LineEnd.x, ofGetWindowWidth()));
        mainPlaylist.addKeyFrame(  Action::tween(0.f, &LineEnd.y, ofGetWindowHeight()));
        mainPlaylist.addKeyFrame(  Action::tween(0.f, &LineRot, Rot ));
        mainPlaylist.addKeyFrame(  Action::tween(50.f, &LineCol.w, TargetCol01,TWEEN_CUBIC,TWEEN_EASE_IN_OUT ));
        mainPlaylist.addToKeyFrame(  Action::tween(50.f, &LineCol.x, TargetCol01,TWEEN_CUBIC,TWEEN_EASE_IN_OUT));
       
        
        mainPlaylist.addKeyFrame(  Action::tween(500.f, &LineStart.x, targetPosEnd.x,TWEEN_CUBIC,TWEEN_EASE_IN_OUT));
        mainPlaylist.addKeyFrame(  Action::tween(500.f, &LineStart.y, targetPosEnd.y,TWEEN_CUBIC,TWEEN_EASE_IN_OUT));
        
        mainPlaylist.addToKeyFrame(  Action::tween(700.f, &LineEnd.x, targetPosEnd.x,TWEEN_CUBIC,TWEEN_EASE_IN_OUT));
        mainPlaylist.addToKeyFrame(  Action::tween(700.f, &LineEnd.y, targetPosEnd.y,TWEEN_CUBIC,TWEEN_EASE_IN_OUT));
        
        mainPlaylist.addKeyFrame(  Action::tween(50.f, &LineCol.w, TargetCol02 ));
        mainPlaylist.addKeyFrame(  Action::tween(0.f, &LineStart.x, 0));
        mainPlaylist.addKeyFrame(  Action::tween(0.f, &LineStart.y, 0));
        mainPlaylist.addKeyFrame(  Action::tween(0.f, &LineEnd.x, 0));
        mainPlaylist.addKeyFrame(  Action::tween(0.f, &LineEnd.y, 0));
        
}

void Line::CircleDrawing(){
    Tweenzor::add(&RR, 0.f, 30.f, 0.f, 0.1f);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&RR), this, &Line::CircleDrawing1End);
    
}
//--------------------------------------------------------------
void Line::CircleDrawing1End(float* arg){
    
    using namespace Playlist;
    
    ofVec2f RRTargetPos = ofVec2f (ofRandom(0, ofGetWindowWidth()),ofRandom(0, ofGetWindowHeight()));
    
    linePlaylist.addKeyFrame(Action::tween(0.f, &RRpos.x, RRTargetPos.x));
    linePlaylist.addToKeyFrame(Action::tween(100.f, &Reso, 64,TWEEN_BOUNCE));
    linePlaylist.addToKeyFrame(Action::tween(0.f, &RRpos.y, RRTargetPos.y));
    
    linePlaylist.addToKeyFrame(Action::tween(100.f, &RR, 300,TWEEN_LIN,TWEEN_EASE_IN_OUT));
    
    
    linePlaylist.addToKeyFrame(Action::tween(100.f, &CircleCol2.x, 255));
    linePlaylist.addToKeyFrame(Action::tween(100.f, &CircleCol2.w, 225));
    linePlaylist.addKeyFrame(Action::tween(50.f, &CircleCol2.x, 0));
    linePlaylist.addKeyFrame(Action::tween(50.f, &CircleCol2.w, 0));
    linePlaylist.addToKeyFrame(Action::tween(0.f, &RR, 0));
    linePlaylist.addToKeyFrame(Action::tween(0.f, &Reso, 0));
}
//--------------------------------------------------------------
void Line::twoPointLine00(){
    
//    p03.set(ofRandom(0,ofGetWindowWidth()), ofRandom(0, ofGetWindowHeight()));
//    p04.set(ofRandom(0,ofGetWindowWidth()), ofRandom(0, ofGetWindowHeight()));
    int R = 0;
    R = ofRandom(4);
    switch (R) {
        case 0:
            p03.set(-1, ofRandom(0, ofGetWindowHeight()));
            p04.set(ofGetWindowWidth(),ofRandom(0, ofGetWindowHeight()) );
            break;
        case 1:
            p04.set(-1, ofRandom(0, ofGetWindowHeight()));
            p03.set(ofGetWindowWidth(),ofRandom(0, ofGetWindowHeight()) );
            break;
        case 2:
            p03.set(ofRandom(0,ofGetWindowWidth()), -1);
            p04.set(ofRandom(0,ofGetWindowWidth()),ofGetWindowHeight() );
            break;
        case 3:
            p04.set(ofRandom(0,ofGetWindowWidth()), -1);
            p03.set(ofRandom(0,ofGetWindowWidth()),ofGetWindowHeight() );
            break;
            
        default:
            break;
    }
    
    
    Tweenzor::add(&p01.x,p03.x,p04.x,0.f,1.f,TWEEN_EASE_IN_OUT);
    Tweenzor::add(&p02.x,p03.x,p04.x,0.f,0.5f,TWEEN_EASE_IN_OUT);
    Tweenzor::add(&p01.y,p03.y,p04.y,0.f,1.f,TWEEN_EASE_IN_OUT);
    Tweenzor::add(&p02.y,p03.y,p04.y,0.f,0.5f,TWEEN_EASE_IN_OUT);
}



void Line::circleLine(){
    
    //step = 0;
    //ofNoFill();
    Tweenzor::add(&pst, 0.f, 1.f, 0.f, 1.2f,EASE_IN_OUT_CUBIC);
    Tweenzor::add(&rr, 0.f, 360.f, 0.f, 1.f,EASE_IN_OUT_CUBIC);
    Tweenzor::addCompleteListener( Tweenzor::getTween(&pst), this, &Line::circleLineEnd);
    
    //drawcircleline = false;
    
}


void Line::circleLineEnd(float* arg) {
    
    Tweenzor::add(&pst, 1.f, 0.f, .5f, 1.f,EASE_IN_OUT_CUBIC);
    Tweenzor::add(&rr, 360.f, 0.f, .7f, 0.7f,EASE_IN_OUT_CUBIC);
    drawcircleline = false;
    
    ofFill();
    
}





