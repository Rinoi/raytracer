/*
** main.c for RT in /home/mayol_l//RT
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat Apr 13 13:23:50 2013 lucas mayol
** Last update Sat Jun  8 20:42:57 2013 louis martin-pierrat
*/

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<stdlib.h>
#include	"rt.h"
#include	"xml.h"
#include	"xml_macros.h"

int	init_rs(t_rs *rs, struct s_xml *tree)
{
  rs->aff = NULL;
  rs->send_rayon = NULL;
  rs->obj_neg = NULL;
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
      else if (m_strcmp(tree->child->name, "obj") == 0)
	new_objs(rs, tree->child);
      else if (m_strcmp(tree->child->name, "obj_neg") == 0)
	new_objs_neg(rs, tree->child);
      else if (m_strcmp(tree->child->name, "environnement") == 0)
	set_env(&rs->env, tree->child);
      tree->child = tree->child->next;
    }
  return (tree == NULL ? EXIT_FAILURE : 0);
}

void	my_end(char **argv)
{
  my_putstr(argv[0], 2);
  my_putstr(" : file.xml\n", 2);
}

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
	rt_server(&rs, argc, argv);
      else if (strcmp(argv[1], "--client") == 0 || strcmp(argv[1], "-c") == 0)
      	rt_client(&rs, argc, argv);
      else
	{
	  if (init_rs(&rs, xml_parsing(argv[1])) == EXIT_FAILURE)
	    return (EXIT_FAILURE);
	  rt_main_mlx(&rs);
	}
    }
  else
    my_end(argv);
  return (EXIT_SUCCESS);
}
