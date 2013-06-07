/*
** nrml.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 08:01:03 2013 karina martynava
** Last update Fri Jun  7 23:58:51 2013 lucas mayol
*/

#include <stdlib.h>
#include "rt.h"

t_ptn	*sphere_nrml(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;
  float	tmp;

  nrml = malloc(sizeof(*nrml));
  if (nrml == NULL)
    return (NULL);
  nrml->x = ptn->x - obj->ptn.x;
  nrml->y = ptn->y - obj->ptn.y;
  nrml->z = ptn->z - obj->ptn.z;
  if (obj->mat->bump != 0)
    my_bump(nrml, ptn, obj->mat->bump);
  /* nrml->x = -nrml->x; */
  /* nrml->y = -nrml->y; */
  /* nrml->z = -nrml->z; */
  return (nrml);
}

t_ptn	*sphere_nrml_inv(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;

  nrml = sphere_nrml(obj, ptn);
  nrml->x *= -1;
  nrml->y *= -1;
  nrml->z *= -1;
  return (nrml);
}
