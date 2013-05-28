/*
** wind.c for RT in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Mon May 27 23:30:59 2013 karina martynava
** Last update Tue May 28 02:45:05 2013 lucas mayol
*/
#include		<unistd.h>
#include		<stdlib.h>

#include		"mlx.h"
#include		"rt.h"

#define	ESC_CODE	65307

void			rtv1_ini(t_rs *rs)
{
  if ((rs->wind.mlx_ptr = mlx_init()) == NULL)
    {
      my_putstr("Mlx error\n", 2);
      exit(EXIT_FAILURE);
    }
  rs->wind.wind_ptr = mlx_new_window(rs->wind.mlx_ptr,
				     rs->eyes->larg, rs->eyes->lng, "RT");
  rs->wind.img.img_ptr = mlx_new_image(rs->wind.mlx_ptr,
				       rs->eyes->larg, rs->eyes->lng);
  rs->wind.img.img = mlx_get_data_addr(rs->wind.img.img_ptr,
				       &(rs->wind.img.bpp),
				       &(rs->wind.img.sizeline),
				       &(rs->wind.img.endian));
}

int	my_keybrd(int keycode, t_rs *rs)
{
  if (keycode == ESC_CODE)
    {
      mlx_destroy_window(rs->wind.mlx_ptr, rs->wind.wind_ptr);
      exit(EXIT_FAILURE);
    }
  return (0);
}

int	my_expose(t_rs *rs)
{
  mlx_put_image_to_window(rs->wind.mlx_ptr, rs->wind.wind_ptr,
			  rs->wind.img.img_ptr, 0, 0);
  return (0);
}

void	rt_main_mlx(t_rs *rs)
{
  rtv1_ini(rs);
  rs->eyes->cam.x = -14;
  rs->eyes->cam.y = 0;
  rs->eyes->cam.z = 0;
  /* ini_texture(rs); */
  send_rayon_main(rs);
  mlx_put_image_to_window(rs->wind.mlx_ptr, rs->wind.wind_ptr,
			  rs->wind.img.img_ptr, 0, 0);
  mlx_expose_hook(rs->wind.wind_ptr, my_expose, rs);
  mlx_key_hook(rs->wind.wind_ptr, my_keybrd, rs);
  mlx_loop_hook(rs->wind.mlx_ptr, &my_expose, rs);
  mlx_loop(rs->wind.mlx_ptr);
}
