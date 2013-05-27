/*
** call_lux_cos.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat May 11 15:57:49 2013 lucas mayol
** Last update Mon May 13 20:43:19 2013 lucas mayol
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/rtv1.h"

static float	my_call_pc(t_ptn *w, t_ptn *inter, t_ptn *lum)
{
  float		pc;

  pc = w->x * (lum->x - inter->x);
  pc += w->y * (lum->y - inter->y);
  pc += w->z * (lum->z - inter->z);
  return (- pc);
}

float		my_cal_lux_cos_triangle(t_obj *o, t_ptn *ptn, t_lux *lum)
{
  t_ptn		w;
  float		r;

  //  printf("x : %f, y : %f, z : %f\n", ptn->x, ptn->y, ptn->z);
  w.x = (o->data[1] * o->data[5]) - (o->data[2] * o->data[4]);
  w.y = (o->data[2] * o->data[3]) - (o->data[0] * o->data[5]);
  w.z = (o->data[0] * o->data[4]) - (o->data[1] * o->data[3]);
  r =  (my_call_pc(&w, ptn, &lum->cord)
	/
	(my_call_dist(ptn, &lum->cord)
	 * sqrt(pow(w.x, 2) + pow(w.y, 2) + pow(w.z, 2)))
	);
  //printf("r : %f\n", r);
  if (r >= 0)
    return (r);
  w.x = -w.x;
  w.y = -w.y;
  w.z = -w.z;
  r =  (my_call_pc(&w, ptn, &lum->cord)
	/
	(my_call_dist(ptn, &lum->cord)
	 * sqrt(pow(w.x, 2) + pow(w.y, 2) + pow(w.z, 2)))
	);
  return (r);
}
