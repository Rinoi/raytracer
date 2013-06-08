/*
** creat_tree_e.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Fri May  3 14:45:13 2013 lucas mayol
** Last update Sun Jun  9 00:47:42 2013 lucas mayol
*/

#include <stdio.h>
#include <stdlib.h>
#include "rt.h"

void		my_put_obj_in_tree(t_l_obj **list, t_obj *obj)
{
  t_l_obj	*elemn;

  if ((elemn = malloc(sizeof(t_l_obj))) == NULL)
    {
      my_putstr("malloc error\n", 2);
      exit(EXIT_FAILURE);
    }
  elemn->obj = obj;
  elemn->next = *list;
  *list = elemn;
}

int	where_obj_is_in_plan(t_plan *plan, t_box *box)
{
  int	i;

  i = 0;
  if (plan->ptn.x != MAXDOUBLE)
    {
      i += box->origine.x > plan->ptn.x ? 1 : 0;
      i += (box->origine.x + box->lenght.x) < plan->ptn.x ? -1 : 0;
    }
  else if (plan->ptn.y != MAXDOUBLE)
    {
      i += box->origine.y > plan->ptn.y ? 2 : 0;
      i += (box->origine.y + box->lenght.y) < plan->ptn.y ? -1 : 0;
    }
  else if (plan->ptn.z != MAXDOUBLE)
    {
      i += box->origine.z > plan->ptn.z ? 2 : 0;
      i += (box->origine.z + box->lenght.z) < plan->ptn.z ? -1 : 0;
    }
  return (i);
}

void	ini_ptn_tree(t_kdtree *tree, int b)
{
  if (b == 1)
    {
      tree->ori.x = tree->t_p->plan.ptn.x != MAXDOUBLE ?
	tree->t_p->plan.ptn.x : tree->t_p->ori.x;
      tree->ori.y = tree->t_p->plan.ptn.y != MAXDOUBLE ?
	tree->t_p->plan.ptn.y : tree->t_p->ori.y;
      tree->ori.z = tree->t_p->plan.ptn.z != MAXDOUBLE ?
	tree->t_p->plan.ptn.z : tree->t_p->ori.z;
      tree->max.x = tree->t_p->max.x;
      tree->max.y = tree->t_p->max.y;
      tree->max.z = tree->t_p->max.z;
      return ;
    }
  tree->ori.x = tree->t_p->ori.x;
  tree->ori.y = tree->t_p->ori.y;
  tree->ori.z = tree->t_p->ori.z;
  tree->max.x = tree->t_p->plan.ptn.x != MAXDOUBLE ?
    tree->t_p->plan.ptn.x : tree->t_p->max.x;
  tree->max.y = tree->t_p->plan.ptn.y != MAXDOUBLE ?
    tree->t_p->plan.ptn.y : tree->t_p->max.y;
  tree->max.z = tree->t_p->plan.ptn.z != MAXDOUBLE ?
    tree->t_p->plan.ptn.z : tree->t_p->max.z;
}

int		creat_tree_rec(t_kdtree *tree, int b)
{
  t_l_obj	*ptn;
  int		i;

  if (tree->obj == NULL || tree->pr == MAX_ITERATION - 1)
    {
      return (-1);
    }
  ini_ptn_tree(tree, b);
  ini_f_tree(tree);
  creat_plan_for_tree(tree);
  ptn = tree->obj;
  while (ptn != NULL)
    {
      i = where_obj_is_in_plan(&tree->plan, &ptn->obj->box);
      if (i <= 0)
        my_put_obj_in_tree(&tree->t_l->obj, ptn->obj);
      if (i >= 0)
        my_put_obj_in_tree(&tree->t_r->obj, ptn->obj);
      ptn = ptn->next;
    }
  if (creat_tree_rec(tree->t_l, -1) == -1)
    tree->t_l = NULL;
  if (creat_tree_rec(tree->t_r, 1) == -1)
    tree->t_r = NULL;
  return (1);
}
