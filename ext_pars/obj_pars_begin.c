/*
** obj_pars_begin.c for rt in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sun Jun  9 18:05:34 2013 karina martynava
** Last update Sun Jun  9 18:07:28 2013 karina martynava
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "rt.h"
#include "obj_pars.h"

const t_obj_cmd  g_cmd[]=
    {
      {"v", add_point},
      {"f", NULL},
      {"#", NULL}
    };

void  pars(t_ext *ext, t_obj **list)
{
  int  i;
  char  *str;
  char  **tab;
  t_vr  *vr;
  FILE	*fs;
  size_t	n;

  fs = fdopen(ext->fd, "r");
  vr = NULL;
  str = NULL;
  while (getline(&str, &n, fs) >= 0)
    {
      tab = wrd_tab(str, ' ');
      if (tab != NULL && strcmp(g_cmd[0].str, tab[0]) == 0)
      	(g_cmd[0].ptr)(ext, &vr, tab);
      else if (tab != NULL && strcmp(g_cmd[1].str, tab[0]) == 0)
      	add_face(ext, &vr, tab, list);
      i = 0;
      while (tab != NULL && tab[i] != NULL)
	free(tab[i++]);
      free(tab);
      free(str);
      str = NULL;
    }
}

t_obj		*obj_pars_main(char *obj, t_obj *tmp)
{
  t_ext		ext;
  t_obj		*list;

  list = NULL;
  ext.obj = tmp;
  if ((ext.fd = open(obj, O_RDONLY)) == -1)
    return (NULL);
  pars(&ext, &list);
  return (list);
}
