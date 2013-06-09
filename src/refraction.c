/*
** refraction.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sun Jun  9 17:45:35 2013 karina martynava
** Last update Sun Jun  9 17:48:09 2013 karina martynava
*/

#include <stdio.h>
#include <stdlib.h>
#include "rt.h"

float	lambert_coef(t_ptn *lightray, t_ptn *nrml, char attribute);
void	new_straight(t_st *droit, t_inter *last);

float	refraction_angle(float dens[2], float ij[4], t_st *st, t_ptn *nrml)
{
  float	dist;

  mult_vect(nrml, 1.0f / sqrt(scal_prod(nrml, nrml)));
  mult_vect(&st->vec, 1.0f / sqrt(scal_prod(&st->vec, &st->vec)));
  ij[0] = fabsf(scal_prod(&st->vec, nrml));
  if (ij[0] > 0.999)
    return (0.0f);
  ij[1] = sqrtf(1.0f - ij[0] * ij[0]);
  ij[3] = (dens[0] / dens[1]) * ij[1];
  if (ij[3] * ij[3] > 0.999)
    return (-1.0);
  ij[2] = sqrtf(1.0f - ij[3] * ij[3]);
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
  if (density[0] != density[1] && density[0] == inter->obj->mat->indice)
    mult_vect(nrml, -1.0);

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
