/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * song_conversion.c
 *
 * Code generation for function 'song_conversion'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "song_conversion.h"
#include "song_conversion_emxutil.h"
#include "abs.h"
#include "detcoef.h"
#include "wavedec.h"

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = { 11,    /* lineNo */
  "song_conversion",                   /* fcnName */
  "/Users/drewsdunne/Documents/School/Semester5/ece4760/lab5/matlab/song_conversion.m"/* pathName */
};

static emlrtRSInfo b_emlrtRSI = { 12,  /* lineNo */
  "song_conversion",                   /* fcnName */
  "/Users/drewsdunne/Documents/School/Semester5/ece4760/lab5/matlab/song_conversion.m"/* pathName */
};

static emlrtRSInfo c_emlrtRSI = { 14,  /* lineNo */
  "song_conversion",                   /* fcnName */
  "/Users/drewsdunne/Documents/School/Semester5/ece4760/lab5/matlab/song_conversion.m"/* pathName */
};

static emlrtRSInfo d_emlrtRSI = { 17,  /* lineNo */
  "song_conversion",                   /* fcnName */
  "/Users/drewsdunne/Documents/School/Semester5/ece4760/lab5/matlab/song_conversion.m"/* pathName */
};

static emlrtRSInfo e_emlrtRSI = { 20,  /* lineNo */
  "song_conversion",                   /* fcnName */
  "/Users/drewsdunne/Documents/School/Semester5/ece4760/lab5/matlab/song_conversion.m"/* pathName */
};

static emlrtRSInfo f_emlrtRSI = { 23,  /* lineNo */
  "song_conversion",                   /* fcnName */
  "/Users/drewsdunne/Documents/School/Semester5/ece4760/lab5/matlab/song_conversion.m"/* pathName */
};

static emlrtRSInfo g_emlrtRSI = { 26,  /* lineNo */
  "song_conversion",                   /* fcnName */
  "/Users/drewsdunne/Documents/School/Semester5/ece4760/lab5/matlab/song_conversion.m"/* pathName */
};

static emlrtRSInfo h_emlrtRSI = { 29,  /* lineNo */
  "song_conversion",                   /* fcnName */
  "/Users/drewsdunne/Documents/School/Semester5/ece4760/lab5/matlab/song_conversion.m"/* pathName */
};

static emlrtRSInfo i_emlrtRSI = { 32,  /* lineNo */
  "song_conversion",                   /* fcnName */
  "/Users/drewsdunne/Documents/School/Semester5/ece4760/lab5/matlab/song_conversion.m"/* pathName */
};

static emlrtRSInfo j_emlrtRSI = { 35,  /* lineNo */
  "song_conversion",                   /* fcnName */
  "/Users/drewsdunne/Documents/School/Semester5/ece4760/lab5/matlab/song_conversion.m"/* pathName */
};

static emlrtRSInfo k_emlrtRSI = { 38,  /* lineNo */
  "song_conversion",                   /* fcnName */
  "/Users/drewsdunne/Documents/School/Semester5/ece4760/lab5/matlab/song_conversion.m"/* pathName */
};

static emlrtRSInfo rb_emlrtRSI = { 13, /* lineNo */
  "max",                               /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/eml/lib/matlab/datafun/max.m"/* pathName */
};

static emlrtRSInfo sb_emlrtRSI = { 19, /* lineNo */
  "minOrMax",                          /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/eml/eml/+coder/+internal/minOrMax.m"/* pathName */
};

static emlrtMCInfo emlrtMCI = { 42,    /* lineNo */
  1,                                   /* colNo */
  "song_conversion",                   /* fName */
  "/Users/drewsdunne/Documents/School/Semester5/ece4760/lab5/matlab/song_conversion.m"/* pName */
};

static emlrtRTEInfo emlrtRTEI = { 1,   /* lineNo */
  14,                                  /* colNo */
  "song_conversion",                   /* fName */
  "/Users/drewsdunne/Documents/School/Semester5/ece4760/lab5/matlab/song_conversion.m"/* pName */
};

static emlrtRTEInfo k_emlrtRTEI = { 39,/* lineNo */
  27,                                  /* colNo */
  "minOrMax",                          /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/eml/eml/+coder/+internal/minOrMax.m"/* pName */
};

static emlrtRTEInfo l_emlrtRTEI = { 121,/* lineNo */
  27,                                  /* colNo */
  "minOrMax",                          /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/eml/eml/+coder/+internal/minOrMax.m"/* pName */
};

static emlrtRSInfo tb_emlrtRSI = { 42, /* lineNo */
  "song_conversion",                   /* fcnName */
  "/Users/drewsdunne/Documents/School/Semester5/ece4760/lab5/matlab/song_conversion.m"/* pathName */
};

/* Function Declarations */
static void disp(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location);
static const mxArray *emlrt_marshallOut(const real_T u[9]);

/* Function Definitions */
static void disp(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location)
{
  const mxArray *pArray;
  pArray = b;
  emlrtCallMATLABR2012b(sp, 0, NULL, 1, &pArray, "disp", true, location);
}

static const mxArray *emlrt_marshallOut(const real_T u[9])
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv2[2] = { 1, 9 };

  real_T (*pData)[9];
  int32_T i;
  y = NULL;
  m0 = emlrtCreateNumericArray(2, iv2, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T (*)[9])emlrtMxGetPr(m0);
  for (i = 0; i < 9; i++) {
    (*pData)[i] = u[i];
  }

  emlrtAssign(&y, m0);
  return y;
}

void song_conversion(const emlrtStack *sp, const real_T read1[2200], real_T b[9])
{
  emxArray_real_T *C;
  emxArray_real_T *cd1;
  emxArray_real_T *cd2;
  emxArray_real_T *cd3;
  emxArray_real_T *cd4;
  emxArray_real_T *cd5;
  emxArray_real_T *cd6;
  emxArray_real_T *cd7;
  emxArray_real_T *cd8;
  emxArray_real_T *cd9;
  emxArray_real_T *cd10;
  emxArray_real_T *cd11;
  real_T L[13];
  boolean_T b0;
  int32_T ixstart;
  int32_T n;
  real_T mtmp;
  int32_T ix;
  boolean_T exitg1;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);

  /* read1 = audioread('trimmed.wav'); */
  /* read1 = read1(:,1); */
  /* read1 = downsample(read1,2); */
  /* read1 = round(read1*256); %256 bc 8 bit resolution */
  /* beat detections per second */
  /* segments = bdps*(length(read1)/22000); */
  memset(&b[0], 0, 9U * sizeof(real_T));
  emxInit_real_T(sp, &C, 1, &emlrtRTEI, true);
  emxInit_real_T(sp, &cd1, 1, &emlrtRTEI, true);
  emxInit_real_T(sp, &cd2, 1, &emlrtRTEI, true);
  emxInit_real_T(sp, &cd3, 1, &emlrtRTEI, true);
  emxInit_real_T(sp, &cd4, 1, &emlrtRTEI, true);
  emxInit_real_T(sp, &cd5, 1, &emlrtRTEI, true);
  emxInit_real_T(sp, &cd6, 1, &emlrtRTEI, true);
  emxInit_real_T(sp, &cd7, 1, &emlrtRTEI, true);
  emxInit_real_T(sp, &cd8, 1, &emlrtRTEI, true);
  emxInit_real_T(sp, &cd9, 1, &emlrtRTEI, true);
  emxInit_real_T(sp, &cd10, 1, &emlrtRTEI, true);
  emxInit_real_T(sp, &cd11, 1, &emlrtRTEI, true);
  st.site = &emlrtRSI;
  wavedec(&st, read1, C, L);
  st.site = &b_emlrtRSI;
  detcoef(&st, C, L, cd1, cd2, cd3, cd4, cd5, cd6, cd7, cd8, cd9, cd10, cd11);
  st.site = &c_emlrtRSI;
  b_abs(&st, cd3, C);
  st.site = &c_emlrtRSI;
  b_st.site = &rb_emlrtRSI;
  c_st.site = &sb_emlrtRSI;
  emxFree_real_T(&cd3);
  emxFree_real_T(&cd2);
  emxFree_real_T(&cd1);
  if ((C->size[0] == 1) || (C->size[0] != 1)) {
    b0 = true;
  } else {
    b0 = false;
  }

  if (!b0) {
    emlrtErrorWithMessageIdR2012b(&c_st, &k_emlrtRTEI,
      "Coder:toolbox:autoDimIncompatibility", 0);
  }

  if (!(C->size[0] > 0)) {
    emlrtErrorWithMessageIdR2012b(&c_st, &l_emlrtRTEI,
      "Coder:toolbox:eml_min_or_max_varDimZero", 0);
  }

  ixstart = 1;
  n = C->size[0];
  mtmp = C->data[0];
  if (C->size[0] > 1) {
    if (muDoubleScalarIsNaN(C->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        ixstart = ix;
        if (!muDoubleScalarIsNaN(C->data[ix - 1])) {
          mtmp = C->data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < C->size[0]) {
      while (ixstart + 1 <= n) {
        if (C->data[ixstart] > mtmp) {
          mtmp = C->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  if (mtmp >= 400.0) {
    b[0] = 1.0;
  }

  st.site = &d_emlrtRSI;
  b_abs(&st, cd4, C);
  st.site = &d_emlrtRSI;
  b_st.site = &rb_emlrtRSI;
  c_st.site = &sb_emlrtRSI;
  emxFree_real_T(&cd4);
  if ((C->size[0] == 1) || (C->size[0] != 1)) {
    b0 = true;
  } else {
    b0 = false;
  }

  if (!b0) {
    emlrtErrorWithMessageIdR2012b(&c_st, &k_emlrtRTEI,
      "Coder:toolbox:autoDimIncompatibility", 0);
  }

  if (!(C->size[0] > 0)) {
    emlrtErrorWithMessageIdR2012b(&c_st, &l_emlrtRTEI,
      "Coder:toolbox:eml_min_or_max_varDimZero", 0);
  }

  ixstart = 1;
  n = C->size[0];
  mtmp = C->data[0];
  if (C->size[0] > 1) {
    if (muDoubleScalarIsNaN(C->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        ixstart = ix;
        if (!muDoubleScalarIsNaN(C->data[ix - 1])) {
          mtmp = C->data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < C->size[0]) {
      while (ixstart + 1 <= n) {
        if (C->data[ixstart] > mtmp) {
          mtmp = C->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  if (mtmp >= 600.0) {
    b[1] = 1.0;
  }

  st.site = &e_emlrtRSI;
  b_abs(&st, cd5, C);
  st.site = &e_emlrtRSI;
  b_st.site = &rb_emlrtRSI;
  c_st.site = &sb_emlrtRSI;
  emxFree_real_T(&cd5);
  if ((C->size[0] == 1) || (C->size[0] != 1)) {
    b0 = true;
  } else {
    b0 = false;
  }

  if (!b0) {
    emlrtErrorWithMessageIdR2012b(&c_st, &k_emlrtRTEI,
      "Coder:toolbox:autoDimIncompatibility", 0);
  }

  if (!(C->size[0] > 0)) {
    emlrtErrorWithMessageIdR2012b(&c_st, &l_emlrtRTEI,
      "Coder:toolbox:eml_min_or_max_varDimZero", 0);
  }

  ixstart = 1;
  n = C->size[0];
  mtmp = C->data[0];
  if (C->size[0] > 1) {
    if (muDoubleScalarIsNaN(C->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        ixstart = ix;
        if (!muDoubleScalarIsNaN(C->data[ix - 1])) {
          mtmp = C->data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < C->size[0]) {
      while (ixstart + 1 <= n) {
        if (C->data[ixstart] > mtmp) {
          mtmp = C->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  if (mtmp >= 600.0) {
    b[2] = 1.0;
  }

  st.site = &f_emlrtRSI;
  b_abs(&st, cd6, C);
  st.site = &f_emlrtRSI;
  b_st.site = &rb_emlrtRSI;
  c_st.site = &sb_emlrtRSI;
  emxFree_real_T(&cd6);
  if ((C->size[0] == 1) || (C->size[0] != 1)) {
    b0 = true;
  } else {
    b0 = false;
  }

  if (!b0) {
    emlrtErrorWithMessageIdR2012b(&c_st, &k_emlrtRTEI,
      "Coder:toolbox:autoDimIncompatibility", 0);
  }

  if (!(C->size[0] > 0)) {
    emlrtErrorWithMessageIdR2012b(&c_st, &l_emlrtRTEI,
      "Coder:toolbox:eml_min_or_max_varDimZero", 0);
  }

  ixstart = 1;
  n = C->size[0];
  mtmp = C->data[0];
  if (C->size[0] > 1) {
    if (muDoubleScalarIsNaN(C->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        ixstart = ix;
        if (!muDoubleScalarIsNaN(C->data[ix - 1])) {
          mtmp = C->data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < C->size[0]) {
      while (ixstart + 1 <= n) {
        if (C->data[ixstart] > mtmp) {
          mtmp = C->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  if (mtmp >= 1000.0) {
    b[3] = 1.0;
  }

  st.site = &g_emlrtRSI;
  b_abs(&st, cd7, C);
  st.site = &g_emlrtRSI;
  b_st.site = &rb_emlrtRSI;
  c_st.site = &sb_emlrtRSI;
  emxFree_real_T(&cd7);
  if ((C->size[0] == 1) || (C->size[0] != 1)) {
    b0 = true;
  } else {
    b0 = false;
  }

  if (!b0) {
    emlrtErrorWithMessageIdR2012b(&c_st, &k_emlrtRTEI,
      "Coder:toolbox:autoDimIncompatibility", 0);
  }

  if (!(C->size[0] > 0)) {
    emlrtErrorWithMessageIdR2012b(&c_st, &l_emlrtRTEI,
      "Coder:toolbox:eml_min_or_max_varDimZero", 0);
  }

  ixstart = 1;
  n = C->size[0];
  mtmp = C->data[0];
  if (C->size[0] > 1) {
    if (muDoubleScalarIsNaN(C->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        ixstart = ix;
        if (!muDoubleScalarIsNaN(C->data[ix - 1])) {
          mtmp = C->data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < C->size[0]) {
      while (ixstart + 1 <= n) {
        if (C->data[ixstart] > mtmp) {
          mtmp = C->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  if (mtmp >= 1500.0) {
    b[4] = 1.0;
  }

  st.site = &h_emlrtRSI;
  b_abs(&st, cd8, C);
  st.site = &h_emlrtRSI;
  b_st.site = &rb_emlrtRSI;
  c_st.site = &sb_emlrtRSI;
  emxFree_real_T(&cd8);
  if ((C->size[0] == 1) || (C->size[0] != 1)) {
    b0 = true;
  } else {
    b0 = false;
  }

  if (!b0) {
    emlrtErrorWithMessageIdR2012b(&c_st, &k_emlrtRTEI,
      "Coder:toolbox:autoDimIncompatibility", 0);
  }

  if (!(C->size[0] > 0)) {
    emlrtErrorWithMessageIdR2012b(&c_st, &l_emlrtRTEI,
      "Coder:toolbox:eml_min_or_max_varDimZero", 0);
  }

  ixstart = 1;
  n = C->size[0];
  mtmp = C->data[0];
  if (C->size[0] > 1) {
    if (muDoubleScalarIsNaN(C->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        ixstart = ix;
        if (!muDoubleScalarIsNaN(C->data[ix - 1])) {
          mtmp = C->data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < C->size[0]) {
      while (ixstart + 1 <= n) {
        if (C->data[ixstart] > mtmp) {
          mtmp = C->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  if (mtmp >= 1800.0) {
    b[5] = 1.0;
  }

  st.site = &i_emlrtRSI;
  b_abs(&st, cd9, C);
  st.site = &i_emlrtRSI;
  b_st.site = &rb_emlrtRSI;
  c_st.site = &sb_emlrtRSI;
  emxFree_real_T(&cd9);
  if ((C->size[0] == 1) || (C->size[0] != 1)) {
    b0 = true;
  } else {
    b0 = false;
  }

  if (!b0) {
    emlrtErrorWithMessageIdR2012b(&c_st, &k_emlrtRTEI,
      "Coder:toolbox:autoDimIncompatibility", 0);
  }

  if (!(C->size[0] > 0)) {
    emlrtErrorWithMessageIdR2012b(&c_st, &l_emlrtRTEI,
      "Coder:toolbox:eml_min_or_max_varDimZero", 0);
  }

  ixstart = 1;
  n = C->size[0];
  mtmp = C->data[0];
  if (C->size[0] > 1) {
    if (muDoubleScalarIsNaN(C->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        ixstart = ix;
        if (!muDoubleScalarIsNaN(C->data[ix - 1])) {
          mtmp = C->data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < C->size[0]) {
      while (ixstart + 1 <= n) {
        if (C->data[ixstart] > mtmp) {
          mtmp = C->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  if (mtmp >= 1800.0) {
    b[6] = 1.0;
  }

  st.site = &j_emlrtRSI;
  b_abs(&st, cd10, C);
  st.site = &j_emlrtRSI;
  b_st.site = &rb_emlrtRSI;
  c_st.site = &sb_emlrtRSI;
  emxFree_real_T(&cd10);
  if ((C->size[0] == 1) || (C->size[0] != 1)) {
    b0 = true;
  } else {
    b0 = false;
  }

  if (!b0) {
    emlrtErrorWithMessageIdR2012b(&c_st, &k_emlrtRTEI,
      "Coder:toolbox:autoDimIncompatibility", 0);
  }

  if (!(C->size[0] > 0)) {
    emlrtErrorWithMessageIdR2012b(&c_st, &l_emlrtRTEI,
      "Coder:toolbox:eml_min_or_max_varDimZero", 0);
  }

  ixstart = 1;
  n = C->size[0];
  mtmp = C->data[0];
  if (C->size[0] > 1) {
    if (muDoubleScalarIsNaN(C->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        ixstart = ix;
        if (!muDoubleScalarIsNaN(C->data[ix - 1])) {
          mtmp = C->data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < C->size[0]) {
      while (ixstart + 1 <= n) {
        if (C->data[ixstart] > mtmp) {
          mtmp = C->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  if (mtmp >= 750.0) {
    b[7] = 1.0;
  }

  st.site = &k_emlrtRSI;
  b_abs(&st, cd11, C);
  st.site = &k_emlrtRSI;
  b_st.site = &rb_emlrtRSI;
  c_st.site = &sb_emlrtRSI;
  emxFree_real_T(&cd11);
  if ((C->size[0] == 1) || (C->size[0] != 1)) {
    b0 = true;
  } else {
    b0 = false;
  }

  if (!b0) {
    emlrtErrorWithMessageIdR2012b(&c_st, &k_emlrtRTEI,
      "Coder:toolbox:autoDimIncompatibility", 0);
  }

  if (!(C->size[0] > 0)) {
    emlrtErrorWithMessageIdR2012b(&c_st, &l_emlrtRTEI,
      "Coder:toolbox:eml_min_or_max_varDimZero", 0);
  }

  ixstart = 1;
  n = C->size[0];
  mtmp = C->data[0];
  if (C->size[0] > 1) {
    if (muDoubleScalarIsNaN(C->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        ixstart = ix;
        if (!muDoubleScalarIsNaN(C->data[ix - 1])) {
          mtmp = C->data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < C->size[0]) {
      while (ixstart + 1 <= n) {
        if (C->data[ixstart] > mtmp) {
          mtmp = C->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  emxFree_real_T(&C);
  if (mtmp >= 750.0) {
    b[8] = 1.0;
  }

  /* fprintf('at time %5.2f\n', (1/bdps)*i) */
  st.site = &tb_emlrtRSI;
  disp(&st, emlrt_marshallOut(b), &emlrtMCI);
  memset(&b[0], 0, 9U * sizeof(real_T));
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (song_conversion.c) */
