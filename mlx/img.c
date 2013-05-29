/*
** img.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Wed May 29 18:59:51 2013 karina martynava
** Last update Wed May 29 19:09:55 2013 karina martynava
*/

#include <rt.h>

int     get_img_color(t_img *img, int x, int y)
{
  int   i;
  int   get;

  get = 0;
  if (img == NULL)
    return (0);
  if (x >= img->x || x < 0 ||
      y >= img->y || y < 0)
    return (0);
  i = img->sizeline * y;
  i += x * img->bpp / 8;
  if (img->endian == 1)
    {
      get = img->img[i + 3] * 0x10000;
      get += img->img[i + 2] * 0x100;
      get += img->img[i + 1];
    }
  else
    {
      get = img->img[i];
      get += img->img[i + 1] * 0x100;
      get += img->img[i + 2] * 0x10000;
    }
  return (get);
}
