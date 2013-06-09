/*
** call_norm.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat May 11 21:26:55 2013 lucas mayol
** Last update Sun Jun  9 12:24:14 2013 lucas mayol
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	"rt.h"

t_ptn		*triangle_nrml(t_obj *o, __attribute__((unused)) t_ptn *p)
{
  t_ptn		*ptn;
  t_tri		*tri;

  tri = (t_tri *)(o->data);
  if ((ptn = malloc(sizeof(t_ptn))) == NULL)
    return (NULL);
  ptn->x =  ((tri->a2.y * tri->a3.z) - (tri->a2.z * tri->a3.y));
  ptn->y =  ((tri->a2.z * tri->a3.x) - (tri->a2.x * tri->a3.z));
  ptn->z =  ((tri->a2.x * tri->a3.y) - (tri->a2.y * tri->a3.x));
  return (ptn);
}
