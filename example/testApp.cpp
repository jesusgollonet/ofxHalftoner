#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

    
	cam.initGrabber(640, 480);

    w = cam.width;
    h = cam.height;
    numPx = w * h;

    threshold = 50;

    imgTx.allocate(w, h, GL_LUMINANCE);
    
	px    = new unsigned char [numPx];
	pxR    = new unsigned char [numPx];
	pxG    = new unsigned char [numPx];
	pxB    = new unsigned char [numPx];
	
    
	//fixedThresholdTx.allocate(w, h, GL_LUMINANCE);
	fixedThresholdTx.allocate(w, h, GL_RGB);
    
	fixedThresholdPx  = new unsigned char [numPx];
	
	fixedThresholdPxR  = new unsigned char [numPx];
	fixedThresholdPxG  = new unsigned char [numPx];
	fixedThresholdPxB  = new unsigned char [numPx];
	
	fixedThresholdPxRGB  = new unsigned char [numPx*3];

	ditherType = FIXEDTHRESH;
	customPatternW = 3;
	customPatternH = 4;
	theCustomPattern = new int *[customPatternW];
	int c= 0;
	
	for (int i = 1; i <= customPatternW*customPatternH; i++){
		values.push_back(i);
	}
	
	for (int i=0; i < customPatternW; i++) {
		theCustomPattern [i]  =new int [customPatternH];
		for (int j=0; j < customPatternH; j++) {
			int valueIndex = (int)ofRandom(0,values.size());
			//
			cout << valueIndex << endl;
			theCustomPattern[i][j] =values.at(valueIndex);//(i+j);
			values.erase(values.begin()+(valueIndex-1));	
			c++;
		}
	}
	//theCustomPattern = {{1,2,3},{4,5,6},{7,8,9}};
	
}

//--------------------------------------------------------------
void testApp::update(){

	ofBackground(210,210,210);
	cam.grabFrame();
	
	for (int i = 0; i < numPx; i++) {
		pxR[i] = cam.getPixels()[i   *3];
		pxG[i] = cam.getPixels()[i *3+1];
		pxB[i] = cam.getPixels()[i*3+2];
	}
	
	
	switch (ditherType) {
		case FIXEDTHRESH:
			ofxHalfToner::fixedThreshold  (pxR, fixedThresholdPxR, w, h, 100);
			ofxHalfToner::fixedThreshold  (pxG, fixedThresholdPxG, w, h, 100);
			ofxHalfToner::fixedThreshold  (pxB, fixedThresholdPxB, w, h,100);

			break;
		case RANDOM:
			ofxHalfToner::random  (pxR, fixedThresholdPxR, w, h);
			ofxHalfToner::random  (pxG, fixedThresholdPxG, w, h);
			ofxHalfToner::random  (pxB, fixedThresholdPxB, w, h);

			break;
		case PATTERN:
			ofxHalfToner::patterned  (pxR, fixedThresholdPxR, w, h);
			ofxHalfToner::patterned  (pxG, fixedThresholdPxG, w, h);
			ofxHalfToner::patterned  (pxB, fixedThresholdPxB, w, h);

			break;
		case ORDCLUST:
			ofxHalfToner::orderedClust	(pxR, fixedThresholdPxR, w, h);
			ofxHalfToner::orderedClust  (pxG, fixedThresholdPxG, w, h);
			ofxHalfToner::orderedClust  (pxB, fixedThresholdPxB, w, h);

			break;
		case ORDDISP:
			ofxHalfToner::orderedDisp  (pxR, fixedThresholdPxR, w, h);
			ofxHalfToner::orderedDisp  (pxG, fixedThresholdPxG, w, h);
			ofxHalfToner::orderedDisp  (pxB, fixedThresholdPxB, w, h);

			break;
		case ORDBAYER:
			ofxHalfToner::orderedBayer  (pxR, fixedThresholdPxR, w, h);
			ofxHalfToner::orderedBayer  (pxG, fixedThresholdPxG, w, h);
			ofxHalfToner::orderedBayer  (pxB, fixedThresholdPxB, w, h);

			break;
		case FLOYDSTEINBERG:
			ofxHalfToner::floydSteinberg  (pxR, fixedThresholdPxR, w, h);
			ofxHalfToner::floydSteinberg  (pxG, fixedThresholdPxG, w, h);
			ofxHalfToner::floydSteinberg  (pxB, fixedThresholdPxB, w, h);

			break;
		case ATKINSON:
			ofxHalfToner::atkinson (pxR, fixedThresholdPxR, w, h);
			ofxHalfToner::atkinson (pxG, fixedThresholdPxG, w, h);
			ofxHalfToner::atkinson (pxB, fixedThresholdPxB, w, h);

			break;
		case CUSTOM:
			/*
			// we can change the custom pattern on the fly
			int c = 0;
			for (int i=0; i < customPatternW; i++) {
				//theCustomPattern [i]  =new int [customPatternH];
				for (int j=0; j < customPatternH; j++) {
					int valueIndex = (int)ofRandom(0,customPatternW * customPatternH);
					//
					//cout << valueIndex << endl;
					theCustomPattern[i][j] =values.at(valueIndex);//(i+j);
					//values.erase(values.begin()+(valueIndex-1));	
					c++;
				}
			}
			*/
			ofxHalfToner::custom (pxR, fixedThresholdPxR, w, h, theCustomPattern, customPatternW, customPatternH);
			ofxHalfToner::custom (pxG, fixedThresholdPxG, w, h, theCustomPattern, customPatternW, customPatternH);
			ofxHalfToner::custom (pxB, fixedThresholdPxB, w, h, theCustomPattern, customPatternW, customPatternH);

			break;

	}
	
	for (int i = 0; i < numPx; i++) {
		fixedThresholdPxRGB [i *3 + 0] = fixedThresholdPxR[i];
		fixedThresholdPxRGB [i * 3 +1] = fixedThresholdPxG[i];
		fixedThresholdPxRGB [i * 3 + 2] = fixedThresholdPxB[i];
	}
    //fixedThresholdTx.loadData   (fixedThresholdPxR, w, h, GL_LUMINANCE);
	fixedThresholdTx.loadData   (fixedThresholdPxRGB, w, h, GL_RGB);
    //fixedThresholdTx.loadData   (px, w, h, GL_LUMINANCE);
    


}

//--------------------------------------------------------------
void testApp::draw(){

    cam.draw(0,0, 320,240);

    //imgTx.draw              (20 + w      , 20, w, h);
	
	//glPushMatrix();
	//glTranslatef(0,0,mouseX);
    fixedThresholdTx.draw   (320, 0, w, h);
    //glPopMatrix();
	
	/*
	randomDitherTx.draw     (20 + (3 * w), 20, w, h);
    ordBayerTx.draw         (20 +  w ,20 +h,   w, h);
    ordClustTx.draw         (20 + (w*2),20 +h, w, h);
    ordDispTx.draw          (20 + (w*3),20 +h, w, h);
    patternTx.draw          (20 + (w),20 +(h*2), w, h);
    floydSteinbergTx.draw   (20 + (w*2),20 +(h*2), w, h);
    atkinsonTx.draw   (20 + (w*3),20 +(h*2), w, h);
	*/



}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	switch (key) {
		case '1':
			ditherType = FIXEDTHRESH;
			break;
		case '2':
			ditherType = RANDOM;
			break;
		case '3':
			ditherType = PATTERN;
			break;
		case '4':
			ditherType = ORDCLUST;
			break;
		case '5':
			ditherType = ORDDISP;
			break;
		case '6':
			ditherType = ORDBAYER;
			break;
		case '7':
			ditherType = FLOYDSTEINBERG;
			break;
		case '8':
			ditherType = ATKINSON;
			break;
		case '9':
			ditherType = CUSTOM;
			break;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    threshold = (int)(((float)x / (float)ofGetScreenWidth()) * 255);

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	//ofxHalfToner::fixedThreshold (px, fixedThresholdPx, w, h, threshold);
    
	/*
	ofxHalfToner::random         (px, randomDitherPx, w, h);
    ofxHalfToner::patterned      (px, patternPx, w, h);
    ofxHalfToner::orderedClust   (px, ordClustPx, w, h);
    ofxHalfToner::orderedDisp    (px, ordDispPx, w, h);
    ofxHalfToner::orderedBayer   (px, ordBayerPx, w, h);
    ofxHalfToner::floydSteinberg (px, floydSteinbergPx, w, h);
    ofxHalfToner::atkinson       (px, atkinsonPx, w, h);

    randomDitherTx.loadData     (randomDitherPx, w, h, GL_LUMINANCE);
    patternTx.loadData          (patternPx, w, h, GL_LUMINANCE);
    ordClustTx.loadData         (ordClustPx, w, h, GL_LUMINANCE);
    ordDispTx.loadData          (ordDispPx, w, h, GL_LUMINANCE);
    ordBayerTx.loadData         (ordBayerPx, w, h, GL_LUMINANCE);
    floydSteinbergTx.loadData   (floydSteinbergPx, w, h, GL_LUMINANCE);
    atkinsonTx.loadData         (atkinsonPx, w, h, GL_LUMINANCE);
*/

}

//--------------------------------------------------------------
void testApp::mouseReleased(){

}
