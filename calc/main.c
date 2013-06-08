/*
** main.c for rt in /home/martyn_k//raytracer/calc
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sat Jun  8 13:25:03 2013 karina martynava
** Last update Sat Jun  8 13:31:07 2013 karina martynava
*/

#include <string.h>
#include <stdio.h>

int	main(int ac, char **av)
{
  int	x;
  float	d[5];

  if (ac == 6)
    {
      printf("HELLO\n");
      d[4] = atoi(av[1]);
      d[3] = atoi(av[2]);
      d[2] = atoi(av[3]);
      d[1] = atoi(av[4]);
      d[0] = atoi(av[5]);
      printf("HELLO %f %f %f %f %f\n", d[4], d[3], d[2], d[1], d[0]);
      resolve_four(d, &x);
    }
}
