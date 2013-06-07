/*
** lum.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 04:06:32 2013 karina martynava
** Last update Sat Jun  8 00:37:40 2013 lucas mayol
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

int	inlight(t_rs *rs, t_st *droit)
{
  t_obj		*ptn;
  t_inter	*inter;

  ptn = rs->obj;
  call_obj_neg(droit, rs);
  //  droit->neg = NULL;
  //  return (1);
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

float	reflect_ptn(t_ptn *toref, t_inter *last, t_ptn *viewpoint)
{
  t_ptn	*nrml;
  float	scal;
  float	dist;
  float	omega;

  nrml = (*(last->cal_norm))(last->obj, &(last->ptn));	//// NORMAL
  mult_vect(nrml, 1.0f / sqrt(scal_prod(nrml, nrml)));		//// NORMAL UNI
  mult_vect(toref, - 1.0f / sqrt(scal_prod(toref, toref)));	//// FROM INTER TO LIGNE UNI
  scal = scal_prod(nrml, toref);				
  scal = 2.0f * scal;
  toref->x = toref->x - scal * nrml->x;			// vecteur reflechi de la lum
  toref->y = toref->y - scal * nrml->y;
  toref->z = toref->z - scal * nrml->z;
  dist = - sqrt(scal_prod(viewpoint, viewpoint));			// 
  free(nrml);
  if (dist != 0)
    {
      mult_vect(viewpoint, 1.0f / dist);		//// NORMAL UNI
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

void	work_with_illumination(t_lux *sv, float col[3], t_inter *point, float coef)
{
  float	tab[3];

  if (point->obj->mat && coef > 0)
    {
      point->obj->cal_color(point->obj, point, tab);
      col[0] = col[0] + coef * sv->blue * tab[0];
      col[1] = col[1] + coef * sv->green * tab[1];
      col[2] = col[2] + coef * sv->red * tab[2];
    }
  else if (coef > 0)
    {
      col[0] = col[0] + coef * sv->blue * 1;
      col[1] = col[1] + coef * sv->green * 1;
      col[2] = col[2] + coef * sv->red * 1;
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

  nrml = (*(point->cal_norm))(point->obj, &(point->ptn));
  sv = rs->lux;
  add_vect(&light.cord, &point->ptn, &st->cord);
  sub_vect(&light.cord, &light.cord, &st->cord);
  while (sv != NULL)
    {
      create_light_vector(sv, &light);
      if (inlight(rs, &light) || sv->attribute == AMB)
	{
	  coef = lambert_coef(&light.vec, nrml, sv->attribute)
	    * sv->lux;
	  coef = (sv->attribute == SPOT) ? coef / SPOTLEN * \
	    (1 - (sqrt(scal_prod(&light.vec, &light.vec)))) : coef;
	  work_with_illumination(sv, col, point, coef);
	  if (sv->attribute != SPOT)
	    blinn_phong(st, &light.vec, point, col, sv);
	}
      sv = sv->next;
    }
  free(nrml);
}
