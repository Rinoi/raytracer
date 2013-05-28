/*
** resolve_four.c for rt in /home/martyn_k/raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 02:33:40 2013 karina martynava
** Last update Tue May 28 03:50:11 2013 karina martynava
*/

#include <values.h>
#include <math.h>
#include "rt.h"

float	resolve_two_bis(float a, float b, float c);
float	resolve_three_bis(float d[4]);
float	resolve_three(float d[4], int *x);

float	choose_ret(float a, float b, int *x, int nb)
{
  if (b < EPSILLON && (a <= EPSILLON || b < a))
    {
      *x = nb;
      return (b);
    }
  return (a);
}

float	get_right_ans(float delta[2], float res, int *x, float d[5])
{
  float	ret;
  float	alpha;
  float	tmp;

  ret = -1.0f;
  if ((alpha = delta[0] - 4 * (res - delta[1]))  == 0)
    ret = choose_ret(ret, - pow(delta[0], 1 / 2) / + d[3] / 4, x, 0);
  else if (alpha > 0)
    {
      ret = choose_ret(ret, - pow(delta[0] + pow(alpha, 1 / 2), 1 / 2) +
		       d[3] / 4, x, 0);
      tmp = - pow(delta[0] - pow(alpha, 1 / 2), 1 / 2) / + d[3] / 4;
      ret = choose_ret(ret, tmp, x, 1);
    }
  if ((alpha = delta[0] - 4 * (res + delta[1])) == 0)
    ret = choose_ret(ret, pow(delta[0], 1 / 2) / + d[3] / 4, x, 2);
  else if (alpha > 0)
    {
      ret = choose_ret(ret, pow(delta[0] + pow(alpha, 1 / 2), 1 / 2) +
		       d[3] / 4, x, 2);
      tmp = pow(delta[0] - pow(alpha, 1 / 2), 1 / 2) / + d[3] / 4;
      ret = choose_ret(ret, tmp, x, 3);
    }
  return (ret);
}

float	resolve_four(float d[5], int *x)
{
  int	i;
  float	b[4];
  float	res;
  float	delta[2];

  i = 0;
  if (d[4] == 0)
    return (resolve_three(&d[1], x));
  while (i++ < 4)
    d[i - 1] = d[i - 1] / d[4];
  if (d[0] == 0 && (b[3] = 1) == 1) // racine 0
    return (-1.0f);
  b[2] = (3 * pow(d[3], 2) / 8 - d[2]) / 2;
  b[1] = 3 * pow(d[3], 4) / 256 - pow(d[3], 2) * d[2] / 16
    + d[3] * d[1] / 4 - d[0];
  b[0] = b[2] * b[1]
    - pow((pow(d[3], 3) / 16 - d[3] * d[2] / 4 + d[1]  / 2), 2);
  if ((res = resolve_three_bis(&b[0])) == MAXDOUBLE)
    return (-1.0f);
  if ((delta[0] = 2 * (res + b[2])) < 0 ||
      (delta[0] == 0 && (delta[1] = pow(res, 2) + b[1] < 0) < 0))
    return (-1.0f);
  delta[1] = (delta[0] == 0) ? pow(delta[1], 1 / 2) :
    pow((b[2] * b[1] - b[0]) * delta[0], 1 / 2);
  return (get_right_ans(delta, res, x, d));
}
