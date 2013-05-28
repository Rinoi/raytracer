/*
** resolve_bis.c for rt in /home/martyn_k/raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 03:48:11 2013 karina martynava
** Last update Tue May 28 03:49:07 2013 karina martynava
*/

#include <values.h>
#include <math.h>
#include "rt.h"

float	resolve_two_bis(float a, float b, float c)
{
  float	delta;

  delta = pow(b, 2) - 4 * a * c;
  if (a != 0.0f && delta >= 0)
    return ((- b - sqrt(delta)) / (2 * a));
  return (MAXDOUBLE);
}

float	resolve_three_pos_delta_bis(float d[4], float q, float r)
{
  int	i;
  float	prime;
  float	t;
  float	s;

  prime = r / pow(q, 3 / 2);
  t = acosf(prime) / 3;
  s = - 2 * pow(q, 1/2);
  i = 0;
  return (s * cosf(t + 2 * M_PI * i / 3) - d[2] / 3);
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
  q = (pow(d[2], 2) - 3 * d[1]) / 9;
  r = (d[2] * (pow(d[2], 2) - 4.5 * d[1]) + 13.5 * d[0]) / 27;
  delta = pow(q, 3) - pow(r, 2);
  if (delta >= 0)
    return (resolve_three_pos_delta_bis(d, q, r));
  s = pow(pow(-delta, 1 / 2) + fabsf(r), 1 / 3);
  ret = (r > 0) ? s + q / s - d[2] / 3 : s - q / s - d[2] / 3;
  return (ret);
}
