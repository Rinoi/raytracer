/*
** lum.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 04:06:32 2013 karina martynava
** Last update Tue May 28 08:07:28 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

float	lambert_coef(t_ptn *lightray, t_ptn *nrml, float coef_ref)
{
  float	lamb;

  lamb = scal_prod(lightray, nrml) * coef_ref;
  return (lamb);
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
	  if (inter->d < 1 && inter->d > 0)
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

#include <stdio.h>

void	enligten(t_inter *point, float coef_ref, t_rs *rs, float col[3])
{
  t_lux	*sv;
  float	coef;
  t_st	light;
  t_ptn	*nrml;

  nrml = (*(point->cal_norm))(point->obj, &(point->ptn));
  sv = rs->lux;
  light.cord = point->ptn;
  while (sv != NULL)
    {
      light.vec.x = sv->cord.x - light.cord.x;
      light.vec.y = sv->cord.y - light.cord.y;
      light.vec.z = sv->cord.z - light.cord.z;
      if (inlight(rs, &light))
	{
	  coef = lambert_coef(&(light.vec), nrml, coef_ref);
	  if (point->obj->mat)
	    {
	      col[0] = col[0] + coef * sv->red * point->obj->mat->red;
	      col[1] = col[1] + coef * sv->green * point->obj->mat->green;
	      col[2] = col[2] + coef * sv->blue * point->obj->mat->blue;
	    }
	  else
	    {
	      col[0] = col[0] + coef * sv->red * 0.5;
	      col[1] = col[1] + coef * sv->green * 0.5;
	      col[2] = col[2] + coef * sv->blue * 0.5;
	    }
	}
      sv = sv->next;
    }
  free(nrml);
}
