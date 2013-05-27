/*
** call_norm.c for RT in /home/mayol_l//git/Raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat May 18 17:04:50 2013 lucas mayol
** Last update Sun May 19 12:54:07 2013 lucas mayol
*/

#include <stdlib.h>
#include <stdio.h>
#include "../include/rtv1.h"

t_ptn		*cal_norm_cylinder(t_obj *o, t_ptn *p)
{
  t_ptn		*norm;

  if ((norm = malloc(sizeof(t_ptn))) == NULL)
    return (NULL);
  norm->x = p->x;
  norm->y = p->y;
  norm->z = 0;
  multipli_x(norm, -o->rot.x);
  return (norm);
}
