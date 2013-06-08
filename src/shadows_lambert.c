/*
** shadows_lambert.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sat Jun  8 12:28:18 2013 karina martynava
** Last update Sat Jun  8 12:29:44 2013 karina martynava
*/

#include <stdlib.h>
#include <math.h>
#include "rt.h"

float	lambert_coef(t_ptn *lightray, t_ptn *nrml, char attribute)
{
  float	lamb;
  float	dist;

  if (attribute == AMB)
    return (1);
  dist = sqrt(scal_prod(lightray, lightray)) * sqrt(scal_prod(nrml, nrml));
  if (dist != 0)
    lamb = scal_prod(lightray, nrml) / dist;
  else
    return (-1.0);
  return (lamb);
}

void	update_lux_col(float lux[3], t_obj *ptn)
{
  lux[2] = lux[2] * ptn->mat->red;
  lux[1] = lux[1] * ptn->mat->green;
  lux[0] = lux[0] * ptn->mat->blue;
}

int	inlight(t_rs *rs, t_st *droit, float lux[3])
{
  t_obj		*ptn;
  t_inter	*inter;

  ptn = rs->obj;
  call_obj_neg(droit, rs);
  while (ptn != NULL)
    {
      inter = ptn->cal_inter(ptn, *droit);
      if (inter != NULL && inter->d < 1 && inter->d > 0)
	{
	  if (inter->obj->mat == NULL ||
	      (inter->obj->mat && inter->obj->mat->reflex == 0 &&
	       inter->obj->mat->indice == 0))
	    {
	      free(inter);
	      return (0);
	    }
	  else if  (inter->obj->mat->reflex && inter->obj->mat->indice)
	    update_lux_col(lux, ptn);
	}
      free(inter);
      ptn = ptn->next;
    }
  return (1);
}
