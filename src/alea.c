/*
** alea.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sun Jun  9 17:38:52 2013 karina martynava
** Last update Sun Jun  9 17:48:54 2013 karina martynava
*/

#include <unistd.h>
#include <stdlib.h>
#include "rt.h"

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

  *area = data->rs->eyes->lng * (data->max - data->ini);
  if ((full = malloc(sizeof(*full) * (*area))) == NULL)
    {
      nrml_pattern(data, droit);
      return (NULL);
    }
  return (full);
}

void	update_alea(char *full, int area, t_st *droit, t_data_t *data)
{
  int	num;

  num = random_num_pattern(full, area);
  full[num] = 1;
  D_Y = num / (data->rs->eyes->lng);
  D_X = num % (data->rs->eyes->lng);
}

void	update_focus_alea(int area, t_data_t *data, float focus[2], char *full)
{
  int	k;

  k = 0;
  focus[0] = data->rs->env.disper * random() / RAND_MAX;
  focus[1] = data->rs->env.disper * random() / RAND_MAX;
  while (k < area)
    full[k++] = 0;
}

void	alea_apply(t_data_t *data, t_st *droit, char *full, int area)
{
  int	i;
  int	j;
  int	k;
  float	focus[2];
  int	color;

  i = 0;
  while (i++ < data->rs->env.complexity && (k = data->ini) >= 0)
    {
      update_focus_alea(area, data, focus, full);
      while (k++ < data->max && (j = 0) == 0)
	{
	  while (j++ < data->rs->eyes->lng)
	    {
	      update_alea(full, area, droit, data);
	      color = antialiasing_color(DT_ANT, droit, data->rs, focus);
	      color = scale_col(get_col(DT_IMG, D_X, D_Y), color, i);
	      my_pixel_put_to_image(DT_IMG, D_X, D_Y, color);
	    }
	  if (data->rs->client != 1)
	    mlx_put_image_to_window(DT_MLX, DT_WIND_PTR, DT_IMG_PTR, 0, 0);
	}
    }
}
