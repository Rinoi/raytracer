/*
** resolve_two.c for rt in /home/martyn_k/raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 01:58:44 2013 karina martynava
** Last update Tue May 28 02:30:25 2013 karina martynava
*/

#include <math.h>
#include "rt.h"

float	resolve_two(float a, float b, float c, int *x)
{
  float	delta;
  float	one;
  float	two;

  delta = pow(b, 2) - 4 * a * c;
  if (a != 0.0f)
    {
      one = (- b - sqrt(delta)) / (2 * a);
      two = (- b + sqrt(delta)) / (2 * a);
      if (one < EPSILLON && two < EPSILLON)
	return (-1.0f);
      else if (one < EPSILLON)
	{
	  *x = 1;
	  return (two);
	}
      else if (two < EPSILLON)
	{
	  *x = 0;
	  return (one);
	}
      *x  =(one < two) ? 0 : 1;
      return ((one < two) ? one : two);
    }
  return (-1.0f);
}
