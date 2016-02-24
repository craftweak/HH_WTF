
#include "polygon.h"


//--------------------------------------------------------------
void polygon::setup(int size){

    points.resize(size);
    points_temp.resize(size);
    
    for (int i=0; i<points.size(); i++) {
        ofVec3f p;
        p.x =   ofRandom(-300,300);
        p.y =   ofRandom(-300,300);
        p.z =   ofRandom(-300,300);
        points.push_back(p);
    }
    for (int i=0; i<points_temp.size(); i++) {
        ofVec3f p;
        p.x =   ofRandom(-300,300);
        p.y =   ofRandom(-300,300);
        p.z =   ofRandom(-300,300);
        points_temp.push_back(p);
    }

}

//--------------------------------------------------------------
void polygon::update(int size , float noise){
    points.resize(size);
    points_temp.resize(size);
    
    float time = ofGetElapsedTimef();
    
    for (int i=0; i< points.size(); i++) {
        //ofVec3f pp;
        points[i].x =   points[i].x *0.95+ points_temp[i].x *0.05 ;
        points[i].y =   points[i].y *0.95+ points_temp[i].y *0.05 ;
        points[i].z =   points[i].z *0.95+ points_temp[i].z *0.05 ;
        
        
        
        points[i] *= 1+ofSignedNoise(time)*noise;
        
        //        points[i].x = pp.x;
        //        points[i].y = pp.y;
        //        points[i].z = pp.z;
        
        //points.push_back(pp);
    }

    
    
}
//--------------------------------------------------------------
void polygon::random(float range){
    
    for (int i=0; i<points.size(); i++) {
        ofVec3f p;
        points_temp[i].x =   ofRandom(-range,range);
        points_temp[i].y =   ofRandom(-range,range);
        points_temp[i].z =   ofRandom(-range,range);
        //points_temp.push_back(p);
    }
    
}

//--------------------------------------------------------------
void polygon::draw(){
    
    
    
}

//--------------------------------------------------------------
void polygon::clear(){
    
    points.clear();
    points_temp.clear();
    
}