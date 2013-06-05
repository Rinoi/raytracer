/*
** my_put.c for rtv1 in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue Feb 19 21:47:47 2013 lucas mayol
** Last update Tue May 28 00:12:09 2013 karina martynava
*/

#include <stdlib.h>
#include <unistd.h>
#include "rt.h"

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    i = i + 1;
  return (i);
}

void	my_putchar(char c, int fd)
{
  if (write(fd, &c, 1) == -1)
    {
      my_putstr("write error", 2);
      exit(EXIT_FAILURE);
    }
}

void	my_putstr(char *str, int fd)
{
  if (write(fd, str, my_strlen(str)) == -1)
    {
      my_putstr("write error", 2);
      exit(EXIT_FAILURE);
    }
}
