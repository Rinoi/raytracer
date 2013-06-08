/*
** resolve_two.c for rt in /home/martyn_k/raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 01:58:44 2013 karina martynava
** Last update Sat Jun  8 19:27:58 2013 lucas mayol
*/

#include <stdio.h>
#include <math.h>
#include "rt.h"

float	resolve_two_inv(float a, float b, float c, int *x)
{
  float	delta;
  float	one;
  float	two;

  delta = pow(b, 2) - 4 * a * c;
  if (a == 0 && b != 0)
    return (- c / b);
  if (a != 0.0f && delta >= 0)
    {
      one = (- b - sqrt(delta)) / (2 * a);
      two = (- b + sqrt(delta)) / (2 * a);
      if (one <= EPSILLON && two <= EPSILLON)
        return (-1.0);
      if (two <= EPSILLON && (*x = 0) == 0)
	return (one);
      if (one <= EPSILLON)
        {
          *x = 1;
          return (two);
        }
      *x = one > two ? 1 : 0;
      return (two > one ? two : one);
    }
  return (-1.0);
}

float	resolve_two(float a, float b, float c, int *x)
{
  float	delta;
  float	one;
  float	two;

  delta = pow(b, 2) - 4 * a * c;
  if (a == 0 && b != 0)
    return (- c / b);
  if (a != 0.0f && delta >= 0)
    {
      one = (- b - sqrt(delta)) / (2 * a);
      two = (- b + sqrt(delta)) / (2 * a);
      if (one <= EPSILLON && two <= EPSILLON)
	return (-1.0);
      if (two <= EPSILLON)
	{
	  *x = 0;
	  return (one);
	}
      if (one <= EPSILLON && (*x = 1) == 1)
	return (two);
      *x = one > two ? 1 : 0;
      return (one > two ? two : one);
    }
  return (-1.0);
}
