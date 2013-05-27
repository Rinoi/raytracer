/*
** creat_tree.c for colle in /home/mayol_l//git/Raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 14 20:03:34 2013 lucas mayol
** Last update Sat May 18 18:44:11 2013 lucas mayol
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
      tree->ori.x = tree->ori.x > ptn->box.origine.x ? ptn->box.origine.x : tree->ori.x;
      tree->ori.y = tree->ori.y > ptn->box.origine.y ? ptn->box.origine.y : tree->ori.y;
      tree->ori.z = tree->ori.z > ptn->box.origine.z ? ptn->box.origine.z : tree->ori.z;
      tree->max.x = tree->max.x < ptn->box.origine.x + ptn->box.lenght.x ?
        ptn->box.origine.x + ptn->box.lenght.x : tree->max.x;
      tree->max.y = tree->max.y < ptn->box.origine.y + ptn->box.lenght.y ?
        ptn->box.origine.y + ptn->box.lenght.y : tree->max.y;
      tree->max.z = tree->max.z < ptn->box.origine.z + ptn->box.lenght.z ?
        ptn->box.origine.z + ptn->box.lenght.z : tree->max.z;
      ptn = ptn->next;
    }
  /* printf("origine : x : %f, y : %f, z : %f\n", tree->ori.x, tree->ori.y, tree->ori.z); */
  /* printf("max : x : %f, y : %f, z : %f\n", tree->max.x, tree->max.y, tree->max.z); */
  tree->obj = NULL;
}

void		pars_tree(t_kdtree *tree, int i)
{
  t_l_obj	*ptn;
  int		a;

  if (tree == NULL)
    return ;
  ptn = tree->obj;
  printf("pr = %d\n", MAX_ITERATION - i);
  if (i <= 0 || (tree->t_l == NULL && tree->t_r == NULL))
    {
      a = 0;
      while (ptn != NULL)
	{
	  //write(1, "a", 1);
	  a += 1;
	  ptn = ptn->next;
	}
      printf("ELEMN = %d\n", a);
      return ;
    }
  pars_tree(tree->t_l, i - 1);
  pars_tree(tree->t_r, i - 1);
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
      /* else  */
      /* 	my_separ_tri(tree, ptn); */
      ptn = ptn->next;      
    }
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
  //  pars_tree(tree, MAX_ITERATION - 1);
  return (tree);
}
