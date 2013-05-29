/*
** wind.c for RT in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Mon May 27 23:30:59 2013 karina martynava
** Last update Wed May 29 19:10:31 2013 karina martynava
*/
#include		<unistd.h>
#include		<stdlib.h>

#include		"mlx.h"
#include		"rt.h"

#define	ESC_CODE	65307

void	*xpm_img_frmlx(void *mlx_ptr, char *filename,
		       int width, int height)
{
  void	*ret;

  ret = mlx_xpm_file_to_image(mlx_ptr, filename,
			      &width, &height);
  return (ret);
}

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
  rs->bckground.img_ptr =
    xpm_img_frmlx(rs->wind.mlx_ptr,
		  "./img/bck.xpm", 1920, 1080);
  rs->bckground.x = 1920;
  rs->bckground.y = 1080;
  if (rs->bckground.img_ptr != NULL)
    rs->bckground.img =
      mlx_get_data_addr(rs->bckground.img_ptr,
			&(rs->bckground.bpp),
			&(rs->bckground.sizeline),
			&(rs->bckground.endian));
  else
    my_putstr("Background loading failure\n", 2);
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
  usleep(10000);
  return (0);
}


#include <stdio.h>

void	rt_main_mlx(t_rs *rs)
{
  rtv1_ini(rs);
  /* ini_texture(rs); */
  printf("MLX %f, %f, %f\n", rs->eyes->cam.x, rs->eyes->cam.y, rs->eyes->cam.z);
  send_rayon_main(rs);
  mlx_put_image_to_window(rs->wind.mlx_ptr, rs->wind.wind_ptr,
			  rs->wind.img.img_ptr, 0, 0);
  mlx_expose_hook(rs->wind.wind_ptr, my_expose, rs);
  mlx_key_hook(rs->wind.wind_ptr, my_keybrd, rs);
  mlx_loop_hook(rs->wind.mlx_ptr, &my_expose, rs);
  mlx_loop(rs->wind.mlx_ptr);
}
