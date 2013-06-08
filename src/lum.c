/*
** lum.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 04:06:32 2013 karina martynava
** Last update Sat Jun  8 12:35:44 2013 karina martynava
*/

#include <stdlib.h>
#include <math.h>
#include "rt.h"

void	work_with_illumination(float col[4], t_inter *point, float lux[3])
{
  float	tab[3];

  if (point->obj->mat && col[3] > 0)
    {
      point->obj->cal_color(point->obj, point, tab);
      col[0] = col[0] + col[3] * lux[0] * tab[0];
      col[1] = col[1] + col[3] * lux[1] * tab[1];
      col[2] = col[2] + col[3] * lux[2] * tab[2];
    }
  else if (col[3] > 0)
    {
      col[0] = col[0] + col[3] * lux[0] * 1;
      col[1] = col[1] + col[3] * lux[1] * 1;
      col[2] = col[2] + col[3] * lux[2] * 1;
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
  float	coef;
  t_st	light;
  t_ptn	*nrml;
  float	lux[3];

  nrml = (*(point->cal_norm))(point->obj, &(point->ptn));
  sv = rs->lux;
  add_vect(&light.cord, &point->ptn, &st->cord);
  sub_vect(&light.cord, &light.cord, &st->cord);
  while (sv != NULL && init_lux(lux, sv))
    {
      create_light_vector(sv, &light);
      if (inlight(rs, &light, lux) || sv->attribute == AMB)
	{
	  coef = lambert_coef(&light.vec, nrml, sv->attribute) * sv->lux;
	  coef = (sv->attribute == SPOT) ? coef / SPOTLEN * \
	    (1 - (sqrt(scal_prod(&light.vec, &light.vec)))) : coef;
	  work_with_illumination(col, point, lux);
	  if (sv->attribute != AMB && point->obj->mat != NULL)
	    blinn_phong(st, &light.vec, point, col, sv);
	}
      sv = sv->next;
    }
  free(nrml);
}
