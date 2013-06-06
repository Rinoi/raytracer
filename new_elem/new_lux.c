/*
** new_lux.c for rt in /home/mart_p//raytracer
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Mon Jun  3 23:35:43 2013 louis martin-pierrat
** Last update Thu Jun  6 15:59:03 2013 louis martin-pierrat
*/

#include	"rt.h"

static void	m_add_to_end(t_lux **obj, t_lux *new)
{
  t_lux         *tmp;

  tmp = (*obj);
  while (tmp != NULL && tmp->next != NULL)
    tmp = tmp->next;
  (tmp == NULL) ? ((*obj) = new) : (tmp->next = new);
}

void		new_lux(t_lux **lux, struct s_xml *tree)
{
  t_lux		*new;

  new = xmalloc(sizeof(t_lux));
  get_fvalue(tree, "lux", &new->lux) == FAIL ? new->lux = 1 : 0;
  get_fvalue(tree, "red", &new->red) == FAIL ? new->red = 1 : 0;
  get_fvalue(tree, "blue", &new->blue) == FAIL ? new->blue = 1 : 0;
  get_fvalue(tree, "green", &new->green) == FAIL ? new->green = 1 : 0;
  get_ivalue(tree, "color", &new->color) == FAIL ? new->color = 0xFFFFFF : 0;
  get_fvalues(tree, "coord", "x", &new->cord.x) == FAIL ?
    new->cord.x = -200 : 0;
  get_fvalues(tree, "coord", "y", &new->cord.y) == FAIL ?
    new->cord.y = 0 : 0;
  get_fvalues(tree, "coord", "z", &new->cord.z) == FAIL ?
    new->cord.z = 0 : 0;
  get_ivalue(tree, "attribute", &new->attribute) == FAIL ?
    new->attribute = NONE : 0;
  new->next = NULL;
  m_add_to_end(lux, new);
}
