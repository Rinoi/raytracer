/*
** new_plane.c for raytracer in /home/mart_p//raytracer/new_elem
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Thu Jun  6 15:30:13 2013 louis martin-pierrat
** Last update Thu Jun  6 21:09:25 2013 louis martin-pierrat
*/
#include	"rt.h"

void		new_plane(t_obj **obj, t_mat *mat, struct s_xml *tree, int i)
{
  int		mat_id;
  t_obj		*new;

  mat_id = 0;
  new = xmalloc(sizeof(t_obj));
  new->id = i;
  get_fvalues(tree, "coord", "x", &new->ptn.x) == FAIL ? new->ptn.x = 0 : 0;
  get_fvalues(tree, "coord", "y", &new->ptn.y) == FAIL ? new->ptn.y = 0 : 0;
  get_fvalues(tree, "coord", "z", &new->ptn.z) == FAIL ? new->ptn.z = 0 : 0;
  get_fvalues(tree, "rot", "x", &new->rot.x) == FAIL ? new->rot.x = 0 : 0;
  get_fvalues(tree, "rot", "y", &new->rot.y) == FAIL ? new->rot.y = 0 : 0;
  get_fvalues(tree, "rot", "z", &new->rot.z) == FAIL ? new->rot.z = 0 : 0;
  get_ivalue(tree, "material_id", &mat_id) == FAIL ?
    (new->mat = NULL) : (new->mat = seek_mat(mat_id, mat));
  new->next = NULL;
  new->matrix = NULL;
  creat_matrice_for_obj(new);
  new->cal_color = cal_color_plan;
  new->cal_inter = call_inter_plane;
  add_to_end(obj, new);
}
