/*
** vect_op.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 04:00:53 2013 karina martynava
** Last update Tue May 28 04:10:27 2013 karina martynava
*/

#include "rt.h"

float	scal_prod(t_ptn *a, t_ptn *b)
{
  float	scal;

  scal = a->x * b->x + a->y * b->y + a->y * b->y;
  return (scal);
}

void	sub_vect(t_ptn *tochange, t_ptn a, t_ptn b)
{
  t_ptn	tmp;

  tmp.x = a->x - b->x;
  tmp.y = a->y - b->y;
  tmp.z = a->z - b->z;
  *tochange = tmp;
}

void	add_vect(t_ptn *tochange, t_ptn a, t_ptn b)
{
  t_ptn	tmp;

  tmp.x = a->x + b->x;
  tmp.y = a->y + b->y;
  tmp.z = a->z + b->z;
  *tochange = tmp;
}
