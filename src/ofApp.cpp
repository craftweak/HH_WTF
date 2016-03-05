#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    WW = 2560;
    WH = 720;
    
    receiver.setup(PORT);
    ofSetWindowPosition(-2540, 100);
    ofSetWindowShape(WW, WH);
    
//--background
    
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    
    
//--AudioIn
    
    bufferSize = 1024;
	
    ll = new float[bufferSize];
    rr = new float[bufferSize];
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
    vol.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    HoldTime  = 15;
    DecayRate = 0.95;
    
    
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
    for (int i = 0 ; i<18; i++) {
        Lpeak[i] = 0.0 ;
        Rpeak[i] = 0.0;
    }
    
//--FFT
    
    FFTanalyzerL.setup(44100, BUFFER_SIZE/2, 2);
	FFTanalyzerL.peakHoldTime = HoldTime; // hold longer
	FFTanalyzerL.peakDecayRate = DecayRate; // decay slower
	FFTanalyzerL.linearEQIntercept = 0.9f; // reduced gain at lowest frequency
	FFTanalyzerL.linearEQSlope = 0.1f; // increasing gain at higher frequencies
	
	FFTanalyzerR.setup(44100, BUFFER_SIZE/2, 2);
	FFTanalyzerR.peakHoldTime = HoldTime; // hold longer
	FFTanalyzerR.peakDecayRate = DecayRate; // decay slower
	FFTanalyzerR.linearEQIntercept = 0.9f; // reduced gain at lowest frequency
	FFTanalyzerR.linearEQSlope = 0.1f; // increasing gain at higher frequencies
    
//--fftLive
    
    fftLive.setMirrorData(false);
    //fftLive.setup();
    
//--Syphon
    
    ofSetWindowTitle("HH_Syn-Infection_HK");
    mainOutputSyphonServer.setName("");
    
//--Sphere
    
    meshOriginal = meshWarped = ofMesh::icosphere(300, Resolution);
    //meshOriginal = meshWarped = ofMesh::plane(300, 300, Resolution, Resolution);
    
//--MIDI
    
    note = 0;
    velocity = 0;
    MIDI_toggle = false;
    
    a = 0.0;
    b= 0.0;
    
    test01 = false;
    test02 = false;
    
    ofFill();
    
    guii = false;
    fftdraw = false;
    audioThreshold = 1.0;
    audioPeakDecay = 0.915;
    audioMaxDecay = 0.955;
    audioMirror = true;
    Depth = true;
    Resolution = 2;
    sphereToggle = true;
    sphereRidus =500;
    
    OSC_toggle = false ;
    
    //sphereRidus = 300;
    
    red.r = 255;
    red.g = 0;
    red.b =0;
    
    RX = 0;
    RY = 0;
    RZ = 0;
    
    ofSetColor(red);
    
    ofColor white (255, 255, 255);
    ofSetColor(white);
    
    lr = 1.0;
    lg = 1.0;
    lb = 1.0;
    lw = 1.0;
    ar = 1.0;
    ag = 1.0;
    ab = 1.0;
    c = 1.0;
    d = 1.0;
    e = 1.0;
    
    lightToggle= true;
    
    xyCol.set(255,255);
    
//--plane
    plane.set(2000, 2000, 15, 15);
    
    plane.setPosition(0,0,0);
    plane.rotate(-90,1,0,0);
//    plane.rotate(75,0,1,0);
    
//--polygon
    polySize = 0;
    polygon.setup(polySize);
    polyRandomToggle = true;
    
//--EasingCam
    EcamToggle = false;
    EcamRandom = false;
    EcamSpeed = 0.001;
    
    Ecam.setup();
    Ecam.setCamSpeed(EcamSpeed);
    
//--GUI
//HH_Jaguar
    
    //gui0->setColorFill(red);
    gui0 = new ofxUISuperCanvas("*", OFX_UI_FONT_SMALL);
    gui0->addLabel("HH_HH_Syn-Infection_HK", OFX_UI_FONT_LARGE)->setColorFill(ofColor(255,0,0,200));
    //gui0->setWidth(500.0);
    gui0->addSpacer();
    gui0->addFPS();
    //gui0->setColorFill(red);
    gui0->addLabelToggle("OSC", &OSC_toggle);
    gui0->addLabelToggle("MIDI", &MIDI_toggle);
    gui0->addIntSlider("note", 0, 127, &note);
    gui0->addIntSlider("velocity", 0, 127, &velocity);
    gui0->addToggle("GRID", &GridToggle);
    gui0->addToggle("POS00", &posi00, 20, 20);
    gui0->addToggle("POS01", &posi01, 20, 20);
    gui0->addTextArea("AUDIO","AUDIO",OFX_UI_FONT_LARGE);
    gui0->addSlider("audioThreshold", 0.0, 1.0, &audioThreshold);
    gui0->addSlider("audioPeakDecay", 0.0, 1.0, &audioPeakDecay);
    gui0->addSlider("audioMaxDecay", 0.0, 1.0, &audioMaxDecay);
    gui0->addToggle("audioMirror", &audioMirror);
    gui0->addIntSlider("HoldTime", 0, 20, &HoldTime);
    gui0->addSlider("DecayRate", 0.0, 1.0, &DecayRate);

    //gui0->addMovingGraph("Volume", volHistory, BUFFER_SIZE/2, 0.0 ,1.0);
   
    
//Light
    
    gui0->autoSizeToFitWidgets();
    ofAddListener(gui0->newGUIEvent,this,&ofApp::guiEvent);
    
    gui1 = new ofxUISuperCanvas("Light", OFX_UI_FONT_MEDIUM);
    gui1->addSpacer();
    gui1->setPosition(212, 0);
    gui1->addToggle("Light", &lightToggle);
    gui1->addIntSlider("COLOR", 0, 10, &colorSwitch);
    gui1->addToggle("ColorMode", &colorMode);
    gui1->addSpacer();
    gui1->addToggle("BackgroundAUTO", &backAuto);
    gui1->addMinimalSlider("BackAlpha", 0, 255, &backAlpha);
    gui1->add2DPad("LIGHT", ofPoint(-9000,9000), ofPoint(-9000, 9000), &lightPos,200,200);
    gui1->addSlider("LIGHT_Z", -9000.0, 9000.0, &lightPosZ);
    gui1->addSpacer();
    gui1->addToggle("MENU", &MENU);
    gui1->setWidgetPosition(OFX_UI_WIDGET_POSITION_UP);
    gui1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	gui1->addSlider("lr", 0.0, 1.5,&lr, 7, 64);
    
	gui1->addSlider("lg", 0.0, 1.5,&lg, 7, 64);
    gui1->addSlider("lb", 0.0, 1.5,&lb, 7, 64);
    gui1->addSlider("lw", 0.0, 1.5,&lw, 7, 64);
                                                    
    gui1->addSlider("ar", 0.0, 1.5,&ar, 7, 64);
    gui1->addSlider("ag", 0.0, 1.5,&ag, 7, 64);
    gui1->addSlider("ab", 0.0, 1.5,&ab, 7, 64);
    
    gui1->addSlider("c", 0.0, 1.5,&c, 7, 64);
    gui1->addSlider("d", 0.0, 1.5,&d, 7, 64);
    gui1->addSlider("e", 0.0, 1.5,&e, 7, 64);
    gui1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
                    
//    gui1->addMinimalSlider("lr", 0.0, 2.0, &lr);
//    gui1->addMinimalSlider("ar", 0.0, 2.0, &ar);
//    gui1->addMinimalSlider("c", 0.0, 2.0, &c);
//    gui1->addMinimalSlider("lr", 0.0, 2.0, &lr);
//    gui1->addMinimalSlider("lg", 0.0, 2.0, &lg);
//    gui1->addMinimalSlider("lb", 0.0, 2.0, &lb);
//    gui1->addMinimalSlider("lw", 0.0, 2.0, &lw);
//    gui1->addMinimalSlider("ar", 0.0, 2.0, &ar);
//    gui1->addMinimalSlider("ag", 0.0, 2.0, &ag);
//    gui1->addMinimalSlider("ab", 0.0, 2.0, &ab);
//    gui1->addMinimalSlider("c", 0.0, 2.0, &c);
//    gui1->addMinimalSlider("d", 0.0, 2.0, &d);
//    gui1->addMinimalSlider("e", 0.0, 2.0, &e);
    
    

    
    gui1->autoSizeToFitWidgets();
    ofAddListener(gui1->newGUIEvent,this,&ofApp::guiEvent);
    
//MENU03
    
    gui2 = new ofxUISuperCanvas("MISC", OFX_UI_FONT_MEDIUM);
    gui2->setPosition(424, 0);
    gui2->addSpacer();
    gui2->addToggle("line", &test01);
    gui2->addToggle("circle", &test02);
    gui2->addToggle("aaa", &Line.drawcircleline);
    gui2->addSpacer();
    gui2->addLabelToggle("triSphere", &triSphere);
    gui2->addIntSlider("nTri", 0, 500, &nTri);
    gui2->addMinimalSlider("Rad", 0.0, 1000.0, &Rad);
    gui2->addMinimalSlider("rad", 0.0, 500.0, &rad);
    gui2->addMinimalSlider("ccc", 0.0, 2.0, &ccc);
    gui2->addToggle("rrr", &rrr);
    
    gui2->addLabelToggle("lineline", &lineline);
    gui2->addToggle("lineRandom", &lineRandom);
    gui2->addSpacer();
    gui2->addLabelToggle("XY_oscilloscope", &xy);
    gui2->addSlider("X_Scale", 0, 4096, &xyScale.x);
    gui2->addSlider("Y_Scale", 0, 4096, &xyScale.y);
    gui2->addSlider("P_Scale", 0, 100, &smoothedVolScale);
    gui2->addSlider("Width", 1, 10, &waveformWidth);
    gui2->addSlider("xyRotZ", 0, 360, &xyRot.z);
    
    gui2->addLabelToggle("WAVEFORM", &Waveform);
    gui2->addToggle("Fill", &lineFill);
    gui2->addSlider("Scale", 0, ofGetWindowHeight()*2, &WaveformScale);
    gui2->addMinimalSlider("Width", 1, 5, &waveWidth);
    gui2->addLabelToggle("SPECTRUM", &Spectrum);
    
//    gui2->setGlobalButtonDimension(30);
//    gui2->addLabel("FLAT");
//    gui2->addToggleMatrix("A", 4, 4);
    
    gui2->autoSizeToFitWidgets();
    ofAddListener(gui2->newGUIEvent,this,&ofApp::guiEvent);
    
//CAMERA
    
    gui3 = new ofxUISuperCanvas("CAMERA", OFX_UI_FONT_MEDIUM);
    gui3->setPosition(636, 0);
    gui3->addSpacer();
    gui3->addLabelToggle("Mouse Control", &camToggle);
    //gui3->add2DPad("CAM", ofPoint(-5000,5000), ofPoint(-5000, 5000), &camPos,200,200);
    gui3->addToggle("Depth", &Depth);
    gui3->addSlider("CAM_X", -1000, 1000, &camPos.x);
    gui3->addSlider("CAM_Y", -1000, 1000, &camPos.y);
    gui3->addSlider("CAM_Z", -1000.0, 10000.0, &camZ);
    gui3->addSlider("ROT_X", -360, 360, &camRot.x);
    gui3->addSlider("ROT_Y", -360, 360, &camRot.y);
    gui3->addSlider("ROT_Z", -360, 360, &camRot.z);
    gui3->addSpacer();
    gui3->addIntSlider("CamPre", 0, 8, &CamNum);
    gui3->addSpacer();
    
    gui3->addIntSlider("FadeTime", 0, 30, &CamFadeTime);
    gui3->addSpacer();
    gui3->addToggle("CamPre00", &CamPre[0]);
    gui3->addToggle("CamPre01", &CamPre[1]);
    gui3->addToggle("CamPre02", &CamPre[2]);
    gui3->addToggle("CamPre03", &CamPre[3]);
    gui3->addToggle("CamPre04", &CamPre[4]);
    gui3->addToggle("CamPre05", &CamPre[5]);
    gui3->addToggle("CamPre06", &CamPre[6]);
    gui3->addToggle("CamPre07", &CamPre[7]);
    gui3->addToggle("CamPre08", &CamPre[8]);
    //gui3->addToggle("CamPre09", &CamPre[9]);
    
    gui3->autoSizeToFitWidgets();
    ofAddListener(gui3->newGUIEvent,this,&ofApp::guiEvent);

//SPHERE
    
    gui4 = new ofxUISuperCanvas("SPHERE", OFX_UI_FONT_MEDIUM);
    gui4->setPosition(848, 0);
    gui4->addSpacer();
    gui4->addLabelToggle("SPHERE", &sphereToggle);
    gui4->addIntSlider("Resolution", 0, 5.5, &Resolution);
    gui4->addMinimalSlider("SphereRidus", 0.0, 600, &sphereRidus);
    gui4->addSlider("Width", 0.001, 10, &sphereLineWidth);
    gui4->addSlider("FACE", 0, 255, &sphereFaceColor.w);
    gui4->addSlider("WIRE", 0, 255, &sphereWireColor.w);
    gui4->addSlider("PosNoise", 0, 2000, &spherePosNoise);
    gui4->addSlider("PosSpeed", 0, 2, &spherePosSpeed);
    gui4->addSlider("PosX", -1000, 1000, &spherePos.x);
    gui4->addSlider("PosY", -1000, 1000, &spherePos.y);
    gui4->addSlider("PosZ", -1000, 1000, &spherePos.z);
    
    gui4->autoSizeToFitWidgets();
    ofAddListener(gui4->newGUIEvent,this,&ofApp::guiEvent);

//WaveMesh
    
    gui5 = new ofxUISuperCanvas("WaveMesh", OFX_UI_FONT_MEDIUM);
    
    gui5->setPosition(1060, 0);
    gui5->addSpacer();
    gui5->addLabelToggle("WaveMesh", &waveMeshToggle);
    gui5->addSlider("cosfreq", 0, 200, &freq);
    gui5->addSlider("Noise", 0, 200, &noise);
    gui5->addSlider("fSpeed", 0, 3.5, &fSpeed);
    gui5->addSlider("level", 0, 10, &level);
    gui5->addSlider("Width", 0.001, 10, &planeLineWidth);
    gui5->addIntSlider("FACE", 0, 255, &FaceAlpha);
    gui5->addIntSlider("WIRE", 0, 255, &WireAlpha);
    gui5->addSpacer();
    gui5->addMinimalSlider("planeRotX", 0, 360, &planeRot.x);
    gui5->addMinimalSlider("planeRotY", 0, 360, &planeRot.y);
    gui5->addMinimalSlider("planeRotZ", 0, 360, &planeRot.z);
    gui5->addSpacer();
    gui5->addMinimalSlider("planePosX", -1000, 1000, &planePos.x);
    gui5->addMinimalSlider("planePosY", -1000, 1000, &planePos.y);
    gui5->addMinimalSlider("planePosZ", -1000, 1000, &planePos.z);
    
    gui5->autoSizeToFitWidgets();
    ofAddListener(gui5->newGUIEvent,this,&ofApp::guiEvent);

//AUDIO
    
    gui6 = new ofxUISuperCanvas("AudioAnalysis", OFX_UI_FONT_MEDIUM);
    gui6->setPosition(1272, 0);
    gui6->addSpacer();
    gui6->addTextArea("WAVEFORM","WAVEFORM", OFX_UI_FONT_SMALL);
    gui6->addWaveform("WAVEFORM_L", ll, bufferSize/2, 0.0, 1.0);
    gui6->addWaveform("WAVEFORM_R", rr, bufferSize/2, 0.0, 1.0);
    gui6->addTextArea("SPECTRUM","SPECTRUM", OFX_UI_FONT_SMALL);
    gui6->addSpacer();
    gui6->addWaveform("SPECTRUM_L", powerL, BUFFER_SIZE/2, 0.0, 50.0);
    gui6->addSpacer();
    gui6->addWaveform("SPECTRUM_R", powerR, BUFFER_SIZE/2, 0.0, 50.0);
    gui6->addLabel("FFT Analysis", OFX_UI_FONT_SMALL);
    gui6->addSpacer();
    gui6->addSlider("", 0.0, 255.0,&Lpeak[0], 5.5, 64);
    gui6->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui6->addSlider("", 0.0, 255.0,&Lpeak[1], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Lpeak[2], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Lpeak[3], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Lpeak[4], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Lpeak[5], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Lpeak[6], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Lpeak[7], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Lpeak[8], 5.5, 64);
    gui6->addSlider("", 0.0, 255.0,&Lpeak[9], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Lpeak[10], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Lpeak[11], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Lpeak[12], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Lpeak[13], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Lpeak[14], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Lpeak[15], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Lpeak[16], 5.5, 64);
    gui6->addSlider("", 0.0, 255.0,&Lpeak[17], 5.5, 64);
	gui6->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    gui6->addSlider("", 0.0, 255.0,&Rpeak[0], 5.5, 64);
    gui6->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui6->addSlider("", 0.0, 255.0,&Rpeak[1], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Rpeak[2], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Rpeak[3], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Rpeak[4], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Rpeak[5], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Rpeak[6], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Rpeak[7], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Rpeak[8], 5.5, 64);
    gui6->addSlider("", 0.0, 255.0,&Rpeak[9], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Rpeak[10], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Rpeak[11], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Rpeak[12], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Rpeak[13], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Rpeak[14], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Rpeak[15], 5.5, 64);
	gui6->addSlider("", 0.0, 255.0,&Rpeak[16], 5.5, 64);
    gui6->addSlider("", 0.0, 255.0,&Rpeak[17], 5.5, 64);
	
    gui6->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    gui6->autoSizeToFitWidgets();
    ofAddListener(gui6->newGUIEvent,this,&ofApp::guiEvent);
    
//POLYGON
    
    gui7 = new ofxUISuperCanvas("POLYGON", OFX_UI_FONT_MEDIUM);
    gui7->addSpacer();
    gui7->addLabelToggle("POLYGON_PLF", &polyToggle);
    gui7->addSlider("NOISE", 0.0, 0.1, &polyNoise);
    gui7->addIntSlider("size", 0, 500, &polySize);
    gui7->addSlider("range", 0, 5000, &polyRange);
    gui7->addMinimalSlider("Width", 0.01, 10, &polyLineWidth);
    gui7->addMinimalSlider("Psize", 0, 10, &polyPointSize);
    gui7->addSpacer();
    gui7->addToggle("RANDOM", &polyRandomToggle);
    gui7->addMinimalSlider("Face", 0, 255, &polyFaceCol.x);
    gui7->addMinimalSlider("Wire", 0, 255, &polyWireCol.x);
    gui7->addMinimalSlider("Point", 0, 255, &polyPointCol.x);
    gui7->addSpacer();
    gui7->addMinimalSlider("polyRotX", 0, 360, &polyRot.x);
    gui7->addMinimalSlider("polyRotY", 0, 360, &polyRot.y);
    gui7->addMinimalSlider("polyRotZ", 0, 360, &polyRot.z);
    gui7->addSpacer();
    gui7->addMinimalSlider("polyPosX", -1000, 1000, &polyPos.x);
    gui7->addMinimalSlider("polyPosY", -1000, 1000, &polyPos.y);
    gui7->addMinimalSlider("polyPosZ", -1000, 1000, &polyPos.z);
    gui7->addToggle("Rotate", &RotateArena);
    
    gui7->autoSizeToFitWidgets();
    ofAddListener(gui7->newGUIEvent,this,&ofApp::guiEvent);
    
    polySize = 5;
    polygon.random(ofRandom(polyRange-100,polyRange));
    polyRandomToggle = true;
    
//8
    
    gui8 = new ofxUISuperCanvas("Rotation", OFX_UI_FONT_MEDIUM);
    gui8->addSpacer();
    gui8->addSlider("RX", 0.0, 360.0, &RX);
    gui8->addSlider("RY", 0.0, 360.0, &RY);
    gui8->addSlider("RZ", 0.0, 360.0, &RZ);
    
    gui8->autoSizeToFitWidgets();
    ofAddListener(gui8->newGUIEvent,this,&ofApp::guiEvent);
    
//9
    
    gui9 = new ofxUISuperCanvas("Background", OFX_UI_FONT_MEDIUM);
    gui9->addSpacer();
    //gui9->addSlider("Lcol.x", <#float _min#>, <#float _max#>, <#float *_value#>)
    gui9->add2DPad("LcolB", ofPoint(0,255), ofPoint(0, 255), &LcolB,50,50);
    gui9->add2DPad("RcolB", ofPoint(0,255), ofPoint(0, 255), &RcolB,50,50);
    gui9->add2DPad("Lpos", ofPoint(0,ofGetWindowWidth()), ofPoint(0, ofGetWindowHeight()), &Lpos1,50,50);
    gui9->add2DPad("Lwh", ofPoint(0,ofGetWindowWidth()), ofPoint(0, ofGetWindowHeight()), &Lwh,50,50);
    gui9->add2DPad("Rpos", ofPoint(0,ofGetWindowWidth()), ofPoint(0, ofGetWindowHeight()), &Rpos1,50,50);
    gui9->add2DPad("Rwh", ofPoint(0,ofGetWindowWidth()), ofPoint(0, ofGetWindowHeight()), &Rwh,50,50);
    
    gui9->autoSizeToFitWidgets();
    ofAddListener(gui9->newGUIEvent,this,&ofApp::guiEvent);

    
//--Light
    
    light.enable();
    //light.setPointLight();
    //light.setDirectional();
    ofSetSmoothLighting(false);
    light.setPosition(0, 0, -500);
    light.setAmbientColor(ofFloatColor(lr,lg,lb,lw));
    light.setDiffuseColor(ofFloatColor(ar,ag,ab));
    light.setSpecularColor(ofFloatColor(c,d,e));
    
//--CAMERA
    
    cam.disableMouseInput();
    
    //cam.lookAt(node);
    
    node.setPosition(0, 0, 0);
    
    cam.setFarClip(30000);
    cam.setFov(30);
    
    Tweenzor::init();
    
//--FALT
    
    circle.setup();
    full01.setup();
    full02.setup(33);
    
//--Waveform
    
    Lcol.set(255,255);
    Rcol.set(255,255);
    LcolB.set(0,255);
    RcolB.set(0,255);
    
//--TriSphere
    
    nTri = 500;			//The number of the triangles
	nVert= nTri * 3;		//The number of the vertices
    
	Rad = 250;	//The sphere's radius
	rad = 25;	//Maximal triangle's ìradiusî
	//(formally, it's the maximal coordinates'
	//deviation from the triangle's center)
    
	//Fill the vertices array
	vertices.resize( nVert );		//Set the array size
	for (int i=0; i<nTri; i++) {	//Scan all the triangles
		//Generate the center of the triangle
		//as a random point on the sphere
        
		//Take the random point from
		//cube [-1,1]x[-1,1]x[-1,1]
		 center.set( ofRandom( -1, 1 ),
                       ofRandom( -1, 1 ),
                       ofRandom( -1, 1 ) );
		center.normalize(); //Normalize vector's length to 1
		center *= Rad;	//Now the center vector has
		//length Rad
        
		//Generate the triangle's vertices
		//as the center plus random point from
		//[-rad, rad]x[-rad, rad]x[-rad, rad]
		for (int j=0; j<3; j++) {
			vertices[ i*3 + j ] =
            center + ofPoint( ofRandom( -rad, rad ),
                             ofRandom( -rad, rad ),
                             ofRandom( -rad, rad ) );
		}
	}
    
	//Fill the array of triangles' colors
	colors.resize( nTri );
	for (int i=0; i<nTri; i++) {
		//Take a random color from black to red
		colors[i] = ofColor( ofRandom( 0, 255 ) );
	}
    
    
    
    
//--Random_Line_Point
    
    for (int i=0; i<30; i++) {
        ofVec3f p;
        p.x =   ofRandom(-ofGetWindowWidth(),ofGetWindowWidth());
        p.y =   ofRandom(-ofGetWindowWidth(),ofGetWindowWidth());
        p.z =   ofRandom(-300,300);
        points.push_back(p);
    }
    
    
    for (int i=0; i<5; i++) {
        ofVec3f p;
        p.x =   ofRandom(-ofGetWindowWidth()*2,ofGetWindowWidth()*2);
        p.y =   ofRandom(-ofGetWindowWidth()*2,ofGetWindowWidth()*2);
        p.z =   ofRandom(-300,300);
        points2.push_back(p);
    }
    
    
    
    gui0->loadSettings("gui0Settings.xml");
    gui1->loadSettings("gui1Settings.xml");
    gui2->loadSettings("gui2Settings.xml");
    gui3->loadSettings("gui3Settings.xml");
    gui4->loadSettings("gui4Settings.xml");
    gui5->loadSettings("gui5Settings.xml");
    gui6->loadSettings("gui6Settings.xml");
    gui7->loadSettings("gui7Settings.xml");
    gui8->loadSettings("gui8Settings.xml");
    gui9->loadSettings("gui9Settings.xml");
    
    
    saveCam.cutNow(2);
    
    saveCam.setup(&cam,"xml");
    
    //saveCam.tweenNow(0, 0);
    
    grid.loadImage("1024_300.jpg");
    gridT = false;
    
    alembicSetup();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetBackgroundAuto(backAuto);
//-- EasingCam--
    Ecam.update();
    Ecam.setCamSpeed(EcamSpeed);
    
    if (EcamChange) {
        
        Ecam.setScale(EcamScale);
        Ecam.setPos(EcamX, EcamY, EcamZ);
        EcamChange = false;
    }
    
    
    if (EcamRandom) {
        Ecam.setRandomPos();
        Ecam.setRandomScale(0.1, 2);
        EcamRandom = false;
    }
    
    
    

    
//--OSCtoggle--
//    
//    if (OSC_toggle) {
//        if (sphereTogglef>=1) {
//            sphereToggle = true;
//        }else{
//            sphereToggle = false;
//        }
//    }
//    
//    if(OSC_toggle){
//        if (triSpheref>=1) {
//            triSphere = true;
//        }else{
//            triSphere = false;
//        }
//    }
    

    
    
    
//--fft
    
    FFTanalyzerL.peakHoldTime = HoldTime; // hold longer
	FFTanalyzerL.peakDecayRate = DecayRate; // decay slower
    FFTanalyzerR.peakHoldTime = HoldTime; // hold longer
	FFTanalyzerR.peakDecayRate = DecayRate; // decay slower
    
    static int index=0;
	float avg_powerL = 0.0f;
	float avg_powerR = 0.0f;
    
    /* do the FFT	*/
	myfftL.powerSpectrum0(0,(int)BUFFER_SIZE/2, ll,BUFFER_SIZE,&magnitudeL[0],&phaseL[0],&powerL[0],&avg_powerL);
	myfftR.powerSpectrum0(0,(int)BUFFER_SIZE/2, rr,BUFFER_SIZE,&magnitudeR[0],&phaseR[0],&powerR[0],&avg_powerR);
	
    for (int i = 0; i < (int)(BUFFER_SIZE/2); i++){
		freqL[i] = magnitudeL[i];
		freqR[i] = magnitudeR[i];
	}
	
	FFTanalyzerL.calculate(freqL);
	FFTanalyzerR.calculate(freqR);
    for (int i = 0 ; i<18; i++) {
        Lpeak[i] = 0.0 ;
        Rpeak[i] = 0.0;
    }
	
    for (int i = 0; i < FFTanalyzerL.nAverages; i++){
		Lpeak[i] = FFTanalyzerL.peaks[i];
    }
    for (int i = 0; i < FFTanalyzerR.nAverages; i++){
		Rpeak[i]= FFTanalyzerR.peaks[i];
    }
    
    meshOriginal = meshWarped = ofMesh::icosphere(sphereRidus, Resolution);
    //meshOriginal = meshWarped = ofMesh::plane(300, 300, Resolution, Resolution);
    
//--fftLive
    
    fftLive.setThreshold(audioThreshold);
    fftLive.setPeakDecay(audioPeakDecay);
    fftLive.setMaxDecay(audioMaxDecay);
    fftLive.setMirrorData(audioMirror);
    
    fftLive.audioIn(ll, bufferSize, 2);
    fftLive.update();
    
    
    //lets scale the vol up to a 0-1 range
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
	
    //lets record the volume into an array
	volHistory.push_back( scaledVol );
	//mg->addPoint(volHistory);
    
    
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
    
//--Sphere
    
    //---------------------------------------------------------- dispacing mesh using audio.
    vector<ofVec3f> & vertsOriginal = meshOriginal.getVertices();
    vector<ofVec3f> & vertsWarped = meshWarped.getVertices();
    int numOfVerts = meshOriginal.getNumVertices();
    
    float * audioData = new float[numOfVerts];
    fftLive.getFftPeakData(audioData, numOfVerts);
    
    //cout << numOfVerts <<endl;
    
    float meshDisplacement = 500;
    
    for(int i=0; i<numOfVerts; i++) {
        float audioValue = audioData[i];
        ofVec3f & vertOriginal = vertsOriginal[i];
        ofVec3f & vertWarped = vertsWarped[i];
        
        ofVec3f direction = vertOriginal.getNormalized();
        vertWarped = vertOriginal + direction * meshDisplacement * audioValue;
        
        
    }
    
    delete[] audioData;
    
    ofSetDepthTest(Depth);
    
    //Resolution = Reso;
    
    //cam.setDistance(1000);
    
//--Light
    
    light.setPosition(lightPos.x, lightPos.y*-1, lightPosZ);
    
    if (colorMode) {
        light.setAmbientColor(ofFloatColor(lr,lg,lb,lw));
        light.setDiffuseColor(ofFloatColor(ar,ag,ab));
        light.setSpecularColor(ofFloatColor(c,d,e));
    }else{
//        lg = lg * 0.95 + lr *0.05;
//        lb = lb * 0.95 + lr *0.05;
//        lw = lw * 0.95 + lr *0.05;
//        
//        ag = ag * 0.95 + ar *0.05;
//        ab = ab * 0.95 + ar *0.05;
//        
//        d = d * 0.95 + c *0.05;
//        e = e * 0.95 + c *0.05;
        
        light.setAmbientColor(ofFloatColor(lr,lr,lr,lr));
        light.setDiffuseColor(ofFloatColor(ar,ar,ar));
        light.setSpecularColor(ofFloatColor(c,c,c));
    }
    
    if (lightToggle) {
        light.enable();
    }else{
        light.disable();
    }
    
//--FLAT Animation
    
    Line.update();
    
    Tweenzor::update( ofGetElapsedTimeMillis() );
    
//--POLYGON
    
    polygon.update(polySize, polyNoise);
    
    if (polyRandomToggle) {
        polygon.random(ofRandom(polyRange-100,polyRange));
        polyRandomToggle = false;
    }
    
    
//--Cam PreSet--
    
    if (camToggle) {
        cam.enableMouseInput();
        camPos.x = cam.getPosition().x;
        camPos.y = cam.getPosition().y;
        camZ = cam.getPosition().z;
        camRot.x = cam.getOrientationEuler().x;
        camRot.y = cam.getOrientationEuler().y;
        camRot.z = cam.getOrientationEuler().z;
        
        
    }else{
        cam.disableMouseInput();
        cam.setPosition(camPos.x, camPos.y, camZ);
        cam.setOrientation(camRot);
    }
    
   saveCam.update();
    
    for (int j = 0; j<9; j++) {
        if (CamPre[j] == true) {
            if (CamFadeTime == 0) {
                saveCam.cutNow(j);
            }
            saveCam.tweenNow(j, CamFadeTime);
            CamNum = j ;
            for (int i =0; i<9; i++) {
                CamPre[i] = false ;
            }
            
            //CamPre[j] = true;
        }
    }
    
    
    
//--TriSphere--
    
    if (rrr) {
        for (int i=0; i<nTri; i++) {	//Scan all the triangles
            //Generate the center of the triangle
            //as a random point on the sphere
            
            //Take the random point from
            //cube [-1,1]x[-1,1]x[-1,1]
            
                ofPoint center( ofRandom( -1, 1 ),
                               ofRandom( -1, 1 ),
                               ofRandom( -1, 1 ) );
            
            
            
            //
            center.normalize(); //Normalize vector's length to 1
            center *= Rad;	//Now the center vector has
            //length Rad
            
            //Generate the triangle's vertices
            //as the center plus random point from
            //[-rad, rad]x[-rad, rad]x[-rad, rad]
            for (int j=0; j<3; j++) {
                vertices[ i*3 + j ] =
                center + ofPoint( ofRandom( -rad, rad ),
                                 ofRandom( -rad, rad ),
                                 ofRandom( -rad, rad ) );
            }
        }
    
        rrr= false;
    
    }

//--Random_Line_Point--
    
    if (lineRandom) {
        points.clear();
        points2.clear();
        for (int i=0; i<30; i++) {
            ofVec3f p;
            p.x =   ofRandom(-ofGetWindowWidth(),ofGetWindowWidth());
            p.y =   ofRandom(-ofGetWindowWidth(),ofGetWindowWidth());
            p.z =   ofRandom(-300,300);
            points.push_back(p);
        }
        
        
        for (int i=0; i<5; i++) {
            ofVec3f p;
            p.x =   ofRandom(-ofGetWindowWidth()*2,ofGetWindowWidth()*2);
            p.y =   ofRandom(-ofGetWindowWidth()*2,ofGetWindowWidth()*2);
            p.z =   ofRandom(-300,300);
            points2.push_back(p);
        }
        
        lineRandom = false;
    }
    
    
    circle.update();
    
    
    if (MENU) {
        gui0->setVisible(true);
        gui1->setVisible(true);
        gui2->setVisible(true);
        gui3->setVisible(true);
        gui4->setVisible(true);
        gui5->setVisible(true);
        gui6->setVisible(true);
        gui7->setVisible(true);
        gui8->setVisible(true);
        gui9->setVisible(true);
    }else{
        gui0->setVisible(false);
        gui1->setVisible(false);
        gui2->setVisible(false);
        gui3->setVisible(false);
        gui4->setVisible(false);
        gui5->setVisible(false);
        gui6->setVisible(false);
        gui7->setVisible(false);
        gui8->setVisible(false);
        gui9->setVisible(false);
    }

    
    osc();
    midi();
    alembicUpdate();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
//    ofBackground(0, 0, 0);
    
    ofSetColor(0,0,0, backAlpha);
    ofRect(0,0, ofGetWindowWidth(), ofGetWindowHeight());
    ofSetColor(255);
    
    int w = OFX_FFT_WIDTH;
    int h = OFX_FFT_HEIGHT;
    int x = 20;
    int y = ofGetHeight() - h - 20;
    if (fftdraw) {
        fftLive.draw(x, y, w, h);
    }
    
   
    
    //--WaveForm
    
    if (Waveform) {

        
    //L
        
        ofPushStyle();
         ofSetColor(255-RcolB.x,255-RcolB.x,255-RcolB.x,waveAlpha);
        
        
        if (lineFill) {
            ofFill();
            //Depth = false;
        }else{
            ofNoFill();
            
            //Depth = true;
        }
        ofSetLineWidth(waveWidth);
        ofBeginShape();
       
        for ( int i = 0 ; i<bufferSize/2; i++) {
            
            float hh = ofMap(rr[i], 0, 1, 0, WaveformScale)+ofGetWindowHeight()/2;
            ofVertex(ofGetWindowWidth()/2+i*((ofGetWindowWidth()/2)/(bufferSize/2)*1.8) , hh);
            
        }
        ofVertex(ofGetWindowWidth()+1, ofGetWindowHeight()/2);
        ofVertex(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
        ofEndShape();
        ofPopStyle();
    }
    
    //R
    
    if (Waveform) {
        ofPushMatrix();
        //ofTranslate(-ofGetWindowWidth()/2, 0);
        ofPushStyle();
        
        ofSetColor(255-LcolB.x,255-LcolB.x,255-LcolB.x,waveAlpha);
        
        if (lineFill) {
            ofFill();
        }else{
            
            ofNoFill();
        }
        ofSetLineWidth(waveWidth);
        ofBeginShape();
        
        for ( int j = 0 ; j<bufferSize/2; j++) {
            float hh2 = ofMap(ll[j], 0, 1, 0, WaveformScale)+ofGetWindowHeight()/2;
            ofVertex(ofGetWindowWidth()/2-j*((ofGetWindowWidth()/2)/(bufferSize/2))*1.8, hh2);
            
        }
        ofVertex(0, ofGetWindowHeight()/2);
        ofVertex(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
        
        ofEndShape();
        ofPopStyle();
        ofPopMatrix();
    }
    
    
    

    
    
    if(EcamToggle){
        Ecam.begin();
    }
    else
    {
        cam.begin();
    }
    
    ofPushStyle();
    ofFill();
    alembicDraw();
    ofPopStyle();
    
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255, 255, 255,255);
    
    if (GridToggle) {
        ofDrawGridPlane(10000);
        ofRotate(90, 0, 0, -1);
        ofDrawGridPlane(10000);
        
        ofRotate(90, 0, 1, 0);
        ofDrawGridPlane(10000);
    }
    

    
    ofPopStyle();
    ofPopMatrix();
 
    
//--sphere
    
    if (sphereToggle) {
    ofPushMatrix();
    ofPushStyle();
    //ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
    ofTranslate(spherePos.x, spherePos.y, spherePos.z);
    ofRotateX(RX);
    ofRotateY(RY);
    ofRotateZ(RZ);
    float time = ofGetElapsedTimef()*(spherePosSpeed);
    
        
    ofTranslate(ofSignedNoise(time, 0, 0)*spherePosNoise,
                ofSignedNoise(0, time, 0)*spherePosNoise,
                ofSignedNoise( 0, 0,time)*spherePosNoise);

        
    //ofSetColor(sphereFaceColor.x,sphereFaceColor.y,sphereFaceColor.z,sphereFaceColor.w);
        ofSetColor(sphereFaceColor.w,sphereFaceColor.w);
    meshWarped.drawFaces();
    //ofSetColor(sphereWireColor.x,sphereWireColor.y,sphereWireColor.z,sphereWireColor.w);
        ofSetColor(sphereWireColor.w,sphereWireColor.w);
    ofSetLineWidth(sphereLineWidth);
        
        //ofSetLineWidth(0.1);
    meshWarped.drawWireframe();
    ofPopStyle();
    ofPopMatrix();
    }
    
//--triSphere
    
    if (triSphere) {
        ofPushMatrix();						//Store the coordinate system
        ofPushStyle();
        ofFill();
        //Move the coordinate center to screen's center
        ofTranslate( 0, 0,0 );
//        ofRotateX(RX);
//        ofRotateY(RY);
//        ofRotateZ(RZ);
        //Calculate the rotation angle
        float time = ofGetElapsedTimef();	//Get time in seconds
        float angle = time * 2 *ccc;			//Compute angle. We rotate at speed 10 degrees per second
        ofRotate( angle, 0, 1, 0 );			//Rotate the coordinate system along y-axe
        
        //Draw the triangles
        for (int i=0; i<nTri; i++) {
            ofSetColor( colors[i] );
            ofRotate( time*0.1*ccc, 0, 1, 0 );//Set color
            ofTriangle( vertices[ i*3 ],
                       vertices[ i*3 + 1 ],
                       vertices[ i*3 + 2 ] );		//Draw triangle
        }
        ofPopStyle();
        ofPopMatrix();	//Restore the coordinate system
    }
    
//--Random_Line_Point
    
        if(lineline){
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(0, 0,0);
        //ofRotateY(ofGetElapsedTimef()*3);
            ofRotateX(RX);
            ofRotateY(RY);
            ofRotateZ(RZ);
        ofSetLineWidth(1);
        for (int i = 0; i < points.size(); i++){
            ofLine(points[i-1], points[i]);
        }
        
        
        ofSetLineWidth(2);
        for (int i = 0; i < points2.size(); i++){
            //ofLine(points2[i-1], points2[i]);
            ofSphere(points2[i],5);
        }
        ofPushStyle();
        ofPopMatrix();
        
        }
    
//--WaveMesh
    
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);
    
    if (waveMeshToggle) {
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(planePos.x,planePos.y,planePos.z);
        ofRotateX(planeRot.x);
        ofRotateY(planeRot.y);
        ofRotateZ(planeRot.z);
        
        
        
        //plane.drawFaces();
        
        //plane.setPosition(ofGetWidth()*.2, ofGetHeight()*.25, 0);
        //    plane.rotate(spinX, 1.0, 0.0, 0.0);
        //    plane.rotate(spinY, 0, 1.0, 0.0);
        
        planeMesh = plane.getMesh();
        
        int numOfVerts = planeMesh.getNumIndices();
        
        ofVec3f planeDims = plane.getResolution();
        float planeAngleY = ofGetElapsedTimef()*fSpeed;
        float planeAngleInc = 3.f/(float)planeDims.y;
        
        float * audioData = new float [numOfVerts];
        fftLive.getFftPeakData(audioData, numOfVerts);
        
        
        ofVec3f vert;
        for(int i = 0; i < planeMesh.getNumIndices(); i++ ) {
            float audioValue = audioData[i];
            
            //planeAngleY = ofGetElapsedTimef()*1;
            //cout<<audioValue<<endl;
            planeAngleY += planeAngleInc;
            int ii = planeMesh.getIndex( i );
            vert = planeMesh.getVertex( ii );
            vert.z += freq*cos(planeAngleY);
            //cout<<vert.z<<endl;
            vert.z += noise*ofSignedNoise(planeAngleY);
            vert.z *= (audioValue*level+1);
            planeMesh.setVertex( ii, vert );
        }
        
        ofFill();
        ofSetColor(WireAlpha,WireAlpha);
        
        plane.transformGL();
        ofSetLineWidth(planeLineWidth);
        planeMesh.drawWireframe();
        ofSetColor(FaceAlpha,FaceAlpha);
        planeMesh.drawFaces();
        plane.restoreTransformGL();
        
        ofPopStyle();
        ofPopMatrix();
        
    }
    
//--XY
    
    if (xy) {
        
    
    
    ofPushMatrix();
    //ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight()/2, 0);
    ofPushStyle();
    ofTranslate(0, 0, 0);
    //ofRotate(180, 0, 0, 1);
    //ofRotate(-45, 0, 0, 1);
    
        ofRotateZ(xyRot.z);
    
    
    ofSetLineWidth(waveformWidth);
    ofSetColor(xyCol.x, xyCol.x , xyCol.x ,xyCol.y);
    ofBeginShape();
    for (unsigned int i = 0; i < left.size(); i++){
        //ofVertex(left[i]*512.0f, right[i]*384.0f);
        
        ofFill();
        ofCircle(left[i]*xyScale.x, right[i]*xyScale.y,smoothedVol*smoothedVolScale);
        ofNoFill();
        ofVertex(left[i]*xyScale.x, right[i]*xyScale.y);
        //                ofVec3f p01;
        //                p01.set(left[i]*2048.f, right[i]*2048.f,0);
        //                ofVec3f p02;
        //                p01.set(left[i-1]*2048.f, right[i-1]*2048.f,0);
        //                ofLine(p01, p02);
    }
    ofEndShape(close);
    ofPopStyle();
    ofPopMatrix();
	
    }

//--polygon
    
    if (polyToggle) {
        
        ofPushMatrix();
        ofPushStyle();
        //ofTranslate(0, 0, 0);
        ofTranslate(polyPos.x,polyPos.y,polyPos.z);
        if (RotateArena) {
            ofRotateX(RX);
            ofRotateY(RY);
            ofRotateZ(RZ);
        }
        
        ofRotateX(polyRot.x);
        ofRotateY(polyRot.y);
        ofRotateZ(polyRot.z);
        
        ofSetSphereResolution(3);
        
        
        //glBegin(GL_POINTS);
        ofSetLineWidth(polyLineWidth);
        for (int i = 0; i < polySize; i++){
            ofPushMatrix();
            ofPushStyle();
//            ofTranslate(polyPos.x,polyPos.y,polyPos.z);
            ofRotateX(-polyRot.x);
            ofRotateY(-polyRot.y);
            ofRotateZ(-polyRot.z);
            ofFill();
            ofSetColor(polyPointCol.x,polyPointCol.x,polyPointCol.x, polyPointCol.y);
            ofSphere(polygon.points[i],polyPointSize);
            ofPopStyle();
            ofPopMatrix();
            ofPushStyle();
            ofSetColor(polyWireCol.x, polyWireCol.x);
            ofLine(polygon.points[i-1], polygon.points[i]);
            ofPopStyle();
            
        }
        for (int i = 0; i < polySize; i++){
            if(ofRandom(2)>1){
            ofPushStyle();
            ofFill();
            ofSetColor(polyFaceCol.x,  polyFaceCol.x);
                if (polygon.points[i].squareDistance(polygon.points[i+1])<300000) {
                    ofTriangle(polygon.points[i],polygon.points[i-1],polygon.points[i+1]);
                }
            
            ofPopStyle();
            }
        }
        
        
        ofPopStyle();
        ofPopMatrix();
        


    }
    
    
    if(abc3D){
        ofPushMatrix();
        ofScale(1.8, 1.8, 1.8 );
        ofPushStyle();
        ofSetColor(200, 200, 200, a3 );
        
        if(w3){
            ofFill();
        }else{
            ofNoFill();
        }
        abc3.draw();
        ofPopStyle();
        ofPopMatrix();
    }
    
    if(abc5D){
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(-50, 200,0);
        ofSetColor(255, 0, 0, a5 );
        ofFill();
        abc5.draw();
        ofPopStyle();
        ofPopMatrix();
    }
    
    if(EcamToggle){
        Ecam.end();
    }
    else
    {
        cam.end();
    }
    
    //--Background
    ofPushMatrix();
    //ofTranslate(0, 0,-3000);
    ofPushStyle();
    ofFill();
    ofSetColor(LcolB.x,LcolB.x,LcolB.x, LcolB.y);
    ofRect(Lpos1.x, Lpos1.y, Lwh.x, Lwh.y);
    ofSetColor(RcolB.x,RcolB.x,RcolB.x, RcolB.y);
    ofRect(Rpos1.x, Rpos1.y, Rwh.x, Rwh.y);
    
    
    ofPopStyle();
    ofPopMatrix();
    ofTranslate(0, 0,1);
    Line.draw();
    circle.draw();
    
    ofPushStyle();
    ofSetColor(255, 100);
    ofFill();
    full01.draw();
    full02.draw(33);
    ofPopStyle();
    
    
    if (gridT) {
        ofSetColor(255, 255,255,255);
        grid.draw(0, 0);
    }

    mainOutputSyphonServer.publishScreen();
    
    ofPushStyle();
    ofSetColor(255, 255);
    ofDrawBitmapString(ofToString(ofGetFrameRate(),2), 2540, 700);
    ofPopStyle();
}
//--------------------------------------------------------------
void ofApp::alembicSetup(){
    string path1 ="abc/Untitled 4.abc";
    abc1.open(path1);
    
    string path2 ="abc/Untitled 2.abc";
    abc2.open(path2);
    
    string path3 ="abc/sphere01.abc";
    abc3.open(path3);
    
    string path4 ="abc/ex2.abc";
    abc4.open(path4);
    
    string path5 ="abc/HH.abc";
    abc5.open(path5);
    
    string path6 ="abc/line00.abc";
    abc6.open(path6);
    
    string path7 ="abc/lineIn01.abc";
    abc7.open(path7);

//    string path8 ="abc/HH.abc";
//    abc8.open(path8);
}
//--------------------------------------------------------------
void ofApp::alembicUpdate(){
    if (p1) {
        
        if (s1 == false) {
            t1 += 0.02;
        }else{
            t1 -= 0.02;
        }
        
        
        if(t1 < abc1.getMaxTime()){
            abc1.setTime(t1);
        }else{
            t1 = 0;
            abc1D =false;
            
        }
    }
    
    
    
    if (p2) {
        
        if (s2== false) {
            t2 += 0.02;
        }else{
            t2 -= 0.02;
        }
        
        
        
        if(t2 < abc2.getMaxTime()){
            abc2.setTime(t2);
        }else{
            t2 = 0;
            abc2D =false;
            
        }
    }
    if (p3) {
        if (s3== false) {
            t3 += 0.02;
        }else{
            t3 -= 0.02;
        }
        
        if(t3 < abc3.getMaxTime()){
            abc3.setTime(t3);
        }else{
            t3 = 0;
            abc3D =false;
            
        }
    }
    
    if (p4) {
        if (s4== false) {
            t4 += 0.02;
        }else{
            t4 -= 0.02;
        }
        
        if(t4 < abc4.getMaxTime()){
            abc4.setTime(t4);
        }else{
            t4 = 0;
            abc4D =false;
            
        }
    }
    
    if (p5) {
        if (s5== false) {
            t5 += 0.02;
        }else{
            t5 -= 0.02;
        }
        
        if(t5 < abc5.getMaxTime()){
            abc5.setTime(t5);
        }else{
            t5 = 0;
            abc5D =false;
            
        }
    }
    
    if (p6) {
        if (s6== false) {
            t6 += 0.02;
        }else{
            t6 -= 0.02;
        }
        
        if(t6 < abc6.getMaxTime()){
            abc6.setTime(t6);
        }else{
            t6 = 0;
            abc6D =false;
            
        }
    }
    
    if (p7) {
        if (s7== false) {
            t7 += 0.02;
        }else{
            t7 -= 0.02;
        }
        
        if(t7 < abc7.getMaxTime()){
            abc7.setTime(t7);
        }else{
            t7 = 0;
            abc7D =false;
            
        }
    }
    
    if (p8) {
        if (s8== false) {
            t8 += 0.02;
        }else{
            t8 -= 0.02;
        }
        
        if(t8 < abc8.getMaxTime()){
            abc8.setTime(t8);
        }else{
            t8 = 0;
            abc8D =false;
            
        }
    }
    
    if (r1) {
        t1 = ofRandom(abc1.getMaxTime());
        r1 = false;
    }
    if (r2) {
        t2 = ofRandom(abc2.getMaxTime());
        r2 = false;
    }
    if (r3) {
        t3 = ofRandom(abc3.getMaxTime());
        r3 = false;
    }
    if (r4) {
        t4 = ofRandom(abc4.getMaxTime());
        r4 = false;
    }
    
    if (r5) {
        t5 = ofRandom(abc5.getMaxTime());
        r5 = false;
    }
    
    if (r6) {
        t6 = ofRandom(abc6.getMaxTime());
        r6 = false;
    }
    if (r7) {
        t7 = ofRandom(abc7.getMaxTime());
        r7 = false;
    }
    
    if (r8) {
        t8 = ofRandom(abc8.getMaxTime());
        r8 = false;
    }
    
    if (z1) {
        t1 = 0;
        z1 = false;
    }
    if (z2) {
        t2 = 0;
        z2 = false;
    }
    if (z3) {
        t3 = 0;
        z3 = false;
    }
    if (z4) {
        t4 = 0;
        z4 = false;
    }
    if (z5) {
        t5 = 0;
        z5 = false;
    }
    
    if (z6) {
        t6 = 0;
        z6 = false;
    }
    if (z7) {
        t7 = 0;
        z7 = false;
    }
    if (z8) {
        t8 = 0;
        z8 = false;
    }
}
//--------------------------------------------------------------
void ofApp::alembicDraw(){
    
    if(abc1D){
        abc1.draw();
    }
    if(abc2D){
        abc2.draw();
    }

    
    if(abc4D){
        ofPushMatrix();
        ofTranslate(300, 300, 300);
        ofPushStyle();
        ofSetColor(0, 125, 255,200);
        abc4.draw();
        ofPopStyle();
        ofPopMatrix();
    }

    if(abc6D){
        ofPushMatrix();
        ofTranslate(0, 0, 0);
        ofScale(5, 5, 5);
        ofRotateX(30);
        ofRotateY(30);
        ofRotateZ(30);
        abc6.draw();
        ofPopMatrix();
    }
    if(abc7D){
        ofPushMatrix();
        ofTranslate(0, 0, 0);
        ofScale(5, 5, 5);
        abc7.draw();
        ofPopMatrix();
    }
    
}

//--------------------------------------------------------------
void ofApp::osc(){
    
    if(OSC_toggle){
        //--osc--
        while(receiver.hasWaitingMessages()){
                // get the next message
                ofxOscMessage m;
                receiver.getNextMessage(&m);
                
                // check for mouse moved message
                if(m.getAddress() == "/note"){
                    // both the arguments are int32's
                    note = m.getArgAsInt32(0);
                    velocity = m.getArgAsInt32(1);
                    
                }
                else if(m.getAddress() == "/RX"){
                    // both the arguments are int32's
                    //			mouseX = m.getArgAsInt32(0);
                    //			mouseY = m.getArgAsInt32(1);
                    RX = m.getArgAsFloat(0);
                }
                else if(m.getAddress() == "/RY"){
                    // both the arguments are int32's
                    //			mouseX = m.getArgAsInt32(0);
                    //			mouseY = m.getArgAsInt32(1);
                    RY = m.getArgAsFloat(0);
                }
                else if(m.getAddress() == "/RZ"){
                    // both the arguments are int32's
                    //			mouseX = m.getArgAsInt32(0);
                    //			mouseY = m.getArgAsInt32(1);
                    RZ = m.getArgAsFloat(0);
                }
                else if(m.getAddress() == "/sphereToggle"){
                    // both the arguments are int32's
                    //			mouseX = m.getArgAsInt32(0);
                    //			mouseY = m.getArgAsInt32(1);
                    sphereTogglef = m.getArgAsFloat(0);
                }
                else if(m.getAddress() == "/triSphere"){
                    // both the arguments are int32's
                    //			mouseX = m.getArgAsInt32(0);
                    //			mouseY = m.getArgAsInt32(1);
                    triSpheref = m.getArgAsFloat(0);
                }
                else if(m.getAddress() == "/lineline"){
                    // both the arguments are int32's
                    //			mouseX = m.getArgAsInt32(0);
                    //			mouseY = m.getArgAsInt32(1);
                    linelinef = m.getArgAsFloat(0);
                }
                else if(m.getAddress() == "/camera"){
                    
                    CamFadeTime = m.getArgAsInt32(0);
        //            int j = m.getArgAsInt32(1);
        //            CamPre[j] = true;
                    camToggle = m.getArgAsInt32(2);
                    Depth = m.getArgAsInt32(3);
                    camZ = m.getArgAsFloat(4);
                    camRot.z = m.getArgAsFloat(5);
                    GridToggle = m.getArgAsInt32(6);
                    

                    
                }else if(m.getAddress() == "/cameraPre"){
                    // both the arguments are int32's
                    //			mouseX = m.getArgAsInt32(0);
                    //			mouseY = m.getArgAsInt32(1);
                    int j = m.getArgAsInt32(0);
                    CamPre[j] = true;
                }
                else if(m.getAddress() == "/Ecam"){
                    EcamToggle = m.getArgAsInt32(0);
                    EcamSpeed = m.getArgAsFloat(1);
                    EcamRandom = m.getArgAsInt32(2);
                    EcamChange = m.getArgAsInt32(3);
                    EcamScale = m.getArgAsFloat(4);
                    EcamX = m.getArgAsFloat(5);
                    EcamY = m.getArgAsFloat(6);
                    EcamZ = m.getArgAsFloat(7);
                    
                    
                    
                }
                else if(m.getAddress() == "/audio"){
                    audioThreshold = m.getArgAsFloat(0);
                    audioPeakDecay = m.getArgAsFloat(1);
                    audioMaxDecay = m.getArgAsFloat(2);
                    audioMirror = m.getArgAsInt32(3);
                    HoldTime = m.getArgAsInt32(4);
                    DecayRate = m.getArgAsFloat(5);
                }
                else if(m.getAddress() == "/light"){
                    lightToggle = m.getArgAsInt32(0);
                    lightPos.x = m.getArgAsFloat(1);
                    lightPos.y = m.getArgAsFloat(2);
                    lightPosZ = m.getArgAsFloat(3);
                    backAuto = m.getArgAsInt32(4);
                    backAlpha = m.getArgAsFloat(5);
                    MENU = m.getArgAsInt32(6);
                }
                else if(m.getAddress() == "/lightColor"){
                    lr = m.getArgAsFloat(0);
                    lg = m.getArgAsFloat(1);
                    lb = m.getArgAsFloat(2);
                    lw = m.getArgAsFloat(3);
                    ar = m.getArgAsFloat(4);
                    ag = m.getArgAsFloat(5);
                    ab = m.getArgAsFloat(6);
                    c = m.getArgAsFloat(7);
                    d = m.getArgAsFloat(8);
                }
                else if(m.getAddress() == "/lightColor1"){
                    e = m.getArgAsFloat(0);
                    colorMode = m.getArgAsInt32(1);
                    
                }
                else if(m.getAddress() == "/sphere"){
                    
                    sphereToggle = m.getArgAsInt32(0);
                    Resolution = m.getArgAsInt32(1);
                    sphereRidus = m.getArgAsFloat(2);
                    sphereLineWidth = m.getArgAsFloat(3);
                    sphereFaceColor.w = m.getArgAsFloat(4);
                    sphereWireColor.w= m.getArgAsFloat(5);
                    spherePosNoise = m.getArgAsFloat(6);
                    spherePosSpeed = m.getArgAsFloat(7);
                    
                }
                else if(m.getAddress() == "/sphere2"){
                    
                    spherePos.x = m.getArgAsFloat(0);
                    spherePos.y = m.getArgAsFloat(1);
                    spherePos.z = m.getArgAsFloat(2);
                    
                    
                }
                else if(m.getAddress() == "/waveMesh"){
                    
                    waveMeshToggle = m.getArgAsInt32(0);
                    freq = m.getArgAsFloat(1);
                    noise = m.getArgAsFloat(2);
                    fSpeed = m.getArgAsFloat(3);
                    level = m.getArgAsFloat(4);
                    planeLineWidth = m.getArgAsFloat(5);
                    FaceAlpha = m.getArgAsFloat(6);
                    WireAlpha = m.getArgAsFloat(7);
                }
                else if(m.getAddress() == "/waveMesh1"){
                    
                    planePos.x = m.getArgAsFloat(0);
                    planePos.y = m.getArgAsFloat(1);
                    planePos.z = m.getArgAsFloat(2);
                    planeRot.x = m.getArgAsFloat(3);
                    planeRot.y = m.getArgAsFloat(4);
                    planeRot.z = m.getArgAsFloat(5);
                    
                    
                }
                else if(m.getAddress() == "/waveMeshFace"){
                    
                    FaceAlpha = m.getArgAsFloat(0);
                    
                    
                    
                }
                else if(m.getAddress() == "/sphMeshFace"){
                    
                    sphereFaceColor.w = m.getArgAsFloat(0);
                    
                    
                    
                }
                else if(m.getAddress() == "/polygon"){
                    
                    polyToggle = m.getArgAsInt32(0);
                    polyNoise = m.getArgAsFloat(1);
                    polySize = m.getArgAsInt32(2);
                    polyRange = m.getArgAsFloat(3);
                    polyLineWidth = m.getArgAsFloat(4);
                    polyPointSize = m.getArgAsFloat(5);
                    polyRandomToggle = m.getArgAsInt32(6);
                    polyFaceCol.x = m.getArgAsFloat(7);
                    polyWireCol.x = m.getArgAsFloat(8);
                    
                    
                }
                else if(m.getAddress() == "/polygon1"){
                    polyPointCol.x = m.getArgAsFloat(0);
                    polyRot.x = m.getArgAsFloat(1);
                    polyRot.y = m.getArgAsFloat(2);
                    polyRot.z = m.getArgAsFloat(3);
                    polyPos.x = m.getArgAsFloat(4);
                    polyPos.y = m.getArgAsFloat(5);
                    polyPos.z = m.getArgAsFloat(6);
                    RotateArena = m.getArgAsInt32(7);
                    
                }
                else if(m.getAddress() == "/trisphere"){
                    
                    triSphere = m.getArgAsInt32(0);
                    nTri = m.getArgAsInt32(1);
                    Rad = m.getArgAsFloat(2);
                    rad = m.getArgAsFloat(3);
                    ccc = m.getArgAsFloat(4);
                    rrr= m.getArgAsInt32(5);
//                    spherePosNoise = m.getArgAsFloat(6);
//                    spherePosSpeed = m.getArgAsFloat(7);
                    
                }
                else if(m.getAddress() == "/lineline"){
                    
                    lineline = m.getArgAsInt32(0);
                    lineRandom = m.getArgAsInt32(1);
                    
                    
                }
                else if(m.getAddress() == "/xy"){
                    
                    xy = m.getArgAsInt32(0);
                    xyScale.x = m.getArgAsFloat(1);
                    xyScale.y = m.getArgAsFloat(2);
                    smoothedVolScale = m.getArgAsFloat(3);
                    xyRot.z = m.getArgAsFloat(4);
                    waveformWidth = m.getArgAsFloat(5);
                    xyCol.x = m.getArgAsFloat(6);
                    xyCol.y = m.getArgAsFloat(7);
                    
                }
                else if(m.getAddress() == "/waveform"){
                    
                    Waveform = m.getArgAsInt32(0);
                    lineFill = m.getArgAsInt32(1);
                    WaveformScale = m.getArgAsFloat(2);
                    waveWidth = m.getArgAsFloat(3);
                    waveAlpha = m.getArgAsFloat(4);
                    
                }
                else if(m.getAddress() == "/spectrum"){
                    
                    Spectrum = m.getArgAsInt32(0);
                    
                    
                }
                else if(m.getAddress() == "/background"){
                    
                    LcolB.x = m.getArgAsFloat(0);
                    LcolB.y = m.getArgAsFloat(1);
                    RcolB.x = m.getArgAsFloat(2);
                    RcolB.y = m.getArgAsFloat(3);
//                    Lpos1.x = m.getArgAsFloat(4);
//                    Lpos1.y = m.getArgAsFloat(5);
//                    Lwh.x = m.getArgAsFloat(6);
//                    Lwh.y = m.getArgAsFloat(7);
//                    Rpos1.x = m.getArgAsFloat(8);
//                    Rpos1.y = m.getArgAsFloat(9);
                    
                }
                else if(m.getAddress() == "/background2"){
                    
//                    Rwh.x = m.getArgAsFloat(0);
//                    Rwh.y = m.getArgAsFloat(1);
                  
                    
                }else if(m.getAddress() == "/ABC01"){
                    abc1D = m.getArgAsFloat(0);
                    p1 = m.getArgAsFloat(1);
                    s1 = m.getArgAsFloat(2);
                    r1 = m.getArgAsFloat(3);
                    z1 = m.getArgAsFloat(4);
                    w1 = m.getArgAsFloat(5);
                    a1 = m.getArgAsFloat(6);
                    
                    
                    
                }else if(m.getAddress() == "/ABC02"){
                    abc2D = m.getArgAsFloat(0);
                    p2 = m.getArgAsFloat(1);
                    s2 = m.getArgAsFloat(2);
                    r2 = m.getArgAsFloat(3);
                    z2 = m.getArgAsFloat(4);
                    w2 = m.getArgAsFloat(5);
                    a2 = m.getArgAsFloat(6);
                    
                    
                    
                }else if(m.getAddress() == "/ABC03"){
                    abc3D = m.getArgAsFloat(0);
                    p3 = m.getArgAsFloat(1);
                    s3 = m.getArgAsFloat(2);
                    r3 = m.getArgAsFloat(3);
                    z3 = m.getArgAsFloat(4);
                    w3 = m.getArgAsFloat(5);
                    a3 = m.getArgAsFloat(6);
                    
                    
                    
                }else if(m.getAddress() == "/ABC04"){
                    abc4D = m.getArgAsFloat(0);
                    p4 = m.getArgAsFloat(1);
                    s4 = m.getArgAsFloat(2);
                    r4 = m.getArgAsFloat(3);
                    z4 = m.getArgAsFloat(4);
                    w4 = m.getArgAsFloat(5);
                    a4 = m.getArgAsFloat(6);
                    
                    
                    
                }else if(m.getAddress() == "/ABC05"){
                    abc5D = m.getArgAsFloat(0);
                    p5 = m.getArgAsFloat(1);
                    s5 = m.getArgAsFloat(2);
                    r5 = m.getArgAsFloat(3);
                    z5 = m.getArgAsFloat(4);
                    w5 = m.getArgAsFloat(5);
                    a5 = m.getArgAsFloat(6);
                    
                    
                    
                }
                else if(m.getAddress() == "/ABC06"){
                         abc6D = m.getArgAsFloat(0);
                         p6 = m.getArgAsFloat(1);
                         s6 = m.getArgAsFloat(2);
                         r6 = m.getArgAsFloat(3);
                         z6 = m.getArgAsFloat(4);
                         w6 = m.getArgAsFloat(5);
                         a6 = m.getArgAsFloat(6);
                         
                         
                         
                }else if(m.getAddress() == "/ABC07"){
                    abc7D = m.getArgAsFloat(0);
                    p7 = m.getArgAsFloat(1);
                    s7 = m.getArgAsFloat(2);
                    r7 = m.getArgAsFloat(3);
                    z7 = m.getArgAsFloat(4);
                    w7 = m.getArgAsFloat(5);
                    a7 = m.getArgAsFloat(6);
                    
                    
                    
                }else if(m.getAddress() == "/ABC08"){
                    abc8D = m.getArgAsFloat(0);
                    p8 = m.getArgAsFloat(1);
                    s8 = m.getArgAsFloat(2);
                    r8 = m.getArgAsFloat(3);
                    z8 = m.getArgAsFloat(4);
                    w8 = m.getArgAsFloat(5);
                    a8 = m.getArgAsFloat(6);
                    
                    
                    
                }

           
            
        }
    
    }
    
}
//--------------------------------------------------------------
void ofApp::midi(){
    //--MIDI
    if (note ==60 && velocity > 1) {
        
        
        full01.fadeSoildIn01();
        
    }
    if (note ==61 && velocity > 1) {
        
        full01.fadeSoildIn02();
        
    }
    
    if (note ==62 && velocity > 1) {
        
        full01.fadeSoildIn03();
        
    }
    if (note ==63 && velocity > 1) {
        
        full01.fadeSoildIn04();
        
    }
    if (note ==64 && velocity > 1) {
        
        full02.fadeLineIn01();
        
    }
    if (note ==65 && velocity > 1) {
        
        full02.fadeLineIn02();
        
    }
    if (note ==66 && velocity > 1) {
        
        full02.fadeLineIn03();
        
    }
    if (note ==67 && velocity > 1) {
        
        full02.fadeLineIn04();
        
    }
    if((note == 69 && velocity >1)||test01 == true){
        //test01 = true;
        Line.twoPointLine00();
        test01 = false;
    }
    if((note == 70 && velocity >1)||test02 == true){
        //test01 = true;
        Line.CircleDrawing2();
        test02 = false;
    }
    if ((note == 71 && velocity >1)||Line.drawcircleline == true) {
        circle.circleline();
        Line.drawcircleline = false ;
    }
    
//    if (test01) {
//        Line.twoPointLine00();
//        test01 = false;
//    }
    
//    if (test02) {
//        Line.CircleDrawing2();
//        test02 = false;
//    }
    
    if (Line.drawcircleline) {
        circle.circleline();
        Line.drawcircleline = false ;
    }
    
}
//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
    
    //cam.disableMouseInput();
    //    string name = e.widget->getName();
//    int kind = e.widget->getKind();
//    
//    if(name == "A(0,0)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[0][0]= 1;
//        //ofxUIToggle *toggle = 0 ;
//        cout<<A[0][0]<<endl;
//        //A[0][0]= 0;
//    }else if (name == "A(1,0)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[1][0]= 1;
//        cout<<A[1][0]<<endl;
//        
//    }else if (name == "A(2,0)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[2][0]= 1;
//        cout<<A[2][0]<<endl;
//        
//    }else if (name == "A(3,0)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[3][0]= 1;
//        cout<<A[3][0]<<endl;
//        
//    }else if(name == "A(0,1)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[0][1]= 1;
//        cout<<A[0][1]<<endl;
//    }else if (name == "A(1,1)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[1][1]= 1;
//        cout<<A[1][1]<<endl;
//        
//    }else if (name == "A(2,1)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[2][1]= 1;
//        cout<<A[2][1]<<endl;
//        
//    }else if (name == "A(3,1)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[3][1]= 1;
//        cout<<A[3][1]<<endl;
//        
//    }else if (name == "A(0,2)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[0][2]= 1;
//        cout<<A[0][2]<<endl;
//    }else if (name == "A(1,2)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[1][2]= 1;
//        cout<<A[1][2]<<endl;
//        
//    }else if (name == "A(2,2)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[2][2]= 1;
//        cout<<A[2][2]<<endl;
//        
//    }else if (name == "A(3,2)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[3][2]= 1;
//        cout<<A[3][2]<<endl;
//        
//    }else if(name == "A(0,3)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[0][3]= 1;
//        cout<<A[0][3]<<endl;
//    }else if (name == "A(1,3)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[1][3]= 1;
//        cout<<A[1][3]<<endl;
//        
//    }else if (name == "A(2,3)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[2][3]= 1;
//        cout<<A[2][3]<<endl;
//        
//    }else if (name == "A(3,3)")
//    {
//        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
//        A[3][3]= 1;
//        cout<<A[3][3]<<endl;
//        
//    }
    
    
}
//--------------------------------------------------------------
void ofApp::exit(){
    gui0->saveSettings("gui0Settings.xml");
    gui1->saveSettings("gui1Settings.xml");
    gui2->saveSettings("gui2Settings.xml");
    gui3->saveSettings("gui3Settings.xml");
    gui4->saveSettings("gui4Settings.xml");
    gui5->saveSettings("gui5Settings.xml");
    gui6->saveSettings("gui6Settings.xml");
    gui7->saveSettings("gui7Settings.xml");
    gui8->saveSettings("gui8Settings.xml");
    gui9->saveSettings("gui9Settings.xml");

    
    delete gui0;
    delete gui1;
    delete gui2;
    delete gui3;
    delete gui4;
    delete gui5;
    delete gui6;
    delete gui7;
    delete gui8;
    delete gui9;

}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	
	curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
    
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        
        ll[i]    = input[i*2];
        rr[i]    = input[i*2+1];
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
        vol[i] = left[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '1':
            gui0->toggleVisible();
            break;
        case '2':
            gui1->toggleVisible();
            break;
        case '3':
            gui2->toggleVisible();
            break;
        case '4':
            gui3->toggleVisible();
            break;
        case '5':
            gui4->toggleVisible();
            break;
        case '6':
            gui5->toggleVisible();
            break;
        case '7':
            gui6->toggleVisible();
            break;
        case '8':
            gui7->toggleVisible();
            break;
        case '9':
            gui8->toggleVisible();
            break;
        case '0':
            gui9->toggleVisible();
            break;
            
            
        case 's':
            gui0->saveSettings("gui0Settings.xml");
            gui1->saveSettings("gui1Settings.xml");
            gui2->saveSettings("gui2Settings.xml");
            gui3->saveSettings("gui3Settings.xml");
            gui4->saveSettings("gui4Settings.xml");
            gui5->saveSettings("gui5Settings.xml");
            gui6->saveSettings("gui6Settings.xml");
            gui7->saveSettings("gui7Settings.xml");
            gui8->saveSettings("gui8Settings.xml");
            gui9->saveSettings("gui9Settings.xml");
            break;
        case 'l':
            gui0->loadSettings("gui0Settings.xml");
            gui1->loadSettings("gui1Settings.xml");
            gui2->loadSettings("gui2Settings.xml");
            gui3->loadSettings("gui3Settings.xml");
            gui4->loadSettings("gui4Settings.xml");
            gui5->loadSettings("gui5Settings.xml");
            gui6->loadSettings("gui6Settings.xml");
            gui7->loadSettings("gui7Settings.xml");
            gui8->loadSettings("gui8Settings.xml");
            gui9->loadSettings("gui9Settings.xml");
            break;
        default:
            break;
    }
    if (key == 'z') {
        camToggle = !camToggle;
        //saveCam.setup(&cam,"CAMERA");
    }
    

//    if(key == 'x'){
//        saveCam.tweenNow(4, 2); // first int is what camera to tween to , secound int is time
//
//    }
//    if(key == 'c'){
//        saveCam.tweenNow(5, 4);
//
//    }
//    if(key == 'v'){
//        saveCam.tweenNow(6, 5);
//
//    }
//    if(key == 'z'){
//        saveCam.tweenNow(7, 5);
//    }
//    if(key == 'q'){
//        saveCam.tweenNow(8, 100);
//    }
//    if(key == 'b'){
//        saveCam.cutNow((int)ofRandom(2));
//    }
    
    if (key == 'a') {
        gui0->setVisible(false);
        gui1->setVisible(false);
        gui2->setVisible(false);
        gui3->setVisible(false);
        gui4->setVisible(false);
        gui5->setVisible(false);
        gui6->setVisible(false);
        gui7->setVisible(false);
        gui8->setVisible(false);
        gui9->setVisible(false);
        
        Depth =! Depth;
        backAuto =! backAuto;
    }
    if(key == 'm'){
        saveCam.setup(&cam,"xml");
    }
    if (key == 'q') {
        MENU =! MENU;
        
//        gui0->toggleVisible();
//        gui1->toggleVisible();
//        gui2->toggleVisible();
//        gui3->toggleVisible();
//        gui4->toggleVisible();
//        gui5->toggleVisible();
//        gui6->toggleVisible();
//        gui7->toggleVisible();
//        gui8->toggleVisible();
//        gui9->toggleVisible();
    }
    
    if (key == 'f') {
        ofToggleFullscreen();
    }
    
    if (key == 'g') {
        gridT =! gridT;
    }
    
    if (key == ',') {
        ofSetWindowPosition(-2540, 100);
    }
    if (key == '.') {
        ofSetWindowPosition(0, 100);
    }
    if (key == ' ') {
        Ecam.setRandomPos();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
