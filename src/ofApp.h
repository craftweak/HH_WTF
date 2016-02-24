#pragma once

#include "ofMain.h"
#include "ofxFFTLive.h"
#include "ofxUI.h"
#include "ofxOsc.h"
#include "ofxSyphon.h"
#include "ofxTweenzor.h"
#include "ofxCameraMove.h"
#include "ofxAlembic.h"
#include "ofxEasingCam.h"

#include "fft0.h"
#include "fftOctaveAnalyzer.h"

#include "Line.h"
#include "circle.h"
#include "fullLine.h"
#include "fullSoild.h"
#include "polygon.h"


// listen on port 12345
#define PORT 55666
#define NUM_MSG_STRINGS 20

#define BUFFER_SIZE 1024

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void audioIn(float * input, int bufferSize, int nChannels);
    
        void osc();
        void midi();
    
        void alembicSetup();
        void alembicUpdate();
        void alembicDraw();
    
//--Position
        bool posi00;
        bool posi01;
    
        int WW;
        int WH;
    
//--osc--
        ofxOscReceiver receiver;
        
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
    
        bool OSC_toggle;
    
        int note,velocity;
        bool MIDI_toggle;
    

    
//--UI--
        ofxUISuperCanvas *gui0;
        ofxUISuperCanvas *gui1;
        ofxUISuperCanvas *gui2;
        ofxUISuperCanvas *gui3;
        ofxUISuperCanvas *gui4;
        ofxUISuperCanvas *gui5;
        ofxUISuperCanvas *gui6;
        ofxUISuperCanvas *gui7;
        ofxUISuperCanvas *gui8;
        ofxUISuperCanvas *gui9;
        void guiEvent(ofxUIEventArgs &e);
    
        ofxUIMovingGraph *mg;
    
//--Syphon
    
        ofxSyphonServer mainOutputSyphonServer;
    
    
        float Reso;
        
        int Resolution;
    
        int ww,hh;
    
    
        
        bool guii;
        
        bool fftdraw;
    
//--SPHERE
    
        ofMesh meshOriginal;
        ofMesh meshWarped;
        bool sphereToggle;
        float sphereTogglef;
    
        ofVec4f sphereWireColor;
        ofVec4f sphereFaceColor;
    
        float sphereLineWidth;
        ofVec3f spherePos;
        float spherePosNoise;
        float spherePosSpeed;
    
//--Light
        ofLight light;
        float a,b,c,d,e;
        float lr,lg,lb,lw;
        float ar,ag,ab;
        int colorSwitch;
    
        bool lightToggle;
        bool colorMode;
    
        ofPoint lightPos;
        float lightPosZ;
    
        bool MENU;
    
        float RX,RY,RZ;
        float sphereRidus;
    
        int scene;
    
    
        Line Line;
    
        bool test01,test02;
    
//--TriSphere
    
        bool triSphere;
        float triSpheref;
    
        vector<ofPoint> vertices;
        vector<ofColor> colors;
        int nTri;		//The number of triangles
        int nVert;	//The number of the vertices equals nTri * 3
        
        float Rad;
        float rad;
        float ccc;
        ofPoint center;
        bool rrr;
        float rrrf;
    
    
    
        ofNode node;
    
//--FLAT Animation
    
        vector <ofVec3f> points;
        vector <ofVec3f> points2;
    
        bool lineline;
        float linelinef;
        bool lineRandom;
        float lineRandomf;
    
    
        circle circle;
    
    
    
        ofColor red;
    
    
        fullSoild full01;
        fullLine full02;
    
        bool full01_01,full01_02,full01_03,full01_04;
        bool full02_01,full02_02,full02_03,full02_04;
    
//--FullScreen
    
        float backAlpha;
        bool backAuto;
    
    
//--cam
    
        ofPoint camPos;
        float camZ;
        ofVec3f camRot;
    
        ofxCameraMove saveCam;
        ofEasyCam cam;
        bool camToggle;
        int A[4][4];
    
        bool CamPre[10];
        int CamNum;
        int CamFadeTime;
    
        bool GridToggle;
    
//--EasingCam
    
        ofxEasingCam Ecam;
    
        bool EcamToggle;
        float EcamSpeed;
        bool EcamRandom;
        bool EcamChange;
        float EcamScale;
        float EcamX,EcamY,EcamZ;
    
    
//--plane
    
        float freq;
        float noise;
        float fSpeed;
        float level;
        
        int FaceAlpha;
        int WireAlpha;
    
        float planeLineWidth;
    
        ofVec4f planeColor;
    
        ofPlanePrimitive plane;
        ofMesh planeMesh;
    
        ofNode planeNode;
    
        bool waveMeshToggle;
    
        ofVec3f planePos;
        ofVec3f planeRot;
    
    
//--XY_oscilloscope
    
        bool xy;
        ofPoint xyScale;
    
        float smoothedVolScale;
    
        ofVec3f xyPos;
        ofVec3f xyRot;
        ofVec2f xyCol;
    
//--WaveForm
    
        bool Waveform;
        float WaveformScale;
        bool lineFill;
        bool Spectrum;
        float waveWidth;
        float waveformWidth;
        float waveAlpha;
        ofPoint Lcol,Rcol;
        ofPoint LcolB,RcolB;
        ofPoint Lpos1,Lwh,Rpos1,Rwh;
    
    
//--Polygon line
    
        polygon polygon;
    
        bool polyToggle;
        float polyNoise;
        int polySize;
        float polyRange;
        float polyLineWidth;
        float polyPointSize;
        ofVec2f polyWireCol;
        ofVec2f polyFaceCol;
        ofVec2f polyPointCol;
        bool polyRandomToggle;
        ofVec3f polyPos;
        ofVec3f polyRot;
    
        bool RotateArena;
    
    
//--Sound Input
   //--fftLive
    
        ofxFFTLive fftLive;
        float audioThreshold;
        float audioPeakDecay;
        float audioMaxDecay;
        
        bool audioMirror;
        bool Depth;
    
        vector <float> left;
        vector <float> right;
        vector <float> volHistory;
        vector <float> vol;
    
        float *ll, *rr;
    
        float curVol;
        
        int 	bufferCounter;
        int 	drawCounter;
        
        float smoothedVol;
        float scaledVol;
        
        ofSoundStream soundStream;
        int bufferSize;
    
        FFTOctaveAnalyzer FFTanalyzerL;
        FFTOctaveAnalyzer FFTanalyzerR;
        float Lpeak[18],Rpeak[18];
        fft0		myfftL;
        fft0		myfftR;
        
        float magnitudeL[BUFFER_SIZE];
        float phaseL[BUFFER_SIZE];
        float powerL[BUFFER_SIZE];
        float freqL[BUFFER_SIZE/2];
        
        float magnitudeR[BUFFER_SIZE];
        float phaseR[BUFFER_SIZE];
        float powerR[BUFFER_SIZE];
        float freqR[BUFFER_SIZE/2];
        
        int HoldTime;
        float DecayRate;
    
    
        ofImage grid;
        bool gridT;
    
    //---abc
    
    
    ofxAlembic::Reader abc1;
    ofxAlembic::Reader abc2;
    ofxAlembic::Reader abc3;
    ofxAlembic::Reader abc4;
    ofxAlembic::Reader abc5;
    ofxAlembic::Reader abc6;
    ofxAlembic::Reader abc7;
    ofxAlembic::Reader abc8;
    
    ofMesh Amesh1;
    ofMesh Amesh2;
    ofMesh Amesh3;
    ofMesh Amesh4;
    ofMesh Amesh5;
    ofMesh Amesh6;
    ofMesh Amesh7;
    ofMesh Amesh8;
    
    float t1,t2,t3,t4,t5,t6,t7,t8;
    float s1,s2,s3,s4,s5,s6,s7,s8;
    float p1,p2,p3,p4,p5,p6,p7,p8;
    float r1,r2,r3,r4,r5,r6,r7,r8;
    float z1,z2,z3,z4,z5,z6,z7,z8;
    float w1,w2,w3,w4,w5,w6,w7,w8;
    int a1,a2,a3,a4,a5,a6,a7,a8;
    
    bool abc1D,abc2D,abc3D,abc4D,abc5D,abc6D,abc7D,abc8D;
};
