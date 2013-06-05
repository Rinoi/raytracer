/*
** antialiasing.c for rt in /home/martyn_k//raytracer/src
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sun Jun  2 20:18:27 2013 karina martynava
** Last update Wed Jun  5 21:02:19 2013 thibault martinez
*/

#include "rt.h"

void	antialiasing_init(int *i, float final_col[3])
{
  *i = 0;
  final_col[0] = 0;
  final_col[1] = 0;
  final_col[2] = 0;
}

void	stereoscopic(float cyan[3], float red[3])
{
  cyan[1] = red[1];
  cyan[2] = red[2];
}

void	second_img(int antialias, t_st *droit, t_rs *rs, float goal[3])
{
  int	i;
  int	j;
  float	final_col[4];
  float	col[3];
  float	antia;

  antia = (antialias % 2 != 0 || antialias == 0) ? 1.0f : 1.0f / antialias;
  antialiasing_init(&i, final_col);
  while (i < antialias)
    {
      j = 0;
      droit->vec.z = (rs->eyes->larg / 2 - droit->y + i++ * antia) ;
      while (j < antialias)
	{
	  droit->vec.y = rs->eyes->larg / 2 - droit->x + j++ * antia;
	  my_send_rayon(rs, droit, col);
	  final_col[0] += col[0];
	  final_col[1] += col[1];
	  final_col[2] += col[2];
	}
    }
  goal[0] = final_col[0] * antia;
  goal[1] = final_col[1] * antia;
  goal[2] = final_col[2] * antia;
}

int	antialiasing_color(int antialias, t_st *droit, t_rs *rs)
{
  int	i;
  int	j;
  float	final_col[4];
  float	col[3];
  float	antia;

  antia = (antialias % 2 != 0 || antialias == 0) ? 1.0f : 1.0f / antialias;
  antialiasing_init(&i, final_col);
  while (i < antialias)
    {
      j = 0;
      droit->vec.z = rs->eyes->larg / 2 - droit->y + i++ * antia;
      while (j < antialias)
	{
	  droit->vec.y = rs->eyes->larg / 2 - droit->x + j++ * antia;
	  my_send_rayon(rs, droit, col);
	  final_col[0] += col[0];
	  final_col[1] += col[1];
	  final_col[2] += col[2];
	}
    }
  final_col[0] = final_col[0] * antia;
  final_col[1] = final_col[1] * antia;
  final_col[2] = final_col[2] * antia;
  return (convert_col(final_col));
}
