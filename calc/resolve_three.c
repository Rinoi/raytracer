/*
** resolve_three.c for rt in /home/martyn_k/raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 02:09:42 2013 karina martynava
** Last update Fri May 31 15:50:06 2013 karina martynava
*/

#include <values.h>
#include <math.h>
#include <stdio.h>

float	resolve_two_bis(float a, float b, float c);

#define RET_VAL 0

float arrondi(float x)
{
  if (x > 0)
    return (floor(fabs(x) * 1e10 + 0.5) / 1e10);
  if (x < 0)
    return (- floor(fabs(x) * 1e10 + 0.5) / 1e10);
  return (0);
}

float uv(float a, float b)
{
  float	delta_prime;
  float	m;
  float	n;
  float	u;
  float	v;

  delta_prime = 4.0 * a * a * a + 27.0 * b * b;
  m = - b * 0.5 + 0.5 * sqrt(delta_prime / 27.0);
  n = - b * 0.5 - 0.5 * sqrt(delta_prime / 27.0);
  u = (m < 0) ? - 1.0 : 1.0;
  v = (n < 0) ? - 1.0 : 1.0;
  m = pow(fabs(m), 1.0 / 3.0) * u;
  n = pow(fabs(n), 1.0 / 3.0) * v;
  return (m + n);
}

float	right_root_three(float root[3], int *x)
{
  int	i;
  float	ret;

  ret = MAXFLOAT;
  i = 0;
  while (i < 3)
    {
      if (root[i] != MAXFLOAT)
	return (root[i]);
      if (root[i] != MAXFLOAT && root[i] > RET_VAL && \
	  (ret == MAXFLOAT || ret > root[i]))
	{
	  ret = root[i];
	  *x = i;
	}
      /* printf("%f\n", root[i]); */
      i++;
    }
  /* printf("%f\n", ret); */
  return (ret);
}

float	via_cadran(float eq[4], int *x, float rts[3])
{
  float	delta;
  float	a;
  float	b;
  float	kos;
  float	r;
  int	i;

  a = eq[1] / eq[3] - eq[2] * eq[2] / (3.0 * eq[3] * eq[3]);
  b = 2.0 * eq[2] * eq[2] * eq[2] / (27.0 * eq[3] * eq[3] * eq[3]);
  b += - eq[2] * eq[1] / (3.0 * eq[3] * eq[3]) + eq[0] / eq[3];
  delta = pow(a / 3.0, 3) + pow(b / 2.0, 2);
  /* printf("A = %f, B = %f, D = %f\n", a, b, delta); */
  if (delta <= 0)
    {
      i = 3;
      kos = (a) ? -b / 2.0 / sqrt(- a * a * a / 27.0) : 0;
      r = (a) ? sqrt(- a / 3) : 0;
      kos = (fabsf(fabsf(kos) - 1) < 1e-14) ?
	- M_PI * (kos - 1) / 2 : acos(kos);
      while (i-- > 0)
	rts[i] = 2 * r * cos((kos + 2 * i * M_PI) / 3) \
	  - eq[2] / (3 * eq[3]);
    }
  else
    rts[0] = uv(a, b) - eq[2] / (3 * eq[3]);
  return (right_root_three(rts, x));
}

float	resolve_three(float eq[4], int *x)
{
  int	i;
  float	rts[3];

  i = 0;
  while (i < 3)
    rts[i++] = MAXFLOAT;
  if (eq[3] == 0)
    return (resolve_two_bis(eq[2], eq[1], eq[0]));
  return (via_cadran(eq, x, rts));
}
