/*
** lum.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 04:06:32 2013 karina martynava
** Last update Tue May 28 06:22:26 2013 lucas mayol
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

void	enligten(t_inter *point, float coef_ref, t_rs *rs)
{
  t_lux	*sv;
  float	lambert;
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
	  lambert = lambert_coef(&(light.vec), nrml, coef_ref);
	  printf("%f\n", lambert);
	}
      sv = sv->next;
    }
  free(nrml);
}
