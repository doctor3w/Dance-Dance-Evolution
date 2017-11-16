/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * detcoef.c
 *
 * Code generation for function 'detcoef'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "song_conversion.h"
#include "detcoef.h"
#include "song_conversion_emxutil.h"
#include "indexShapeCheck.h"

/* Variable Definitions */
static emlrtRSInfo mb_emlrtRSI = { 16, /* lineNo */
  "detcoef",                           /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/detcoef.m"/* pathName */
};

static emlrtRSInfo nb_emlrtRSI = { 41, /* lineNo */
  "detcoef",                           /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/detcoef.m"/* pathName */
};

static emlrtRSInfo ob_emlrtRSI = { 45, /* lineNo */
  "detcoef",                           /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/detcoef.m"/* pathName */
};

static emlrtRTEInfo i_emlrtRTEI = { 1, /* lineNo */
  22,                                  /* colNo */
  "detcoef",                           /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/detcoef.m"/* pName */
};

static emlrtBCInfo h_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  45,                                  /* lineNo */
  26,                                  /* colNo */
  "",                                  /* aName */
  "detcoef",                           /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/detcoef.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo i_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  45,                                  /* lineNo */
  35,                                  /* colNo */
  "",                                  /* aName */
  "detcoef",                           /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/detcoef.m",/* pName */
  0                                    /* checkKind */
};

static emlrtRTEInfo o_emlrtRTEI = { 87,/* lineNo */
  23,                                  /* colNo */
  "detcoef",                           /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/detcoef.m"/* pName */
};

/* Function Definitions */
void detcoef(const emlrtStack *sp, const emxArray_real_T *coefs, const real_T
             longs[13], emxArray_real_T *varargout_1, emxArray_real_T
             *varargout_2, emxArray_real_T *varargout_3, emxArray_real_T
             *varargout_4, emxArray_real_T *varargout_5, emxArray_real_T
             *varargout_6, emxArray_real_T *varargout_7, emxArray_real_T
             *varargout_8, emxArray_real_T *varargout_9, emxArray_real_T
             *varargout_10, emxArray_real_T *varargout_11)
{
  int32_T i;
  int32_T first[11];
  int32_T last[11];
  boolean_T b1;
  int32_T i0;
  int32_T i1;
  int32_T iv1[2];
  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &mb_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  for (i = 0; i < 11; i++) {
    first[i] = 0;
    last[i] = 0;
  }

  first[10] = (int32_T)longs[0] + 1;
  last[10] = (int32_T)longs[0] + (int32_T)longs[1];
  for (i = 9; i >= 0; i--) {
    first[i] = first[i + 1] + (int32_T)longs[10 - i];
    last[i] = (first[i] + (int32_T)longs[11 - i]) - 1;
  }

  b_st.site = &nb_emlrtRSI;
  if ((first[10] >= (int32_T)muDoubleScalarMin(coefs->size[0], 1.0)) && (last[0]
       <= coefs->size[0])) {
    b1 = true;
  } else {
    b1 = false;
  }

  if (!b1) {
    emlrtErrorWithMessageIdR2012b(&b_st, &o_emlrtRTEI, "MATLAB:badsubscript", 0);
  }

  if (first[0] > last[0]) {
    i0 = 1;
    i1 = 1;
  } else {
    i0 = coefs->size[0];
    if (!((first[0] >= 1) && (first[0] <= i0))) {
      emlrtDynamicBoundsCheckR2012b(first[0], 1, i0, &h_emlrtBCI, &st);
    }

    i0 = first[0];
    i1 = coefs->size[0];
    if (!((last[0] >= 1) && (last[0] <= i1))) {
      emlrtDynamicBoundsCheckR2012b(last[0], 1, i1, &i_emlrtBCI, &st);
    }

    i1 = last[0] + 1;
  }

  iv1[0] = 1;
  iv1[1] = i1 - i0;
  b_st.site = &ob_emlrtRSI;
  indexShapeCheck(&b_st, coefs->size[0], iv1);
  i = varargout_1->size[0];
  varargout_1->size[0] = i1 - i0;
  emxEnsureCapacity_real_T(&st, varargout_1, i, &i_emlrtRTEI);
  i = i1 - i0;
  for (i1 = 0; i1 < i; i1++) {
    varargout_1->data[i1] = coefs->data[(i0 + i1) - 1];
  }

  if (first[1] > last[1]) {
    i0 = 1;
    i1 = 1;
  } else {
    i0 = coefs->size[0];
    if (!((first[1] >= 1) && (first[1] <= i0))) {
      emlrtDynamicBoundsCheckR2012b(first[1], 1, i0, &h_emlrtBCI, &st);
    }

    i0 = first[1];
    i1 = coefs->size[0];
    if (!((last[1] >= 1) && (last[1] <= i1))) {
      emlrtDynamicBoundsCheckR2012b(last[1], 1, i1, &i_emlrtBCI, &st);
    }

    i1 = last[1] + 1;
  }

  iv1[0] = 1;
  iv1[1] = i1 - i0;
  b_st.site = &ob_emlrtRSI;
  indexShapeCheck(&b_st, coefs->size[0], iv1);
  i = varargout_2->size[0];
  varargout_2->size[0] = i1 - i0;
  emxEnsureCapacity_real_T(&st, varargout_2, i, &i_emlrtRTEI);
  i = i1 - i0;
  for (i1 = 0; i1 < i; i1++) {
    varargout_2->data[i1] = coefs->data[(i0 + i1) - 1];
  }

  if (first[2] > last[2]) {
    i0 = 1;
    i1 = 1;
  } else {
    i0 = coefs->size[0];
    if (!((first[2] >= 1) && (first[2] <= i0))) {
      emlrtDynamicBoundsCheckR2012b(first[2], 1, i0, &h_emlrtBCI, &st);
    }

    i0 = first[2];
    i1 = coefs->size[0];
    if (!((last[2] >= 1) && (last[2] <= i1))) {
      emlrtDynamicBoundsCheckR2012b(last[2], 1, i1, &i_emlrtBCI, &st);
    }

    i1 = last[2] + 1;
  }

  iv1[0] = 1;
  iv1[1] = i1 - i0;
  b_st.site = &ob_emlrtRSI;
  indexShapeCheck(&b_st, coefs->size[0], iv1);
  i = varargout_3->size[0];
  varargout_3->size[0] = i1 - i0;
  emxEnsureCapacity_real_T(&st, varargout_3, i, &i_emlrtRTEI);
  i = i1 - i0;
  for (i1 = 0; i1 < i; i1++) {
    varargout_3->data[i1] = coefs->data[(i0 + i1) - 1];
  }

  if (first[3] > last[3]) {
    i0 = 1;
    i1 = 1;
  } else {
    i0 = coefs->size[0];
    if (!((first[3] >= 1) && (first[3] <= i0))) {
      emlrtDynamicBoundsCheckR2012b(first[3], 1, i0, &h_emlrtBCI, &st);
    }

    i0 = first[3];
    i1 = coefs->size[0];
    if (!((last[3] >= 1) && (last[3] <= i1))) {
      emlrtDynamicBoundsCheckR2012b(last[3], 1, i1, &i_emlrtBCI, &st);
    }

    i1 = last[3] + 1;
  }

  iv1[0] = 1;
  iv1[1] = i1 - i0;
  b_st.site = &ob_emlrtRSI;
  indexShapeCheck(&b_st, coefs->size[0], iv1);
  i = varargout_4->size[0];
  varargout_4->size[0] = i1 - i0;
  emxEnsureCapacity_real_T(&st, varargout_4, i, &i_emlrtRTEI);
  i = i1 - i0;
  for (i1 = 0; i1 < i; i1++) {
    varargout_4->data[i1] = coefs->data[(i0 + i1) - 1];
  }

  if (first[4] > last[4]) {
    i0 = 1;
    i1 = 1;
  } else {
    i0 = coefs->size[0];
    if (!((first[4] >= 1) && (first[4] <= i0))) {
      emlrtDynamicBoundsCheckR2012b(first[4], 1, i0, &h_emlrtBCI, &st);
    }

    i0 = first[4];
    i1 = coefs->size[0];
    if (!((last[4] >= 1) && (last[4] <= i1))) {
      emlrtDynamicBoundsCheckR2012b(last[4], 1, i1, &i_emlrtBCI, &st);
    }

    i1 = last[4] + 1;
  }

  iv1[0] = 1;
  iv1[1] = i1 - i0;
  b_st.site = &ob_emlrtRSI;
  indexShapeCheck(&b_st, coefs->size[0], iv1);
  i = varargout_5->size[0];
  varargout_5->size[0] = i1 - i0;
  emxEnsureCapacity_real_T(&st, varargout_5, i, &i_emlrtRTEI);
  i = i1 - i0;
  for (i1 = 0; i1 < i; i1++) {
    varargout_5->data[i1] = coefs->data[(i0 + i1) - 1];
  }

  if (first[5] > last[5]) {
    i0 = 1;
    i1 = 1;
  } else {
    i0 = coefs->size[0];
    if (!((first[5] >= 1) && (first[5] <= i0))) {
      emlrtDynamicBoundsCheckR2012b(first[5], 1, i0, &h_emlrtBCI, &st);
    }

    i0 = first[5];
    i1 = coefs->size[0];
    if (!((last[5] >= 1) && (last[5] <= i1))) {
      emlrtDynamicBoundsCheckR2012b(last[5], 1, i1, &i_emlrtBCI, &st);
    }

    i1 = last[5] + 1;
  }

  iv1[0] = 1;
  iv1[1] = i1 - i0;
  b_st.site = &ob_emlrtRSI;
  indexShapeCheck(&b_st, coefs->size[0], iv1);
  i = varargout_6->size[0];
  varargout_6->size[0] = i1 - i0;
  emxEnsureCapacity_real_T(&st, varargout_6, i, &i_emlrtRTEI);
  i = i1 - i0;
  for (i1 = 0; i1 < i; i1++) {
    varargout_6->data[i1] = coefs->data[(i0 + i1) - 1];
  }

  if (first[6] > last[6]) {
    i0 = 1;
    i1 = 1;
  } else {
    i0 = coefs->size[0];
    if (!((first[6] >= 1) && (first[6] <= i0))) {
      emlrtDynamicBoundsCheckR2012b(first[6], 1, i0, &h_emlrtBCI, &st);
    }

    i0 = first[6];
    i1 = coefs->size[0];
    if (!((last[6] >= 1) && (last[6] <= i1))) {
      emlrtDynamicBoundsCheckR2012b(last[6], 1, i1, &i_emlrtBCI, &st);
    }

    i1 = last[6] + 1;
  }

  iv1[0] = 1;
  iv1[1] = i1 - i0;
  b_st.site = &ob_emlrtRSI;
  indexShapeCheck(&b_st, coefs->size[0], iv1);
  i = varargout_7->size[0];
  varargout_7->size[0] = i1 - i0;
  emxEnsureCapacity_real_T(&st, varargout_7, i, &i_emlrtRTEI);
  i = i1 - i0;
  for (i1 = 0; i1 < i; i1++) {
    varargout_7->data[i1] = coefs->data[(i0 + i1) - 1];
  }

  if (first[7] > last[7]) {
    i0 = 1;
    i1 = 1;
  } else {
    i0 = coefs->size[0];
    if (!((first[7] >= 1) && (first[7] <= i0))) {
      emlrtDynamicBoundsCheckR2012b(first[7], 1, i0, &h_emlrtBCI, &st);
    }

    i0 = first[7];
    i1 = coefs->size[0];
    if (!((last[7] >= 1) && (last[7] <= i1))) {
      emlrtDynamicBoundsCheckR2012b(last[7], 1, i1, &i_emlrtBCI, &st);
    }

    i1 = last[7] + 1;
  }

  iv1[0] = 1;
  iv1[1] = i1 - i0;
  b_st.site = &ob_emlrtRSI;
  indexShapeCheck(&b_st, coefs->size[0], iv1);
  i = varargout_8->size[0];
  varargout_8->size[0] = i1 - i0;
  emxEnsureCapacity_real_T(&st, varargout_8, i, &i_emlrtRTEI);
  i = i1 - i0;
  for (i1 = 0; i1 < i; i1++) {
    varargout_8->data[i1] = coefs->data[(i0 + i1) - 1];
  }

  if (first[8] > last[8]) {
    i0 = 1;
    i1 = 1;
  } else {
    i0 = coefs->size[0];
    if (!((first[8] >= 1) && (first[8] <= i0))) {
      emlrtDynamicBoundsCheckR2012b(first[8], 1, i0, &h_emlrtBCI, &st);
    }

    i0 = first[8];
    i1 = coefs->size[0];
    if (!((last[8] >= 1) && (last[8] <= i1))) {
      emlrtDynamicBoundsCheckR2012b(last[8], 1, i1, &i_emlrtBCI, &st);
    }

    i1 = last[8] + 1;
  }

  iv1[0] = 1;
  iv1[1] = i1 - i0;
  b_st.site = &ob_emlrtRSI;
  indexShapeCheck(&b_st, coefs->size[0], iv1);
  i = varargout_9->size[0];
  varargout_9->size[0] = i1 - i0;
  emxEnsureCapacity_real_T(&st, varargout_9, i, &i_emlrtRTEI);
  i = i1 - i0;
  for (i1 = 0; i1 < i; i1++) {
    varargout_9->data[i1] = coefs->data[(i0 + i1) - 1];
  }

  if (first[9] > last[9]) {
    i0 = 1;
    i1 = 1;
  } else {
    i0 = coefs->size[0];
    if (!((first[9] >= 1) && (first[9] <= i0))) {
      emlrtDynamicBoundsCheckR2012b(first[9], 1, i0, &h_emlrtBCI, &st);
    }

    i0 = first[9];
    i1 = coefs->size[0];
    if (!((last[9] >= 1) && (last[9] <= i1))) {
      emlrtDynamicBoundsCheckR2012b(last[9], 1, i1, &i_emlrtBCI, &st);
    }

    i1 = last[9] + 1;
  }

  iv1[0] = 1;
  iv1[1] = i1 - i0;
  b_st.site = &ob_emlrtRSI;
  indexShapeCheck(&b_st, coefs->size[0], iv1);
  i = varargout_10->size[0];
  varargout_10->size[0] = i1 - i0;
  emxEnsureCapacity_real_T(&st, varargout_10, i, &i_emlrtRTEI);
  i = i1 - i0;
  for (i1 = 0; i1 < i; i1++) {
    varargout_10->data[i1] = coefs->data[(i0 + i1) - 1];
  }

  if (first[10] > last[10]) {
    i0 = 1;
    i1 = 1;
  } else {
    i0 = coefs->size[0];
    if (!((first[10] >= 1) && (first[10] <= i0))) {
      emlrtDynamicBoundsCheckR2012b(first[10], 1, i0, &h_emlrtBCI, &st);
    }

    i0 = first[10];
    i1 = coefs->size[0];
    if (!((last[10] >= 1) && (last[10] <= i1))) {
      emlrtDynamicBoundsCheckR2012b(last[10], 1, i1, &i_emlrtBCI, &st);
    }

    i1 = last[10] + 1;
  }

  iv1[0] = 1;
  iv1[1] = i1 - i0;
  b_st.site = &ob_emlrtRSI;
  indexShapeCheck(&b_st, coefs->size[0], iv1);
  i = varargout_11->size[0];
  varargout_11->size[0] = i1 - i0;
  emxEnsureCapacity_real_T(&st, varargout_11, i, &i_emlrtRTEI);
  i = i1 - i0;
  for (i1 = 0; i1 < i; i1++) {
    varargout_11->data[i1] = coefs->data[(i0 + i1) - 1];
  }
}

/* End of code generation (detcoef.c) */
