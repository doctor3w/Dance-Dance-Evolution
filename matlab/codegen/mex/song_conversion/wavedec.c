/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * wavedec.c
 *
 * Code generation for function 'wavedec'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "song_conversion.h"
#include "wavedec.h"
#include "song_conversion_emxutil.h"
#include "dwt.h"

/* Variable Definitions */
static emlrtRSInfo l_emlrtRSI = { 42,  /* lineNo */
  "wavedec",                           /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/wavedec.m"/* pathName */
};

static emlrtRTEInfo b_emlrtRTEI = { 1, /* lineNo */
  18,                                  /* colNo */
  "wavedec",                           /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/wavedec.m"/* pName */
};

static emlrtRTEInfo c_emlrtRTEI = { 31,/* lineNo */
  5,                                   /* colNo */
  "wavedec",                           /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/wavedec.m"/* pName */
};

/* Function Definitions */
void wavedec(const emlrtStack *sp, const real_T x[2200], emxArray_real_T *c,
             real_T l[13])
{
  int32_T i;
  emxArray_real_T *xv;
  emxArray_real_T *d;
  emxArray_real_T *b_xv;
  int32_T k;
  int32_T loop_ub;
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);
  i = c->size[0];
  c->size[0] = 0;
  emxEnsureCapacity_real_T(sp, c, i, &b_emlrtRTEI);
  for (i = 0; i < 13; i++) {
    l[i] = 0.0;
  }

  emxInit_real_T(sp, &xv, 1, &c_emlrtRTEI, true);
  i = xv->size[0];
  xv->size[0] = 2200;
  emxEnsureCapacity_real_T(sp, xv, i, &b_emlrtRTEI);
  for (i = 0; i < 2200; i++) {
    xv->data[i] = x[i];
  }

  l[12] = 2200.0;
  emxInit_real_T(sp, &d, 1, &b_emlrtRTEI, true);
  emxInit_real_T(sp, &b_xv, 1, &b_emlrtRTEI, true);
  for (k = 0; k < 11; k++) {
    i = b_xv->size[0];
    b_xv->size[0] = xv->size[0];
    emxEnsureCapacity_real_T(sp, b_xv, i, &b_emlrtRTEI);
    loop_ub = xv->size[0];
    for (i = 0; i < loop_ub; i++) {
      b_xv->data[i] = xv->data[i];
    }

    st.site = &l_emlrtRSI;
    dwt(&st, b_xv, xv, d);
    i = b_xv->size[0];
    b_xv->size[0] = d->size[0] + c->size[0];
    emxEnsureCapacity_real_T(sp, b_xv, i, &b_emlrtRTEI);
    loop_ub = d->size[0];
    for (i = 0; i < loop_ub; i++) {
      b_xv->data[i] = d->data[i];
    }

    loop_ub = c->size[0];
    for (i = 0; i < loop_ub; i++) {
      b_xv->data[i + d->size[0]] = c->data[i];
    }

    i = c->size[0];
    c->size[0] = b_xv->size[0];
    emxEnsureCapacity_real_T(sp, c, i, &b_emlrtRTEI);
    loop_ub = b_xv->size[0];
    for (i = 0; i < loop_ub; i++) {
      c->data[i] = b_xv->data[i];
    }

    l[11 - k] = d->size[0];
  }

  emxFree_real_T(&d);
  i = b_xv->size[0];
  b_xv->size[0] = xv->size[0] + c->size[0];
  emxEnsureCapacity_real_T(sp, b_xv, i, &b_emlrtRTEI);
  loop_ub = xv->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_xv->data[i] = xv->data[i];
  }

  loop_ub = c->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_xv->data[i + xv->size[0]] = c->data[i];
  }

  i = c->size[0];
  c->size[0] = b_xv->size[0];
  emxEnsureCapacity_real_T(sp, c, i, &b_emlrtRTEI);
  loop_ub = b_xv->size[0];
  for (i = 0; i < loop_ub; i++) {
    c->data[i] = b_xv->data[i];
  }

  emxFree_real_T(&b_xv);
  l[0] = xv->size[0];
  emxFree_real_T(&xv);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (wavedec.c) */
