/*
** resolve_three.c for rt in /home/martyn_k/raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 02:09:42 2013 karina martynava
** Last update Tue May 28 03:01:12 2013 karina martynava
*/

#include <math.h>
#include "rt.h"

float	resolve_two(float a, float b, float c, int *x);

float	resolve_three_pos_delta(float d[4], int *x, float q, float r)
{
  int	i;
  float	prime;
  float	t;
  float	s;
  float	tmp;
  float	ret;

  prime = r / pow(q, 3 / 2);
  t = acosf(prime) / 3;
  s = - 2 * pow(q, 1/2);
  i = 0;
  ret = -1.0f;
  while (i < 3)
    {
      tmp = s * cosf(t + 2 * M_PI * i / 3) - d[2] / 3;
      if (tmp > EPSILLON && (i == 0 || ret > tmp))
	{
	  ret = tmp;
	  *x = i;
	}
      i++;
    }
  return (ret);
}

float	resolve_three(float d[4], int *x)
{
  int	i;
  float	q;
  float	r;
  float	delta;
  float	s;
  float	ret;

  i = 0;
  if (d[3] == 0)
    return (resolve_two(d[2], d[1], d[0], x));
  while (i++ < 3)
    d[i - 1] = d[i - 1] / d[3];
  q = (pow(d[2], 2) - 3 * d[1]) / 9;
  r = (d[2] * (pow(d[2], 2) - 4.5 * d[1]) + 13.5 * d[0]) / 27;
  delta = pow(q, 3) - pow(r, 2);
  if (delta >= 0) // 3 solutions
    return (resolve_three_pos_delta(d, x, q, r));
  // 1 solution
  s = pow(pow(-delta, 1 / 2) + fabsf(r), 1 / 3);
  ret = (r > 0) ? s + q / s - d[2] / 3 : s - q / s - d[2] / 3;
  if (ret > EPSILLON)
    return (-1.0f);
  *x = 0;
  return (ret);
}
