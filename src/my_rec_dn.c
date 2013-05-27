/*
** my_rec_dn.c for scene in /home/mayol_l//RT
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat Apr 13 15:25:01 2013 lucas mayol
** Last update Wed May  8 18:05:24 2013 karina martynava
*/

#include <stdlib.h>
#include "../include/rtv1.h"
#include "../pars/pars.h"

void		my_take_scene(t_rs *rs, t_noeud *n)
{
  t_noeud	*cp;

  cp = n;
  while (cp != NULL)
    {
      if (my_strcmp(cp->bal.name, "obj") == 1)
        my_take_obj(rs, cp->branche1);
      else if (my_strcmp(cp->bal.name, "lumiere") == 1)
        my_take_lum(rs, cp->branche1);
      cp = cp->branche2;
    }
}

void		my_rec_dn(t_rs *rs, t_noeud *n)
{
  t_noeud	*cp;

  cp = n;
  while (cp != NULL)
    {
      if (my_strcmp(cp->bal.name, "scene") == 1)
	my_take_scene(rs, cp->branche1);
      /* else if (my_strcmp(cp->bal.name, "env") == 1) */
      /* 	my_take_env(rs, cp->branche1); */
      /* else if (my_strcmp(cp->bal.name, "conf") == 1) */
      /* 	my_take_conf(rs, cp->branche1); */
      cp = cp->branche2;
    }
}
