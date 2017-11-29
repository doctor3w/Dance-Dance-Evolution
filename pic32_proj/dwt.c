/* wavelet/dwt.c
 *
 * Copyright (C) 2004 Ivo Alxneit
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

/* function dwt_step is based on the public domain function pwt.c
 * available from http://www.numerical-recipes.com
 */

//#include "config.h"
#include "gsl_errno.h"
#include "gsl_wavelet.h"
// #include <gsl/gsl_wavelet2d.h>

#define ELEMENT(a,stride,i) ((a)[(stride)*(i)])

static int binary_logn (const size_t n);
static void dwt_step (const gsl_wavelet * w, int *a, size_t stride, size_t n, gsl_wavelet_direction dir, gsl_wavelet_workspace * work);

static int
binary_logn (const size_t n)
{
  size_t ntest;
  size_t logn = 0;
  size_t k = 1;

  while (k < n)
  {
    k *= 2;
    logn++;
  }

  ntest = ((size_t)1 << logn);

  if (n != ntest)
  {
    return -1;                /* n is not a power of 2 */
  }

  return logn;
}

static void
dwt_step (const gsl_wavelet * w, int *a, size_t stride, size_t n,
          gsl_wavelet_direction dir, gsl_wavelet_workspace * work)
{
  int ai, ai1;
  size_t i, ii;
  size_t jf;
  size_t k;
  size_t n1, ni, nh, nmod;

  for (i = 0; i < work->n; i++)
  {
    work->scratch[i] = 0;
  }

  nmod = w->nc * n;
  nmod -= w->offset;            /* center support */

  n1 = n - 1;
  nh = n >> 1;

  if (dir == gsl_wavelet_forward)
  {
    for (ii = 0, i = 0; i < n; i += 2, ii++)
    {
      double h = 0, g = 0;

      ni = i + nmod;

      for (k = 0; k < w->nc; k++)
      {
        jf = n1 & (ni + k);
        h += w->h1[k] * (double)ELEMENT (a, stride, jf);
        g += w->g1[k] * (double)ELEMENT (a, stride, jf);
      }

      work->scratch[ii] += (int)h;
      work->scratch[ii + nh] += (int)g;
    }
  }
  else
  {
    for (ii = 0, i = 0; i < n; i += 2, ii++)
    {
      ai = ELEMENT (a, stride, ii);
      ai1 = ELEMENT (a, stride, ii + nh);
      ni = i + nmod;
      for (k = 0; k < w->nc; k++)
        {
          jf = (n1 & (ni + k));
          work->scratch[jf] += (int)(w->h2[k] * (double)ai + w->g2[k] * (double)ai1);
        }
    }
  }

  for (i = 0; i < n; i++)
  {
    ELEMENT (a, stride, i) = work->scratch[i];
  }
}

int
gsl_wavelet_transform (const gsl_wavelet * w,
                       int *data, size_t stride, size_t n,
                       gsl_wavelet_direction dir,
                       gsl_wavelet_workspace * work)
{
  size_t i;

  if (work->n < n)
    {
      printf("Error\n");
      return GSL_EINVAL;
    }

  if (binary_logn (n) == -1)
    {
      printf("Error\n");
      return GSL_EINVAL;
    }

  if (n < 2)
    {
      return GSL_SUCCESS;
    }

  if (dir == gsl_wavelet_forward)
    {
      for (i = n; i >= 2; i >>= 1)
        {
          dwt_step (w, data, stride, i, dir, work);
        }
    }
  else
    {
      for (i = 2; i <= n; i <<= 1)
        {
          dwt_step (w, data, stride, i, dir, work);
        }
    }

  return GSL_SUCCESS;
}

int
gsl_wavelet_transform_forward (const gsl_wavelet * w,
                               int *data, size_t stride, size_t n,
                               gsl_wavelet_workspace * work)
{
  return gsl_wavelet_transform (w, data, stride, n, gsl_wavelet_forward, work);
}

int
gsl_wavelet_transform_inverse (const gsl_wavelet * w,
                               int *data, size_t stride, size_t n,
                               gsl_wavelet_workspace * work)
{
  return gsl_wavelet_transform (w, data, stride, n, gsl_wavelet_backward, work);
}


/* Leaving this out for now BJG */
#if 0
int
gsl_dwt_vector (const gsl_wavelet * w, gsl_vector *v, gsl_wavelet_direction
                dir, gsl_wavelet_workspace * work)
{
  return gsl_dwt (w, v->data, v->stride, v->size, dir, work);
}
#endif
