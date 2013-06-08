/*
** new_extern.c for raytracer in /home/mart_p//raytracer
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Sat Jun  8 20:53:43 2013 louis martin-pierrat
** Last update Sat Jun  8 23:54:13 2013 lucas mayol
*/
#include	"rt.h"

void		parsing(char *path, t_obj *new)
{
  t_extern	*ext;

  ext = xmalloc(sizeof(t_extern));
  ext->obj = obj_pars_main(path, new);
  ext->kdtree = creat_tree(ext->obj);
  new->data = (void *)(ext);
}

void		new_extern(t_obj **obj, t_mat *mat, struct s_xml *tree, int i)
{
  t_obj		*new;
  char		*path;
  int		mat_id;

  new = xmalloc(sizeof(t_obj));
  new->id = i;
  get_fvalues(tree, "coord", "x", &new->ptn.x) == FAIL ? new->ptn.x = 0 : 0;
  get_fvalues(tree, "coord", "y", &new->ptn.y) == FAIL ? new->ptn.y = 0 : 0;
  get_fvalues(tree, "coord", "z", &new->ptn.z) == FAIL ? new->ptn.z = 0 : 0;
  get_fvalues(tree, "rot", "x", &new->rot.x) == FAIL ? new->rot.x = 0 : 0;
  get_fvalues(tree, "rot", "y", &new->rot.y) == FAIL ? new->rot.y = 0 : 0;
  get_fvalues(tree, "rot", "z", &new->rot.z) == FAIL ? new->rot.z = 0 : 0;
  get_strvalue(tree, "file", &path) == FAIL ? path = NULL : 0;
  get_ivalue(tree, "material_id", &mat_id) == FAIL ?
    (new->mat = NULL) : (new->mat = seek_mat(mat_id, mat));
  new->next = NULL;
  new->matrix = NULL;
  creat_matrice_for_obj(new);
  parsing(path, new);
  /* new->cal_color = cal_color_extern; */
  /* new->cal_inter = call_inter_extern; */
  add_to_end(obj, new);
}
