/*
** color.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 09:27:46 2013 karina martynava
** Last update Sat Jun  1 20:09:44 2013 karina martynava
*/

#define	EXPO	-0.66f

#include <math.h>
#include "rt.h"

int		convert_col(float col[3])
{
  unsigned int	color;
  unsigned char	*modif;
  float		max;

  max = (col[0] > col[1]) ? col[0] : col[1];
  max = (max > col[2]) ? max : col[2];
  max = (max > 1.0) ? 1.0 / max : 1.0;
  col[0] = col[0] * max;
  col[1] = col[1] * max;
  col[2] = col[2] * max;
  if (B_AND_W || SEPIA)
    {
      max = (col[0] + col[1] + col[2]) / 3.0;
      col[0] = max;
      col[1] = max;
      col[2] = max;
      /* printf("%f %f %f\n", col[0], col[1], col[2]); */
      if (SEPIA)
      	{
      	  col[0] = col[0] * SEP_BLUE / 255.0f;
      	  col[1] = col[1] * SEP_GREEN / 255.0f;
      	  col[2] = col[2] * SEP_RED / 255.0f;
      	}
      /* printf("%f %f %f\n", col[0], col[1], col[2]); */
    }
  modif = (unsigned char *)&color;
  modif[0] = col[0] * 0xFF;
  modif[1] = col[1] * 0xFF;
  modif[2] = col[2] * 0xFF;
  return (color);
}
