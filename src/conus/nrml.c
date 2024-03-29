/*
** nrml.c<3> for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 08:09:56 2013 karina martynava
** Last update Sun Jun  9 16:10:34 2013 lucas mayol
*/

#include <stdlib.h>
#include "rt.h"

t_ptn	*conus_nrml(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;
  float	angle;
  t_ptn	cp;
  t_ptn	*mat;

  cp.x = ptn->x - obj->ptn.x;
  cp.y = ptn->y - obj->ptn.y;
  cp.z = ptn->z - obj->ptn.z;
  mat = mul_m_p(obj->matrix, &cp);
  cp = *mat;
  free(mat);
  angle = ((float *)(obj->data))[0];
  angle = tan(RAD(angle));
  angle = 1 / pow(angle, 2);
  nrml = malloc(sizeof(*nrml));
  nrml->x = cp.x;
  nrml->y = cp.y;
  nrml->z = - (angle);
  mat = mul_m_p(obj->matrix_inv, nrml);
  *nrml = *mat;
  free(mat);
  return (nrml);
}
