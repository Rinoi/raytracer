/*
** color_bruit.c for rt in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Thu Jun  6 15:03:56 2013 lucas mayol
** Last update Thu Jun  6 15:51:34 2013 lucas mayol
*/

#include "rt.h"

int		color_bruit_bois(t_obj *obj, t_inter *inter)
{
  t_ptn		ptn;
  float		col[3];
  double	valeur;
  double	f;

  ptn.x = obj->ptn.x + 999999;
  ptn.x = obj->ptn.x + 999999;
  ptn.x = obj->ptn.x + 999999;
  valeur = fmod(bruit_coherent3D(&ptn, 0.1), 0.2);
  if (valeur > 0.2 / 2)
    valeur = 0.2 - valeur;
  f = (1 - cos(3.1415 * valeur / (0.2 / 2))) / 2;
  col[2] = obj->mat->bruit.color1.x * (1 - f)
    + obj->mat->bruit.color2.x * f;
  col[1] = obj->mat->bruit.color1.y * (1 - f)
    + obj->mat->bruit.color2.y * f;
  col[0] = obj->mat->bruit.color1.z * (1 - f)
    + obj->mat->bruit.color2.z * f;
  return (convert_col(col));
}
