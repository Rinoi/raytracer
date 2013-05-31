/*
** resolve_bis.c for rt in /home/martyn_k/raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 03:48:11 2013 karina martynava
** Last update Sat Jun  1 00:25:25 2013 karina martynava
*/

#include <stdio.h>
#include <values.h>
#include <math.h>
#include "rt.h"

float	resolve_two_bis(float a, float b, float c)
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
      if (one > EPSILLON)
	return (one);
      return (two);
    }
  return (MAXFLOAT);
}

float	resolve_three_pos_delta_bis(float d[4], float q, float r)
{
  int	i;
  float	prime;
  float	t;
  float	s;
  float	tmp;
  float	ret;

  prime = r / sqrt(q * q * q);
  t = acos(prime) / 3.0;
  s = - 2 * sqrt(q);
  i = 0;
  ret = -1.0f;
  while (i < 3)
    {
      tmp = s * cos(t + 2 * M_PI * i / 3.0) - d[2] / 3.0;
      if (tmp > 0)
	return (tmp);
      if (tmp > EPSILLON && (ret < 0 || ret > tmp))
	ret = tmp;
      i++;
    }
  return (ret);
}

float	resolve_three_bis(float d[4])
{
  int	i;
  float	q;
  float	r;
  float	delta;
  float	s;
  float	ret;

  i = 0;
  if (d[3] == 0)
    return (resolve_two_bis(d[2], d[1], d[0]));
  while (i++ < 3)
    d[i - 1] = d[i - 1] / d[3];

  q = (pow(d[2], 2) - 3 * d[1]) / 9.0;
  r = (d[2] * (pow(d[2], 2) - 4.5 * d[1]) + 13.5 * d[0]) / 27.0;
  delta = pow(q, 3) - pow(r, 2);
  if (delta >= 0) // 3 solutions
    return (resolve_three_pos_delta_bis(d, q, r));
  // 1 solution
  s = sqrt(-delta) + fabsf(r);
  s = pow(s, 1.0f / 3.0f);
  ret = (r < 0) ?
    s + q / s - d[2] / 3.0f :
    - s - q / s - d[2] / 3.0f;
  if (ret < 0)
    return (-1.0f);
  return (ret);
}
