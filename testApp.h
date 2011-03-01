#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "Halftoner.h"

enum {
	FIXEDTHRESH,
	RANDOM,
	PATTERN,
	ORDCLUST,
	ORDDISP,
	ORDBAYER,
	FLOYDSTEINBERG,
	ATKINSON,
	CUSTOM
};


//const int 
class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();


        ofImage             img;

        ofTexture           imgTx,
                            fixedThresholdTx,
                            randomDitherTx,
                            patternTx,
                            ordClustTx,
                            ordDispTx,
                            ordBayerTx,
                            floydSteinbergTx,
                            atkinsonTx;


        unsigned char * px;
		unsigned char * pxR;
		unsigned char * pxG;
		unsigned char * pxB;



        unsigned char * fixedThresholdPx;
		
		unsigned char * fixedThresholdPxR;
		unsigned char * fixedThresholdPxG;
		unsigned char * fixedThresholdPxB;
		unsigned char * fixedThresholdPxRGB;
		
		
		
        unsigned char * randomDitherPx;
        unsigned char * patternPx;
        unsigned char * ordClustPx;
        unsigned char * ordDispPx;
        unsigned char * ordBayerPx;
        unsigned char * floydSteinbergPx;
        unsigned char * atkinsonPx;
		
		ofVideoGrabber cam;
		int ditherType;

		int ** theCustomPattern;
		int customPatternW, customPatternH;
        int w, h, numPx;

        int threshold;

		vector <int> values;
		bool alias;


};

#endif
