/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * dwt.h
 *
 * Code generation for function 'dwt'
 *
 */

#ifndef DWT_H
#define DWT_H

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
extern void dwt(const emlrtStack *sp, const emxArray_real_T *x, emxArray_real_T *
                a, emxArray_real_T *d);

#endif

/* End of code generation (dwt.h) */
