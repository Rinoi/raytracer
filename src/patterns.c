/*
** patterns.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sun Jun  2 19:19:16 2013 karina martynava
** Last update Thu Jun  6 21:28:58 2013 karina martynava
*/

#include <unistd.h>
#include <stdlib.h>
#include "rt.h"

/* int	focus(t_st *droit, t_rs *rs) */
/* { */
/*   int	tmp; */
/*   float	col[3]; */
/*   int	i; */
/*   t_st	dr_cp; */
/*   t_ptn	disturb; */
/*   t_ptn	goal; */
/*   t_ptn	start; */
/*   t_ptn	dir; */
/*   unsigned char	*modif; */

/*   dir.x = droit->vec.x; */
/*   dir.y = droit->vec.y;  */
/*   dir.z = droit->vec.z; */
/*   mult_vect(&dir, 1 / sqrt(scal_prod(&dir, &dir)));  */
/*   start.x = 500; */
/*   start.y = 500; */
/*   start.z = 0; */
/*   goal.x = start.x + DISPER * dir.x; */
/*   goal.y = start.y + DISPER * dir.y; */
/*   goal.z = start.z + DISPER * dir.z; */
/*   dr_cp = *droit; */
/*   col[0] = 0; */
/*   col[1] = 0; */
/*   col[2] = 0; */
/*   i = 0; */
/*   while (i++ < COMPLEXITY) */
/*     { */
/*       dr_cp = *droit; */
/*       disturb.x = DISPER / RAND_MAX * random(); */
/*       disturb.y = DISPER / RAND_MAX * random(); */
/*       disturb.z = 0; */
/*       dr_cp.cord.y += disturb.x; */
/*       dr_cp.cord.z += disturb.y; */
/*       dr_cp.vec.x = goal.x - dr_cp.cord.x; */
/*       dr_cp.vec.y = goal.y - dr_cp.cord.y; */
/*       dr_cp.vec.z = goal.z - dr_cp.cord.z; */
/*       tmp = antialiasing_color(2, &dr_cp, rs); */
/*       modif = (unsigned char *)&tmp; */
/*       col[0] += modif[0] / 225.0f; */
/*       col[1] += modif[1] / 255.0f; */
/*       col[2] += modif[2] / 255.0f; */
/*     } */
/*   col[0] = col[0] / COMPLEXITY; */
/*   col[1] = col[1] / COMPLEXITY; */
/*   col[2] = col[2] / COMPLEXITY; */
/*   return (convert_col(col)); */
/* } */

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

void	vert_pattern(t_data_t *data, t_st *droit)
{
  int	color;

  droit->x = droit->y;
  while (droit->x <= data->max)
    {
      droit->y = 0;
      while (droit->y <= data->rs->eyes->larg)
	{
	  color = antialiasing_color(2, droit, data->rs);
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

  srandom(time(NULL) * getpid());
  while (droit->y <= data->max)
    {
      droit->x = 0;
      while (droit->x <= data->rs->eyes->lng)
	{
	  color = antialiasing_color(2, droit, data->rs);
	  // color = focus(droit, data->rs);
	  my_pixel_put_to_image(&data->rs->wind.sampled, droit->x, droit->y, color);
	  droit->x += 1;
	}
      droit->y += 1;
      if (data->rs->client != 1)
	mlx_put_image_to_window(data->rs->wind.mlx_ptr, data->rs->wind.wind_ptr,
				data->rs->wind.sampled.img_ptr, 0, 0);
    }
}

char	*alea_init(t_data_t *data, int *area, t_st *droit)
{
  char	*full;
  int	i;

  srandom(time(NULL) * getpid());
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

void	alea_pattern(t_data_t *data, t_st *droit)
{
  char	*full;
  int	area;
  int	i;
  int	j;
  int	num;
  int	color;

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
	  color = antialiasing_color(2, droit, data->rs);
	  my_pixel_put_to_image(&data->rs->wind.sampled, droit->x, droit->y, color);
	}
      if (data->rs->client != 1)
	mlx_put_image_to_window(data->rs->wind.mlx_ptr, data->rs->wind.wind_ptr,
				data->rs->wind.sampled.img_ptr, 0, 0);
    }
}
