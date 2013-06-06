/*
** call_color.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Thu May 30 17:28:25 2013 lucas mayol
** Last update Thu Jun  6 11:56:55 2013 lucas mayol
*/

#include <stdio.h>
#include "rt.h"

int	cal_texture_sphere(t_obj *obj, t_ptn inter)
{
  float	x;
  float	y;
  float	pc;

  inter.x -= obj->ptn.x;
  inter.y -= obj->ptn.y;
  inter.z -= obj->ptn.z;

  pc = inter.y;
  x = acos( - (pc / sqrt(pow(inter.x, 2) + pow(inter.y, 2) + pow(inter.z, 2))));
  x =  x / (3.1415);
  x *= obj->mat->img.x;

  pc = inter.z;
  y = acos(- (pc / sqrt(pow(inter.x, 2) + pow(inter.y, 2) + pow(inter.z, 2))));
  y = y / (3.1415);
  y *= obj->mat->img.y;
  if (y < 0 || x < 0)
    {
      printf("max %d %d\n", obj->mat->img.x, obj->mat->img.y);
      printf("x %f y %f\n", x, y);
    }
  return (get_col(&obj->mat->img, x, y));
}

static double seuil = 0.2;

static double c1[3] = {0.6, 0.6, 0.0}; // brun clair
static double c2[3] = {0.2, 0.2, 0.0}; // brun foncé

int    color_bruit(int x, int y, int z)
{
  t_ptn ptn;
  float col[3];
  unsigned int c;
  ptn.x = x + 99999;
  ptn.y = y + 99999;
  ptn.z = z + 99999;
  double valeur = fmod(bruit_coherent3D(&ptn, 0.1), seuil);
  if(valeur > seuil / 2)
    valeur = seuil - valeur;

  double f = (1 - cos(3.1415 * valeur / (seuil / 2))) / 2;
  col[2] = c1[0] * (1 - f) + c2[0] * f;
  col[1] = c1[1] * (1 - f) + c2[1] * f;
  col[0] = c1[2] * (1 - f) + c2[2] * f;
  /* col[2] = valeur; */
  /* col[1] = valeur; */
  /* col[0] = valeur; */
  //  printf("%f %f %f\n", col[0], col[1], col[2]);
  return (convert_col(col));
}

void		cal_color_shere(t_obj *obj, t_inter *inter, float tab[3])
{
  int		color;
  unsigned char	*tabs;

  if (obj->mat != NULL && obj->mat->img.img != NULL)
    {
      color = cal_texture_sphere(obj, inter->ptn);
      tabs = (unsigned char *)&color;
      tab[0] = (unsigned char)tabs[0] / 255.0;
      tab[1] = (unsigned char)tabs[1] / 255.0;
      tab[2] = (unsigned char)tabs[2] / 255.0;
    }
  else
    {
      tab[0] = 1;
      tab[1] = 1;
      tab[2] = 1;
      color = color_bruit(inter->ptn.x - obj->ptn.x,
      			  inter->ptn.y - obj->ptn.y,
      			  inter->ptn.z - obj->ptn.z);
      tabs = (unsigned char *)&color;
      tab[0] = (unsigned char)tabs[0] / 255.0;
      tab[1] = (unsigned char)tabs[1] / 255.0;
      tab[2] = (unsigned char)tabs[2] / 255.0;
      /* if (obj->mat != NULL) */
      /* 	{ */
      /* 	  tab[0] = obj->mat->blue; */
      /* 	  tab[1] = obj->mat->green; */
      /* 	  tab[2] = obj->mat->red; */
      /* 	} */
      /* else */
      /* 	{ */
      /* 	  tab[0] = 1; */
      /* 	  tab[1] = 1; */
      /* 	  tab[2] = 1; */
      /* 	} */
    }
}
