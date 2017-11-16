/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * wconv1.c
 *
 * Code generation for function 'wconv1'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "song_conversion.h"
#include "wconv1.h"
#include "song_conversion_emxutil.h"
#include "eml_int_forloop_overflow_check.h"
#include "song_conversion_data.h"
#include "blas.h"

/* Variable Definitions */
static emlrtRTEInfo h_emlrtRTEI = { 1, /* lineNo */
  14,                                  /* colNo */
  "wconv1",                            /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/wconv1.m"/* pName */
};

/* Function Definitions */
void wconv1(const emlrtStack *sp, const emxArray_real_T *x, emxArray_real_T *y)
{
  int32_T cEnd1;
  int32_T ma;
  boolean_T overflow;
  int32_T iC;
  real_T BiB;
  int32_T i;
  int32_T firstRowA;
  int32_T b_i;
  int32_T a_length;
  int32_T cidx;
  int32_T r;
  ptrdiff_t n_t;
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack h_st;
  emlrtStack i_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &y_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  g_st.prev = &f_st;
  g_st.tls = f_st.tls;
  h_st.prev = &g_st;
  h_st.tls = g_st.tls;
  i_st.prev = &h_st;
  i_st.tls = h_st.tls;
  b_st.site = &ab_emlrtRSI;
  cEnd1 = y->size[0];
  y->size[0] = x->size[0] - 1;
  emxEnsureCapacity_real_T(&b_st, y, cEnd1, &h_emlrtRTEI);
  ma = x->size[0];
  for (cEnd1 = 0; cEnd1 <= ma - 2; cEnd1++) {
    y->data[cEnd1] = 0.0;
  }

  c_st.site = &bb_emlrtRSI;
  d_st.site = &gb_emlrtRSI;
  e_st.site = &cb_emlrtRSI;
  f_st.site = &db_emlrtRSI;
  g_st.site = &eb_emlrtRSI;
  overflow = ((!(1 > x->size[0])) && (x->size[0] > 2147483646));
  if (overflow) {
    h_st.site = &v_emlrtRSI;
    i_st.site = &v_emlrtRSI;
    check_forloop_overflow_error(&i_st);
  }

  cEnd1 = x->size[0];
  d_st.site = &fb_emlrtRSI;
  ma = x->size[0];
  iC = 0;
  BiB = 0.70710678118654757;
  for (i = 0; i < 2; i++) {
    firstRowA = (i < 1);
    if (i + ma <= cEnd1 - 1) {
      b_i = ma;
    } else {
      b_i = cEnd1 - i;
    }

    a_length = b_i - firstRowA;
    if (a_length >= 32) {
      e_st.site = &ib_emlrtRSI;
      f_st.site = &kb_emlrtRSI;
      f_st.site = &jb_emlrtRSI;
      n_t = (ptrdiff_t)a_length;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      daxpy(&n_t, &BiB, &x->data[firstRowA], &incx_t, &y->data[iC], &incy_t);
    } else {
      cidx = iC;
      e_st.site = &hb_emlrtRSI;
      for (r = 1; r <= a_length; r++) {
        y->data[cidx] += 0.70710678118654757 * x->data[firstRowA];
        firstRowA++;
        cidx++;
      }
    }

    if (i >= 1) {
      iC++;
    }
  }
}

/* End of code generation (wconv1.c) */
