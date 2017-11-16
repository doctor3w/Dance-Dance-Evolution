/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * wavedec.h
 *
 * Code generation for function 'wavedec'
 *
 */

#ifndef WAVEDEC_H
#define WAVEDEC_H

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mwmathutil.h"
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "rtwtypes.h"
#include "song_conversion_types.h"

/* Function Declarations */
extern void wavedec(const emlrtStack *sp, const real_T x[2200], emxArray_real_T *
                    c, real_T l[13]);

#endif

/* End of code generation (wavedec.h) */
