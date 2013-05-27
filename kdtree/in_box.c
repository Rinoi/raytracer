/*
** in_box.c for RT in /home/martyn_k//RT
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Thu Apr 18 16:54:27 2013 karina martynava
** Last update Thu Apr 18 19:20:12 2013 karina martynava
*/

#include "kdtree.h"

#define OUT	1
#define IN	0




#define	MAX	6




int	bol_inbox_x(t_box *big, t_box *toplace, float cste)
{
  cste = cste + big->origine->x;
  if (toplace->origine->x > cste + big->origine->x ||
      toplace->origine->x + toplace->length->x < cste)
    return (OUT);
  return (IN);
}

int	bol_inbox_y(t_box *big, t_box *toplace, float cste)
{
  cste = cste + big->origine->y;
  if (toplace->origine->y > cste ||
      toplace->origine->y + toplace->length->y < cste)
    return (OUT);
  return (IN);
}

int	bol_inbox_z(t_box *big, t_box *toplace, float cste)
{
  cste = cste + big->origine->z;
  if (toplace->origine->z > cste ||
      toplace->origine->z + toplace->length->z < cste)
    return (OUT);
  return (IN);
}

int	bol_inbox(t_box *big, t_box *toplace, float cste, int axis)
{
  if (axis == 0)
    return (bol_inbox_x(big, toplace, cste));
  else if (axis == 0)
    return (bol_inbox_y(big, toplace, cste));
  else
    return (bol_inbox_z(big, toplace, cste));
}

float	find_better_split(void)
{
  return (0.50);
}

void	init_boxes(*t_kdtree *ptr, int nb, t_box *big)
{
  ptr = x_malloc(sizeof(*ptr));
  ptr->obj = x_malloc(sizeof(*(current->left->obj)) * ++nb_one);
  ptr->obj[--nb] = NULL;
  ptr->box->origine->x = big->origine->x;
  ptr->box->origine->y = big->origine->y;
  ptr->box->origine->z = big->origine->z;
  ptr->box->lenght->x = big->length->x; 
  ptr->box->lenght->y = big->length->y; 
  ptr->box->lenght->z = big->length->z; 
}

void	cut_boxes(t_kdtree *ptr, float cste, int bol, int axis)
{
  if (bol)
    {
      if (axis == 0)
	ptr->box->lenght->x = cste;
      else if (axis == 1)
	ptr->box->lenght->y = cste;
      else
	ptr->box->lenght->z = cste;
    }
  else
    if (axis == 0)
      {
	ptr->box->origine->x += cste;
	ptr->box->lenght->x = cste;
      }
    else if (axis == 1)
      {
	ptr->box->origine->y += cste;
	ptr->box->lenght->y = cste;
      }
    else
      {
	ptr->box->origine->z += cste;
	ptr->box->lenght->z = cste;
      }
}

float	get_right_ptn(t_ptn *a, int axis)
{
  if (axis == 0)
    return (a->x);
  else if (axis == 1)
    return (a->y);
  else
    return (a->z);
}

void	recall(t_kdtree *current, int level, int axis, int max)
{
  if (level + 1 <= max)
    return ;
  split_box(current->right, level + 1, (axis + 1) % 3);
  split_box(current->left, level + 1, (axis + 1) % 3);
}

void	split_box(t_kdtree *current, int level, int axis, int max)
{
  int	i;
  float	cste;
  int	nb_one;
  int	nb_two;

  nb_one = 0;
  nb_two = 0;
  i = 0;
  tab = x_malloc(sizeof(*tab) * current->nb_obj);
  cste = find_better_split() * get_right_ptn(current->box->lenght, axis);
  while (current->obj[i] != NULL)
    {
      tab[i++] = bol_inbox(axis, current->obj[i], cste);
      (tab[i - 1]) ? nb_one++ : nb_two++;
    }
  init_boxes(current->left, nb_one--);
  cut_boxes(current->left, cste, 1, axis);
  init_boxes(current->right, nb_two--);
  cut_boxes(current->right,
	    cste - get_right_ptn(current->box->lenght, axis), 0, axis);
  while (i-- > 0)
    (tab[i]) ? current->left->obj[--nb_one] = current->obj[i] :
      current->right->obj[--nb_two] = current->obj[i];
  recall(current, level, axis, max);
}

t_kdtree	*init_first_box(int nb_obj, t_obj *chain, t_ptn *lim, int max)
{
  *t_kdtree	*node;
  int		i;

  i = 0;
  node = x_malloc(sizeof(*node));
  node->nb_obj = nb_obj;
  node->obj = malloc(sizeof(*(node->obj)) * (nb_obj + 1));
  node->box->origine->x = 0; 
  node->box->origine->y = 0;
  node->box->origine->z = 0;
  node->box->lenght->x = lim->x; 
  node->box->lenght->y = lim->y;
  node->box->lenght->z = lim->z;
  while (i < nb_obj)
    {
      node->obj[i++] = chain;
      chain = chain->next;
    }
  split_box(node, 0, 0, max);
  return (node);
}
