/*
** main.c for rt in /home/martyn_k//svn/Raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sat May 11 18:19:53 2013 karina martynava
** Last update Sun Jun  9 08:55:26 2013 karina martynava
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "rt.h"
#include "obj_pars.h"

void  add_point(t_ext *ex, t_vr **vr, char **tab);

const t_obj_cmd  g_cmd[]=
    {
      {"v", add_point},
      {"f", NULL},
      {"#", NULL}
    };

char  **wrd_tab(char *str, char c);

void  add_point(__attribute__((unused))t_ext *ex, t_vr **vr, char **tab)
{
  t_vr  *new;
  int  i;
  int  bol;

  if ((i = 0) == 0 && (bol = 1) && (*vr == NULL || (*vr)->i == 99))
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
  while (i < 3)
    {
      if (bol && tab[i + 1] == NULL) // EMPECHE DE SIGSEV SI MOINS DE 3 SOMMETS
	bol = 0;
      (*vr)->ptn[((*vr)->i)][i] = (bol) ? atof(tab[i + 1]) : 0;
      i++;
    }
  (*vr)->i += 1;
}

void	init_ptn_safety(t_ptn *ptn, t_ptn *obj)
{
  ptn->x = 0 + obj->x;
  ptn->y = 0 + obj->y;
  ptn->z = 0 + obj->z;
}

void	get_cord_face(t_vr **vr, char *str, t_ptn *ptn, t_ptn *obj)
{
  // Le but de la fonction est de trouver le bon numero de vortex, pour recuperer les bonnes coordonnes
  int	nb;

  nb = atoi(str);
  if (nb <= 0 || (*vr) == NULL)
    return ;
  // Initialiastion
  init_ptn_safety(ptn, obj);
  while (nb <= (*vr)->total || nb - 1 >= (*vr)->total + 99) // Recherche de la bonne structure
    {
      if (nb - 1 <= (*vr)->total)
	{
	  if ((*vr)->prv == NULL)
	    return ;
	  *vr = (*vr)->prv;
	}
      else
	{
	  if ((*vr)->nxt == NULL)
            return ;
	  *vr = (*vr)->nxt;
	}
    }
  ptn->x += (*vr)->ptn[(nb - 1 - (*vr)->total)][0];
  ptn->y += (*vr)->ptn[(nb - 1 - (*vr)->total)][1];
  ptn->z += (*vr)->ptn[(nb - 1 - (*vr)->total)][2];
}


void	from_ptns_to_vec(t_tri *tri, t_obj *elem)
{
  tri->a2.x -= elem->ptn.x;
  tri->a2.y -= elem->ptn.y;
  tri->a2.z -= elem->ptn.z;
  tri->a3.x -= elem->ptn.x;
  tri->a3.y -= elem->ptn.y;
  tri->a3.z -= elem->ptn.z;
}

void    add_face(t_ext *ex, t_vr **vr, char **tab, t_obj **list)
{
  t_obj	*elem;
  t_tri	*tri;
  int    bol;

  tri = malloc(sizeof(t_tri));
  bol = 1;
  if ((elem = malloc(sizeof(t_obj))) == NULL)
    return ;
  elem = ex->obj;
  if (bol && tab != NULL && tab[0])
    get_cord_face(vr, tab[0], &elem->ptn, &ex->obj->ptn);
  else
    bol = 0;
  if (bol && tab != NULL && tab[0])
    get_cord_face(vr, tab[1], &tri->a2, &ex->obj->ptn);
  else
    bol = 0;
  if (bol && tab != NULL && tab[0])
    get_cord_face(vr, tab[2], &tri->a3, &ex->obj->ptn);
  from_ptns_to_vec(tri, elem);
  elem->data = (void *)(tri);
  elem->next = *list;
  *list = elem;
}

void  pars(t_ext *ext, t_obj **list)
{
  int  i;
  int  j;
  char  *str;
  char  **tab;
  t_vr  *vr;
  FILE	*fs;
  size_t	n;

  fs = fdopen(ext->fd, "r");
  vr = NULL;
  str = NULL;
  while (getline(&str, &n, fs) != 0)
    {
      tab = wrd_tab(str, ' ');
      if (tab != NULL && strcmp(g_cmd[0].str, tab[0]) == 0)
      	(g_cmd[0].ptr)(ext, &vr, tab);
      else if (tab != NULL && strcmp(g_cmd[1].str, tab[0]) == 0)
      	add_face(ext, &vr, tab, list);
      printf("\n");
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
  ext.obj = tmp; // mettre les valeur a utiliser plus tard
  ext.ptn.x = 0;
  ext.ptn.y = 0;
  ext.ptn.z = 0;
  ext.rot.x = 0;
  ext.rot.y = 0;
  ext.rot.z = 0;
  if ((ext.fd = open(obj, O_RDONLY)) == -1)
    return (NULL);
  pars(&ext, &list);
  return (list);
}
