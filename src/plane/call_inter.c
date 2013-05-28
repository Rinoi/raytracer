/*
** call_inter.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 28 02:57:22 2013 lucas mayol
** Last update Tue May 28 08:28:00 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

t_inter		*call_inter_plane(t_obj *obj, t_st dr)
{
  t_inter	*inter;
  float		k;
  
  change_dr(obj, &dr);
  if (dr.cord.z == 0)
    return (NULL);
  if ((inter = malloc(sizeof(t_inter))) == NULL)
    return (NULL);
  k = dr.cord.z / dr.cord.z;
  if (k > EPSILLON)
    inter->d = k;
  else
    inter->d = - 1.0f;
  if (inter->d < 0)
    {
      free(inter);
      return (NULL);
    }
  return (inter);
}
