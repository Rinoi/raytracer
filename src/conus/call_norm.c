/*
** call_norm.c for RT in /home/mayol_l//git/Raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat May 18 17:04:50 2013 lucas mayol
** Last update Sun May 19 13:14:06 2013 lucas mayol
*/

#include <stdlib.h>
#include <stdio.h>
#include "../include/rtv1.h"

t_ptn		*cal_norm_conus(t_obj *o, t_ptn *p)
{
  t_ptn		*norm;

  if ((norm = malloc(sizeof(t_ptn))) == NULL)
    return (NULL);
  norm->x = p->x;
  norm->y = p->y;
  norm->z = - tan(RAD(o->data[0])) * p->z;
  multipli_z(norm, o->rot.x);
  return (norm);
}
