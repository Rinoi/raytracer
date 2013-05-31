/*
** nrml.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 08:04:31 2013 karina martynava
** Last update Fri May 31 18:15:09 2013 lucas mayol
*/

#include <stdlib.h>
#include "rt.h"

t_ptn	*cylinder_nrml(__attribute__((unused))t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;
 
  nrml = malloc(sizeof(*nrml));
  if (nrml == NULL)
    return (NULL);
  nrml->x = ptn->x - obj->ptn.x;
  nrml->y = ptn->y - obj->ptn.y;
  nrml->z = 0;
  return (nrml);
}
 
