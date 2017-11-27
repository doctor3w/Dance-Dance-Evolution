#include <stdio.h>
#include <math.h>
#include <gsl/gsl_sort.h>
#include <gsl/gsl_wavelet.h>

double absmax(double *array, int N) {
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

int
main (int data[2048])
{
  int i;
  int n = 2048;
  //double *data = malloc (n * sizeof (double));
  //double *abscoeff = malloc (n * sizeof (double));
  //size_t *p = malloc (n * sizeof (size_t));

  //FILE * f;
  gsl_wavelet *w;
  gsl_wavelet_workspace *work;

  w = gsl_wavelet_alloc (gsl_wavelet_daubechies, 4);
  work = gsl_wavelet_workspace_alloc (n);

  //f = fopen (argv[1], "r");
  //for (i = 0; i < n; i++)
  //  {
  //    fscanf (f, "%lg", &data[i]);
  //  }
  //fclose (f);

  gsl_wavelet_transform_forward (w, data, 1, n, work);

  for (i = 0; i < n; i++)
    {
      data[i] = fabs (data[i]);
    }

  double cd0[1];
  double cd1[2];
  double cd2[4];
  double cd3[8];
  double cd4[16];
  double cd5[32];
  double cd6[64];
  double cd7[128];
  double cd8[256];
  double cd9[512];
  double cd10[1024];

  for (i = 0; i < 2048; ++i) {
    printf("%f ",data[i]);
    if (i<2) cd0[0] = data[i];
    else if (i<4) cd1[i-2] = data[i];
    else if (i<8) cd2[i-4] = data[i];
    else if (i<16) cd3[i-8] = data[i];
    else if (i<32) cd4[i-16] = data[i];
    else if (i<64) cd5[i-32] = data[i];
    else if (i<128) cd6[i-64] = data[i];
    else if (i<256) cd7[i-128] = data[i];
    else if (i<512) cd8[i-256] = data[i];
    else if (i<1024) cd9[i-512] = data[i];
    else cd10[i-1024] = data[i];
  }

  if(absmax(cd8,256) >= 400) {
    printf("cd8 beat \n");
  }
  if(absmax(cd7,128) >= 600) {
    printf("cd7 beat \n");
  }
  if(absmax(cd6,64) >= 1000) {
    printf("cd6 beat \n");
  }
  if(absmax(cd5,32) >= 1500) {
    printf("cd5 beat \n");
  }
  if(absmax(cd4,16) >= 1500) {
    printf("cd4 beat \n");
  }
  if(absmax(cd3,8) >= 1800) {
    printf("cd3 beat \n");
  }
  if(absmax(cd2,4) >= 1800) {
    printf("cd2 beat \n");
  }
  if(absmax(cd1,2) >= 750) {
    printf("cd1 beat \n");
  }
  
  gsl_wavelet_free (w);
  gsl_wavelet_workspace_free (work);

  //free (data);
  //free (abscoeff);
  //free (p);
  return 0;
}