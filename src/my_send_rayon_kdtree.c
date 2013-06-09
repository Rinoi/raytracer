/*
** my_send_rayon_kdtree.c for RT in /home/mayol_l//git/Raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 14 23:41:41 2013 lucas mayol
** Last update Sun Jun  9 17:57:59 2013 karina martynava
*/

#include <values.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "rt.h"

double		my_place_c_kd(t_kdtree *tree, t_st *droite)
{
  double	r;
  double	t;

  r = MAXDOUBLE;
  if ((t = sqrt(pow(tree->ori.x - droite->cord.x, 2)) / droite->vec.x) !=
      MAXDOUBLE && v_abs(t) < v_abs(r) && my_check_for_p(tree, droite, t) == 1)
    r = t;
  if ((t = sqrt(pow(tree->ori.y - droite->cord.y, 2)) / droite->vec.y) !=
      MAXDOUBLE && v_abs(t) < v_abs(r) && my_check_for_p(tree, droite, t) == 1)
    r = t;
  if ((t = sqrt(pow(tree->ori.z - droite->cord.z, 2)) / droite->vec.z) !=
      MAXDOUBLE && v_abs(t) < v_abs(r) && my_check_for_p(tree, droite, t) == 1)
    r = t;
  if ((t = sqrt(pow(tree->ori.x - droite->cord.x, 2)) / droite->vec.x) !=
      MAXDOUBLE && v_abs(t) < v_abs(r) && my_check_for_p(tree, droite, t) == 1)
    r = t;
  if ((t = sqrt(pow(tree->ori.y - droite->cord.y, 2)) / droite->vec.y) !=
      MAXDOUBLE && v_abs(t) < v_abs(r) && my_check_for_p(tree, droite, t) == 1)
    r = t;
  if ((t = sqrt(pow(tree->ori.z - droite->cord.z, 2)) / droite->vec.z) !=
      MAXDOUBLE && v_abs(t) < v_abs(r) && my_check_for_p(tree, droite, t) == 1)
    r = t;
  return (r);
}

t_inter		*my_send_rayon_rec_suite(t_kdtree *tree, t_st *droite, int a)
{
  t_inter       *my_return;
  double       	r1;
  double       	r2;

  r1 = tree->t_l != NULL ? my_place_c_kd(tree->t_l, droite) : MAXDOUBLE;
  r2 = tree->t_r != NULL ? my_place_c_kd(tree->t_r, droite) : MAXDOUBLE;
  if (v_abs(r1) <= v_abs(r2) && r1 != MAXDOUBLE)
    {
      my_return = my_send_rayon_rec(tree->t_l, droite, a - 1);
      if (my_return == NULL && r2 != MAXDOUBLE)
      	return (my_send_rayon_rec(tree->t_r, droite, a - 1));
      return (my_return);
    }
  else if (v_abs(r1) >= v_abs(r2) && r2 != MAXDOUBLE)
    {
      my_return = my_send_rayon_rec(tree->t_r, droite, a - 1);
      if (my_return == NULL && r1 != MAXDOUBLE)
	return (my_send_rayon_rec(tree->t_l, droite, a - 1));
      return (my_return);
    }
  return (NULL);
}

t_inter		*my_send_rayon_rec(t_kdtree *tree, t_st *droite, int a)
{
  t_inter       *my_return;

  if (tree == NULL)
    return (NULL);
  if (a <= 1 || (tree->t_l == NULL && tree->t_r == NULL))
    {
      my_return = check_obj_in_tree(tree->obj, droite);
      if (my_return != NULL
	  && my_check_for_p(tree, droite, my_return->d) == -1)
	return (NULL);
      return (my_return);
    }
  return (my_send_rayon_rec_suite(tree, droite, a));
}

t_inter		*my_send_rayon_act_kdtree(t_rs *rs, t_st *droite)
{
  t_inter	*inter;

  inter = my_send_rayon_rec(rs->tree, droite, MAX_ITERATION - 1);
  return (inter);
}
