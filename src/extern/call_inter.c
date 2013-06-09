/*
** call_inter.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sun Jun  9 01:10:29 2013 lucas mayol
** Last update Sun Jun  9 05:24:01 2013 lucas mayol
*/

#include <stdio.h>
#include "rt.h"

t_inter         *call_inter_extern(t_obj *obj, t_st dr)
{
  t_inter	*inter;
  t_extern	*ext;

  ext = (t_extern*)(obj->data);
  inter = my_send_rayon_rec(ext->kdtree, &dr, MAX_ITERATION - 1);
  return (inter);
}
