/*
** new_eyes.c for raytracer in /home/mart_p//raytracer/new_elem
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Thu Jun  6 15:20:03 2013 louis martin-pierrat
** Last update Thu Jun  6 15:39:18 2013 louis martin-pierrat
*/
#include	"rt.h"

void		new_eyes(t_pov **eyes, struct s_xml *tree)
{
  t_pov		*new;
  t_pov		*tmp;

  tmp = (*eyes);
  new = xmalloc(sizeof(t_pov));
  get_ivalues(tree, "screen", "larg", &new->larg) == FAIL ? \
    new->larg = SIZE_LARG : 0;
  get_ivalues(tree, "screen", "long", &new->lng) == FAIL ? \
    new->lng = SIZE_LONG : 0;
  get_fvalues(tree, "cam", "x", &new->cam.x) == FAIL ? new->cam.x = -200 : 0;
  get_fvalues(tree, "cam", "y", &new->cam.y) == FAIL ? new->cam.y = 0 : 0;
  get_fvalues(tree, "cam", "z", &new->cam.z) == FAIL ? new->cam.z = 0 : 0;
  get_fvalues(tree, "rot", "x", &new->rot.x) == FAIL ? new->rot.x = 0 : 0;
  get_fvalues(tree, "rot", "y", &new->rot.y) == FAIL ? new->rot.y = 0 : 0;
  get_fvalues(tree, "rot", "z", &new->rot.z) == FAIL ? new->rot.z = 0 : 0;
  new->next = NULL;
  while (tmp != NULL && tmp->next != NULL)
    tmp = tmp->next;
  (tmp == NULL) ? ((*eyes) = new) : (tmp->next = new);
}
