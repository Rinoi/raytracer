/*
** noise.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed Jun  5 14:40:53 2013 lucas mayol
** Last update Wed Jun  5 18:07:42 2013 lucas mayol
*/

#include "rt.h"

double		smooth_noise_1d(double x)
{
  int		int_x;
  double	float_x;
  double	a;
  double	b;

  int_x = (int)(x);
  float_x = x - int_x;
  a = rand_noise(int_x);
  b = rand_noise(int_x + 1);

  return (linear_interpolate(a, b, float_x));
}

double		smooth_noise(double x, double y, double z)
{
  int		my_int[3];
  double       	my_float[3];
  double	a[2];
  double	b[2];
  double	c[2];
  double	d[2];
  double	res[6];

  my_int[0] = (int)(x);
  my_int[1] = (int)(y);
  my_int[2] = (int)(z);
  my_float[0] = my_int[0] - x;
  my_float[1] = my_int[1] - y;
  my_float[2] = my_int[2] - z;

  a[0] = noise_3d(my_int[0], my_int[1], my_int[2]);
  a[1] = noise_3d(my_int[0] + 1, my_int[1], my_int[2]);

  b[0] = noise_3d(my_int[0], my_int[1] + 1, my_int[2]);
  b[1] = noise_3d(my_int[0] + 1, my_int[1] + 1, my_int[2]);

  c[0] = noise_3d(my_int[0], my_int[1], my_int[2] + 1);
  c[1] = noise_3d(my_int[0] + 1, my_int[1], my_int[2] + 1);

  d[0] = noise_3d(my_int[0], my_int[1] + 1, my_int[2] + 1);
  d[1] = noise_3d(my_int[0] + 1, my_int[1] + 1, my_int[2] + 1);

  res[0] = cosine_interpolate(a[0], a[1], my_float[0]);
  res[1] = cosine_interpolate(b[0], b[1], my_float[0]);
  res[2] = cosine_interpolate(c[0], c[1], my_float[0]);
  res[3] = cosine_interpolate(d[0], d[1], my_float[0]);
  res[4] = cosine_interpolate(res[0], res[1], my_float[1]);
  res[5] = cosine_interpolate(res[2], res[3], my_float[1]);
  //  printf("r : %f\n",  cosine_interpolate(res[4], res[5], my_float[2]));
  return (cosine_interpolate(res[4], res[5], my_float[2]));
}