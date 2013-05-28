/*
** nrml.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 08:04:31 2013 karina martynava
** Last update Tue May 28 23:24:46 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

t_ptn	*cylinder_nrml(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;
  t_ptn	*mat;

  nrml = malloc(sizeof(*nrml));
  if (nrml == NULL)
    return (NULL);
  mat = mul_m_p(obj->matrix, &obj->ptn);
  nrml->x = ptn->x - mat->x;
  nrml->y = ptn->y - mat->y;
  nrml->z = 0;
  mat = mul_m_p(obj->matrix, nrml);
  if (mat != NULL)
    *nrml = *mat;
  free(mat);
  return (nrml);
}
 
