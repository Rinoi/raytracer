/*
** lol.c for rt in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed Jun  5 18:57:12 2013 lucas mayol
** Last update Thu Jun  6 12:03:39 2013 lucas mayol
*/

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rt.h" 

const double pi = 3.14159265;
 
static int pas1D = 0;
static int nombre_octaves1D = 0;
static int taille = 0;
static double* valeurs1D;
 
static int pas2D = 0;
static int nombre_octaves2D = 0;
static int hauteur = 0;
static int longueur = 0;
static int longueur_max = 0;
static double* valeurs2D;

static int pas3D = 0;
static int nombre_octaves3D = 0;
static int hauteur_3 = 0;
static int longueur_3 = 0;
static int largeur_3 = 0;
static int longueur_max_3 = 0;
static int hauteur_max_3 = 0;
static double* valeurs3D;
 
void initBruit1D(int t, int p, int n) {
  nombre_octaves1D = n;
  if(taille != 0)
    free(valeurs1D);
  taille = t;
  pas1D = p;
 
  valeurs1D = (double*) malloc(sizeof(double) * (int) ceil(taille * pow(2, nombre_octaves1D  - 1)  / pas1D));
 
  srand(time(NULL));
  int i;
  for(i = 0; i < ceil(taille *  pow(2, nombre_octaves1D  - 1)  / pas1D); i++)
    valeurs1D[i] = (double) rand() / RAND_MAX;
}
 
void destroyBruit1D() {
  if(taille != 0)
    free(valeurs1D);
  taille = 0;
}
 
static double bruit1D(int i) {
  return valeurs1D[i];
}
 
static double interpolation_cos1D(double a, double b, double x) {
  double k = (1 - cos(x * pi)) / 2;
  return a * (1 - k) + b * k;
}
 
static double fonction_bruit1D(double x) {
  int i = (int) (x / pas1D);
  return interpolation_cos1D(bruit1D(i), bruit1D(i + 1), fmod(x / pas1D, 1));
}
 
 
double bruit_coherent1D(double x, double persistance) {
  double somme = 0;
  double p = 1;
  int f = 1;
  int i;
 
  for(i = 0 ; i < nombre_octaves1D ; i++) {
    somme += p * fonction_bruit1D(x * f);
    p *= persistance;
    f *= 2;
  }
  return somme * (1 - persistance) / (1 - p);
}
 
void initBruit2D(int l, int h, int p, int n) {
  nombre_octaves2D = n;
  if(taille != 0)
    free(valeurs2D);
  longueur = l;
  hauteur = h;
  pas2D = p;
  longueur_max = (int) ceil(longueur * pow(2, nombre_octaves2D  - 1)  / pas2D);
  int hauteur_max = (int) ceil(hauteur * pow(2, nombre_octaves2D  - 1)  / pas2D);
 
  valeurs2D = (double*) malloc(sizeof(double) * longueur_max * hauteur_max);
 
  srand(time(NULL));
  int i;
  for(i = 0; i < longueur_max * hauteur_max; i++)
    valeurs2D[i] = ((double) rand()) / RAND_MAX;
}
 
void destroyBruit2D() {
  if(longueur != 0)
    free(valeurs2D);
  longueur = 0;
}
 
static double bruit2D(int i, int j) {
  return valeurs2D[(i * longueur_max + j) % (longueur * hauteur)];
}

static double interpolation_cos2D(double a, double b, double c, double d, double x, double y) {
  double y1 = interpolation_cos1D(a, b, x);
  double y2 = interpolation_cos1D(c, d, x);
  return  interpolation_cos1D(y1, y2, y);
}
 
static double fonction_bruit2D(double x, double y) {
  int i = (int) (x / pas2D);
  int j = (int) (y / pas2D);
  return interpolation_cos2D(bruit2D(i, j),
			     bruit2D(i + 1, j),
			     bruit2D(i, j + 1),
			     bruit2D(i + 1, j + 1),
			     fmod(x / pas2D, 1),
			     fmod(y / pas2D, 1));
}

double bruit_coherent2D(double x, double y, double persistance) {
  double somme = 0;
  double p = 1;
  int f = 1;
  int i;
 
  if (x < 0)
    x = -x;
  if (y < 0)
    y = -y;
  for(i = 0 ; i < nombre_octaves2D ; i++) {
    somme += p * fonction_bruit2D(x * f, y * f);
    p *= persistance;
    f *= 2;
  }
  return somme * (1 - persistance) / (1 - p);
}

void initBruit3D(int l, int h, int k, int p, int n) {
  nombre_octaves3D = n;
  longueur_3 = l;
  hauteur_3 = h;
  largeur_3 = k;
  pas3D = p;
  longueur_max_3 = (int) ceil(longueur_3 * pow(2, nombre_octaves3D  - 1)  / pas3D);
  hauteur_max_3 = (int) ceil(hauteur_3 * pow(2, nombre_octaves3D  - 1)  / pas3D);
  int largeur_max = (int) ceil(largeur_3 * pow(2, nombre_octaves3D  - 1)  / pas3D);

  printf("%d %d %d\n", longueur_max_3 , hauteur_max_3 , largeur_max);
  /* valeurs3D = malloc(sizeof(double) * longueur_max_3 * hauteur_max_3 * largeur_max); */
  /* if (valeurs3D == NULL) */
  /*   exit(EXIT_FAILURE); */

  /* srand(time(NULL)); */
  /* int i; */
  /* for(i = 0; i < longueur_max_3 * hauteur_max_3 * largeur_max; i++) */
  /*     valeurs3D[i] = ((double) rand()) / RAND_MAX; */
}

static double bruit3D(int i, int j, int k) {
  return (noise_3d(i, j, k));
  /* return valeurs3D[(i * longueur_max_3 + j * hauteur_max_3 + k) */
  /* 		   % (longueur_3 * hauteur_3 * largeur_3)]; */
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
