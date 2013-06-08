/*
** new_tore.c for raytracer in /home/martyn_k//raytracer
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sat Jun  8 14:02:22 2013 karina martynava
** Last update Sat Jun  8 18:39:44 2013 karina martynava
*/
#include	"rt.h"

void		new_tore(t_obj **obj, t_mat *mat, struct s_xml *tree, int i)
{
  t_obj		*new;
  float		*rayon;
  int		mat_id;

  new = xmalloc(sizeof(t_obj));
  rayon = xmalloc(sizeof(float) * 2);
  new->id = i;
  get_fvalues(tree, "coord", "x", &new->ptn.x) == FAIL ? new->ptn.x = 0 : 0;
  get_fvalues(tree, "coord", "y", &new->ptn.y) == FAIL ? new->ptn.y = 0 : 0;
  get_fvalues(tree, "coord", "z", &new->ptn.z) == FAIL ? new->ptn.z = 0 : 0;
  get_fvalues(tree, "rot", "x", &new->rot.x) == FAIL ? new->rot.x = 0 : 0;
  get_fvalues(tree, "rot", "y", &new->rot.y) == FAIL ? new->rot.y = 0 : 0;
  get_fvalues(tree, "rot", "z", &new->rot.z) == FAIL ? new->rot.z = 0 : 0;
  get_fvalue(tree, "rayon1", &rayon[0]) == FAIL ? rayon[0] = 0 : 0;
  get_fvalue(tree, "rayon2", &rayon[1]) == FAIL ? rayon[1] = 0 : 0;
  get_ivalue(tree, "material_id", &mat_id) == FAIL ?
    (new->mat = NULL) : (new->mat = seek_mat(mat_id, mat));
  new->next = NULL;
  new->matrix = NULL;
  creat_matrice_for_obj(new);
  new->data = (void *)(rayon);
  new->cal_color = cal_color_shere;
  new->cal_inter = call_inter_tore;
  add_to_end(obj, new);
}
