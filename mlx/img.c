/*
** img.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Wed May 29 18:59:51 2013 karina martynava
** Last update Wed May 29 21:14:08 2013 lucas mayol
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

void    load_img(t_rs *rs, t_img *text, char *str)
{
  text->img_ptr = mlx_xpm_file_to_image(rs->wind.mlx_ptr,
                                    str, &text->x, &text->y);
  if (text->img_ptr != NULL)
    {
      text->img = mlx_get_data_addr(text->img,
				    &(text->bpp),
				    &(text->sizeline), &(text->endian));
    }
  else
    text->img = NULL;
}

int		my_get_color_text(t_img *tex, int x, int y)
{
  unsigned int	*color;
  unsigned char	cl[3];

  if (tex != NULL)
    {
      color = (unsigned int*)cl;
      cl[0] = (unsigned char)tex->img[y * tex->sizeline + (tex->bpp / 8) *
                                       x];
      cl[1] = (unsigned char)tex->img[y * tex->sizeline + (tex->bpp / 8) *
                                       x + 1];
      cl[2] = (unsigned char)tex->img[y * tex->sizeline + (tex->bpp / 8) *
                                       x + 2];
      cl[3] = (unsigned char)tex->img[y * tex->sizeline + (tex->bpp / 8) *
                                       x + 3];
      return (*color);
    }
  else
    return (0);
}
