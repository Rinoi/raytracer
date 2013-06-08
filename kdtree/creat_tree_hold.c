/*
** creat_tree.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Fri May  3 11:43:49 2013 lucas mayol
** Last update Tue May 14 20:25:26 2013 lucas mayol
*/

#include <stdlib.h>
#include <stdio.h>
#include "../include/rtv1.h"

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

void	creat_plan_for_tree(t_kdtree *tree)
{
  tree->plan.ptn.x = 0;
  tree->plan.ptn.y = 0;
  tree->plan.ptn.z = 0;
  if (tree->pr % 3 == 0)
    tree->plan.ptn.x = (tree->max.x - tree->ori.x) / 2; 
  else if (tree->pr % 3 == 1)
    tree->plan.ptn.y = (tree->max.y - tree->ori.y) / 2; 
  else
    tree->plan.ptn.z = (tree->max.z - tree->ori.z) / 2; 
}

void	ini_first_tree(t_kdtree *tree, t_obj *obj)
{
  t_obj	*ptn;

  ptn = obj;
  tree->pr = 0;
  tree->t_l = NULL;
  tree->t_r = NULL;
  tree->t_p = NULL;
  tree->ori.x = ptn->box.origine.x;
  tree->ori.y = ptn->box.origine.y;
  tree->ori.z = ptn->box.origine.z;
  tree->max.x = ptn->box.origine.x + ptn->box.lenght.x;
  tree->max.y = ptn->box.origine.y + ptn->box.lenght.y;
  tree->max.z = ptn->box.origine.z + ptn->box.lenght.z;
  while (ptn != NULL)
    {
      ptn->box.origine.x = tree->ori.x > ptn->box.origine.x ? ptn->box.origine.x : tree->ori.x;
      ptn->box.origine.y = tree->ori.y > ptn->box.origine.y ? ptn->box.origine.y : tree->ori.y;
      ptn->box.origine.z = tree->ori.z > ptn->box.origine.z ? ptn->box.origine.z : tree->ori.z;
      tree->max.x = tree->max.x < ptn->box.origine.x + ptn->box.lenght.x ?
	ptn->box.origine.x + ptn->box.lenght.x : tree->max.x;
      tree->max.y = tree->max.y < ptn->box.origine.y + ptn->box.lenght.y ?
	ptn->box.origine.y + ptn->box.lenght.y : tree->max.y;
      tree->max.z = tree->max.z < ptn->box.origine.z + ptn->box.lenght.z ?
	ptn->box.origine.z + ptn->box.lenght.z : tree->max.z;
      ptn = ptn->next;
    }
  printf("origine : x : %f, y : %f, z : %f\n", tree->ori.x, tree->ori.y, tree->ori.z);
  printf("max : x : %f, y : %f, z : %f\n", tree->max.x, tree->max.y, tree->max.z);
  tree->obj = NULL;
}

void		parc_tree(t_kdtree *tree)
{
  t_l_obj	*obj;
  int		i;

  if (tree == NULL)
    return ;
  if (tree->pr == MAX_ITERATION - 2)
    {
      for (i = 0; i < tree->pr; i++)
	printf(" ");
      printf("TREE PR : %d\n\n\n\n\n", tree->pr);
      obj = tree->obj;
      while (obj != NULL)
	{
	  for (i = 0; i < tree->pr + 2; i++)
	    printf(" ");
	  printf("O = x : %f, y : %f, z : %f\n", obj->obj->box.origine.x,
		 obj->obj->box.origine.y, obj->obj->box.origine.z);
	  //      printf("NULL\n");
	  obj = obj->next;
	}
    }
  parc_tree(tree->t_l);
  parc_tree(tree->t_r);
}

t_kdtree       	*creat_tree(t_obj *obj)
{
  t_kdtree	*tree;
  t_obj		*ptn;

  if ((tree = malloc(sizeof(t_kdtree))) == NULL)
    exit(EXIT_FAILURE);
  ini_first_tree(tree, obj);
  ini_f_tree(tree);
  creat_plan_for_tree(tree);
  ptn = obj;
  while (ptn != NULL)
    {
      if (where_obj_is_in_plan(&tree->plan, &ptn->box) <= 0)
	my_put_obj_in_tree(&tree->t_r->obj, ptn);
      else if (where_obj_is_in_plan(&tree->plan, &ptn->box) >= 0)
	my_put_obj_in_tree(&tree->t_l->obj, ptn);
      ptn = ptn->next;
    }
  if (creat_tree_rec(tree->t_l, -1) == -1)
    tree->t_l = NULL;
  if (creat_tree_rec(tree->t_r, 1) == -1)
    tree->t_r = NULL;
  parc_tree(tree);
  return (tree);
}
