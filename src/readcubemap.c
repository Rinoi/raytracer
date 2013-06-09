/*
** readcubemap.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sun Jun  9 14:40:03 2013 lucas mayol
** Last update Sun Jun  9 17:49:04 2013 lucas mayol
*/

#include "rt.h"

int	readtexture(t_img *img, float u, float v)
{
  if (img->img == NULL)
    return (0);
  return (get_col(img, u, v));
}

int	readcubemap(t_st *st, t_rs *rs)
{
  if (fabs(st->vec.x) >= fabs(st->vec.y) && fabs(st->vec.x) >= fabs(st->vec.z))
    {
      if (st->vec.x > 0.0f)
	return (readtexture(&rs->cube.right,
			    1.0f - (st->vec.z / st->vec.x + 1.0f) * 0.5f,
			    (st->vec.y / st->vec.x + 1.0f) * 0.5f));
      return (readtexture(&rs->cube.left,
			  1.0f - (st->vec.z / st->vec.x + 1.0f) * 0.5f,
			  1.0f - (st->vec.y / st->vec.x + 1.0f) * 0.5f));
    }
  else if ((fabs(st->vec.y) >= fabs(st->vec.x)) && (fabs(st->vec.y)
						    >= fabs(st->vec.z)))
    {
      if (st->vec.y > 0.0f)
	return (readtexture(&rs->cube.up,
			    (st->vec.x / st->vec.y + 1.0f) * 0.5f,
			    1.0f - (st->vec.z / st->vec.y + 1.0f) * 0.5f));
      return (readtexture(&rs->cube.down,
			  1.0f - (st->vec.x / st->vec.y + 1.0f) * 0.5f,
			  (st->vec.z / st->vec.y + 1.0f) * 0.5f));
    }
  if (st->vec.z > 0.0f)
    return (readtexture(&rs->cube.forward,
			(st->vec.x / st->vec.z + 1.0f) * 0.5f,
			(st->vec.y / st->vec.z + 1.0f) * 0.5f));
  return (readtexture(&rs->cube.backward,
		      (st->vec.x / st->vec.z + 1.0f) * 0.5f,
		      1.0f - (st->vec.y / st->vec.z + 1.0f) * 0.5f));
}
