/*
** patterns.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sun Jun  2 19:19:16 2013 karina martynava
** Last update Sun Jun  9 17:48:54 2013 karina martynava
*/

#include <unistd.h>
#include <stdlib.h>
#include "rt.h"

int		scale_col(int a, int b, int i)
{
  int		col;
  unsigned char	*modif_1;
  unsigned char	*modif_2;
  unsigned char	*modif;

  modif_1 = (unsigned char *)&a;
  modif_2 = (unsigned char *)&b;
  modif = (unsigned char *)&col;
  modif[0] = (i - 1) * modif_1[0] / i + modif_2[0] / i;
  modif[1] = (i - 1) * modif_1[1] / i + modif_2[1] / i;
  modif[2] = (i - 1) * modif_1[2] / i + modif_2[2] / i;
  modif[3] = (i - 1) * modif_1[3] / i + modif_2[3] / i;
  return (col);
}

void	vert_pattern(t_data_t *data, t_st *droit)
{
  int	color;
  int	i;
  float	focus[2];
  int	sv;

  srandom(time(NULL) * getpid());
  i = 0;
  sv = D_Y;
  while (i++ < data->rs->env.complexity && (D_X = sv) == sv)
    {
      focus[0] = data->rs->env.disper * random() / RAND_MAX;
      focus[1] = data->rs->env.disper * random() / RAND_MAX;
      while (D_X <= data->max && (D_Y = 0) == 0)
	{
	  while (D_Y <= data->rs->eyes->larg)
	    {
	      color = antialiasing_color(DT_ANT, droit, data->rs, focus);
	      color = scale_col(get_col(DT_IMG, D_X, D_Y), color, i);
	      my_pixel_put_to_image(DT_IMG, D_X, D_Y++, color);
	    }
	  D_X += 1;
	  if (data->rs->client != 1)
	    mlx_put_image_to_window(DT_MLX, DT_WIND_PTR, DT_IMG_PTR, 0, 0);
	}
    }
}

void	nrml_pattern(t_data_t *data, t_st *droit)
{
  int	color;
  int	i;
  float	focus[2];
  int	sv;

  srandom(time(NULL) * getpid());
  i = 0;
  sv = D_Y;
  while (i++ < data->rs->env.complexity && (D_Y = sv) == sv)
    {
      focus[0] = data->rs->env.disper * random() / RAND_MAX;
      focus[1] = data->rs->env.disper * random() / RAND_MAX;
      while (D_Y <= data->max && (D_X = 0) == 0)
	{
	  while (D_X <= data->rs->eyes->lng)
	    {
	      color = antialiasing_color(DT_ANT, droit, data->rs, focus);
	      color = scale_col(get_col(DT_IMG, D_X, D_Y), color, i);
	      my_pixel_put_to_image(DT_IMG, D_X++, D_Y, color);
	    }
	  D_Y += 1;
	  if (data->rs->client != 1)
	    mlx_put_image_to_window(DT_MLX, DT_WIND_PTR, DT_IMG_PTR, 0, 0);
	}
    }
}

void	alea_pattern(t_data_t *data, t_st *droit)
{
  char	*full;
  int	area;

  if ((full = alea_init(data, &area, droit)) == NULL)
    {
      nrml_pattern(data, droit);
      return ;
    }
  srandom(time(NULL) * getpid());
  alea_apply(data, droit, full, area);
}
