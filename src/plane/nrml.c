/*
** nrml.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 08:20:26 2013 karina martynava
** Last update Tue May 28 08:22:46 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

t_ptn	*plane_nrml(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;

  nrml = malloc(sizeof(*nrml));
  if (nrml == NULL)
    return (NULL);
  nrml->x = 0;
  nrml->y = 0;
  nrml->z = 100;
  return (nrml);
}
