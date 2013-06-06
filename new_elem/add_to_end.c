/*
** add_to_end.c for raytracer in /home/mart_p//raytracer/new_elem
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Thu Jun  6 15:27:39 2013 louis martin-pierrat
** Last update Thu Jun  6 15:52:53 2013 louis martin-pierrat
*/
#include	"rt.h"

void		add_to_end(t_obj **obj, t_obj *new)
{
  t_obj		*tmp;

  tmp = (*obj);
  while (tmp != NULL && tmp->next != NULL)
    tmp = tmp->next;
  (tmp == NULL) ? ((*obj) = new) : (tmp->next = new);
}
