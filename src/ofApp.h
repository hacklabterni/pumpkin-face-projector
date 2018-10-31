#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxPumpkinFace.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void loadImage(size_t fileIndex);
    void nextImage();
    void prevImage();

    // generate a random target rect
    void makeTargetRect();
    ofRectangle targetRect;

    ofImage image;
    ofxCv::ContourFinder contourFinder;
    ofxPumpkinFace pumpkinFace;

    ofEasyCam easyCam;

    ofDirectory dir;
    size_t fileIndex;

    float extrusionDepth;
    float nextResetTime;
    float resetIntervalTime;

    bool  	bFullscreen;
    bool  	bCalibrate;
    bool  	bNeedImageReload;

};
