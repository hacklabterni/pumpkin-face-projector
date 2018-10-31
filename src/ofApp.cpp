#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofDisableArbTex();
    ofEnableDepthTest();

    makeTargetRect();

    bFullscreen = false;
    bCalibrate = false;
    bNeedImageReload = false;

    nextResetTime = 0;
    resetIntervalTime = 10;
    extrusionDepth = -50.0;

    fileIndex = 0;
    dir.allowExt("jpg");
    dir.allowExt("jpeg");
    dir.allowExt("png");
    dir.listDir("images");
    dir.sort();

    pumpkinFace.setup(extrusionDepth, targetRect);
    loadImage(fileIndex);

    easyCam.setTarget(ofVec3f(0, 0, 0));
}

//--------------------------------------------------------------
void ofApp::update(){
    if (!bCalibrate) {
        float now = ofGetElapsedTimef();
        if (now > nextResetTime) {
          nextImage();
          nextResetTime = now + resetIntervalTime;
        }
        pumpkinFace.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    easyCam.begin();
        if (!bCalibrate) {
            if (bNeedImageReload) {
                bNeedImageReload = false;
                pumpkinFace.setTargetRect(targetRect);
                loadImage(fileIndex);
            }
            pumpkinFace.draw();
        } else {
            ofPushMatrix();
                ofTranslate(-targetRect.getWidth()/2, -targetRect.getHeight()/2);
                ofSetColor(ofColor(0, 0, 255));
                ofDrawRectangle(targetRect);
            ofPopMatrix();
        }
    easyCam.end();
}

//--------------------------------------------------------------
void ofApp::makeTargetRect() {
    // create a target rectangle aligned to the center of the screen (needed for 'calibration')
    targetRect.setFromCenter(ofGetWidth()  / 2.0f, ofGetHeight() / 2.0f, 400.0f, 400.0f);
    targetRect.setPosition(ofVec3f(0, 0, 0));
}

//--------------------------------------------------------------
void ofApp::loadImage(size_t fileIndex){
    image.load(dir.getFile(fileIndex).getAbsolutePath());
    image.mirror(true, false);
    pumpkinFace.setImage(image, false);
}

//--------------------------------------------------------------
void ofApp::nextImage(){
    fileIndex += 1;
    if (fileIndex == dir.size()) {
        fileIndex = 0;
    }
    loadImage(fileIndex);
}

//--------------------------------------------------------------
void ofApp::prevImage(){
    if (fileIndex != 0) {
        fileIndex -= 1;
    }
    else {
        fileIndex = dir.size() - 1;
    }
    loadImage(fileIndex);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'n') {
        nextImage();
    } else if (key == 'p') {
        prevImage();
    } else if (key == 'f') {
        bFullscreen = !bFullscreen;
        ofSetFullscreen(bFullscreen);
    } else if (key == 'c') {
        bCalibrate = !bCalibrate;
    }

    if (bCalibrate) {
        if (key == OF_KEY_UP) {
            targetRect.height += 1;
        } else if (key == OF_KEY_DOWN) {
            targetRect.height -= 1;
        } else if (key == OF_KEY_RIGHT) {
            targetRect.width += 1;
        } else if (key == OF_KEY_LEFT) {
            targetRect.width -= 1;
        }
        bNeedImageReload = true;
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
