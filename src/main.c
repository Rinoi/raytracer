/*
** main.c for RT in /home/mayol_l//RT
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat Apr 13 13:23:50 2013 lucas mayol
** Last update Tue May 28 01:49:32 2013 karina martynava
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "rt.h"

#define	SIZE_LARG	500;
#define	SIZE_LONG	500;

int	init_rs(t_rs *rs)
{
  float	*r;

  rs->aff = NULL;
  rs->send_rayon = NULL;
  rs->eyes = malloc(sizeof(*(rs->eyes)));
  if (rs->eyes == NULL)
    return (EXIT_FAILURE);
  rs->obj_inf = NULL;
  rs->obj = NULL;
  rs->tree = NULL;
  rs->eyes->cam.x = 0;
  rs->eyes->cam.y = 0;
  rs->eyes->cam.z = -50;
  rs->eyes->rot.x = 0;
  rs->eyes->rot.y = 0;
  rs->eyes->rot.z = 0;
  rs->eyes->larg = SIZE_LARG;
  rs->eyes->lng = SIZE_LONG;
  
  if ((rs->obj_inf = malloc(sizeof(*(rs->obj_inf)))) == NULL)
    return (EXIT_FAILURE);
  rs->obj_inf->next = NULL;
  rs->obj_inf->ptn.x = 0;
  rs->obj_inf->ptn.y = 0;
  rs->obj_inf->ptn.z = 0;
  rs->obj_inf->rot.x = 0;
  rs->obj_inf->rot.y = 0;
  rs->obj_inf->rot.z = 0;
  rs->obj_inf->mat = NULL;
  rs->obj_inf->matrix = NULL;
  r = malloc(sizeof(float));
  *r = 5;
  rs->obj_inf->data = (void *)r;
  return (EXIT_SUCCESS);
}

int	main(int argc, __attribute__((unused))char **argv)
{
  int	fd;
  t_rs	rs;

  if (argc == 2)
    {
      if ((fd = open(argv[1], O_RDONLY)) == -1)
      	{
      	  my_putstr("open error\n", 2);
      	  return (EXIT_FAILURE);
      	}
      if (init_rs(&rs) == EXIT_FAILURE)
	return (EXIT_FAILURE);
      /* my_take_data_for_rs(&rs, fd); */
      /* rs.tree = creat_tree(rs.obj); */
      rt_main_mlx(&rs);
    }
  else
    {
      my_putstr(argv[0], 2);
      my_putstr(" : file.xml\n", 2);
    }
  return (EXIT_SUCCESS);
}
