/*
** rand_set.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue Jun  4 22:02:21 2013 lucas mayol
** Last update Wed Jun  5 16:08:28 2013 lucas mayol
*/

#include "rt.h"

double	rand_noise_n(int t)
{
  float	r;

  t = (t << 13) ^ t;
  t = (t * ( t * t * 15731 + 789221) + 1376312589);
  r = (1.0 - (t & 0x7fffffff) / 1073741824.0);

  return (r);
}

double	rand_noise(int t)
{
  float	n;

  n = rand_noise_n(t);
  n = (n + 1.0) / 2.;
  /* if (n < 0.5) */
  /*   printf("t : %f\n", n); */
  return (n);
}

double	noise_2d(int x, int y)
{
  float	tmp_x;
  float	tmp_y;

   tmp_x = rand_noise(x) * 850000;
   tmp_y = rand_noise(tmp_x + y);
  //  printf("n : %f\n", tmp_y);
  return (tmp_y);
}

double	noise_3d(int x, int y, int z)
{
  int	tmp_x;
  int	tmp_y;

  tmp_x = rand_noise(x) * 850000;
  tmp_y = rand_noise(tmp_x + y) * 85000;
  return (rand_noise(tmp_y + z));
}
