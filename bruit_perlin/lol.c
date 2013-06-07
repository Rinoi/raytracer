/*
** lol.c for rt in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed Jun  5 18:57:12 2013 lucas mayol
** Last update Fri Jun  7 17:45:29 2013 lucas mayol
*/

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rt.h" 

const double pi = 3.14159265;
 
static int pas3D = 0;
static int nombre_octaves3D = 0;
static int hauteur_3 = 0;
static int longueur_3 = 0;
static int largeur_3 = 0;
static int longueur_max_3 = 0;
static int hauteur_max_3 = 0;
 
static double interpolation_cos1D(double a, double b, double x) {
  double k = (1 - cos(x * pi)) / 2;
  return a * (1 - k) + b * k;
}
 

void initBruit3D(int l, int h, int k, int p, int n) {
  nombre_octaves3D = n;
  longueur_3 = l;
  hauteur_3 = h;
  largeur_3 = k;
  pas3D = p;
  longueur_max_3 = (int) ceil(longueur_3 * pow(2, nombre_octaves3D  - 1)  / pas3D);
  hauteur_max_3 = (int) ceil(hauteur_3 * pow(2, nombre_octaves3D  - 1)  / pas3D);
}

static double bruit3D(int i, int j, int k) {
  return (noise_3d(i, j, k));
}

static double interpolation_cos3D(double a0, double a1,
				  double b0, double b1,
				  double c0, double c1,
				  double d0, double d1,
				  double x, double y, double z) {
  double a = interpolation_cos1D(a0, a1, x);
  double b = interpolation_cos1D(b0, b1, x);
  double e = interpolation_cos1D(a, b, y);
  double c = interpolation_cos1D(c0, c1, x);
  double d = interpolation_cos1D(d0, d1, x);
  double f = interpolation_cos1D(c, d, y);
  return  interpolation_cos1D(e, f, z);
}

static double fonction_bruit3D(double x, double y, double z) {
  int i = (int) (x / pas3D);
  int j = (int) (y / pas3D);
  int k = (int) (z / pas3D);

  return interpolation_cos3D(bruit3D(i, j, k),
			     bruit3D(i + 1, j, k),
			     bruit3D(i, j + 1, k),
			     bruit3D(i + 1, j + 1, k),
			     bruit3D(i, j, k + 1),
			     bruit3D(i + 1, j, k + 1),
			     bruit3D(i, j + 1, k + 1),
			     bruit3D(i + 1, j + 1, k + 1),
			     fmod(x / pas3D, 1),
			     fmod(y / pas3D, 1),
			     fmod(z / pas3D, 1));
}

double	bruit_coherent3D(t_ptn *ptn, double persistance)
{
  double somme = 0;
  double p = 1;
  int f = 1;
  int i;
  
  for(i = 0 ; i < nombre_octaves3D ; i++) {
    somme += p * fonction_bruit3D(ptn->x * f, ptn->y * f, ptn->z * f);
    p *= persistance;
    f *= 2;
  }
  return (somme * (1 - persistance) / (1 - p));
}
