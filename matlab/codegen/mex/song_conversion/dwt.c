/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * dwt.c
 *
 * Code generation for function 'dwt'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "song_conversion.h"
#include "dwt.h"
#include "song_conversion_emxutil.h"
#include "eml_int_forloop_overflow_check.h"
#include "indexShapeCheck.h"
#include "wconv1.h"
#include "song_conversion_data.h"
#include "blas.h"

/* Variable Definitions */
static emlrtRSInfo m_emlrtRSI = { 53,  /* lineNo */
  "dwt",                               /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/dwt.m"/* pathName */
};

static emlrtRSInfo n_emlrtRSI = { 56,  /* lineNo */
  "dwt",                               /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/dwt.m"/* pathName */
};

static emlrtRSInfo o_emlrtRSI = { 57,  /* lineNo */
  "dwt",                               /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/dwt.m"/* pathName */
};

static emlrtRSInfo p_emlrtRSI = { 60,  /* lineNo */
  "dwt",                               /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/dwt.m"/* pathName */
};

static emlrtRSInfo q_emlrtRSI = { 61,  /* lineNo */
  "dwt",                               /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/dwt.m"/* pathName */
};

static emlrtRSInfo r_emlrtRSI = { 33,  /* lineNo */
  "wextend",                           /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/wextend.m"/* pathName */
};

static emlrtRSInfo s_emlrtRSI = { 91,  /* lineNo */
  "wextend",                           /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/wextend.m"/* pathName */
};

static emlrtRSInfo t_emlrtRSI = { 98,  /* lineNo */
  "wextend",                           /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/wextend.m"/* pathName */
};

static emlrtRSInfo u_emlrtRSI = { 257, /* lineNo */
  "wextend",                           /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/wextend.m"/* pathName */
};

static emlrtRSInfo w_emlrtRSI = { 277, /* lineNo */
  "wextend",                           /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/wextend.m"/* pathName */
};

static emlrtRSInfo x_emlrtRSI = { 697, /* lineNo */
  "wextend",                           /* fcnName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/wextend.m"/* pathName */
};

static emlrtRTEInfo d_emlrtRTEI = { 1, /* lineNo */
  18,                                  /* colNo */
  "dwt",                               /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/dwt.m"/* pName */
};

static emlrtRTEInfo e_emlrtRTEI = { 53,/* lineNo */
  1,                                   /* colNo */
  "dwt",                               /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/dwt.m"/* pName */
};

static emlrtRTEInfo f_emlrtRTEI = { 56,/* lineNo */
  1,                                   /* colNo */
  "dwt",                               /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/dwt.m"/* pName */
};

static emlrtRTEInfo g_emlrtRTEI = { 277,/* lineNo */
  5,                                   /* colNo */
  "wextend",                           /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/wextend.m"/* pName */
};

static emlrtBCInfo emlrtBCI = { -1,    /* iFirst */
  -1,                                  /* iLast */
  61,                                  /* lineNo */
  15,                                  /* colNo */
  "",                                  /* aName */
  "dwt",                               /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/dwt.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo b_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  61,                                  /* lineNo */
  7,                                   /* colNo */
  "",                                  /* aName */
  "dwt",                               /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/dwt.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo c_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  57,                                  /* lineNo */
  15,                                  /* colNo */
  "",                                  /* aName */
  "dwt",                               /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/dwt.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo d_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  57,                                  /* lineNo */
  7,                                   /* colNo */
  "",                                  /* aName */
  "dwt",                               /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/dwt.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo e_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  721,                                 /* lineNo */
  15,                                  /* colNo */
  "",                                  /* aName */
  "wextend",                           /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/wextend.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo f_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  278,                                 /* lineNo */
  11,                                  /* colNo */
  "",                                  /* aName */
  "wextend",                           /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/wextend.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo g_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  698,                                 /* lineNo */
  7,                                   /* colNo */
  "",                                  /* aName */
  "wextend",                           /* fName */
  "/Applications/MATLAB_R2017b.app/toolbox/wavelet/eml/wextend.m",/* pName */
  0                                    /* checkKind */
};

/* Function Declarations */
static int32_T div_s32_floor(const emlrtStack *sp, int32_T numerator, int32_T
  denominator);

/* Function Definitions */
static int32_T div_s32_floor(const emlrtStack *sp, int32_T numerator, int32_T
  denominator)
{
  int32_T quotient;
  uint32_T absNumerator;
  uint32_T absDenominator;
  boolean_T quotientNeedsNegation;
  uint32_T tempAbsQuotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }

    emlrtDivisionByZeroErrorR2012b(NULL, sp);
  } else {
    if (numerator < 0) {
      absNumerator = ~(uint32_T)numerator + 1U;
    } else {
      absNumerator = (uint32_T)numerator;
    }

    if (denominator < 0) {
      absDenominator = ~(uint32_T)denominator + 1U;
    } else {
      absDenominator = (uint32_T)denominator;
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }

      quotient = -(int32_T)tempAbsQuotient;
    } else {
      quotient = (int32_T)tempAbsQuotient;
    }
  }

  return quotient;
}

void dwt(const emlrtStack *sp, const emxArray_real_T *x, emxArray_real_T *a,
         emxArray_real_T *d)
{
  emxArray_real_T *y;
  emxArray_int32_T *I;
  int32_T iB;
  int32_T ma;
  emxArray_real_T *z;
  boolean_T overflow;
  int32_T k;
  int32_T i;
  int32_T iv0[2];
  int32_T iC;
  boolean_T p;
  int32_T firstRowA;
  int32_T b_i;
  int32_T a_length;
  real_T BiB;
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
  emlrtStack j_st;
  st.prev = sp;
  st.tls = sp->tls;
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
  j_st.prev = &i_st;
  j_st.tls = i_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);
  st.site = &m_emlrtRSI;
  b_st.site = &r_emlrtRSI;
  emxInit_real_T(&b_st, &y, 1, &e_emlrtRTEI, true);
  if (x->size[0] == 0) {
    c_st.site = &s_emlrtRSI;
    d_st.site = &u_emlrtRSI;
    iB = y->size[0];
    y->size[0] = 2;
    emxEnsureCapacity_real_T(&b_st, y, iB, &d_emlrtRTEI);
    for (iB = 0; iB < 2; iB++) {
      y->data[iB] = 0.0;
    }
  } else {
    emxInit_int32_T(&b_st, &I, 2, &g_emlrtRTEI, true);
    c_st.site = &t_emlrtRSI;
    d_st.site = &w_emlrtRSI;
    iB = I->size[0] * I->size[1];
    I->size[0] = 1;
    I->size[1] = 2 + x->size[0];
    emxEnsureCapacity_int32_T(&d_st, I, iB, &d_emlrtRTEI);
    ma = 2 + x->size[0];
    for (iB = 0; iB < ma; iB++) {
      I->data[iB] = 0;
    }

    I->data[0] = 1;
    e_st.site = &x_emlrtRSI;
    overflow = (x->size[0] > 2147483646);
    if (overflow) {
      f_st.site = &v_emlrtRSI;
      g_st.site = &v_emlrtRSI;
      check_forloop_overflow_error(&g_st);
    }

    for (k = 1; k <= x->size[0]; k++) {
      iB = I->size[1];
      i = 1 + k;
      if (!((i >= 1) && (i <= iB))) {
        emlrtDynamicBoundsCheckR2012b(i, 1, iB, &g_emlrtBCI, &d_st);
      }

      I->data[i - 1] = k;
    }

    iB = I->size[1];
    i = x->size[0] + 2;
    if (!((i >= 1) && (i <= iB))) {
      emlrtDynamicBoundsCheckR2012b(i, 1, iB, &e_emlrtBCI, &d_st);
    }

    I->data[i - 1] = x->size[0];
    k = x->size[0];
    iB = y->size[0];
    y->size[0] = I->size[1];
    emxEnsureCapacity_real_T(&c_st, y, iB, &d_emlrtRTEI);
    ma = I->size[1];
    for (iB = 0; iB < ma; iB++) {
      i = I->data[I->size[0] * iB];
      if (!((i >= 1) && (i <= k))) {
        emlrtDynamicBoundsCheckR2012b(i, 1, k, &f_emlrtBCI, &c_st);
      }

      y->data[iB] = x->data[i - 1];
    }

    emxFree_int32_T(&I);
  }

  emxInit_real_T(&b_st, &z, 1, &f_emlrtRTEI, true);
  st.site = &n_emlrtRSI;
  wconv1(&st, y, z);
  if (2 > x->size[0] + 1) {
    iB = 1;
    i = 1;
    k = 0;
  } else {
    iB = z->size[0];
    if (!(2 <= iB)) {
      emlrtDynamicBoundsCheckR2012b(2, 1, iB, &d_emlrtBCI, sp);
    }

    iB = 2;
    i = 2;
    iC = z->size[0];
    k = x->size[0] + 1;
    if (!((k >= 1) && (k <= iC))) {
      emlrtDynamicBoundsCheckR2012b(k, 1, iC, &c_emlrtBCI, sp);
    }
  }

  iv0[0] = 1;
  iv0[1] = div_s32_floor(sp, k - iB, i) + 1;
  st.site = &o_emlrtRSI;
  indexShapeCheck(&st, z->size[0], iv0);
  iC = a->size[0];
  a->size[0] = div_s32_floor(sp, k - iB, i) + 1;
  emxEnsureCapacity_real_T(sp, a, iC, &d_emlrtRTEI);
  ma = div_s32_floor(sp, k - iB, i);
  for (iC = 0; iC <= ma; iC++) {
    a->data[iC] = z->data[(iB + i * iC) - 1];
  }

  st.site = &p_emlrtRSI;
  b_st.site = &y_emlrtRSI;
  c_st.site = &ab_emlrtRSI;
  iB = z->size[0];
  z->size[0] = y->size[0] - 1;
  emxEnsureCapacity_real_T(&c_st, z, iB, &d_emlrtRTEI);
  ma = y->size[0];
  for (iB = 0; iB <= ma - 2; iB++) {
    z->data[iB] = 0.0;
  }

  d_st.site = &bb_emlrtRSI;
  e_st.site = &gb_emlrtRSI;
  f_st.site = &cb_emlrtRSI;
  g_st.site = &db_emlrtRSI;
  p = true;
  h_st.site = &eb_emlrtRSI;
  overflow = ((!(1 > y->size[0])) && (y->size[0] > 2147483646));
  if (overflow) {
    i_st.site = &v_emlrtRSI;
    j_st.site = &v_emlrtRSI;
    check_forloop_overflow_error(&j_st);
  }

  for (k = 0; k + 1 <= y->size[0]; k++) {
    if (p && ((!muDoubleScalarIsInf(y->data[k])) && (!muDoubleScalarIsNaN
          (y->data[k])))) {
      p = true;
    } else {
      p = false;
    }
  }

  overflow = !p;
  k = y->size[0];
  e_st.site = &fb_emlrtRSI;
  ma = y->size[0];
  iC = 0;
  iB = 0;
  for (i = 0; i < 2; i++) {
    firstRowA = (i < 1);
    if (i + ma <= k - 1) {
      b_i = ma;
    } else {
      b_i = k - i;
    }

    a_length = b_i - firstRowA;
    BiB = -0.70710678118654757 + 1.4142135623730951 * (real_T)iB;
    if ((-0.70710678118654757 + 1.4142135623730951 * (real_T)iB == 0.0) &&
        overflow) {
      p = true;
    } else {
      p = false;
    }

    if ((!p) && (a_length >= 32)) {
      f_st.site = &ib_emlrtRSI;
      g_st.site = &kb_emlrtRSI;
      g_st.site = &jb_emlrtRSI;
      n_t = (ptrdiff_t)a_length;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      daxpy(&n_t, &BiB, &y->data[firstRowA], &incx_t, &z->data[iC], &incy_t);
    } else {
      cidx = iC;
      f_st.site = &hb_emlrtRSI;
      for (r = 1; r <= a_length; r++) {
        z->data[cidx] += BiB * y->data[firstRowA];
        firstRowA++;
        cidx++;
      }
    }

    iB++;
    if (i >= 1) {
      iC++;
    }
  }

  emxFree_real_T(&y);
  if (2 > x->size[0] + 1) {
    iB = 1;
    i = 1;
    k = 0;
  } else {
    iB = z->size[0];
    if (!(2 <= iB)) {
      emlrtDynamicBoundsCheckR2012b(2, 1, iB, &b_emlrtBCI, sp);
    }

    iB = 2;
    i = 2;
    iC = z->size[0];
    k = x->size[0] + 1;
    if (!((k >= 1) && (k <= iC))) {
      emlrtDynamicBoundsCheckR2012b(k, 1, iC, &emlrtBCI, sp);
    }
  }

  iv0[0] = 1;
  iv0[1] = div_s32_floor(sp, k - iB, i) + 1;
  st.site = &q_emlrtRSI;
  indexShapeCheck(&st, z->size[0], iv0);
  iC = d->size[0];
  d->size[0] = div_s32_floor(sp, k - iB, i) + 1;
  emxEnsureCapacity_real_T(sp, d, iC, &d_emlrtRTEI);
  ma = div_s32_floor(sp, k - iB, i);
  for (iC = 0; iC <= ma; iC++) {
    d->data[iC] = z->data[(iB + i * iC) - 1];
  }

  emxFree_real_T(&z);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (dwt.c) */
