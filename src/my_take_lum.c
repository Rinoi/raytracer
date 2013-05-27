/*
** my_take_obj.c for rtv1 in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat Feb 23 16:33:15 2013 lucas mayol
** Last update Sun May 12 22:57:52 2013 lucas mayol
*/

#include <stdio.h>
#include <stdlib.h>
#include "rtv1.h"
#include "pars.h"

void		my_conf_elem_l(t_lux *elem, __attribute__((unused))t_noeud *n)
{
  elem->cord.x = 0;
  elem->cord.y = 0;
  elem->cord.z = 0;
}

static void	my_get_cord(t_ptn *cord, t_noeud *n)
{
  t_noeud	*cp;

  cp = n;
  while (cp != NULL)
    {
      if (my_strcmp(cp->bal.name, "x") == 1)
	cord->x = my_get_dn(cp->bal.data, "x");
      else if (my_strcmp(cp->bal.name, "y") == 1)
	cord->y = my_get_dn(cp->bal.data, "y");
      else if (my_strcmp(cp->bal.name, "z") == 1)
	cord->z = my_get_dn(cp->bal.data, "z");
      cp = cp->branche2;
    }
}

void		creat_new_lum(t_lux **list, t_noeud *n)
{
  t_noeud	*cp;
  t_lux	*elem;

  cp = n->branche1;
  if ((elem = malloc(sizeof(*elem))) == NULL)
    {
      my_putstr("malloc error\n", 2);
      exit(EXIT_FAILURE);
    }
  my_conf_elem_l(elem, n);
  while (cp != NULL)
    {
      if (my_strcmp(cp->bal.name, "cord") == 1)
	my_get_cord(&elem->cord, cp->branche1);
      if (my_strcmp(cp->bal.name, "color") == 1)
	elem->color = my_get_dn(cp->bal.data, "color");
      cp = cp->branche2;
    }
  elem->next = *list;
  printf("lum : x = %f, y = %f, z = %f\n", elem->cord.x, elem->cord.y, elem->cord.z);
  *list = elem;
}

void		my_take_lum(t_rs *rs, t_noeud *n)
{
  t_noeud	*cp;

  cp = n;
  rs->lux = NULL;
  while (cp != NULL)
    {
      creat_new_lum(&rs->lux, cp);
      cp = cp->branche2;
    }
}
