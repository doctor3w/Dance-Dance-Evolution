/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * song_conversion.h
 *
 * Code generation for function 'song_conversion'
 *
 */

#ifndef SONG_CONVERSION_H
#define SONG_CONVERSION_H

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
extern void song_conversion(const emlrtStack *sp, const real_T read1[2200],
  real_T b[9]);

#endif

/* End of code generation (song_conversion.h) */
