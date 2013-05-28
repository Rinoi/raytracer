/*
** resolve_four.c for rt in /home/martyn_k/raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 02:33:40 2013 karina martynava
** Last update Tue May 28 03:01:10 2013 karina martynava
*/

#include <value.h>
#include <math.h>
#include "rt.h"

float	resolve_three(float d[4], int *x);

float	resolve_three_pos_delta_bis(float d[4], float q, float r)
{
  int	i;
  float	prime;
  float	t;
  float	s;
  float	tmp;

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
    return (resolve_two(d[2], d[1], d[0], x));
  while (i++ < 3)
    d[i - 1] = d[i - 1] / d[3];
  q = (pow(d[2], 2) - 3 * d[1]) / 9;
  r = (d[2] * (pow(d[2], 2) - 4.5 * d[1]) + 13.5 * d[0]) / 27;
  delta = pow(q, 3) - pow(r, 2);
  if (delta >= 0)
    return (resolve_three_pos_delta_bis(x, q, r));
  s = pow(pow(-delta, 1 / 2) + fabsf(r), 1 / 3);
  ret = (r > 0) ? s + q / s - d[2] / 3 : s - q / s - d[2] / 3;
  return (ret);
}

float	resolve_four(float d[5], int *x);
{
  int	i;
  float	b[4];
  float	res;
  float	delta;
  float	prime;
  float	alpha;
  float	ret;

  i = 0;
  if (d[4] == 0)
    return (resolve_three(&d[1], x));
  while (i < 4)
    {
      d[i] = d[i] / d[4];
      i++;
    }
  if (d[0] == 0) // racine 0
    return (-1.0f)
  else
    {
      b[3] = 1;
      b[2] = (3 * pow(d[3], 2) / 8 - d[2]) / 2;
      b[1] = 3 * pow(d[3], 4) / 256 - pow(d[3], 2) * d[2] / 16
	+ d[3] * d[1] / 4 - d[0];
      b[0] = b[2] * b[1]
	- pow((pow(d[3], 3) / 16 - d[3] * d[2] / 4 + d[1]  / 2), 2);
      res = resolve_three_bis(&b[0], x);
      delta = 2 * (res + b[2]);
      if (delta < 0)
	return (-1.0f);
      else if (delta == 0)
	{
	  prime = pow(res, 2) + b[1];
	  if (prime < 0)
	    return (-1.0f);
	  prime = pow(prime, 1 / 2);
	}
      else
	{
	  prime = pow((b[2] * b[1] - b[0]) * delta, 1 / 2);
	}
      alpha = delta - 4 * (res - prime);
      ret = -1.0f;
      if (a == 0)
	ret = - pow(delta, 1 / 2) / + d[3] / 4;
      else if (a > 0)
	{
	  ret = - pow(delta + pow(alpha, 1 / 2), 1 / 2) / + d[3] / 4;
	  if (ret > EPSILLON)
	    *x = 0;
	  prime = - pow(delta - pow(alpha, 1 / 2), 1 / 2) / + d[3] / 4;
	  if (prime > EPSILLON && prime < ret)
	    {
	      ret = prime;
	      *x = 1;
	    }
	}
      if (ret > EPSILLON)
	*x = 0;


      if (a == 0)
	ret = - pow(delta, 1 / 2) / + d[3] / 4;
      else if (a > 0)
	{
	  ret = - pow(delta + pow(alpha, 1 / 2), 1 / 2) / + d[3] / 4;
	  if (ret > EPSILLON)
	    *x = 0;
	  prime = - pow(delta - pow(alpha, 1 / 2), 1 / 2) / + d[3] / 4;
	  if (prime > EPSILLON && prime < ret)
	    {
	      ret = prime;
	      *x = 1;
	    }
	}
      if (ret > EPSILLON)
	*x = 0;
    }
  return (-1.0f);
}

