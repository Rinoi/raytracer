/*
** color.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 09:27:46 2013 karina martynava
** Last update Sun Jun  9 15:28:04 2013 karina martynava
*/

#include <math.h>
#include "rt.h"

void	sepia_tone(float col[3])
{
  float	sepia[3];
  float	red;
  float	green;
  float	blue;

  blue = col[0];
  green = col[1];
  red = col[2];
  sepia[2] = (red * 0.393f) + (green * 0.769f) + (blue * 0.189f);
  sepia[1] = (red * 0.349f) + (green * 0.686f) + (blue * 0.168f);
  sepia[0] = (red * 0.272f) + (green * 0.534f) + (blue * 0.131f);
  col[0] = sepia[0];
  col[1] = sepia[1];
  col[2] = sepia[2];
}

void	negative_color(float col[3])
{
  col[0] = 1.0f - col[0];
  col[1] = 1.0f - col[1];
  col[2] = 1.0f - col[2];
}

void	black_and_white(float col[3])
{
  float	medium;

  medium = (col[0] + col[1] + col[2]) / 3.0;
  col[0] = medium;
  col[1] = medium;
  col[2] = medium;
}

void	exposure(float col[3], t_rs *rs)
{
  float		blue;
  float		green;
  float		red;
  float		exposure;

  exposure = rs->env.expo;
  blue = col[0];
  green = col[1];
  red = col[2];
  blue = 1.0f - expf(blue * exposure);
  red = 1.0f - expf(red * exposure);
  green = 1.0f - expf(green * exposure);
  col[0] = blue;
  col[1] = green;
  col[2] = red;
}

int		convert_col(float col[3], t_rs *rs)
{
  unsigned int	color;
  unsigned char	*modif;
  float		max;

  exposure(col, rs);
  if (rs->env.sepia)
    sepia_tone(col);
  max = (col[0] > col[1]) ? col[0] : col[1];
  max = (max > col[2]) ? max : col[2];
  max = (max > 1.0) ? 1.0 / max : 1.0;
  col[0] = col[0] * max;
  col[1] = col[1] * max;
  col[2] = col[2] * max;
  if (rs->env.b_and_w)
    black_and_white(col);
  if (rs->env.negative)
    negative_color(col);
  modif = (unsigned char *)&color;
  modif[0] = (char)(col[0] * 225);
  modif[1] = (char)(col[1] * 255);
  modif[2] = (char)(col[2] * 255);
  return (color);
}
