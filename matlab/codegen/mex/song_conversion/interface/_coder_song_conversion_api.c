/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_song_conversion_api.c
 *
 * Code generation for function '_coder_song_conversion_api'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "song_conversion.h"
#include "_coder_song_conversion_api.h"
#include "song_conversion_data.h"

/* Function Declarations */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[2200];
static const mxArray *b_emlrt_marshallOut(const real_T u[9]);
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[2200];
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *read1,
  const char_T *identifier))[2200];

/* Function Definitions */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[2200]
{
  real_T (*y)[2200];
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
  static const mxArray *b_emlrt_marshallOut(const real_T u[9])
{
  const mxArray *y;
  const mxArray *m1;
  static const int32_T iv3[2] = { 0, 0 };

  static const int32_T iv4[2] = { 1, 9 };

  y = NULL;
  m1 = emlrtCreateNumericArray(2, iv3, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m1, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m1, iv4, 2);
  emlrtAssign(&y, m1);
  return y;
}

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[2200]
{
  real_T (*ret)[2200];
  static const int32_T dims[1] = { 2200 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[2200])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *read1,
  const char_T *identifier))[2200]
{
  real_T (*y)[2200];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(read1), &thisId);
  emlrtDestroyArray(&read1);
  return y;
}

void song_conversion_api(const mxArray * const prhs[1], const mxArray *plhs[1])
{
  real_T (*b)[9];
  real_T (*read1)[2200];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  b = (real_T (*)[9])mxMalloc(sizeof(real_T [9]));

  /* Marshall function inputs */
  read1 = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "read1");

  /* Invoke the target function */
  song_conversion(&st, *read1, *b);

  /* Marshall function outputs */
  plhs[0] = b_emlrt_marshallOut(*b);
}

/* End of code generation (_coder_song_conversion_api.c) */
