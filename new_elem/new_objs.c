/*
** new_objs.c for raytracer in /home/mart_p//raytracer
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Thu Jun  6 21:02:55 2013 louis martin-pierrat
** Last update Thu Jun  6 21:11:42 2013 louis martin-pierrat
*/
#include	"rt.h"

void		new_objs(t_rs *rs, struct s_xml *tree)
{
  static int	i = 1;

  while (tree != NULL && tree->child != NULL)
    {
      if (m_strcmp(tree->child->name, "sphere") == 0)
  	new_sphere(&rs->obj, rs->mat, tree->child, i++);
      else if (m_strcmp(tree->child->name, "plan") == 0)
	new_plane(&rs->obj, rs->mat, tree->child, i++);
      else if (m_strcmp(tree->child->name, "cylindre") == 0)
	new_cylinder(&rs->obj, rs->mat, tree->child, i++);
      else if (m_strcmp(tree->child->name, "cone") == 0)
	new_conus(&rs->obj, rs->mat, tree->child, i++);
      else if (m_strcmp(tree->child->name, "triangle") == 0)
	new_triangle(&rs->obj, rs->mat, tree->child, i++);
      tree->child = tree->child->next;
    }
}

void		new_objs_neg(t_rs *rs, struct s_xml *tree)
{
  static int	i = 1;

  while (tree != NULL && tree->child != NULL)
    {
      if (m_strcmp(tree->child->name, "sphere") == 0)
  	new_sphere(&rs->obj_neg, rs->mat, tree->child, i++);
      else if (m_strcmp(tree->child->name, "plan") == 0)
	new_plane(&rs->obj_neg, rs->mat, tree->child, i++);
      else if (m_strcmp(tree->child->name, "cylindre") == 0)
	new_cylinder(&rs->obj_neg, rs->mat, tree->child, i++);
      else if (m_strcmp(tree->child->name, "cone") == 0)
	new_conus(&rs->obj_neg, rs->mat, tree->child, i++);
      else if (m_strcmp(tree->child->name, "triangle") == 0)
	new_triangle(&rs->obj_neg, rs->mat, tree->child, i++);
      tree->child = tree->child->next;
    }
}
