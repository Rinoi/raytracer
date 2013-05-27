/*
** my_send_rayon_kdtree.c for RT in /home/mayol_l//git/Raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 14 23:41:41 2013 lucas mayol
** Last update Mon May 27 11:56:32 2013 lucas mayol
*/

#include <values.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/rtv1.h"

static void     my_cpy_tmp(t_ptn *tmp, t_ptn *ptn)
{
  ptn->x = tmp->x;
  ptn->y = tmp->y;
  ptn->z = tmp->z;
}

t_inter		*check_obj_in_tree(t_l_obj *obj, t_st *droit)
{
  t_ptn		*tmp;
  t_l_obj	*cp;
  t_inter	*my_return;

  if ((my_return = malloc(sizeof(t_inter))) == NULL)
    exit(EXIT_FAILURE);
  cp = obj;
  my_return->d = -1;
  while (cp != NULL)
    {
      tmp = cp->obj->cal_inter(cp->obj, droit);
      if (tmp != NULL)
        {
          if (my_return->d == -1 || my_call_dist(&droit->cord, tmp) <= my_return->d)
            {
              my_return->d = my_call_dist(&droit->cord, tmp);
              my_return->obj = cp->obj;
              my_cpy_tmp(tmp, &my_return->ptn);
            }
	  free(tmp);
        }
      cp = cp->next;
    }
  if (my_return->d == -1)
    {
      free(my_return);
      return (NULL);
    }
  return (my_return);
}

float		v_abs(double nb)
{
  if (nb < 0)
    nb = -nb;
  return (nb);
}

int		my_check_for_p(t_kdtree *tree, t_st *droite, double t)
{
  t_ptn		p;

  p.x = droite->cord.x + (droite->vec.x * t);
  p.y = droite->cord.y + (droite->vec.y * t);
  p.z = droite->cord.z + (droite->vec.z * t);
  if ((tree->ori.x - 0.1 <= p.x && p.x <= tree->max.x + 0.1)
      && (tree->ori.y - 0.1 <= p.y && p.y <= tree->max.y + 0.1)
      && (tree->ori.z - 0.1 <= p.z && p.z <= tree->max.z) + 0.1)
    return (1);
  return (-1);
}

double		my_place_c_kd(t_kdtree *tree, t_st *droite)
{
  int		b;
  double	r;
  double	t;

  b = -1;
  r = MAXDOUBLE;
  if ((t = sqrt(pow(tree->ori.x - droite->cord.x, 2)) / droite->vec.x) != MAXDOUBLE
      && v_abs(t) < v_abs(r))
    if (my_check_for_p(tree, droite, t) == 1)
      {
	r = t;
	b = 1;
      }
  if ((t = sqrt(pow(tree->ori.y - droite->cord.y, 2)) / droite->vec.y) != MAXDOUBLE
      && v_abs(t) < v_abs(r))
    if (my_check_for_p(tree, droite, t) == 1)
      {
  	r = t;
  	b = 1;
      }
  if ((t = sqrt(pow(tree->ori.z - droite->cord.z, 2)) / droite->vec.z) != MAXDOUBLE
      && v_abs(t) < v_abs(r))
    if (my_check_for_p(tree, droite, t) == 1)
      {
  	r = t;
  	b = 1;
      }
  if ((t = sqrt(pow(tree->ori.x - droite->cord.x, 2)) / droite->vec.x) != MAXDOUBLE
      && v_abs(t) < v_abs(r))
    if (my_check_for_p(tree, droite, t) == 1)
      {
  	r = t;
  	b = 1;
      }
  if ((t = sqrt(pow(tree->ori.y - droite->cord.y, 2)) / droite->vec.y) != MAXDOUBLE
      && v_abs(t) < v_abs(r))
    if (my_check_for_p(tree, droite, t) == 1)
      {
  	r = t;
  	b = 1;
      }
  if ((t = sqrt(pow(tree->ori.z - droite->cord.z, 2)) / droite->vec.z) != MAXDOUBLE
      && v_abs(t) < v_abs(r))
    if (my_check_for_p(tree, droite, t) == 1)
      {
  	r = t;
  	b = 1;
      }
  return (r);
}

t_inter		*my_send_rayon_rec(t_kdtree *tree, t_st *droite, int a)
{
  t_inter       *my_return;
  t_inter       *my_return2;
  double       	r1;
  double       	r2;

  if (tree == NULL)
    return (NULL);
  if (a <= 1 || (tree->t_l == NULL && tree->t_r == NULL))
    {
      my_return = check_obj_in_tree(tree->obj, droite);
      if (my_return != NULL && my_check_for_p(tree, droite, my_return->d) == -1)
	return (NULL);
      return (my_return);
    }
  my_return2 = NULL;
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

t_inter		*my_inter_inf_obj(t_rs *rs, t_st *droit)
{
  t_ptn         *tmp;
  t_obj         *cp;
  t_inter       *my_return;

  if ((my_return = malloc(sizeof(t_inter))) == NULL)
    exit(EXIT_FAILURE);
  cp = rs->obj_inf;
  my_return->d = -1;
  while (cp != NULL)
    {
      tmp = cp->cal_inter(cp, droit);
      if (tmp != NULL)
        {
          if (my_return->d == -1 || my_call_dist(&droit->cord, tmp) <= my_return->d)
            {
              my_return->d = my_call_dist(&droit->cord, tmp);
              my_return->obj = cp;
              my_cpy_tmp(tmp, &my_return->ptn);
            }
          free(tmp);
        }
      cp = cp->next;
    }
  return (my_return->d != -1 ? my_return : NULL);
}

t_inter		*my_send_rayon_act_kdtree(t_rs *rs, t_st *droite)
{
  t_inter	*inter;
  t_inter	*inter2;

  inter = my_inter_inf_obj(rs, droite);
  inter2 = my_send_rayon_rec(rs->tree, droite, MAX_ITERATION - 1);
  if (inter == NULL)
    return (inter2);
  if (inter2 == NULL)
    return (inter);
  if (inter->d < inter2->d)
    return (inter);
  return (inter2);
}
