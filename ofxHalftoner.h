#ifndef _OFX_HALFTONER_H
#define _OFX_HALFTONER_H

#include "ofMain.h"
const int patternW = 4;
const int patternH = 4;

const int patterns [4][patternW][patternH] = {{{0,0,1,0},
											   {0,1,0,0},
											   {1,0,0,0},
											   {0,0,0,1}},

                                               {{1,1,0,0},
                                                {1,1,0,0},
                                                {1,1,0,0},
                                                {1,1,0,0}},

                                               {{0,1,1,1},
                                                {1,1,1,1},
                                                {1,1,1,0},
                                                {4,1,0,0}},


                                               {{1,1,1,1},
                                                {1,1,1,1},
                                                {1,1,1,1},
                                                {1,1,1,1}}};



const int clusterPattern   [3][3] = {{8, 3, 4},
                                      {6, 1, 2},
                                      {7, 5, 9}};

const int dispersedPattern [3][3] = {{1, 7, 4},
                                      {5, 8, 3},
                                      {6, 2, 9}};

const int bayerPattern [2][2] = {{1,3},
                                  {4,2}};

const int fsPattern[3][3] = {{0, 0, 0},
                              {0, 0, 7},
                              {3, 5, 1}};



class ofxHalfToner {
    
	public:

        static unsigned char * fixedThreshold   (const unsigned char * src, unsigned char * dst, int w, int h, int threshold);
        static unsigned char * random           (const unsigned char * src, unsigned char * dst, int w, int h);
        static unsigned char * patterned        (const unsigned char * src, unsigned char * dst, int w, int h);
        static unsigned char * orderedClust     (const unsigned char * src, unsigned char * dst, int w, int h);
        static unsigned char * orderedDisp      (const unsigned char * src, unsigned char * dst, int w, int h) ;
        static unsigned char * orderedBayer     (const unsigned char * src, unsigned char * dst, int w, int h);

        // TODO: both of these leave the right & bottom margins undone.
        static unsigned char * floydSteinberg   (const unsigned char * src, unsigned char * dst, int w, int h);
        static unsigned char * atkinson         (const unsigned char * src, unsigned char * dst, int w, int h);
		
		static unsigned char * custom			(const unsigned char * src, unsigned char * dst, int w, int h, int ** customPattern, int customPatternW, int customPatternH);

};



#endif
