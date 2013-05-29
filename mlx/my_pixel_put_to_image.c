/*
** my_pixel_put_to_image.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Mon May  6 13:51:56 2013 lucas mayol
** Last update Wed May 29 21:07:03 2013 karina martynava
*/

#include "rt.h"

void		my_pixel_put_to_image(t_img *img, int x, int y, unsigned int color)
{
  unsigned char	*col;

  col = (unsigned char*)&color;
  img->img[y * img->sizeline + (img->bpp / 8) * x] = col[0];
  img->img[y * img->sizeline + (img->bpp / 8) * x + 1] = col[1];
  img->img[y * img->sizeline + (img->bpp / 8) * x + 2] = col[2];
  img->img[y * img->sizeline + (img->bpp / 8) * x + 3] = col[3];
}
