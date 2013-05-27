/*
** my_send_rayon_kdtree.c for RT in /home/mayol_l//git/Raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 14 23:41:41 2013 lucas mayol
** Last update Sat May 18 02:48:41 2013 lucas mayol
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

int	find_i(t_ptn *ptn, t_ptn *plan)
{
  if (plan->x != MAXDOUBLE)
    return (ptn->x < plan->x ? -1 : 1);
  else if (plan->y != MAXDOUBLE)
    return (ptn->y < plan->y ? -1 : 1);
  return (ptn->z < plan->z ? -1 : 1);
}

t_inter		*check_obj_in_tree(t_l_obj *obj, t_st *droit)
{
  t_ptn		*tmp;
  t_l_obj	*cp;
  t_inter	*my_return;
  int		i;

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

double		find_inter_plan_dr(t_plan *plan, t_st *droite)
{
  double	r;

  if (plan->ptn.x != MAXDOUBLE)
    {
      if ((droite->c_kd.x > plan->ptn.x && droite->vec.x > 0)
      	  || (droite->c_kd.x < plan->ptn.x && droite->vec.x < 0))
      	return (MAXDOUBLE);
      r = sqrt(pow(plan->ptn.x - droite->c_kd.x, 2)) / droite->vec.x;
    }
  else if (plan->ptn.y != MAXDOUBLE)
    {
      if ((droite->c_kd.y > plan->ptn.y && droite->vec.y > 0)
      	  || (droite->c_kd.y < plan->ptn.y && droite->vec.y < 0))
      	return (MAXDOUBLE);
      r = sqrt(pow(plan->ptn.y - droite->c_kd.y, 2)) / droite->vec.y;
    }
  else if (plan->ptn.z != MAXDOUBLE)
    {
      if ((droite->c_kd.z > plan->ptn.z && droite->vec.z > 0)
      	  || (droite->c_kd.z < plan->ptn.z && droite->vec.z < 0))
      	return (MAXDOUBLE);
      r = sqrt(pow(plan->ptn.z - droite->c_kd.z, 2)) / droite->vec.z;
    }
  if (r < 0)
    return (-r);
  return (r);
}

float		v_abs(double nb)
{
  if (nb < 0)
    nb = -nb;
  return (nb);
}

t_inter		*my_send_rayon_rec(t_kdtree *tree, t_st *droite, int a)
{
  int		i;
  t_inter       *my_return;
  t_inter       *my_return2;
  double	r1;
  double	r2;

  if (tree == NULL)
    return (NULL);
  if (a <= 1  || (tree->t_l == NULL && tree->t_r == NULL))
    return (check_obj_in_tree(tree->obj, droite));
  i = find_i(&droite->c_kd, &tree->plan.ptn);
  my_return = NULL;
  if (i <= 0)
    my_return = my_send_rayon_rec(tree->t_l, droite, MAX_ITERATION - 1);
  else
    my_return = my_send_rayon_rec(tree->t_r, droite, MAX_ITERATION - 1);
  r1 = find_inter_plan_dr(&tree->plan, droite);
  r2 = find_inter_plan_dr(&tree->t_p->plan, droite);
  if (r1 != MAXDOUBLE)
    {
      if (i <= 0)
	my_return2 = my_send_rayon_rec(tree->t_r, droite, MAX_ITERATION - 1);
      else
	my_return2 = my_send_rayon_rec(tree->t_l, droite, MAX_ITERATION - 1);
      if (my_return != NULL && my_return2 != NULL)
	{
	  if (my_return->d < my_return2->d)
	    {
	      free(my_return2);
	      return (my_return);
	    }
	  free(my_return);
	  return (my_return2);
	}
      if (my_return == NULL)
	return (my_return2);
      return (my_return);
    }
  return (my_return);
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

int		my_place_c_kd(t_kdtree *tree, t_st *droite)
{
  int		b;
  double	r;
  double	t;

  b = -1;
  r = MAXDOUBLE;
  if (my_check_for_p(tree, droite, 0) == 1)
    {
      droite->c_kd.x = droite->cord.x;
      droite->c_kd.y = droite->cord.y;
      droite->c_kd.z = droite->cord.z;
      return (1);
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
  droite->c_kd.x = droite->cord.x + (droite->vec.x * r);
  droite->c_kd.y = droite->cord.y + (droite->vec.y * r);
  droite->c_kd.z = droite->cord.z + (droite->vec.z * r);
  return (b);
}

t_inter		*my_send_rayon_act_kdtree(t_rs *rs, t_st *droite)
{
  int           i;
  t_inter       *my_return;
  double	r1;
  
  if (my_place_c_kd(rs->tree, droite) == -1)
    return (NULL);
  i = find_i(&droite->c_kd, &rs->tree->plan.ptn);
  if (i < 0)
    my_return = my_send_rayon_rec(rs->tree->t_l, droite, MAX_ITERATION - 1);
  else
    my_return = my_send_rayon_rec(rs->tree->t_r, droite, MAX_ITERATION - 1);
  if (my_return != NULL)
    return (my_return);
  if (i <= 0)
    return (my_send_rayon_rec(rs->tree->t_r, droite, MAX_ITERATION - 1));
  return (my_return = my_send_rayon_rec(rs->tree->t_l, droite, MAX_ITERATION - 1));
}
