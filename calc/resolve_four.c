/*
** resolve_four.c for rt in /home/martyn_k/raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 02:33:40 2013 karina martynava
** Last update Sat Jun  8 19:25:33 2013 lucas mayol
*/

#include <unistd.h>
#include <stdio.h>
#include <values.h>
#include <math.h>

float	resolve_three(float d[4], int *x);

#define	EPSILLON	0

float	right_root_four(float root[4], int *x)
{
  int	i;
  float	ret;

  ret = MAXFLOAT;
  i = 0;
  while (i < 4)
    {
      if (root[i] != MAXFLOAT && root[i] > EPSILLON && \
	  (ret == MAXFLOAT || ret > root[i]))
	{
	  ret = root[i];
	  *x = i;
	}
      i++;
    }
  return (ret);
}

float	ferrari_rules(int *x, float ans, float abc[3], float bs)
{
  int	k;
  float	rts[4];
  float	tmp;
  float	z;

  z = abc[1] / 2 / (ans - abc[0]);
  k = 0;
  while (k < 4)
    rts[k++] = MAXFLOAT;
  k = 0;
  tmp = ans - abc[0] - 4 * (z * sqrt(ans - abc[0]) + ans / 2);
  if (tmp >= 0 && ++k)
    {
      rts[0] = (sqrt(ans - abc[0]) + sqrt(tmp)) / 2 - bs;
      rts[1] = (sqrt(ans - abc[0]) - sqrt(tmp)) / 2 - bs;
    }
  tmp = ans - abc[0] - 4 * (-z * sqrt(ans - abc[0]) + ans / 2);
  if (tmp >= 0 && ++k)
    {
      rts[2] = (-sqrt(ans - abc[0]) + sqrt(tmp)) / 2 - bs;
      rts[3] = (-sqrt(ans - abc[0]) - sqrt(tmp)) / 2 - bs;
    }
  if (k == 0)
    return (MAXFLOAT);
  return (right_root_four(rts, x));
}

float	sqrt_from_second(float abc[3], int *x, float bs)
{
  float	rts[4];
  float	delta;
  int	i;

  i = 0;
  while (i < 4)
    rts[i++] = MAXFLOAT;
  delta = abc[0] * abc[0] - 4 * abc[2];
  if (delta < 0)
    return (MAXFLOAT);
  rts[0] = (- abc[0] - sqrt(delta)) / 2.0;
  rts[2] = (- abc[0] + sqrt(delta)) / 2.0;
  rts[3] = (rts[1] >= 0) ? - sqrt(rts[1]) - bs : MAXFLOAT;
  rts[2] = (rts[1] >= 0) ? sqrt(rts[1]) - bs : MAXFLOAT;
  rts[1] = (rts[0] >= 0) ? - sqrt(rts[0]) - bs : MAXFLOAT;
  rts[0] = (rts[0] >= 0) ? sqrt(rts[0]) - bs : MAXFLOAT;
  return (right_root_four(rts, x));
}

float	resolve_four(float d[5], int *x)
{
  float	abc[3];
  float	eq[4];
  float	ans;
  int	k;

  if (d[4] == 0)
    return (resolve_three(d, x));
  abc[0] = - 3.0 * d[3] * d[3] / 8 / d[4] / d[4] + d[2] / d[4];
  abc[1] = pow(d[3] * 0.5, 3) / d[4] / d[4] / d[4] \
    - 0.5 * d[3] * d[2] / d[4] / d[4] + d[1] / d[4];
  abc[2] = - 3.0 * pow(d[3] / 4.0 / d[4], 4.0) + d[2] * pow(d[3] / 4.0, 2) \
    / pow(d[4], 3) - 0.250 * d[3] * d[1] / d[4] / d[4] + d[0] / d[4];
  if (abc[1] == 0)
    return (sqrt_from_second(abc, x, d[3] / 4 / d[4]));
  eq[3] = 1.0;
  eq[2] = - abc[0];
  eq[1] = - 4 * abc[2];
  eq[0] = 4 * abc[0] * abc[2] - abc[1] * abc[1];
  ans = resolve_three(eq, &k);
  return (ferrari_rules(x, ans, abc, d[3] / 4 / d[4]));
}
