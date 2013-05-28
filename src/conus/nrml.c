/*
** nrml.c<3> for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 08:09:56 2013 karina martynava
** Last update Tue May 28 20:23:22 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

t_ptn	*conus_nrml(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;
  float	angle;
  t_ptn	*mat;
 
  angle = ((float *)(obj->data))[0];
  angle = tan(RAD(angle));
  angle = 1 / pow(angle, 2);
  nrml = malloc(sizeof(*nrml));
  if (nrml == NULL)
    return (NULL);
  nrml->x = ptn->x - obj->ptn.x;
  nrml->y = ptn->y - obj->ptn.y;
  nrml->z = - (ptn->z - obj->ptn.z) * angle;
  mat = mul_m_p(obj->matrix_inv, nrml);
  if (mat != NULL)
    *nrml = *mat;
  free(mat);
  return (nrml);
}
 
