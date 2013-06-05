/*
** main.c for RT in /home/mayol_l//RT
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat Apr 13 13:23:50 2013 lucas mayol
** Last update Wed Jun  5 16:55:52 2013 louis martin-pierrat
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "rt.h"

#include	"xml.h"
#include	"xml_macros.h"

/* int	init_rs(t_rs *rs) */
/* { */
/*   float	*r; */
/*   t_mat	*a; */
/*   t_mat	*c; */

/*   rs->aff = NULL; */
/*   rs->send_rayon = NULL; */
/*   rs->eyes = malloc(sizeof(*(rs->eyes))); */

/*   // MATERIEEEL */
/*   if ((rs->mat = malloc(sizeof(*(rs->mat)))) == NULL) */
/*     return (EXIT_FAILURE); */
/*   rs->mat->red = 0.2; */
/*   rs->mat->green = 0.2; */
/*   rs->mat->blue = 1; */
/*   rs->mat->reflex = 0.5; */
/*   if ((a = malloc(sizeof(*a))) == NULL) */
/*     return (EXIT_FAILURE); */
/*   a->red = 0.4; */
/*   a->green = 1; */
/*   a->blue = 1; */
/*   a->reflex = 0.5; */
/*   if ((c = malloc(sizeof(*c))) == NULL) */
/*     return (EXIT_FAILURE); */
/*   c->red = 1; */
/*   c->green = 0.8; */
/*   c->blue = 0; */
/*   c->reflex = 0.5; */


/*   // SPHERES */
/*   if (rs->eyes == NULL) */
/*     return (EXIT_FAILURE); */
/*   rs->obj_inf = NULL; */
/*   rs->obj = NULL; */
/*   rs->tree = NULL; */
/*   rs->eyes->cam.x = -50; */
/*   rs->eyes->cam.y = 0; */
/*   rs->eyes->cam.z = 0; */
/*   rs->eyes->rot.x = 0; */
/*   rs->eyes->rot.y = 0; */
/*   rs->eyes->rot.z = 0; */
/*   rs->eyes->larg = SIZE_LARG; */
/*   rs->eyes->lng = SIZE_LONG; */

/*   if ((rs->obj = malloc(sizeof(*(rs->obj)))) == NULL) */
/*     return (EXIT_FAILURE); */
/*   rs->obj->next = NULL; */
/*   rs->obj->mat = NULL; */
/*   rs->obj->ptn.x = 0; */
/*   rs->obj->ptn.y = 0; */
/*   rs->obj->ptn.z = 0; */
/*   rs->obj->rot.x = 0; */
/*   rs->obj->rot.y = 0; */
/*   rs->obj->rot.z = 0; */
/*   rs->obj->matrix = NULL; */
/*   rs->obj->cal_inter = call_inter_sphere; */
/*   rs->obj->cal_color = cal_color_shere; */
/*   r = malloc(sizeof(float)); */
/*   *r = 10; */
/*   rs->obj->data = (void *)r; */
/*   creat_matrice_for_obj(rs->obj); */


int	init_rs(t_rs *rs, __attribute__((unused))struct s_xml *tree)
{
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
      else if (m_strcmp(tree->child->name, "plan") == 0)
	new_plane(&rs->obj, rs->mat, tree->child);
      else if (m_strcmp(tree->child->name, "cylindre") == 0)
	new_cylinder(&rs->obj, rs->mat, tree->child);
      else if (m_strcmp(tree->child->name, "cone") == 0)
	new_conus(&rs->obj, rs->mat, tree->child);
      tree->child = tree->child->next;
    }
  if (tree == NULL)
    return (EXIT_FAILURE);
  //LUMIERE
  /* if ((rs->lux = malloc(sizeof(*(rs->lux)))) == NULL) */
  /*   return (EXIT_FAILURE); */
  /* rs->lux->attribute = NONE; */
  /* rs->lux->lux = 1; */
  /* rs->lux->next = NULL; */
  /* rs->lux->cord.x = -20; */
  /* rs->lux->cord.y = 0; */
  /* rs->lux->cord.z = 0; */
  /* rs->lux->red = 1; */
  /* rs->lux->green = 0; */
  /* rs->lux->blue = 0; */
  return (0);
}


#include <stdio.h>

int	main(int argc, __attribute__((unused))char **argv)
{
  t_rs	rs;

  if (argc == 2)
    {
      if (init_rs(&rs ,  xml_parsing(argv[1])) == EXIT_FAILURE)
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
