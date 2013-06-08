/*
** lum.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 04:06:32 2013 karina martynava
** Last update Sat Jun  8 04:14:46 2013 karina martynava
*/

#include <stdlib.h>
#include <math.h>
#include "rt.h"

void	mult_vect(t_ptn *a, float k);

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

int	inlight(t_rs *rs, t_st *droit, float lux[3])
{
  t_obj		*ptn;
  t_inter	*inter;

  ptn = rs->obj;
  call_obj_neg(droit, rs);
  while (ptn != NULL)
    {
      inter = ptn->cal_inter(ptn, *droit);
      if (inter != NULL)
	{
	  if (inter->d < 1 && inter->d > 0)
	    {
	      if (inter->obj->mat == NULL ||
		  (inter->obj->mat && inter->obj->mat->reflex == 0 &&
		   inter->obj->mat->indice == 0))
		{
		  free(inter);
		  return (0);
		}
	      else if  (inter->obj->mat->reflex && inter->obj->mat->indice)
	      	{
	      	  lux[2] = lux[2] * ptn->mat->red;
	      	  lux[1] = lux[1] * ptn->mat->green;
	      	  lux[0] = lux[0] * ptn->mat->blue;
	      	}
	    }
	  free(inter);
	}
      ptn = ptn->next;
    }
  return (1);
}

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
  dist = - sqrt(scal_prod(viewpoint, viewpoint));			// 
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

#define spec 60

void	blinn_phong(t_st *st, t_ptn *light, t_inter *last, float col[4], t_lux *sv)
{
  t_ptn	ref;
  t_ptn	viewpoint;
  float	omega;

  viewpoint = st->vec;
  ref = *light;
  omega = reflect_ptn(&ref, last, &viewpoint);
  if (omega >= 0)
    {
      omega = pow(omega, spec) * sv->lux;
      col[0] += omega;
      col[1] += omega;
      col[2] += omega;
    }
}

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
  while (sv != NULL)
    {
      lux[2] = sv->red;
      lux[1] = sv->green;
      lux[0] = sv->blue;
      create_light_vector(sv, &light);
      if (inlight(rs, &light, lux) || sv->attribute == AMB)
	{
	  coef = lambert_coef(&light.vec, nrml, sv->attribute) * sv->lux;
	  coef = (sv->attribute == SPOT) ? coef / SPOTLEN * \
	    (1 - (sqrt(scal_prod(&light.vec, &light.vec)))) : coef;
	  work_with_illumination(col, point, lux);
	  if (sv->attribute != AMB)
	    blinn_phong(st, &light.vec, point, col, sv);
	}
      sv = sv->next;
    }
  free(nrml);
}
