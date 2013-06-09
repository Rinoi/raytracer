/*
** lum.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 04:06:32 2013 karina martynava
** Last update Sun Jun  9 17:54:42 2013 karina martynava
*/

#include <stdlib.h>
#include <math.h>
#include "rt.h"
#include "lum.h"

void	work_with_illumination(float col[4], t_inter *point,
			       t_lum *l, t_rs *rs)
{
  float	tab[3];

  if (point->obj->mat && l->coef > 0)
    {
      point->obj->cal_color(point->obj, point, tab, rs);
      col[0] = col[0] + l->coef * l->lux[0] * tab[0];
      col[1] = col[1] + l->coef * l->lux[1] * tab[1];
      col[2] = col[2] + l->coef * l->lux[2] * tab[2];
    }
  else if (l->coef > 0)
    {
      col[0] = col[0] + l->coef * l->lux[0] * 1;
      col[1] = col[1] + l->coef * l->lux[1] * 1;
      col[2] = col[2] + l->coef * l->lux[2] * 1;
    }
}

void	create_light_vector(t_lux *sv, t_st *light)
{
  if (sv->attribute != DIRECT)
    sub_vect(&light->vec, &sv->cord, &light->cord);
  else
    {
      light->vec.x = sv->cord.x;
      light->vec.y = sv->cord.y;
      light->vec.z = sv->cord.z;
      light->cord.x = light->cord.y - light->vec.x * 1000;
      light->cord.y = light->cord.y - light->vec.y * 1000;
      light->cord.z = light->cord.z - light->vec.z * 1000;
    }
}

int	init_lux(float lux[3], t_lux *sv)
{
  lux[2] = sv->red;
  lux[1] = sv->green;
  lux[0] = sv->blue;
  return (1);
}

void	enligten(t_inter *point, t_rs *rs, float col[4], t_st *st)
{
  t_lux	*sv;
  t_st	light;
  t_ptn	*nrml;
  t_lum	l;

  nrml = (*(point->cal_norm))(point->obj, &(point->ptn));
  sv = rs->lux;
  light.cord = point->ptn;
  while (sv != NULL && init_lux(l.lux, sv))
    {
      create_light_vector(sv, &light);
      if (inlight(rs, &light, l.lux) || sv->attribute == AMB)
	{
	  l.coef = lambert_coef(&light.vec, nrml, sv->attribute) * sv->lux;
	  l.coef = (sv->attribute == SPOT) ? l.coef / SPOTLEN * \
	    (1 - (sqrt(scal_prod(&light.vec, &light.vec)))) : l.coef;
	  work_with_illumination(col, point, &l, rs);
	  if (sv->attribute != AMB && point->obj->mat != NULL)
	    blinn_phong(st, &light.vec, point, col, sv);
	}
      sv = sv->next;
    }
  free(nrml);
}
