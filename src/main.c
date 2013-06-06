/*
** main.c for RT in /home/mayol_l//RT
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat Apr 13 13:23:50 2013 lucas mayol
** Last update Thu Jun  6 15:08:25 2013 louis martin-pierrat
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "rt.h"

#include	"xml.h"
#include	"xml_macros.h"

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
  	new_material(&rs->mat, rs, tree->child);
      else if (m_strcmp(tree->child->name, "sphere") == 0)
  	new_sphere(&rs->obj, rs->mat, tree->child);
      else if (m_strcmp(tree->child->name, "plan") == 0)
	new_plane(&rs->obj, rs->mat, tree->child);
      else if (m_strcmp(tree->child->name, "cylindre") == 0)
	new_cylinder(&rs->obj, rs->mat, tree->child);
      else if (m_strcmp(tree->child->name, "cone") == 0)
	new_conus(&rs->obj, rs->mat, tree->child);
      else if (m_strcmp(tree->child->name, "triangle") == 0)
	new_triangle(&rs->obj, rs->mat, tree->child);
      tree->child = tree->child->next;
    }
  if (tree == NULL)
    exit (EXIT_FAILURE);
  return (0);
}


#include <stdio.h>

int	main(int argc, char **argv)
{
  t_rs	rs;

  rs.client = -1;
  if (argc != 1)
    {
      if ((rs.wind.mlx_ptr = mlx_init()) == NULL)
	{
	  my_putstr("Mlx error\n", 2);
	  exit(EXIT_FAILURE);
	}
      if (strcmp(argv[1], "--server") == 0 || strcmp(argv[1], "-s") == 0)
	rt_server(&rs, argv);
      else if (strcmp(argv[1], "--client") == 0 || strcmp(argv[1], "-c") == 0)
      	rt_client(&rs, argv);
      else
	{
	  if (init_rs(&rs ,  xml_parsing(argv[1])) == EXIT_FAILURE)
	    return (EXIT_FAILURE);
	  printf("MLX %f, %f, %f\n", rs.eyes->cam.x, rs.eyes->cam.y, rs.eyes->cam.z);
	  /* my_take_data_for_rs(&rs, fd); */
	  /* rs.tree = creat_tree(rs.obj); */
	  rt_main_mlx(&rs);
	}
    }
  else
    {
      my_putstr(argv[0], 2);
      my_putstr(" : file.xml\n", 2);
    }
  return (EXIT_SUCCESS);
}
