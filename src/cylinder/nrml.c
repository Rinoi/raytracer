/*
** nrml.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 08:04:31 2013 karina martynava
** Last update Tue May 28 20:59:19 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

t_ptn	*cylinder_nrml(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;
  t_ptn	*mat;
  /* t_ptn	*cord; */

  nrml = malloc(sizeof(*nrml));
  if (nrml == NULL)
    return (NULL);
  /* cord = mul_m_p(obj->matrix_inv, &(obj->ptn)); */
  nrml->x = ptn->x - obj->ptn.x;
  nrml->y = ptn->y - obj->ptn.y;
  nrml->z = ptn->z - obj->ptn.z;
  mat = mul_m_p(obj->matrix, nrml);
  if (mat != NULL)
    *nrml = *mat;
  nrml->z = 0;
  free(mat);
  mat = mul_m_p(obj->matrix_inv, nrml);
  if (mat != NULL)
    *nrml = *mat;
  free(mat);
  return (nrml);
}
 
