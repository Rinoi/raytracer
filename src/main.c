/*
** main.c for RT in /home/mayol_l//RT
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat Apr 13 13:23:50 2013 lucas mayol
** Last update Sat Jun  1 00:42:10 2013 karina martynava
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
  float	*b;
  t_mat	*a;
  t_mat	*c;

  rs->aff = NULL;
  rs->send_rayon = NULL;
  rs->eyes = malloc(sizeof(*(rs->eyes)));

  // MATERIEEEL
  if ((rs->mat = malloc(sizeof(*(rs->mat)))) == NULL)
    return (EXIT_FAILURE);
  rs->mat->red = 0.2;
  rs->mat->green = 0.2;
  rs->mat->blue = 1;
  rs->mat->reflex = 0.5;
  if ((a = malloc(sizeof(*a))) == NULL)
    return (EXIT_FAILURE);
  a->red = 0.4;
  a->green = 1;
  a->blue = 1;
  a->reflex = 0.5;
  if ((c = malloc(sizeof(*c))) == NULL)
    return (EXIT_FAILURE);
  c->red = 1;
  c->green = 0.8;
  c->blue = 0;
  c->reflex = 0.5;


  // SPHERES
  if (rs->eyes == NULL)
    return (EXIT_FAILURE);
  rs->obj_inf = NULL;
  rs->obj = NULL;
  rs->tree = NULL;
  rs->eyes->cam.x = -50;
  rs->eyes->cam.y = 0;
  rs->eyes->cam.z = 0;
  rs->eyes->rot.x = 0;
  rs->eyes->rot.y = 0;
  rs->eyes->rot.z = 0;
  rs->eyes->larg = SIZE_LARG;
  rs->eyes->lng = SIZE_LONG;
  if ((rs->obj = malloc(sizeof(*(rs->obj)))) == NULL)
    return (EXIT_FAILURE);
  rs->obj->next = NULL;
  rs->obj->mat = a;
  rs->obj->ptn.x = 0;
  rs->obj->ptn.y = 0;
  rs->obj->ptn.z = -10;
  rs->obj->rot.x = 0;
  rs->obj->rot.y = 0;
  rs->obj->rot.z = 0;
  rs->obj->matrix = NULL;
  rs->obj->cal_inter = call_inter_sphere;
  rs->obj->cal_color = cal_color_cylinder;
  r = malloc(sizeof(float));
  *r = 10;
  rs->obj->data = (void *)r;
  creat_matrice_for_obj(rs->obj);
  if ((rs->obj->next = malloc(sizeof(*(rs->obj->next)))) == NULL)
    return (EXIT_SUCCESS);
  rs->obj->next->next = NULL;
  rs->obj->next->mat = rs->mat;
  rs->obj->next->ptn.x = 0;
  rs->obj->next->ptn.y = 0;
  rs->obj->next->ptn.z = 10;
  rs->obj->next->rot.x = 0;
  rs->obj->next->rot.y = 0;
  rs->obj->next->rot.z = 0;
  rs->obj->next->matrix = NULL;
  rs->obj->next->cal_inter = call_inter_sphere;
  rs->obj->next->cal_color = cal_color_cylinder;
  creat_matrice_for_obj(rs->obj->next);
  rs->obj->next->data = (void *)r;
  if ((rs->obj->next->next = malloc(sizeof(*(rs->obj->next->next)))) == NULL)
    return (EXIT_SUCCESS);
  rs->obj->next->next->next = NULL;
  rs->obj->next->next->mat = c;
  rs->obj->next->next->ptn.x = 0;
  rs->obj->next->next->ptn.y = 20;
  rs->obj->next->next->ptn.z = 0;
  rs->obj->next->next->rot.x = 0;
  rs->obj->next->next->rot.y = 0;
  rs->obj->next->next->rot.z = 0;
  rs->obj->next->next->matrix = NULL;
  rs->obj->next->next->cal_inter = call_inter_sphere;
  rs->obj->next->next->cal_color = cal_color_cylinder;
  rs->obj->next->next->data = (void *)r;
  creat_matrice_for_obj(rs->obj->next->next);

  //LUMIERE
  if ((rs->lux = malloc(sizeof(*(rs->lux)))) == NULL)
    return (EXIT_FAILURE);
  rs->lux->attribute = SPOT;
  rs->lux->lux = 1;
  rs->lux->next = NULL;
  rs->lux->cord.x = -5;
  rs->lux->cord.y = 7;
  rs->lux->cord.z = 0;
  rs->lux->red = 1;
  rs->lux->green = 0;
  rs->lux->blue = 0;
  if ((rs->lux->next = malloc(sizeof(*(rs->lux)))) == NULL)
    return (EXIT_FAILURE);
  rs->lux->next->attribute = NONE;
  rs->lux->next->lux = 0.6;
  rs->lux->next->next = NULL;
  rs->lux->next->cord.x = -50;
  rs->lux->next->cord.y = 20;
  rs->lux->next->cord.z = -100;
  rs->lux->next->red = 1;
  rs->lux->next->green = 1;
  rs->lux->next->blue = 1;
  if ((rs->lux->next->next = malloc(sizeof(*(rs->lux)))) == NULL)
    return (EXIT_FAILURE);
  rs->lux->next->next->attribute = AMB;
  rs->lux->next->next->lux = 0.1;
  rs->lux->next->next->next = NULL;
  rs->lux->next->next->cord.x = 0;
  rs->lux->next->next->cord.y = 0;
  rs->lux->next->next->cord.z = 0;
  rs->lux->next->next->red = 1;
  rs->lux->next->next->green = 1;
  rs->lux->next->next->blue = 1;
  return (EXIT_SUCCESS);
}


#include <stdio.h>

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
      printf("MLX %f, %f, %f\n", rs.eyes->cam.x, rs.eyes->cam.y, rs.eyes->cam.z);
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
