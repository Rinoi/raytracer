/*
** lum.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 04:06:32 2013 karina martynava
** Last update Wed May 29 20:40:45 2013 karina martynava
*/

#include <stdlib.h>
#include <math.h>
#include "rt.h"

float	lambert_coef(t_ptn *lightray, t_ptn *nrml, float coef_ref, char attribute)
{
  float	lamb;
  float	dist;

  if (attribute == AMB)
    return (1);
  lamb = scal_prod(lightray, nrml);
  dist = sqrt(scal_prod(lightray, lightray)) *
    sqrt(scal_prod(nrml, nrml));
  if (dist != 0)
    lamb = lamb / dist;
  else 
    lamb = -1.0f;
  return (lamb * coef_ref);
}

int	inlight(t_rs *rs, t_st *droit)
{
  t_obj		*ptn;
  t_inter	*inter;

  ptn = rs->obj;
  while (ptn != NULL)
    {
      inter = ptn->cal_inter(ptn, *droit);
      if (inter != NULL)
	{
	  if (inter->d < 1)
	    {
	      free(inter);
	      return (1);
	    }
	  else
	    free(inter);
	}
      ptn = ptn->next;
    }
  return (1);
}

/* void	blinn_phong(float lamber_coef, t_ptn *lightdir, */
/* 		    t_inter *last, t_st *st) */
/* { */
/*   float	light_proj; */
/*   t_ptn	blinn; */
/*   float	dist; */
/*   float	coef_blinn; */

/*   view_proj = lamber_coef / coef_ref; */
/*   sub_vect(&blinn, lightdir, &(st->vec)); */
/*   dist = sqrt(scal_prod(&blinn, &blinn)); */
/*   if (dist != 0.0f) */
/*     { */
/*       coef_blinn = fmaxf(light_proj - view_proj, 0.0f) / dist; */
/*       coef_blinn = pow(coef_blinn, last->obj->mat->spec_pow) * coef_ref; */
/*     } */
/* } */

void	work_with_illumination(t_lux *sv, float col[3], t_inter *point, float coef)
{
  if (point->obj->mat && coef > 0)
    {
      col[0] = col[0] + coef * sv->red * point->obj->mat->red;
      col[1] = col[1] + coef * sv->green * point->obj->mat->green;
      col[2] = col[2] + coef * sv->blue * point->obj->mat->blue;
    }
  else if (coef > 0)
    {
      col[0] = col[0] + coef * sv->red * 1;
      col[1] = col[1] + coef * sv->green * 1;
      col[2] = col[2] + coef * sv->blue * 1;
    }
}

void	enligten(t_inter *point, t_rs *rs, float col[4], t_st *st)
{
  t_lux	*sv;
  float	coef;
  t_st	light;
  t_ptn	*nrml;
  t_ptn	*mat;

  nrml = (*(point->cal_norm))(point->obj, &(point->rela_ptn));
  sv = rs->lux;
  add_vect(&light.cord, &point->rela_ptn, &st->cord);
  mat = mul_m_p(point->obj->matrix, &light.cord);
  light.cord = *mat;
  sub_vect(&light.cord, &light.cord, &st->cord);
  free(mat);
  while (sv != NULL)
    {
      sub_vect(&light.vec, &sv->cord, &light.cord);
      if (inlight(rs, &light) || sv->attribute == AMB)
	{
	  coef = lambert_coef(&light.vec, nrml, col[3], sv->attribute)
	    * sv->lux;
	  work_with_illumination(sv, col, point, coef);
	}
      sv = sv->next;
    }
  free(nrml);
}
