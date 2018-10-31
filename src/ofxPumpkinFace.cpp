#include "ofxPumpkinFace.h"

ofxPumpkinFace::ofxPumpkinFace() {

}

void ofxPumpkinFace::setup(float _extrusionDepth, ofRectangle _targetRect) {
    frontColor = ofColor(0, 0, 0);
    backColor = ofColor(255, 0, 0);
    sideColor = ofColor(255, 255, 0);
    extrusionDepth = _extrusionDepth;
    targetRect = _targetRect;
}

void ofxPumpkinFace::update() {

}

void ofxPumpkinFace::draw() {
    ofPushMatrix();
        ofTranslate(-image.getWidth()/2, -image.getHeight()/2);
        frontPath.draw();
        backPath.draw();
        for (auto side : sides) {
            side.draw();
        }
    ofPopMatrix();
}

void ofxPumpkinFace::setExtrusionDepth(float _extrusionDepth) {
    extrusionDepth = _extrusionDepth;
}

void ofxPumpkinFace::setTargetRect(ofRectangle _targetRect) {
    targetRect = _targetRect;
}

void ofxPumpkinFace::setImage(ofImage _image, bool bIsResizedImage = false) {
    image = _image;
    contourFinder.setInvert(true);
    contourFinder.findContours(image);

    if (!bIsResizedImage) {
        scaleToTargetRect();
    }
    initFront();
    initBack();
    initSide();
}

void ofxPumpkinFace::setFrontColor(ofColor c) {
    frontColor = c;
}

void ofxPumpkinFace::setBackColor(ofColor c) {
    backColor = c;
}

void ofxPumpkinFace::setSideColor(ofColor c) {
    sideColor = c;
}

void ofxPumpkinFace::scaleToTargetRect() {
    // Add polylines to frontPath.
    frontPath.clear();
    for (auto polyline : contourFinder.getPolylines()) {
        frontPath.newSubPath();
        for (auto vertex : polyline) {
            frontPath.lineTo(vertex);
        }
        frontPath.close();
    }

    // Find the frontPath BoundingBox.
    ofRectangle rect;
    for (unsigned long i=0; i<frontPath.getOutline().size(); i++) {
      ofRectangle b = frontPath.getOutline().at(i).getBoundingBox();
      if (i==0) rect = b;
      else rect.growToInclude(b);
    }

    ofRectangle finalRect = rect;
    finalRect.scaleTo(targetRect, OF_ASPECT_RATIO_KEEP);
    float newWidth = image.getWidth() * finalRect.getWidth() / rect.getWidth();
    float newHeight = image.getHeight() * finalRect.getHeight() / rect.getHeight();

    image.resize(newWidth, newHeight);
    setImage(image, true);
}

void ofxPumpkinFace::initFront() {
    // Add polylines to frontPath.
    frontPath.clear();
    for (auto polyline : contourFinder.getPolylines()) {
        frontPath.newSubPath();
        for (auto vertex : polyline) {
            frontPath.lineTo(vertex);
        }
        frontPath.close();
    }

    // Find the frontPath BoundingBox.
    ofRectangle rect;
    for (unsigned long i=0; i<frontPath.getOutline().size(); i++) {
      ofRectangle b = frontPath.getOutline().at(i).getBoundingBox();
      if (i==0) rect = b;
      else rect.growToInclude(b);
    }

    // Scale the BoundingBox and add it to frontPath.
    rect.scaleFromCenter(static_cast<float>(1.2));
    frontPath.newSubPath();
    frontPath.lineTo(rect.getTopLeft());
    frontPath.lineTo(rect.getTopRight());
    frontPath.lineTo(rect.getBottomRight());
    frontPath.lineTo(rect.getBottomLeft());
    frontPath.close();
    frontPath.setFillColor(frontColor);
}

void ofxPumpkinFace::initBack() {
    // Create backPath.
    backPath.clear();
    for (auto polyline : contourFinder.getPolylines()) {
        backPath.newSubPath();
        for (auto vertex : polyline) {
            backPath.lineTo(vertex.x, vertex.y, vertex.z+extrusionDepth);
        }
        backPath.close();
    }
    backPath.setFillColor(backColor);
}

void ofxPumpkinFace::initSide() {
    // Create sides mesh.
    sides.clear();
    for (auto polyline : contourFinder.getPolylines()) {
        ofVboMesh side;
        side.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

        auto & vertices = polyline.getVertices();
        size_t size = vertices.size();
        auto vertex1 = vertices[0];
        auto vertex2 = vertices[0];
        for (unsigned long i=0; i<size; i++){
            if (i < size-1) {
                vertex1 = vertices[i];
                vertex2 = vertices[i+1];
            } else {
                vertex1 = vertices[i];
                vertex2 = vertices[0];
            }

            side.addVertex(vertex1);
            side.addVertex(vertex2);
            side.addVertex(ofPoint(vertex1.x, vertex1.y, vertex1.z+extrusionDepth));
            side.addVertex(ofPoint(vertex2.x, vertex2.y, vertex2.z+extrusionDepth));
            side.addVertex(vertex2);
            side.addColor(sideColor);
            side.addColor(sideColor);
            side.addColor(sideColor);
            side.addColor(sideColor);
            side.addColor(sideColor);
        }

        sides.push_back(side);
    }
}
