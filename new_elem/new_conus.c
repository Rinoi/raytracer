/*
** new_conus.c for raytracer in /home/mart_p//raytracer/new_elem
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Thu Jun  6 15:39:52 2013 louis martin-pierrat
** Last update Thu Jun  6 22:11:54 2013 karina martynava
*/
#include	"rt.h"

void		new_conus(t_obj **obj, t_mat *mat, struct s_xml *tree, int i)
{
  int		mat_id;
  float		*angle;
  t_obj		*new;

  new = xmalloc(sizeof(t_obj));
  angle = xmalloc(sizeof(float));
  new->id = i;
  get_fvalue(tree, "limit_z", &new->limit_z) == FAIL ? new->limit_z = 0 : 0;
  get_fvalues(tree, "coord", "x", &new->ptn.x) == FAIL ? new->ptn.x = 0 : 0;
  get_fvalues(tree, "coord", "y", &new->ptn.y) == FAIL ? new->ptn.y = 0 : 0;
  get_fvalues(tree, "coord", "z", &new->ptn.z) == FAIL ? new->ptn.z = 0 : 0;
  get_fvalues(tree, "rot", "x", &new->rot.x) == FAIL ? new->rot.x = 0 : 0;
  get_fvalues(tree, "rot", "y", &new->rot.y) == FAIL ? new->rot.y = 0 : 0;
  get_fvalues(tree, "rot", "z", &new->rot.z) == FAIL ? new->rot.z = 0 : 0;
  get_fvalue(tree, "angle", angle) == FAIL ? (*angle) = 45 : 0;
  get_ivalue(tree, "material_id", &mat_id) == FAIL ?
    (new->mat = NULL) : (new->mat = seek_mat(mat_id, mat));
  new->next = NULL;
  new->matrix = NULL;
  creat_matrice_for_obj(new);
  new->data = (void *)(angle);
  new->cal_color = cal_color_conus;
  new->cal_inter = call_inter_conus;
  printf("HELLO\n");
  add_to_end(obj, new);
}
