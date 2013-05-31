/*
** supersampl.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Wed May 29 20:40:59 2013 karina martynava
** Last update Thu May 30 18:57:26 2013 karina martynava
*/

#include "mlx.h"
#include "rt.h"

int		get_col(t_img *tex, int x, int y);

int		median_col(int a, int b, int c, int d)
{
  unsigned int	color;
  unsigned char	*modif;
  unsigned char	*m_a;
  unsigned char	*m_b;
  unsigned char	*m_c;
  unsigned char	*m_d;

  modif = (unsigned char *)&color;
  m_a = (unsigned char *)&a;
  m_b = (unsigned char *)&b;
  m_c = (unsigned char *)&c;
  m_d = (unsigned char *)&d;
  modif[0] = (m_a[0] + m_b[0] + m_c[0] + m_d[0]) / 4;
  modif[1] = (m_a[1] + m_b[1] + m_c[1] + m_d[1]) / 4;
  modif[2] = (m_a[2] + m_b[2] + m_c[2] + m_d[2]) / 4;
  modif[3] = (m_a[3] + m_b[3] + m_c[3] + m_d[3]) / 4;
  return (color);
}

void	mlx_supersamp(t_rs *rs, int init, int to)
{
  int	color;
  int	x;
  int	y;
 
  x = init / 2;
  while (x < to)
    {
      y = 0;
      while (y < rs->wind.sampled.y)
	{
	  color =
	    median_col(get_col(&rs->wind.img, x * 2, y * 2),
		       get_col(&rs->wind.img, x * 2, y * 2 + 1),
		       get_col(&rs->wind.img, x * 2 + 1, y * 2),
		       get_col(&rs->wind.img, x * 2 + 1, y * 2 + 1));
	  my_pixel_put_to_image(&(rs->wind.sampled), x, y, color);
	  y++;
	}
      x++;
    }
}
