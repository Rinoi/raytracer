/*
** nrml.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 08:01:03 2013 karina martynava
** Last update Fri May 31 21:19:03 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

t_ptn	*sphere_nrml(__attribute__((unused))t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;

  nrml = malloc(sizeof(*nrml));
  if (nrml == NULL)
    return (NULL);
  nrml->x = ptn->x - obj->ptn.x;
  nrml->y = ptn->y - obj->ptn.y;
  nrml->z = ptn->z - obj->ptn.z;
  return (nrml);
}
