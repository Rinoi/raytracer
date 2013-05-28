/*
** call_inter.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 28 02:57:22 2013 lucas mayol
** Last update Tue May 28 09:25:12 2013 lucas mayol
*/

#include <stdlib.h>
#include "rt.h"

t_inter		*call_inter_plane(t_obj *obj, t_st dr)
{
  t_inter	*inter;

  change_dr(obj, &dr);
  if ((inter = malloc(sizeof(t_inter))) == NULL)
    return (NULL);
  if ((dr.vec.z == 0 && dr.vec.z != obj->ptn.z) ||
      (obj->ptn.z < dr.cord.z && dr.vec.z > 0) ||
      (obj->ptn.z > dr.cord.z && dr.vec.z < 0))
    {
      free(inter);
      return (NULL);
    }
  if (dr.vec.z == 0)
    inter->d = 0;
  else
    inter->d = - dr.cord.z / dr.vec.z;
  if (inter->d < 0)
    {
      free(inter);
      return (NULL);
    }
  inter->cal_norm = plane_nrml;
  return (inter);
}
