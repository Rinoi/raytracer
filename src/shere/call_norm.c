/*
** call_norm.c for RT in /home/mayol_l//git/Raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Mon May 13 21:39:06 2013 lucas mayol
** Last update Mon May 13 21:44:17 2013 lucas mayol
*/

#include <stdlib.h>
#include "../include/rtv.h"

t_ptn   *cal_norm_shere(t_obj *obj, t_ptn *ptn)
{
  t_ptn	*my_return;

  if ((my_return = malloc(sizeof(t_ptn))) == NULL)
    return (NULL);
  my_return->x = ptn->x - obj->ptn.x;
  my_return->y = ptn->y - obj->ptn.y;
  my_return->z = ptn->z - obj->ptn.z;
  return (my_return);
}
