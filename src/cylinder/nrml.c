/*
** nrml.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 08:04:31 2013 karina martynava
** Last update Sun Jun  9 16:29:46 2013 lucas mayol
*/

#include <stdlib.h>
#include "rt.h"

t_ptn	*cylinder_nrml(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;
  t_ptn	cp;
  t_ptn	*mat;

  cp.x = ptn->x - obj->ptn.x;
  cp.y = ptn->y - obj->ptn.y;
  cp.z = ptn->z - obj->ptn.z;
  mat = mul_m_p(obj->matrix, &cp);
  cp = *mat;
  free(mat);
  nrml = malloc(sizeof(*nrml));
  if (nrml == NULL)
    return (NULL);
  nrml->x = cp.x;
  nrml->y = cp.y;
  nrml->z = 0;
  mat = mul_m_p(obj->matrix_inv, nrml);
  free(nrml);
  return (mat);
}

t_ptn	*cylinder_nrml_inv(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;

  nrml = cylinder_nrml(obj, ptn);
  mult_vect(nrml, -1.0f);
  return (nrml);
}
