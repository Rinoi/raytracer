/*
** patterns.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sun Jun  2 19:19:16 2013 karina martynava
** Last update Sat Jun  8 12:25:19 2013 karina martynava
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
  float	focus[COMPLEXITY][2];

  srandom(time(NULL) * getpid());
  i = 0;
  while (i < COMPLEXITY)
    {
      focus[i][0] = DISPER * random() / RAND_MAX;
      focus[i++][1] = DISPER * random() / RAND_MAX;
    }
  droit->x = droit->y;
  while (droit->x <= data->max)
    {
      droit->y = 0;
      while (droit->y <= data->rs->eyes->larg)
	{
	  color = antialiasing_color(2, droit, data->rs, focus);
	  my_pixel_put_to_image(&data->rs->wind.sampled, droit->x, droit->y, color);
	  droit->y += 1;
	}
      droit->x += 1;
      if (data->rs->client != 1)
	mlx_put_image_to_window(data->rs->wind.mlx_ptr, data->rs->wind.wind_ptr,
				data->rs->wind.sampled.img_ptr, 0, 0);
    }
}

void	nrml_pattern(t_data_t *data, t_st *droit)
{
  int	color;
  int	i;
  float	focus[COMPLEXITY][2];

  srandom(time(NULL) * getpid());
  i = 0;
  while (i < COMPLEXITY)
    {
      focus[i][0] = DISPER * random() / RAND_MAX;
      focus[i++][1] = DISPER * random() / RAND_MAX;
    }
  while (droit->y <= data->max)
    {
      droit->x = 0;
      while (droit->x <= data->rs->eyes->lng)
	{
	  color = antialiasing_color(2, droit, data->rs, focus);
	  my_pixel_put_to_image(&data->rs->wind.sampled, droit->x, droit->y, color);
	  droit->x += 1;
	}
      droit->y += 1;
      if (data->rs->client != 1)
	mlx_put_image_to_window(data->rs->wind.mlx_ptr, data->rs->wind.wind_ptr,
				data->rs->wind.sampled.img_ptr, 0, 0);
    }
}

void	alea_pattern(t_data_t *data, t_st *droit)
{
  char	*full;
  int	area;
  int	i;
  int	j;
  int	num;
  int	color;
  float	focus[COMPLEXITY][2];

  srandom(time(NULL) * getpid());
  i = 0;
  while (i < COMPLEXITY)
    {
      focus[i][0] = DISPER * random() / RAND_MAX;
      focus[i++][1] = DISPER * random() / RAND_MAX;
    }
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
	  color = antialiasing_color(2, droit, data->rs, focus);
	  my_pixel_put_to_image(&data->rs->wind.sampled, droit->x, droit->y, color);
	}
      if (data->rs->client != 1)
	mlx_put_image_to_window(data->rs->wind.mlx_ptr, data->rs->wind.wind_ptr,
				data->rs->wind.sampled.img_ptr, 0, 0);
    }
}
