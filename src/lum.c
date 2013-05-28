/*
** lum.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 04:06:32 2013 karina martynava
** Last update Tue May 28 22:59:31 2013 karina martynava
*/

#include <stdlib.h>
#include <math.h>
#include "rt.h"

float	lambert_coef(t_ptn *lightray, t_ptn *nrml, float coef_ref)
{
  float	lamb;
  float	dist;

  lamb = scal_prod(lightray, nrml);
  dist = sqrt(scal_prod(lightray, lightray)) * sqrt(scal_prod(nrml, nrml));
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
	  if (inter->d < 1 && inter->d > EPSILLON)
	    {
	      free(inter);
	      return (0);
	    }
	  else
	    free(inter);
	}
      ptn = ptn->next;
    }
  return (1);
}

void	blinn_phong(float lamber_coef, float coef_ref, t_ptn *lightdir, t_inter *last, t_st *st, float view_proj)
{
  float	light_proj;
  t_ptn	blinn;
  float	dist;
  float	coef_blinn;

  light_proj = lamber_coef / coef_ref;
  sub_vect(&blinn, lightdir, &(st->vec));
  dist = sqrt(scal_prod(&blinn, &blinn));
  if (dist != 0.0f)
    {
      coef_blinn = fmaxf(light_proj - view_proj, 0.0f) / dist;
      coef_blinn = pow(coef_blinn, last->obj->mat->spec_pow) * coef_ref;
    }
}

void	enligten(t_inter *point, float coef_ref, t_rs *rs, float col[3])
{
  t_lux	*sv;
  float	coef;
  t_st	light;
  t_ptn	*nrml;

  nrml = (*(point->cal_norm))(point->obj, &(point->ptn));
  sv = rs->lux;
  light.cord.x = point->ptn.x;
  light.cord.y = point->ptn.y;
  light.cord.z = point->ptn.z;
  while (sv != NULL)
    {
      light.vec.x = sv->cord.x - light.cord.x;
      light.vec.y = sv->cord.y - light.cord.y;
      light.vec.z = sv->cord.z - light.cord.z;
      /* if (inlight(rs, &light)) */
      /* 	{ */
      coef = lambert_coef(&(light.vec), nrml, coef_ref);
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
	  /* } */
	}
      sv = sv->next;
    }
  free(nrml);
}
