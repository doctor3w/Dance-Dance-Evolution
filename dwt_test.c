//dwt_test.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../header/wavelib.h"

double absmax(int *array, int N) {
        double max;
        int i;

        max = 0.0;
        for (i = 0; i < N; ++i) {
                if (fabs(array[i]) >= max) {
                        max = fabs(array[i]);
                }
        }

        return max;
}

int main() {
        wave_object obj;
        wt_object wt;
        double *inp,*out,*diff;
        int N, i,J;

        FILE *ifp;
        double temp[2048];
        int cd1[1024];
        int cd2[512];
        int cd3[256];
        int cd4[128];
        int cd5[64];
        int cd6[32];
        int cd7[16];
        int cd8[8];
        int cd9[4];
    int cd10[2];
        int app[2];

        char *name = "haar";
        obj = wave_init(name);// Initialize the wavelet

        ifp = fopen("signal1.txt", "r");
        i = 0;
        if (!ifp) {
                printf("Cannot Open File");
                exit(100);
        }
        while (!feof(ifp)) {
                fscanf(ifp, "%lf \n", &temp[i]);
                i++;
        }
        N = 2047;

        inp = (double*)malloc(sizeof(double)* N);
        //out = (double*)malloc(sizeof(double)* N);
        //diff = (double*)malloc(sizeof(double)* N);
        //wmean = mean(temp, N);

        for (i = 0; i < N; ++i) {
                inp[i] = temp[i];
                //printf("%g \n",inp[i]);
        }
        J = 10;

        wt = wt_init(obj, "dwt", N, J);// Initialize the wavelet transform object
        setDWTExtension(wt, "sym");// Options are "per" and "sym". Symmetric is the default option
        setWTConv(wt, "direct");
       
        dwt(wt, inp);// Perform DWT
        //DWT output can be accessed using wt->output vector. Use wt_summary to find out how to extract appx and detail coefficients
       
        for (i = 0; i < wt->outlength; ++i) {
                printf("%g ",wt->output[i]);
                if (i<2) app[i] = wt->output[i];
                else if (i<4) cd10[i-2] = wt->output[i];
                else if (i<8) cd9[i-4] = wt->output[i];
                else if (i<16) cd8[i-8] = wt->output[i];
                else if (i<32) cd7[i-16] = wt->output[i];
                else if (i<64) cd6[i-32] = wt->output[i];
                else if (i<128) cd5[i-64] = wt->output[i];
                else if (i<256) cd4[i-128] = wt->output[i];
                else if (i<512) cd3[i-256] = wt->output[i];
                // else if (i<1024) cd2[i-512] = wt->output[i];
                // else if (i<2048) cd1[i-1024] = wt->output[i];
        }

        if(absmax(cd3,256) >= 400) {
        	printf("cd3 beat \n");
        }
        if(absmax(cd4,128) >= 600) {
        	printf("cd4 beat \n");
        }
        if(absmax(cd5,64) >= 1000) {
        	printf("cd5 beat \n");
        }
        if(absmax(cd6,32) >= 1500) {
        	printf("cd6 beat \n");
        }
        if(absmax(cd7,16) >= 1500) {
        	printf("cd7 beat \n");
        }
        if(absmax(cd8,8) >= 1800) {
        	printf("cd8 beat \n");
        }
        if(absmax(cd9,4) >= 1800) {
        	printf("cd9 beat \n");
        }
        if(absmax(cd10,2) >= 750) {
        	printf("cd10 beat \n");
        }
       
        // // Test Reconstruction
        // for (i = 0; i < wt->siglength; ++i) {
        //         diff[i] = wt->output[i] - inp[i];
        // }
       
        // printf("\n MAX %g \n", absmax(diff, wt->siglength)); // If Reconstruction succeeded then the output should be a small value.
       
        wt_summary(wt);// Prints the full summary.
        wave_free(obj);
        wt_free(wt);

        free(inp);
        //free(out);
        //free(diff);
        return 0;
}
