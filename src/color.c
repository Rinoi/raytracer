/*
** color.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Tue May 28 09:27:46 2013 karina martynava
** Last update Wed May 29 21:07:04 2013 karina martynava
*/

int		convert_col(float col[3])
{
  unsigned int	color;
  unsigned char	*modif;

  modif = (unsigned char *)&color;
  modif[0] = col[0] * 0xFF;
  modif[1] = col[1] * 0xFF;
  modif[2] = col[2] * 0xFF;
  return (color);
}
