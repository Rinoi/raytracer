/*
** nrml.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 08:01:03 2013 karina martynava
** Last update Tue May 28 08:29:36 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

t_ptn	*sphere_nrml(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*nrml;

  nrml = malloc(sizeof(*nrml));
  if (nrml == NULL)
    return (NULL);
  sub_vect(nrml, ptn, &(obj->ptn));
  return (nrml);
}
