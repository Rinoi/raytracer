/*
** specular.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sat Jun  8 12:34:55 2013 karina martynava
** Last update Sat Jun  8 12:35:44 2013 karina martynava
*/

#include <stdlib.h>
#include <math.h>
#include "rt.h"

float	reflect_ptn(t_ptn *toref, t_inter *last, t_ptn *viewpoint)
{
  t_ptn	*nrml;
  float	scal;
  float	dist;
  float	omega;

  nrml = (*(last->cal_norm))(last->obj, &(last->ptn));
  mult_vect(nrml, 1.0f / sqrt(scal_prod(nrml, nrml)));
  mult_vect(toref, - 1.0f / sqrt(scal_prod(toref, toref)));
  scal = scal_prod(nrml, toref);
  scal = 2.0f * scal;
  toref->x = toref->x - scal * nrml->x;
  toref->y = toref->y - scal * nrml->y;
  toref->z = toref->z - scal * nrml->z;
  dist = - sqrt(scal_prod(viewpoint, viewpoint));
  free(nrml);
  if (dist != 0)
    {
      mult_vect(viewpoint, 1.0f / dist);
      omega = scal_prod(toref, viewpoint);
      omega = (omega < 0) ? 0 : omega;
      return (omega);
    }
  return (-1);
}

void	blinn_phong(t_st *st, t_ptn *light,
		    t_inter *last, float col[4], t_lux *sv)
{
  t_ptn	ref;
  t_ptn	viewpoint;
  float	omega;

  viewpoint = st->vec;
  ref = *light;
  omega = reflect_ptn(&ref, last, &viewpoint);
  if (omega >= 0)
    {
      omega = pow(omega, last->obj->mat->spec_pow) * sv->lux;
      col[0] += omega;
      col[1] += omega;
      col[2] += omega;
    }
}
