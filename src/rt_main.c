/*
** rt_main.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Mon May  6 12:59:28 2013 lucas mayol
** Last update Mon May 27 11:46:21 2013 lucas mayol
*/

#include <stdlib.h>
#include "mlx.h"
#include "../include/rtv1.h"

void	rtv1_ini(t_rs *rs)
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

int	my_expose(t_rs *rs)
{
  mlx_put_image_to_window(rs->wind.mlx_ptr, rs->wind.wind_ptr,
			  rs->wind.img.img_ptr, 0, 0);
  return (0);
}

void	rt_main(t_rs *rs)
{
  rtv1_ini(rs);
  rs->eyes.x = -50;
  rs->eyes.y = 0;
  rs->eyes.z = 0;
  //ini_texture(rs);
  send_rayon_main(rs);
  mlx_put_image_to_window(rs->wind.mlx_ptr, rs->wind.wind_ptr,
			  rs->wind.img.img_ptr, 0, 0);
  mlx_expose_hook(rs->wind.wind_ptr, my_expose, rs);
  mlx_loop_hook(rs->wind.wind_ptr, my_expose, rs);
  while (42)
    {
      usleep(10000);
      my_expose(rs);
    }
  mlx_loop(rs->wind.mlx_ptr);
}
