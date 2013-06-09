/*
** fresnel.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Thu Jun  6 23:23:12 2013 karina martynava
** Last update Sun Jun  9 09:53:36 2013 karina martynava
*/

#include <stdio.h>
#include <stdlib.h>
#include "rt.h"

float	lambert_coef(t_ptn *lightray, t_ptn *nrml, char attribute);
void	new_straight(t_st *droit, t_inter *last);



void	add_fresnel(t_st *st, t_inter *inter)
{
  t_fresnel	*new;

  new = malloc(sizeof(*new));
  if (new == NULL)
    return ;
  new->indice = inter->obj->mat->indice;
  new->mat = inter->obj->mat;
  new->next = NULL;
  new->prev = st->ind_list;
  if (st->ind_list == NULL)
    {
      st->ind_list = new;
      return ;
    }
  while (st->ind_list != NULL && st->ind_list->next != NULL)
    st->ind_list = st->ind_list->next;
  st->ind_list->next = new;
}

void 	rm_fresnel(t_fresnel *sv)
{
  if (sv->next == NULL)
    {
      if (sv->prev != NULL)
	{
	  sv->prev->next = NULL;
	  free(sv);
	}
      return ;
    }
  sv->next->prev = sv->prev;
  if (sv->prev != NULL)
    sv->prev->next = sv->next;
}

void		fresnel_out(t_inter *inter, t_st *st, float ind[2], t_fresnel *sv)
{
  ind[0] = inter->obj->mat->indice;
  if (sv == NULL ||
      (sv->mat == inter->obj->mat && sv->prev == NULL))
    {
      ind[1] = DEFAULT_INDICE;
      if (sv != NULL)
	{
	  free(sv);
	  st->ind_list = NULL;
	}
    }
  else
    {
      ind[1] = sv->indice;
      while (sv != NULL && sv->prev != NULL)
	{
	  if (sv->mat == inter->obj->mat)
	    {
	      rm_fresnel(sv);
	      return ;
	    }
	  sv = sv->prev;
	}
    }
}

void		fresnel_indice_list(t_inter *inter, t_st *st, float ind[2])
{
  t_fresnel	*sv;

  sv = st->ind_list;
  if (inter->status == GO_IN)
    {
      ind[0] = st->indice;
      ind[1] = inter->obj->mat->indice;
      add_fresnel(st, inter);
      return ;
    }
  else if (inter->status == GO_OUT)
    {
      fresnel_out(inter, st, ind, sv);
      return ;
    }
  ind[0] = st->indice;
  ind[1] = st->indice;
}

float	refraction_angle(float dens[2], float ij[4], t_st *st, t_ptn *nrml)
{
  ij[0] = lambert_coef(&st->vec, nrml, NONE);
  if (ij[0] >= 0.999)
    return (0.0f);
  ij[1] = sqrtf(1.0 - pow(ij[0], 2));
  ij[3] = (dens[0] / dens[1]) * ij[1];
  if (ij[3] * ij[3] >= 0.999)
    return (-1.0);
  ij[2] = sqrtf(1.0 - pow(ij[3], 2));
  mult_vect(nrml, 1.0f / sqrt(scal_prod(nrml, nrml)));
  mult_vect(&st->vec, 1.0f / sqrt(scal_prod(&st->vec, &st->vec)));
  st->vec.x = st->vec.x + ij[0] * nrml->x;
  st->vec.y = st->vec.y + ij[0] * nrml->y;
  st->vec.z = st->vec.z + ij[0] * nrml->z;
  st->vec.x = (dens[0] / dens[1]) * st->vec.x - ij[2] * nrml->x;
  st->vec.y = (dens[0] / dens[1]) * st->vec.y - ij[2] * nrml->y;
  st->vec.z = (dens[0] / dens[1]) * st->vec.z - ij[2] * nrml->z;
  return (1.0);
}

void	refraction(t_inter *inter, t_st *st)
{
  float	density[2];
  float	ij[4];
  t_ptn	*nrml;

  if (inter->obj->mat == NULL || inter->obj->mat->indice == 0.0f)
    {
      new_straight(st, inter);
      return ;
    }
  fresnel_indice_list(inter, st, density);
  nrml = (*(inter->cal_norm))(inter->obj, &(inter->ptn));
  st->indice = density[1];
  if (nrml == NULL || refraction_angle(density, ij, st, nrml) == -1.0f)
    {
      new_straight(st, inter);
      return ;
    }
  st->cord.x = inter->ptn.x;
  st->cord.y = inter->ptn.y;
  st->cord.z = inter->ptn.z;
  free(nrml);
}
