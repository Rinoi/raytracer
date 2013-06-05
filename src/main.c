/*
** main.c for RT in /home/mayol_l//RT
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat Apr 13 13:23:50 2013 lucas mayol
** Last update Wed Jun  5 00:43:13 2013 louis martin-pierrat
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "rt.h"

#include	"xml.h"
#include	"xml_macros.h"

int	init_rs(t_rs *rs, struct s_xml *tree)
{
  /* float	*r; */
  /* float	*r2; */
  /* t_mat	*a; */
  /* t_mat	*c; */
  /* t_mat	*b; */

  rs->aff = NULL;
  rs->send_rayon = NULL;
  rs->obj_inf = NULL;
  rs->obj = NULL;
  rs->tree = NULL;
  rs->eyes = NULL;
  rs->lux = NULL;
  rs->mat = NULL;
  rs->env.pattern = 0;
  while (tree != NULL && tree->child != NULL)
    {
      if (m_strcmp(tree->child->name, "eyes") == 0)
	new_eyes(&rs->eyes, tree->child);
      else if (m_strcmp(tree->child->name, "lumiere") == 0)
	new_lux(&rs->lux, tree->child);
      else if (m_strcmp(tree->child->name, "material") == 0)
	new_material(&rs->mat, tree->child);
      else if (m_strcmp(tree->child->name, "sphere") == 0)
	new_sphere(&rs->obj, rs->mat, tree->child);
      tree->child = tree->child->next;
    }

  /* SPHERES */
  /* if ((rs->obj = malloc(sizeof(*(rs->obj)))) == NULL) */
  /*   return (EXIT_FAILURE); */
  /* rs->obj->next = NULL; */
  /* rs->obj->mat = a; */
  /* rs->obj->ptn.x = 0; */
  /* rs->obj->ptn.y = 0; */
  /* rs->obj->ptn.z = 20; */
  /* rs->obj->rot.x = 0; */
  /* rs->obj->rot.y = 0; */
  /* rs->obj->rot.z = 0; */
  /* rs->obj->limit_z = 15; */
  /* rs->obj->matrix = NULL; */
  /* rs->obj->cal_inter = call_inter_conus; */
  /* rs->obj->cal_color = cal_color_cylinder; */
  /* r = malloc(sizeof(float)); */
  /* *r = 55; */
  /* rs->obj->data = (void *)r; */
  /* creat_matrice_for_obj(rs->obj); */

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
  /* rs->obj->cal_color = cal_color_cylinder; */
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
  /* rs->obj->next->cal_color = cal_color_cylinder; */
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
  /* rs->obj->next->next->cal_color = cal_color_cylinder; */
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
  /* rs->obj->next->next->next->cal_color = cal_color_cylinder; */
  /* creat_matrice_for_obj(rs->obj->next->next->next); */

  /* if ((rs->obj->next->next->next->next = malloc(sizeof(*(rs->obj)))) == NULL) */
  /*   return (EXIT_SUCCESS); */
  /* rs->obj->next->next->next->next->next = NULL; */
  /* rs->obj->next->next->next->next->mat = c; */
  /* rs->obj->next->next->next->next->ptn.x = 0; */
  /* rs->obj->next->next->next->next->ptn.y = -22; */
  /* rs->obj->next->next->next->next->ptn.z = -10; */
  /* rs->obj->next->next->next->next->rot.x = 0; */
  /* rs->obj->next->next->next->next->rot.y = 0; */
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
  /* rs->obj->next->next->next->next->next->rot.y = 0; */
  /* rs->obj->next->next->next->next->next->rot.z = 0; */
  /* rs->obj->next->next->next->next->next->limit_z = 15; */
  /* rs->obj->next->next->next->next->next->matrix = NULL; */
  /* rs->obj->next->next->next->next->next->cal_inter = call_inter_conus; */
  /* rs->obj->next->next->next->next->next->cal_color = cal_color_cylinder; */
  /* rs->obj->next->next->next->next->next->data = (void *)r2; */
  /* creat_matrice_for_obj(rs->obj->next->next->next->next->next); */
  return (0);
}


#include <stdio.h>

int	main(int argc, __attribute__((unused))char **argv)
{
  t_rs	rs;

  if (argc == 2)
    {
      if (init_rs(&rs, xml_parsing(argv[1])) == EXIT_FAILURE)
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
