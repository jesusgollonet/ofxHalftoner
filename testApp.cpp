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
			Halftoner::fixedThreshold  (pxR, fixedThresholdPxR, w, h, 100);
			Halftoner::fixedThreshold  (pxG, fixedThresholdPxG, w, h, 100);
			Halftoner::fixedThreshold  (pxB, fixedThresholdPxB, w, h,100);

			break;
		case RANDOM:
			Halftoner::random  (pxR, fixedThresholdPxR, w, h);
			Halftoner::random  (pxG, fixedThresholdPxG, w, h);
			Halftoner::random  (pxB, fixedThresholdPxB, w, h);

			break;
		case PATTERN:
			Halftoner::patterned  (pxR, fixedThresholdPxR, w, h);
			Halftoner::patterned  (pxG, fixedThresholdPxG, w, h);
			Halftoner::patterned  (pxB, fixedThresholdPxB, w, h);

			break;
		case ORDCLUST:
			Halftoner::orderedClust	(pxR, fixedThresholdPxR, w, h);
			Halftoner::orderedClust  (pxG, fixedThresholdPxG, w, h);
			Halftoner::orderedClust  (pxB, fixedThresholdPxB, w, h);

			break;
		case ORDDISP:
			Halftoner::orderedDisp  (pxR, fixedThresholdPxR, w, h);
			Halftoner::orderedDisp  (pxG, fixedThresholdPxG, w, h);
			Halftoner::orderedDisp  (pxB, fixedThresholdPxB, w, h);

			break;
		case ORDBAYER:
			Halftoner::orderedBayer  (pxR, fixedThresholdPxR, w, h);
			Halftoner::orderedBayer  (pxG, fixedThresholdPxG, w, h);
			Halftoner::orderedBayer  (pxB, fixedThresholdPxB, w, h);

			break;
		case FLOYDSTEINBERG:
			Halftoner::floydSteinberg  (pxR, fixedThresholdPxR, w, h);
			Halftoner::floydSteinberg  (pxG, fixedThresholdPxG, w, h);
			Halftoner::floydSteinberg  (pxB, fixedThresholdPxB, w, h);

			break;
		case ATKINSON:
			Halftoner::atkinson (pxR, fixedThresholdPxR, w, h);
			Halftoner::atkinson (pxG, fixedThresholdPxG, w, h);
			Halftoner::atkinson (pxB, fixedThresholdPxB, w, h);

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
			Halftoner::custom (pxR, fixedThresholdPxR, w, h, theCustomPattern, customPatternW, customPatternH);
			Halftoner::custom (pxG, fixedThresholdPxG, w, h, theCustomPattern, customPatternW, customPatternH);
			Halftoner::custom (pxB, fixedThresholdPxB, w, h, theCustomPattern, customPatternW, customPatternH);

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
	//Halftoner::fixedThreshold (px, fixedThresholdPx, w, h, threshold);
    
	/*
	Halftoner::random         (px, randomDitherPx, w, h);
    Halftoner::patterned      (px, patternPx, w, h);
    Halftoner::orderedClust   (px, ordClustPx, w, h);
    Halftoner::orderedDisp    (px, ordDispPx, w, h);
    Halftoner::orderedBayer   (px, ordBayerPx, w, h);
    Halftoner::floydSteinberg (px, floydSteinbergPx, w, h);
    Halftoner::atkinson       (px, atkinsonPx, w, h);

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
