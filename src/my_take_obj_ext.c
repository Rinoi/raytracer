/*
** my_take_obj.c for rtv1 in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat Feb 23 16:33:15 2013 lucas mayol
** Last update Sun May 12 01:33:31 2013 karina martynava
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "rtv1.h"
#include "pars.h"
#include "obj_pars.h"
#include "get_next_line.h"

void	my_boxing(int i, t_obj *obj)
{
  if (i == 1)
    boxin_sphere(obj);
  else if (i == 2)
    boxin_cone(obj);
  else if (i == 3)
    boxin_cylindre(obj);
}

static void		my_get_cord(t_ptn *cord, t_noeud *n)
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

float		*my_get_data(float *data, t_noeud *n, int i)
{
  t_noeud	*cp;

  cp = n;
  while (cp != NULL)
    {
      if (my_strcmp(cp->bal.name, "rayon") == 1 && i == 1)
	data[0] = my_get_dn(cp->bal.data, "rayon");
      else if (my_strcmp(cp->bal.name, "angle") == 1 && (i == 2 || i == 3))
	data[0] = my_get_dn(cp->bal.data, "angle");
      else if (my_strcmp(cp->bal.name, "ct_z") == 1 && i == 4) 
	data[0] = my_get_dn(cp->bal.data, "ct_z");
      cp = cp->branche2;
    }
  return (data);
}

void		my_conf_ptn(t_obj *elemn, t_noeud *n)
{
  t_noeud	*cp;
  t_ptn		cord;

  cp = n;
  while (cp != NULL)
    {
      my_get_cord(&cord, cp->branche1);
      if (my_strcmp(cp->bal.name, "a1") == 1)
	{
	  elemn->ptn.x = cord.x;
	  elemn->ptn.y = cord.y;
	  elemn->ptn.z = cord.z;
	}
      else if (my_strcmp(cp->bal.name, "a2") == 1)
	{
	  elemn->data[0] = cord.x;
	  elemn->data[1] = cord.y;
	  elemn->data[2] = cord.z;
	}
      else if (my_strcmp(cp->bal.name, "a3") == 1)
	{
	  elemn->data[3] = cord.x;
	  elemn->data[4] = cord.y;
	  elemn->data[5] = cord.z;
	}
      cp = cp->branche2;
    }
  elemn->data[0] = elemn->data[0] - elemn->ptn.x;
  elemn->data[1] = elemn->data[1] - elemn->ptn.y;
  elemn->data[2] = elemn->data[2] - elemn->ptn.z;
  elemn->data[3] = elemn->data[3] - elemn->ptn.x;
  elemn->data[4] = elemn->data[4] - elemn->ptn.y;
  elemn->data[5] = elemn->data[5] - elemn->ptn.z;
}

void		creat_new_obj(t_obj **list, t_noeud *n)
{
  t_noeud	*cp;
  t_obj		*elem;
  int		i;

  cp = n->branche1;
  if ((elem = malloc(sizeof(t_obj))) == NULL)
    return ;
  elem->ref = 0;
  i = my_conf_elem(elem, n);
  while (cp != NULL)
    {
      if (my_strcmp(cp->bal.name, "color") == 1)
	elem->color = my_get_dn(cp->bal.data, "color");
      else if (my_strcmp(cp->bal.name, "cord") == 1)
	my_get_cord(&elem->ptn, cp->branche1);
      else if (my_strcmp(cp->bal.name, "rot") == 1)
      	my_get_cord(&elem->rot, cp->branche1);
      else if (my_strcmp(cp->bal.name, "data") == 1)
	elem->data = my_get_data(elem->data, cp->branche1, i);
      else if (my_strcmp(cp->bal.name, "ptn") == 1)
	my_conf_ptn(elem, cp->branche1);
      else if (my_strcmp(cp->bal.name, "ref") == 1)
	elem->ref = my_get_dn(cp->bal.data, "ref");
      cp = cp->branche2;
    }
  my_boxing(i, elem);
  elem->next = *list;
  *list = elem;
}

void	add_point(t_vr **vr, char **tab)
{
  t_vr	*new;
  int	i;
  int	bol;

  i = 0;
  if (*vr == NULL || (*vr)->i == 99)
    {
      new = malloc(sizeof(*new));
      if (new == NULL)
	return ;
      new->i = 0;
      new->total = (*vr == NULL) ? 0 : (*vr)->total + 99;
      new->prv = *vr;
      new->nxt = NULL;
      if (*vr != NULL)
	(*vr)->nxt = new;
      *vr = new;
    }
  bol = 1;
  while (i < 3)
    {
      if (bol && tab[i + 1] == NULL)
	bol = 0;
      (*vr)->ptn[((*vr)->i)][i] = (bol) ? my_getfloat(tab[i+ 1]) : 0;
      i++;
    }
  (*vr)->i += 1;
}

float	get_cord_face(t_vr **vr, char *str, int sp)
{
  int	nb;

  nb = my_getnbr(str);
  if (nb <= 0 || (*vr) == NULL)
    return (0);
  /* printf("IS THIS WORKING (%d) %d - %d ?\n", nb, (*vr)->total, (*vr)->total + 99); */
  while (nb <= (*vr)->total || nb - 1 >= (*vr)->total + 99)
    {
      if (nb - 1 <= (*vr)->total)
	{
	  if ((*vr)->prv == NULL)
	    return (0);
	  *vr = (*vr)->prv;
	}
      else
	{
	  if ((*vr)->nxt == NULL)
	    return (0);
	  *vr = (*vr)->nxt;
	}
    }
  return ((*vr)->ptn[(nb - (*vr)->total - 1)][sp]);
}

void		add_face(t_ext *ex, t_vr **vr, char **tab, t_obj **list)
{
  t_obj		*elem;
  int		i;

  if ((elem = malloc(sizeof(t_obj))) == NULL)
    return ;
  i = my_conf_triangle(elem);
  elem->color = ex->obj.color;
  elem->ref = ex->obj.ref;
  elem->ptn.x = 0;
  elem->ptn.y = 0;
  elem->ptn.z = 0;
  elem->data[0] = 0;
  elem->data[1] = 0;
  elem->data[2] = 0;
  elem->data[0] = 0;
  elem->data[1] = 0;
  elem->data[2] = 0;
  if ((tab != NULL && tab[1]))
    {
      elem->ptn.x = ex->obj.ptn.x + get_cord_face(vr, tab[1], 0);
      elem->ptn.y = ex->obj.ptn.y + get_cord_face(vr, tab[1], 1);
      elem->ptn.z = ex->obj.ptn.z + get_cord_face(vr, tab[1], 2);
    }
  if ((tab != NULL && tab[2]))
    {
      elem->data[0] = ex->obj.ptn.x + get_cord_face(vr, tab[2], 0);
      elem->data[1] = ex->obj.ptn.y + get_cord_face(vr, tab[2], 1);
      elem->data[2] = ex->obj.ptn.z + get_cord_face(vr, tab[2], 2);
    }
  if ((tab != NULL && tab[3]))
    {
      elem->data[3] = ex->obj.ptn.x + get_cord_face(vr, tab[3], 0);
      elem->data[4] = ex->obj.ptn.y + get_cord_face(vr, tab[3], 1);
      elem->data[5] = ex->obj.ptn.z + get_cord_face(vr, tab[3], 2);
    }
  my_boxing(i, elem);
  elem->next = *list;
  *list = elem;
  free(elem);
}

void	free_vortex(t_vr *vr)
{
  while (vr->prv != NULL)
    {
      vr = vr->prv;
    }
  while (vr->nxt != NULL)
    {
      vr = vr->nxt;
      free(vr->prv);
    }
  free(vr);
}

void	pars_obj_file(t_ext *ext, t_obj **list, char *name)
{
  int	i;
  char	*str;
  char	**tab;
  t_vr	*vr;

  vr = NULL;
  str = NULL;
  ext->fd = open(name, O_RDONLY);
  if (ext->fd == -1)
    return;
  while ((str = get_next_line(ext->fd)) != NULL)
    {
      printf("%s\n", str);
      tab = wrd_tab(str, ' ');
      if (tab != NULL && my_strcmp("v", tab[0]))
	add_point(&vr, tab);
      else if (tab != NULL && my_strcmp("f", tab[0]))
	add_face(ext, &vr, tab, list);
      i = 0;
      while (tab != NULL && tab[i] != NULL)
	free(tab[i++]);
      free(tab);
      free(str);
    }
  free_vortex(vr);
}

void	add_extern_obj(t_obj **list, t_noeud *n)
{
  t_noeud	*cp;
  t_ext		ext;
  int		i;
  int		j;

  cp = n->branche1;
  ext.obj.ptn.x = 0;
  ext.obj.ptn.y = 0;
  ext.obj.ptn.z = 0;
  ext.obj.rot.x = 0;
  ext.obj.rot.y = 0;
  ext.obj.rot.z = 0;
  while (cp != NULL)
    {
      if (my_strcmp(cp->bal.name, "color") == 1)
	ext.obj.color = my_get_dn(cp->bal.data, "color");
      else if (my_strcmp(cp->bal.name, "cord") == 1)
	my_get_cord(&ext.obj.ptn, cp->branche1);
      else if (my_strcmp(cp->bal.name, "rot") == 1)
      	my_get_cord(&ext.obj.rot, cp->branche1);
      else if (my_strcmp(cp->bal.name, "ref") == 1)
	ext.obj.ref = my_get_dn(cp->bal.data, "ref");
      else if (my_strcmp(cp->bal.name, "name") == 1)
	{
	  j = 0;
	  while (j < NB_PARS)
	    {
	      i = 0;
	      while (cp->bal.arg != NULL && cp->bal.arg[i] != NULL)
		if (my_strcmp(g_pars[j].str, cp->bal.arg[i++]) == 1)
		  (g_pars[j].ptr)(&ext, list, cp->bal.data);
		   //		  printf("THIS IS %s\n", g_pars[j].str);
	      j++;
	    }
	  printf("%s\n", cp->bal.data);
	}
      cp = cp->branche2;
    }
}

void		my_take_obj(t_rs *rs, t_noeud *n)
{
  t_noeud	*cp;

  cp = n;
  while (cp != NULL)
    {
      if (my_strcmp(cp->bal.name, "extern") == 1)
	add_extern_obj(&rs->obj, cp);
      else
	creat_new_obj(&rs->obj, cp);
      cp = cp->branche2;
    }
}
