/*
** new_material.c for raytracer in /home/mart_p//raytracer/new_elem
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Thu Jun  6 15:22:33 2013 louis martin-pierrat
** Last update Thu Jun  6 18:09:37 2013 louis martin-pierrat
*/
#include	"rt.h"

static void	m_add_to_end(t_mat **obj, t_mat *new)
{
  t_mat		*tmp;

  tmp = (*obj);
  while (tmp != NULL && tmp->next != NULL)
    tmp = tmp->next;
  (tmp == NULL) ? ((*obj) = new) : (tmp->next = new);
}

struct s_xml	*seek_child(struct s_xml *tree, char *str)
{
  struct s_xml	*child;

  child = (tree != NULL) ? tree->child : NULL;
  while (child != NULL && m_strcmp(child->name, str) != 0)
    child = child->next;
  return (child);
}

void		new_bruit(t_mat *material, struct s_xml *tree)
{
  if (tree != NULL)
    {
      get_ivalue(tree, "type", &material->bruit.type) == FAIL ? \
	material->bruit.type = 0 : 0;
      get_fvalue(tree, "persistance", &material->bruit.persistance) == FAIL ? \
	material->bruit.persistance = 0 : 0;
      get_fvalues(tree, "color1", "red", &material->bruit.color1[0]) == FAIL ? \
	material->bruit.color1[0] = 0 : 0;
      get_fvalues(tree, "color1", "green", &material->bruit.color1[1]) == FAIL ? \
	material->bruit.color1[1] = 0 : 0;
      get_fvalues(tree, "color1", "blue", &material->bruit.color1[2]) == FAIL ? \
	material->bruit.color1[2] = 0 : 0;
      get_fvalues(tree, "color2", "red", &material->bruit.color2[0]) == FAIL ? \
	material->bruit.color2[0] = 0 : 0;
      get_fvalues(tree, "color2", "green", &material->bruit.color2[1]) == FAIL ? \
	material->bruit.color2[1] = 0 : 0;
      get_fvalues(tree, "color2", "blue", &material->bruit.color2[2]) == FAIL ? \
	material->bruit.color2[2] = 0 : 0;
    }
}

void		new_material(t_mat **material, t_rs *rs, struct s_xml *tree)
{
  t_mat		*new;
  char		*path;

  new = xmalloc(sizeof(t_mat));
  get_ivalue(tree, "id", &new->id) == FAIL ? new->id = 0 : 0;
  get_fvalue(tree, "red", &new->red) == FAIL ? new->red = 0.2 : 0; 
  get_fvalue(tree, "blue", &new->blue) == FAIL ? new->blue = 1 : 0;
  get_fvalue(tree, "green", &new->green) == FAIL ? new->green = 0.2 : 0;
  get_fvalue(tree, "reflexion", &new->reflex) == FAIL ? new->reflex = 0 : 0;
  get_fvalue(tree, "spec1", &new->spec[0]) == FAIL ? new->spec[0] = 1.0 : 0;
  get_fvalue(tree, "spec2", &new->spec[1]) == FAIL ? new->spec[1] = 1.0 : 0;
  get_fvalue(tree, "spec3", &new->spec[2]) == FAIL ? new->spec[2] = 1.0 : 0;
  get_fvalue(tree, "specpow", &new->spec_pow) == FAIL ? new->spec_pow = 0 : 0;
  get_strvalue(tree, "texture", &path) == FAIL ?
    new->img.img = NULL : load_img(rs, &new->img, path);
  new_bruit(new, seek_child(tree, ""));
  new->next = NULL;
  m_add_to_end(material, new);
}
