/*
** nrml.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 08:20:26 2013 karina martynava
** Last update Sat Jun  8 04:26:35 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

t_ptn	*plane_nrml(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;
  t_ptn	*mat;

  nrml = malloc(sizeof(*nrml));
  if (nrml == NULL)
    return (NULL);
  nrml->x = 0;
  nrml->y = 0;
  nrml->z = 100;
  mat = mul_m_p(obj->matrix_inv, nrml);
  if (mat != NULL)
    *nrml = *mat;
  free(mat);
  if (obj->mat->bump != 0)
    my_bump(nrml, ptn, obj->mat->bump);
  return (nrml);
}

t_ptn	*plane_nrml_inv(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;
  t_ptn	*mat;
  

  nrml = malloc(sizeof(*nrml));
  if (nrml == NULL)
    return (NULL);
  nrml->x = 0;
  nrml->y = 0;
  nrml->z = -100;
  mat = mul_m_p(obj->matrix_inv, nrml);
  if (mat != NULL)
    *nrml = *mat;
  free(mat);
  if (obj->mat->bump != 0)
    my_bump(nrml, ptn, obj->mat->bump);
  return (nrml);
}
