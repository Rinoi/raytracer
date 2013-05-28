/*
** resolve_two.c for rt in /home/martyn_k/raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 01:58:44 2013 karina martynava
** Last update Tue May 28 02:08:23 2013 karina martynava
*/

#include <math.h>

float	resolve_two(float a, float b, float c, int *x)
{
  float	delta;
  float	one;
  float	two;

  delta = pow(b, 2) - 4 * a;
  if (a != 0.0f)
    {
      one = (- b - sqrt(delta)) / (2 * a);
      two = (- b + sqrt(delta)) / (2 * a);
      if (one < 0.0 && two < 0.0)
	return (-1.0f);
      else if (one < 0.0)
	{
	  *x = 1;
	  return (two);
	}
      else if (two < 0.0)
	{
	  *x = 0;
	  return (one);
	}
      *x  =(one < two) ? 0 : 1;
      return ((one < two) ? one : two);
    }
  return (-1.0f);
}
