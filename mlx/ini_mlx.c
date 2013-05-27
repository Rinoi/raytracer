/*
** ini_mlx.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Mon May 27 23:31:34 2013 lucas mayol
** Last update Mon May 27 23:34:23 2013 lucas mayol
*/

#include "rt.h"

void	ini_mlx(t_rs *rs)
{
  rs->wind.mlx_ptr = mlx_init();
  if (rs->wind.mlx_ptr == NULL)
    exit(EXIT_FAILURE);
  rs->wind.wind_ptr = mlx_new_window(rs->wind.mlx_ptr,
				     1000, 1000, "RTV1");
  rs->wind.img.img_ptr = mlx_new_image(rs->wind.mlx_ptr,
				       1000, 1000);
  rs->wind.img.img = mlx_get_data_addr(rs->wind.img.img_ptr,
				       &(rs->wind.img.bpp),
				       &(rs->wind.img.sizeline), &(rs->wind.img.endian));
}
