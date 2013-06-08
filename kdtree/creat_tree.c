/*
** creat_tree.c for colle in /home/mayol_l//git/Raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 14 20:03:34 2013 lucas mayol
** Last update Sun Jun  9 00:47:04 2013 lucas mayol
*/

#include <stdlib.h>
#include <stdio.h>
#include "rt.h"

void	ini_f_tree(t_kdtree *tree)
{
  if ((tree->t_l = malloc(sizeof(t_kdtree))) == NULL)
    {
      my_putstr("malloc error\n", 2);
      exit(EXIT_FAILURE);
    }
  tree->t_l->obj = NULL;
  tree->t_l->pr = tree->pr + 1;
  tree->t_l->t_p = tree;
  if ((tree->t_r = malloc(sizeof(t_kdtree))) == NULL)
    {
      my_putstr("malloc error\n", 2);
      exit(EXIT_FAILURE);
    }
  tree->t_r->obj = NULL;
  tree->t_r->pr = tree->pr + 1;
  tree->t_r->t_p = tree;
}

void	ini_first_ptn_for_tree(t_kdtree *tree, t_obj *ptn)
{
  tree->ori.x = ptn->box.origine.x;
  tree->ori.y = ptn->box.origine.y;
  tree->ori.z = ptn->box.origine.z;
  tree->max.x = ptn->box.origine.x + ptn->box.lenght.x;
  tree->max.y = ptn->box.origine.y + ptn->box.lenght.y;
  tree->max.z = ptn->box.origine.z + ptn->box.lenght.z;
}

void	ini_first_tree(t_kdtree *tree, t_obj *obj)
{
  t_obj	*ptn;

  ptn = obj;
  tree->pr = 0;
  tree->t_l = NULL;
  tree->t_r = NULL;
  tree->t_p = NULL;
  ini_first_ptn_for_tree(tree, ptn);
  while (ptn != NULL)
    {
      tree->ori.x = tree->ori.x > ptn->box.origine.x ?
	ptn->box.origine.x : tree->ori.x;
      tree->ori.y = tree->ori.y > ptn->box.origine.y ?
	ptn->box.origine.y : tree->ori.y;
      tree->ori.z = tree->ori.z > ptn->box.origine.z ?
	ptn->box.origine.z : tree->ori.z;
      tree->max.x = tree->max.x < ptn->box.origine.x + ptn->box.lenght.x ?
        ptn->box.origine.x + ptn->box.lenght.x : tree->max.x;
      tree->max.y = tree->max.y < ptn->box.origine.y + ptn->box.lenght.y ?
        ptn->box.origine.y + ptn->box.lenght.y : tree->max.y;
      tree->max.z = tree->max.z < ptn->box.origine.z + ptn->box.lenght.z ?
        ptn->box.origine.z + ptn->box.lenght.z : tree->max.z;
      ptn = ptn->next;
    }
  tree->obj = NULL;
}

void		my_creat_first_rec(t_kdtree *tree)
{
  if (creat_tree_rec(tree->t_l, -1) == -1)
    {
      free(tree->t_l);
      tree->t_l = NULL;
    }
  if (creat_tree_rec(tree->t_r, 1) == -1)
    {
      free(tree->t_r);
      tree->t_r = NULL;
    }
}

t_kdtree	*creat_tree(t_obj *obj)
{
  t_kdtree	*tree;
  t_obj		*ptn;
  int		i;

  if ((tree = malloc(sizeof(t_kdtree))) == NULL)
    exit(EXIT_FAILURE);
  ini_first_tree(tree, obj);
  ini_f_tree(tree);
  creat_plan_for_tree(tree);
  ptn = obj;
  while (ptn != NULL)
    {
      i = where_obj_is_in_plan(&tree->plan, &ptn->box);
      if (i <= 0)
	my_put_obj_in_tree(&tree->t_l->obj, ptn);
      if (i >= 0)
	my_put_obj_in_tree(&tree->t_r->obj, ptn);
      ptn = ptn->next;
    }
  my_creat_first_rec(tree);
  return (tree);
}
