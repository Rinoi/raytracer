/*
** main.c for RT in /home/mayol_l//RT
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat Apr 13 13:23:50 2013 lucas mayol
** Last update Mon May 27 23:21:36 2013 karina martynava
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "rtv1.h"

int	main(int argc, char **argv)
{
  int	fd;
  t_rs	rs;

  if (argc == 2)
    {
      /* if ((fd = open(argv[1], O_RDONLY)) == -1) */
      /* 	{ */
      /* 	  my_putstr("open error\n", 2); */
      /* 	  return (EXIT_FAILURE); */
      /* 	} */
      /* my_take_data_for_rs(&rs, fd); */
      /* rs.tree = creat_tree(rs.obj); */
      /* rt_main(&rs); */
    }
  else
    {
      /* my_putstr(argv[0], 2); */
      /* my_putstr(" : file.xml\n", 2); */
    }
  return (EXIT_SUCCESS);
}
