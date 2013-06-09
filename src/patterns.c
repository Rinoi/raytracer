/*
** patterns.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sun Jun  2 19:19:16 2013 karina martynava
** Last update Sun Jun  9 16:05:17 2013 karina martynava
*/

#include <unistd.h>
#include <stdlib.h>
#include "rt.h"

int		scal_color_img(int a, int b, int i)
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

int	random_num_pattern(char *full, int area)
{
  int	num;

  num = random() % area;
  while (full[num] != 0)
    {
      num++;
      if (num == area)
	num = 0;
    }
  return (num);
}

char	*alea_init(t_data_t *data, int *area, t_st *droit)
{
  char	*full;
  int	i;

  *area = data->rs->eyes->lng * (data->max - data->ini);
  if ((full = malloc(sizeof(*full) * (*area))) == NULL)
    {
      nrml_pattern(data, droit);
      return (NULL);
    }
  i = 0;
  while (i < *area)
    full[i++] = 0;
  return (full);
}

void	vert_pattern(t_data_t *data, t_st *droit)
{
  int	color;
  int	i;
  float	focus[2];
  int	sv;

  srandom(time(NULL) * getpid());
  i = 0;
  sv = droit->y;
  while (i++ < data->rs->env.complexity)
    {
      focus[0] = data->rs->env.disper * random() / RAND_MAX;
      focus[1] = data->rs->env.disper * random() / RAND_MAX;
      droit->x = sv;
      while (droit->x <= data->max)
	{
	  droit->y = 0;
	  while (droit->y <= data->rs->eyes->larg)
	    {
	      color = antialiasing_color(data->rs->env.antia, droit, data->rs, focus);
	      color = scal_color_img(get_col(&data->rs->wind.sampled, droit->x, droit->y), color, i);
	      my_pixel_put_to_image(&data->rs->wind.sampled, droit->x, droit->y, color);
	      droit->y += 1;
	    }
	  droit->x += 1;
	  if (data->rs->client != 1)
	    mlx_put_image_to_window(data->rs->wind.mlx_ptr, data->rs->wind.wind_ptr,
				    data->rs->wind.sampled.img_ptr, 0, 0);
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
  sv = droit->y;
  while (i++ < data->rs->env.complexity)
    {
      focus[0] = data->rs->env.disper * random() / RAND_MAX;
      focus[1] = data->rs->env.disper * random() / RAND_MAX;
      droit->y = sv;
      while (droit->y <= data->max)
	{
	  droit->x = 0;
	  while (droit->x <= data->rs->eyes->lng)
	    {
	      color = antialiasing_color(data->rs->env.antia, droit, data->rs, focus);
	      color = scal_color_img(get_col(&data->rs->wind.sampled, droit->x, droit->y), color, i);
	      my_pixel_put_to_image(&data->rs->wind.sampled, droit->x, droit->y, color);
	      droit->x += 1;
	    }
	  droit->y += 1;
	  if (data->rs->client != 1)
	    mlx_put_image_to_window(data->rs->wind.mlx_ptr, data->rs->wind.wind_ptr,
				    data->rs->wind.sampled.img_ptr, 0, 0);
	}
    }
}

void	alea_pattern(t_data_t *data, t_st *droit)
{
  char	*full;
  int	area;
  int	i;
  int	j;
  int	k;
  int	num;
  int	color;
  float	focus[2];

  srandom(time(NULL) * getpid());
  k = 0;
  while (k++ < data->rs->env.complexity)
    {
      focus[0] = data->rs->env.disper * random() / RAND_MAX;
      focus[1] = data->rs->env.disper * random() / RAND_MAX;
      if ((full = alea_init(data, &area, droit)) == NULL)
	return ;
      j = data->ini;
      while (j++ < data->max)
	{
	  i = 0;
	  while (i++ < data->rs->eyes->lng)
	    {
	      num = random_num_pattern(full, area);
	      full[num] = 1;
	      droit->y = num / (data->rs->eyes->lng);
	      droit->x = num % (data->rs->eyes->lng);
	      color = antialiasing_color(data->rs->env.antia, droit, data->rs, focus);
	      my_pixel_put_to_image(&data->rs->wind.sampled, droit->x, droit->y, color);
	    }
	  if (data->rs->client != 1)
	    mlx_put_image_to_window(data->rs->wind.mlx_ptr, data->rs->wind.wind_ptr,
				    data->rs->wind.sampled.img_ptr, 0, 0);
	}
    }
}
