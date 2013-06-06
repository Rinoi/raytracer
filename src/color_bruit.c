/*
** color_bruit.c for rt in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Thu Jun  6 15:03:56 2013 lucas mayol
** Last update Thu Jun  6 18:23:56 2013 lucas mayol
*/

#include "rt.h"

int		color_bruit_bois(t_obj *obj, t_inter *inter)
{
  t_ptn		ptn;
  float		col[3];
  double	valeur;
  double	f;

  ptn.x = inter->ptn.x + 999999;
  ptn.y = inter->ptn.y + 999999;
  ptn.z = inter->ptn.z + 999999;
  valeur = fmod(bruit_coherent3D(&ptn, 0.1), 0.2);
  if (valeur > 0.2 / 2)
    valeur = 0.2 - valeur;
  f = (1 - cos(3.1415 * valeur / (0.2 / 2))) / 2;
  col[2] = valeur;
  col[1] = valeur;
  col[0] = valeur;
  /* col[2] = obj->mat->bruit.color1[0] * (1 - f) */
  /*   + obj->mat->bruit.color2[0] * f; */
  /* col[1] = obj->mat->bruit.color1[1] * (1 - f) */
  /*   + obj->mat->bruit.color2[1] * f; */
  /* col[0] = obj->mat->bruit.color1[2] * (1 - f) */
  /*   + obj->mat->bruit.color2[2] * f; */
  return (convert_col(col));
}
