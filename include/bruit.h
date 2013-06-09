/*
** bruit.h for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue Jun  4 22:05:03 2013 lucas mayol
** Last update Sun Jun  9 08:41:28 2013 lucas mayol
*/

#ifndef _BRUIT_
# define _BRUIT_

double  rand_noise(int t);
double  noise_2d(int x, int y);
double  noise_3d(int x, int y, int z);

double  linear_interpolate(double a, double b, double t);
double  cosine_interpolate(double a, double b, double t);
double  cosine_interpolate_2d(double a, double b, double c, double d,
			                   double x, double y);
double  cubic_interpolate(double bef, double p0, double p1, double af, double t);

double  smooth_noise_1d(double x);
double  smooth_noise(double x, double y, double z);

double bruit_coherent2D(double x, double y, double persistance);
double bruit_coherent3D(t_ptn *ptn, double persistance);
void initBruit3D(int p, int n);
void initBruit2D(int l, int h, int p, int n);

typedef struct	s_bruit_t
{
  double	a0;
  double	a1;
  double	b0;
  double	b1;
  double	c0;
  double	c1;
  double	d0;
  double	d1;
  double	x;
  double	y;
  double	z;
} t_bruit_t;

#endif
