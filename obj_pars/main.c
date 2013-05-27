/*
** main.c for rt in /home/martyn_k//svn/Raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sat May 11 18:19:53 2013 karina martynava
** Last update Sun May 12 00:30:02 2013 karina martynava
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "pars.h"
#include "get_next_line.h"
#include "obj_pars.h"
#include "rtv1.h"

typedef struct s_obj_pars_cmd
{
  char	*str;
  void	(*ptr)(t_ext *, t_vr **, char **);
} t_obj_cmd;

void	add_point(t_ext *ex, t_vr **vr, char **tab);

const t_obj_cmd	g_cmd[]=
  {
    {"v", add_point},
    {"f", NULL},
    {"#", NULL}
  };

char	**wrd_tab(char *str, char c);


int	main(int ac, char **av)
{
  t_ext	ext;
  t_obj	*list;

  list = NULL;
  ext.obj.ptn.x = 0;
  ext.obj.ptn.y = 0;
  ext.obj.ptn.z = 0;
  ext.obj.rot.x = 0;
  ext.obj.rot.y = 0;
  ext.obj.rot.z = 0;
  if (ac > 1)
    {
      if ((ext.fd = open(av[1], O_RDONLY)) == -1)
	return (EXIT_FAILURE);
      pars(&ext, &list);
    }
  return (EXIT_SUCCESS);
}
