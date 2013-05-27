/*
** call_lux_cos.c for rt in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat May 11 15:42:44 2013 lucas mayol
** Last update Sat May 11 15:54:41 2013 lucas mayol
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/rtv1.h"

static float	my_call_pc(t_ptn *obj, t_ptn *ptn, t_ptn *lum)
{
  float		n_pc;

  n_pc = (ptn->x - obj->x) * (lum->x - ptn->x);
  n_pc += (ptn->y - obj->y) * (lum->y - ptn->y);
  n_pc += (ptn->z - obj->z) * (lum->z - ptn->z);
  return (n_pc);
}

float		my_cal_lux_cos_shere(t_obj *obj, t_ptn *ptn, t_lux *lum)
{
  return (my_call_pc(&obj->ptn, ptn, &lum->cord)
	  /
	  (my_call_dist(ptn, &lum->cord) * obj->data[0]));
}
