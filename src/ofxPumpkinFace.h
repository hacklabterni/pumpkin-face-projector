#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class ofxPumpkinFace{

public:

    void setup(float extrusionDepth, ofRectangle targetRect);
    void update();
    void draw();

    void setExtrusionDepth(float extrusionDepth);
    void setTargetRect(ofRectangle targetRect);
    void setImage(ofImage image, bool bIsResizedImage);
    void setFrontColor(ofColor c);
    void setBackColor(ofColor c);
    void setSideColor(ofColor c);

    ofxPumpkinFace();

    ofRectangle targetRect;
    ofImage image;
    ofxCv::ContourFinder contourFinder;
    float extrusionDepth;

    ofColor frontColor;
    ofColor backColor;
    ofColor sideColor;
    ofPath frontPath;
    ofPath backPath;
    ofPath sidePath;
    vector<ofVboMesh> sides;

protected:
    void scaleToTargetRect();
    void initFront();
    void initBack();
    void initSide();

};
