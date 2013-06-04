/*
** main.c for RT in /home/mayol_l//RT
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat Apr 13 13:23:50 2013 lucas mayol
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "rt.h"

#include	"xml.h"

#define	SIZE_LARG	1000;
#define	SIZE_LONG	1000;

int	init_rs(t_rs *rs)
{
  float	*r;
  t_mat	*a;
  t_mat	*c;
  t_mat	*b;

  rs->aff = NULL;
  rs->send_rayon = NULL;
  rs->eyes = malloc(sizeof(*(rs->eyes)));

  rs->env.pattern = 0;

  // MATERIEEEL
  if ((rs->mat = malloc(sizeof(*(rs->mat)))) == NULL)
    return (EXIT_FAILURE);
  rs->mat->red = 0.2;
  rs->mat->green = 0.2;
  rs->mat->blue = 1;
  rs->mat->reflex = 0.5;
  rs->mat->spec[0] = 1.0;
  rs->mat->spec[1] = 1.0;
  rs->mat->spec[2] = 1.0;
  rs->mat->spec_pow = 60;
  if ((rs->mat->next = malloc(sizeof(*a))) == NULL)
    return (EXIT_FAILURE);
  rs->mat->next->red = 0.4;
  rs->mat->next->green = 1;
  rs->mat->next->blue = 1;
  rs->mat->next->reflex = 0.5;
  rs->mat->next->spec[0] = 1.0;
  rs->mat->next->spec[1] = 1.0;
  rs->mat->next->spec[2] = 1.0;
  rs->mat->next->spec_pow = 60;
  a = rs->mat->next;
  if ((rs->mat->next->next = malloc(sizeof(*b))) == NULL)
    return (EXIT_FAILURE);
  rs->mat->next->next->red = 1;
  rs->mat->next->next->green = 0.2;
  rs->mat->next->next->blue = 0.6;
  rs->mat->next->next->reflex = 0.5;
  rs->mat->next->next->spec[0] = 1.0;
  rs->mat->next->next->spec[1] = 1.0;
  rs->mat->next->next->spec[2] = 1.0;
  rs->mat->next->next->spec_pow = 60;
  b = rs->mat->next->next;
  if ((rs->mat->next->next->next = malloc(sizeof(*c))) == NULL)
    return (EXIT_FAILURE);
  rs->mat->next->next->next->next = NULL;
  rs->mat->next->next->next->red = 1;
  rs->mat->next->next->next->green = 0.8;
  rs->mat->next->next->next->blue = 0;
  rs->mat->next->next->next->reflex = 0.5;
  rs->mat->next->next->next->spec[0] = 1.0;
  rs->mat->next->next->next->spec[1] = 1.0;
  rs->mat->next->next->next->spec[2] = 1.0;
  rs->mat->next->next->next->spec_pow = 60;
  c = rs->mat->next->next->next;

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

  // SPHERES
  if ((rs->obj = malloc(sizeof(*(rs->obj)))) == NULL)
    return (EXIT_FAILURE);
  rs->obj->next = NULL;
  rs->obj->mat = b;
  rs->obj->ptn.x = 0;
  rs->obj->ptn.y = 0;
  rs->obj->ptn.z = 0;
  rs->obj->rot.x = 0;
  rs->obj->rot.y = 0;
  rs->obj->rot.z = 0;
  rs->obj->limit_z = 25;
  rs->obj->matrix = NULL;
  rs->obj->cal_inter = call_inter_cylinder;
  rs->obj->cal_color = cal_color_cylinder;
  r = malloc(sizeof(float));
  *r = 5;
  rs->obj->data = (void *)r;
  creat_matrice_for_obj(rs->obj);
  /* if ((rs->obj = malloc(sizeof(*(rs->obj)))) == NULL) */
  /*   return (EXIT_FAILURE); */
  /* rs->obj->next = NULL; */
  /* rs->obj->mat = a; */
  /* rs->obj->ptn.x = 0; */
  /* rs->obj->ptn.y = 0; */
  /* rs->obj->ptn.z = -10; */
  /* rs->obj->rot.x = 0; */
  /* rs->obj->rot.y = 0; */
  /* rs->obj->rot.z = 0; */
  /* rs->obj->limit_z = 0; */
  /* rs->obj->matrix = NULL; */
  /* rs->obj->cal_inter = call_inter_sphere; */
  /* rs->obj->cal_color = cal_color_shere; */
  /* r = malloc(sizeof(float)); */
  /* *r = 10; */
  /* rs->obj->data = (void *)r; */
  /* creat_matrice_for_obj(rs->obj); */
  /* if ((rs->obj->next = malloc(sizeof(*(rs->obj->next)))) == NULL) */
  /*   return (EXIT_SUCCESS); */
  /* rs->obj->next->next = NULL; */
  /* rs->obj->next->mat = rs->mat; */
  /* rs->obj->next->ptn.x = 0; */
  /* rs->obj->next->ptn.y = 0; */
  /* rs->obj->next->ptn.z = 10; */
  /* rs->obj->next->rot.x = 0; */
  /* rs->obj->next->rot.y = 0; */
  /* rs->obj->next->rot.z = 0; */
  /* rs->obj->next->matrix = NULL; */
  /* rs->obj->next->cal_inter = call_inter_sphere; */
  /* rs->obj->next->cal_color = cal_color_shere; */
  /* creat_matrice_for_obj(rs->obj->next); */
  /* rs->obj->next->data = (void *)r; */
  /* if ((rs->obj->next->next = malloc(sizeof(*(rs->obj->next->next)))) == NULL) */
  /*   return (EXIT_SUCCESS); */
  /* rs->obj->next->next->next = NULL; */
  /* rs->obj->next->next->mat = c; */
  /* rs->obj->next->next->ptn.x = 0; */
  /* rs->obj->next->next->ptn.y = 20; */
  /* rs->obj->next->next->ptn.z = 0; */
  /* rs->obj->next->next->rot.x = 0; */
  /* rs->obj->next->next->rot.y = 0; */
  /* rs->obj->next->next->rot.z = 0; */
  /* rs->obj->next->next->matrix = NULL; */
  /* rs->obj->next->next->cal_inter = call_inter_sphere; */
  /* rs->obj->next->next->cal_color = cal_color_shere; */
  /* rs->obj->next->next->data = (void *)r; */
  /* creat_matrice_for_obj(rs->obj->next->next); */
  /* if ((rs->obj->next->next->next = malloc(sizeof(*(rs->obj)))) == NULL) */
  /*   return (EXIT_SUCCESS); */
  /* rs->obj->next->next->next->next = NULL; */
  /* rs->obj->next->next->next->mat = b; */
  /* rs->obj->next->next->next->ptn.x = 0; */
  /* rs->obj->next->next->next->ptn.y = 0; */
  /* rs->obj->next->next->next->ptn.z = -30; */
  /* rs->obj->next->next->next->rot.x = 0; */
  /* rs->obj->next->next->next->rot.y = 0; */
  /* rs->obj->next->next->next->rot.z = 0; */
  /* rs->obj->next->next->next->matrix = NULL; */
  /* rs->obj->next->next->next->cal_inter = call_inter_plane; */
  /* rs->obj->next->next->next->cal_color = cal_color_plan; */
  /* creat_matrice_for_obj(rs->obj->next->next->next); */
  /* if ((rs->obj->next->next->next->next = malloc(sizeof(*(rs->obj)))) == NULL) */
  /*   return (EXIT_SUCCESS); */
  /* rs->obj->next->next->next->next->next = NULL; */
  /* rs->obj->next->next->next->next->mat = b; */
  /* rs->obj->next->next->next->next->ptn.x = 0; */
  /* rs->obj->next->next->next->next->ptn.y = -22; */
  /* rs->obj->next->next->next->next->ptn.z = -10; */
  /* rs->obj->next->next->next->next->rot.x = 0; */
  /* rs->obj->next->next->next->next->rot.y = 85; */
  /* rs->obj->next->next->next->next->rot.z = 0; */
  /* rs->obj->next->next->next->next->limit_z = 15; */
  /* rs->obj->next->next->next->next->matrix = NULL; */
  /* rs->obj->next->next->next->next->cal_inter = call_inter_cylinder; */
  /* rs->obj->next->next->next->next->cal_color = cal_color_cylinder; */
  /* rs->obj->next->next->next->next->data = (void *)r; */
  /* creat_matrice_for_obj(rs->obj->next->next->next->next); */
  /* if ((rs->obj->next->next->next->next->next = malloc(sizeof(*(rs->obj)))) == NULL) */
  /*   return (EXIT_SUCCESS); */
  /* rs->obj->next->next->next->next->next->next = NULL; */
  /* rs->obj->next->next->next->next->next->mat = c; */
  /* rs->obj->next->next->next->next->next->ptn.x = -10; */
  /* rs->obj->next->next->next->next->next->ptn.y = 32; */
  /* rs->obj->next->next->next->next->next->ptn.z = 20; */
  /* rs->obj->next->next->next->next->next->rot.x = 0; */
  /* rs->obj->next->next->next->next->next->rot.y = 90; */
  /* rs->obj->next->next->next->next->next->rot.z = 0; */
  /* rs->obj->next->next->next->next->next->limit_z = 15; */
  /* rs->obj->next->next->next->next->next->matrix = NULL; */
  /* rs->obj->next->next->next->next->next->cal_inter = call_inter_conus; */
  /* rs->obj->next->next->next->next->next->cal_color = cal_color_cylinder; */
  /* float	*r2; */
  /* r2 = malloc(sizeof(float)); */
  /* *r2 = 55; */
  /* printf("%f\n", *r2); */
  /* rs->obj->next->next->next->next->next->data = (void *)r2; */
  /* creat_matrice_for_obj(rs->obj->next->next->next->next->next); */

  //LUMIERE
  if ((rs->lux = malloc(sizeof(*(rs->lux)))) == NULL)
    return (EXIT_FAILURE);
  rs->lux->attribute = NONE;
  rs->lux->lux = 1;
  rs->lux->next = NULL;
  rs->lux->cord.x = -50;
  rs->lux->cord.y = 0;
  rs->lux->cord.z = 0;
  rs->lux->red = 1;
  rs->lux->green = 1;
  rs->lux->blue = 1;
  /* if ((rs->lux = malloc(sizeof(*(rs->lux)))) == NULL) */
  /*   return (EXIT_FAILURE); */
  /* rs->lux->attribute = SPOT; */
  /* rs->lux->lux = 1; */
  /* rs->lux->next = NULL; */
  /* rs->lux->cord.x = -5; */
  /* rs->lux->cord.y = 7; */
  /* rs->lux->cord.z = 0; */
  /* rs->lux->red = 1; */
  /* rs->lux->green = 0; */
  /* rs->lux->blue = 0; */
  /* if ((rs->lux->next = malloc(sizeof(*(rs->lux)))) == NULL) */
  /*   return (EXIT_FAILURE); */
  /* rs->lux->next->attribute = NONE; */
  /* rs->lux->next->lux = 0.8; */
  /* rs->lux->next->next = NULL; */
  /* rs->lux->next->cord.x = -30; */
  /* rs->lux->next->cord.y = 30; */
  /* rs->lux->next->cord.z = 0; */
  /* rs->lux->next->red = 1; */
  /* rs->lux->next->green = 1; */
  /* rs->lux->next->blue = 1; */
  /* if ((rs->lux->next->next = malloc(sizeof(*(rs->lux)))) == NULL) */
  /*   return (EXIT_FAILURE); */
  /* rs->lux->next->next->attribute = AMB; */
  /* rs->lux->next->next->lux = 0.1; */
  /* rs->lux->next->next->next = NULL; */
  /* rs->lux->next->next->cord.x = -50; */
  /* rs->lux->next->next->cord.y = 0; */
  /* rs->lux->next->next->cord.z = 0; */
  /* rs->lux->next->next->red = 1; */
  /* rs->lux->next->next->green = 1; */
  /* rs->lux->next->next->blue = 1; */
  /* return (EXIT_SUCCESS); */
}


#include <stdio.h>

int	main(int argc, __attribute__((unused))char **argv)
{
  int	fd;
  t_rs	rs;

  if (argc == 2)
    {
      xml_parsing(argv[1]);
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
