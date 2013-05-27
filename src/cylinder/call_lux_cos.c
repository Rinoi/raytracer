/*
** call_lux_cos.c for rt in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat May 11 15:42:44 2013 lucas mayol
** Last update Sat May 18 23:37:37 2013 lucas mayol
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/rtv1.h"

float		my_cal_lux_cos_cylinder(t_obj *obj, t_ptn *ptn, t_lux *lum)
{
  double	pc;
  t_ptn		*n;
  double	r;

  if ((n = cal_norm_cylinder(obj, ptn)) == NULL)
    return (0);
  pc = (lum->cord.x - ptn->x) * n->x;
  pc += (lum->cord.y - ptn->y) * n->y;
  pc += (lum->cord.z - ptn->z) * n->z;
  r =  (pc / (my_call_dist(ptn, &lum->cord)
	      * sqrt(pow(n->x, 2) + pow(n->y, 2) + pow(n->z, 2))));
  return (r);
}
