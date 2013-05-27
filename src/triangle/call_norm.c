/*
** call_norm.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat May 11 21:26:55 2013 lucas mayol
** Last update Sat May 11 22:26:58 2013 lucas mayol
*/

#include <stdlib.h>
#include <stdio.h>
#include "../include/rtv1.h"

t_ptn	*cal_norm_triangle(t_obj *o, __attribute__((unused)) t_ptn *p)
{
  t_ptn	*ptn;

  if ((ptn = malloc(sizeof(t_ptn))) == NULL)
    return (NULL);
  ptn->x = (o->data[1] * o->data[5]) - (o->data[2] * o->data[4]);
  ptn->y = (o->data[2] * o->data[3]) - (o->data[0] * o->data[5]);
  ptn->z = (o->data[0] * o->data[4]) - (o->data[1] * o->data[3]);
  return (ptn);
}
