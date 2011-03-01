#include "Halftoner.h"


unsigned char * Halftoner::fixedThreshold(const unsigned char * src, unsigned char * dst, int w, int h, int threshold){
    int numPx = w*h;
    for (int i = 0; i < numPx; i++) {
        dst[i] = src[i] > threshold? 255:0;
    }
}

unsigned char * Halftoner::random(const unsigned char * src, unsigned char * dst, int w, int h) {
    int numPx = w*h;
    for (int i = 0; i < numPx; i++) {
        dst[i] = src[i] > ofRandom(0,255) ? 255:0;
    }

}

unsigned char * Halftoner::patterned(const unsigned char * src, unsigned char * dst, int w, int h) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (src[j*w+i] < 64) {
                dst[j*w+i]= patterns[0][j%patternH][i%patternW]*255;
            } else if (src[j*w+i] >= 64 && src[j*w+i] < 128) {
                dst[j*w+i]= patterns[1][j%patternH][i%patternW]*255;
            } else if (src[j*w+i] >= 128 && src[j*w+i] < 192) {
                dst[j*w+i]= patterns[2][j%patternH][i%patternW]*255;
            } else {
                dst[j*w+i]= patterns[3][j%patternH][i%patternW]*255;
            }
        }
    }
}

unsigned char * Halftoner::orderedClust(const unsigned char * src, unsigned char * dst, int w, int h) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (src[j*w+i]/(255/10) > clusterPattern[j%3][i%3]) {
                dst[j*w+i]= 255;
            } else {
                dst[j*w+i]= 0;
            }
        }
    }
}

unsigned char * Halftoner::orderedDisp(const unsigned char * src, unsigned char * dst, int w, int h) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (src[j*w+i]/(255/10) > dispersedPattern[j%3][i%3]) {
                dst[j*w+i]= 255;
            } else {
                dst[j*w+i]= 0;
            }
        }
    }
}

unsigned char * Halftoner::orderedBayer(const unsigned char * src, unsigned char * dst, int w, int h) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (src[j*w+i]/(255/5) > bayerPattern[j%2][i%2]) {
                dst[j*w+i]= 255;
            } else {
                dst[j*w+i]= 0;
            }
        }
    }
}

unsigned char * Halftoner::floydSteinberg(const unsigned char * src, unsigned char * dst, int w, int h) {

    int oldPx = 0;
    int newPx = 0;
    int qError = 0;

    int threshold = 127;
    memcpy(dst, src, w*h);
    int r, bl, bc, br;
    for (int j = 0; j < h-1; j++) {
        for (int i = 1; i < w-1; i++) {
            oldPx = dst[j*w+i];
            newPx = oldPx < threshold ? 0 : 255;
            dst[j*w+i] = newPx;

            qError = oldPx - newPx;

            // super duper ugly 2 part value clipping (to avoid values beyond 0-255)
            r  = MIN(dst[j*w+(i+1)]     + (int)((7.0f/16.0f) * qError), 255);
            bl = MIN(dst[(j+1)*w+(i-1)] + (int)((3.0f/16.0f) * qError), 255);
            bc = MIN(dst[(j+1)*w+(i)]   + (int)((5.0f/16.0f) * qError), 255);
            br = MIN(dst[(j+1)*w+(i+1)] + (int)((1.0f/16.0f) * qError), 255);

            dst[j*w+(i+1)]     = MAX(r , 0);
            dst[(j+1)*w+(i-1)] = MAX(bl, 0);
            dst[(j+1)*w+(i)]   = MAX(bc, 0);
            dst[(j+1)*w+(i+1)] = MAX(br, 0);

        }
    }
}

unsigned char * Halftoner::atkinson(const unsigned char * src, unsigned char * dst, int w, int h) {

    int pxPos;
    int oldPx = 0;
    int newPx = 0;
    int qError = 0;

    int threshold = 127;
    memcpy(dst, src, w*h);
    int r1, r2,  bl1, bc1, br1, bc2;
    for (int j = 0; j < h-2; j++) {
        for (int i = 1; i < w-2; i++) {
            pxPos = j*w+i;
            oldPx = dst[j*w+i];
            newPx = oldPx < threshold ? 0 : 255;
            dst[j*w+i] = newPx;

            qError = oldPx - newPx;

            // super duper ugly 2 part value clipping (to avoid values beyond 0-255)
            r1  = MIN(dst[j*w+(i+1)]     + (int)(.125f * qError), 255);
            r2  = MIN(dst[j*w+(i+2)]     + (int)(.125f * qError), 255);
            bl1 = MIN(dst[(j+1)*w+(i-1)] + (int)(.125f * qError), 255);
            bc1 = MIN(dst[(j+1)*w+(i)]   + (int)(.125f * qError), 255);
            br1 = MIN(dst[(j+1)*w+(i+1)] + (int)(.125f * qError), 255);
            bc2 = MIN(dst[(j+2)*w+(i)]   + (int)(.125f * qError), 255);

            dst[j*w+(i+1)]     = MAX(r1 , 0);
            dst[(j+1)*w+(i-1)] = MAX(bl1, 0);
            dst[(j+1)*w+(i)]   = MAX(bc1, 0);
            dst[(j+1)*w+(i+1)] = MAX(br1, 0);
            dst[(j+2)*w+(i)]   = MAX(bc2, 0);

        }
    }
}

unsigned char * Halftoner::custom	(const unsigned char * src, unsigned char * dst, int w, int h, int ** customPattern, int customPatternW, int customPatternH) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (src[j*w+i]/(255/((customPatternW*customPatternH)+1)) > customPattern[j%customPatternW][i%customPatternH]) {
                dst[j*w+i]= 255;
            } else {
                dst[j*w+i]= 0;
            }
        }
    }
}


