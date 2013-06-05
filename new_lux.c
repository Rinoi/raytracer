/*
** new_lux.c for rt in /home/mart_p//raytracer
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Mon Jun  3 23:35:43 2013 louis martin-pierrat
** Last update Wed Jun  5 05:09:28 2013 louis martin-pierrat
*/

#include	<stdio.h>
#include	"rt.h"
#include	"xml.h"

void		new_lux(t_lux **lux, struct s_xml *tree)
{
  t_lux		*new;
  t_lux		*tmp;

  tmp = (*lux);
  new = xmalloc(sizeof(t_lux));
  get_fvalue(tree, "lux", &new->lux) == FAILURE ? new->lux = 1 : 0;
  get_fvalue(tree, "red", &new->red) == FAILURE ? new->red = 1 : 0;
  get_fvalue(tree, "blue", &new->blue) == FAILURE ? new->blue = 1 : 0;
  get_fvalue(tree, "green", &new->green) == FAILURE ? new->green = 1 : 0;
  get_ivalue(tree, "color", &new->color) == FAILURE ? new->color = 0xFFFFFF : 0;
  get_fvalues(tree, "coord", "x", &new->cord.x) == FAILURE ? new->cord.x = -200 : 0;
  get_fvalues(tree, "coord", "y", &new->cord.y) == FAILURE ? new->cord.y = 0 : 0;
  get_fvalues(tree, "coord", "z", &new->cord.z) == FAILURE ? new->cord.z = 0 : 0;
  get_ivalue(tree, "attribute", &new->attribute) == FAILURE ? new->attribute = NONE : 0;
  /*  */
  printf("lumiere\n");
  printf("lux : %f red : %f blue : %f green : %f\n", new->lux, new->red, new->blue, new->green);
  printf("cord.x : %f cord.y : %f cord.z : %f attribute : %d\n", new->cord.x, new->cord.y, new->cord.z, new->attribute);
  printf("color : %d\n\n", new->color);
  /*  */
  new->next = NULL;
  while (tmp != NULL && tmp->next != NULL)
    tmp = tmp->next;
  (tmp == NULL) ? ((*lux) = new) : (tmp->next = new);
}

void		new_eyes(t_pov **eyes, struct s_xml *tree)
{
  t_pov		*new;
  t_pov		*tmp;

  tmp = (*eyes);
  new = xmalloc(sizeof(t_pov));
  get_ivalues(tree, "screen", "larg", &new->larg) == FAILURE ? new->larg = SIZE_LARG : 0;
  get_ivalues(tree, "screen", "long", &new->lng) == FAILURE ? new->lng = SIZE_LONG : 0;
  get_fvalues(tree, "camera", "x", &new->cam.x) == FAILURE ? new->cam.x = 0 : 0;
  get_fvalues(tree, "camera", "y", &new->cam.y) == FAILURE ? new->cam.y = 0 : 0;
  get_fvalues(tree, "camera", "z", &new->cam.z) == FAILURE ? new->cam.z = 0 : 0;
  get_fvalues(tree, "rotation", "x", &new->rot.x) == FAILURE ? new->rot.x = 0 : 0;
  get_fvalues(tree, "rotation", "y", &new->rot.y) == FAILURE ? new->rot.y = 0 : 0;
  get_fvalues(tree, "rotation", "z", &new->rot.z) == FAILURE ? new->rot.z = 0 : 0;
  /*  */
  printf("eyes\n");
  printf("larg : %d lng : %d\n", new->larg, new->lng);
  printf("cam.x : %f cam.y : %f cam.z : %f\n", new->cam.x, new->cam.y, new->cam.z);
  printf("cam.x : %f cam.y : %f cam.z : %f\n\n", new->rot.x, new->rot.y, new->rot.z);
  /*  */
  new->next = NULL;
  while (tmp != NULL && tmp->next != NULL)
    tmp = tmp->next;
  (tmp == NULL) ? ((*eyes) = new) : (tmp->next = new);
}

void		new_material(t_mat **material, struct s_xml *tree)
{
  t_mat		*new;
  t_mat		*tmp;

  tmp = (*material);
  new = xmalloc(sizeof(t_mat));
  get_ivalue(tree, "id", &new->id) == FAILURE ? new->id = 0 : 0;
  get_fvalue(tree, "red", &new->red) == FAILURE ? new->red = 0.2 : 0;
  get_fvalue(tree, "green", &new->green) == FAILURE ? new->green = 0.2 : 0;
  get_fvalue(tree, "blue", &new->blue) == FAILURE ? new->blue = 1 : 0;
  get_fvalue(tree, "reflexion", &new->reflex) == FAILURE ? new->reflex = 0 : 0;
  get_fvalue(tree, "specpow", &new->spec_pow) == FAILURE ? new->spec_pow = 60 : 0;
  get_fvalue(tree, "spec1", &new->spec[0]) == FAILURE ? new->spec[0] = 1.0 : 0;
  get_fvalue(tree, "spec2", &new->spec[1]) == FAILURE ? new->spec[1] = 1.0 : 0;
  get_fvalue(tree, "spec3", &new->spec[2]) == FAILURE ? new->spec[2] = 1.0 : 0;
  /*  */
  printf("material\n");
  printf("id = %d\n", new->id);
  printf("red : %f green : %f blue : %f\n", new->red, new->green, new->blue);
  printf("reflexion : %f specpow : %f\n", new->reflex, new->spec_pow);
  printf("spec1 : %f spec2 : %f spec3 : %f\n\n", new->spec[0], new->spec[1], new->spec[2]);
  /*  */
  new->next = NULL;
  while (tmp != NULL && tmp->next != NULL)
    tmp = tmp->next;
  (tmp == NULL) ? ((*material) = new) : (tmp->next = new);
}

t_mat		*seek_mat(int mat_id, t_mat *mat)
{
  t_mat		*tmp;

  tmp = mat;
  while (tmp != NULL && tmp->id != mat_id)
    tmp = tmp->next;
  return (tmp);
}

void		add_to_end(t_obj **obj, t_obj *new)
{
  t_obj		*tmp;

  tmp = (*obj);
  while (tmp != NULL && tmp->next != NULL)
    tmp = tmp->next;
  (tmp == NULL) ? ((*obj) = new) : (tmp->next = new);
}

void		new_sphere(t_obj **obj, t_mat *mat, struct s_xml *tree)
{
  t_obj		*new;
  float		*rayon;
  int		mat_id;

  rayon = xmalloc(sizeof(float));
  new = xmalloc(sizeof(t_obj));
  get_fvalues(tree, "coord", "x", &new->ptn.x) == FAILURE ? new->ptn.x = 0 : 0;
  get_fvalues(tree, "coord", "y", &new->ptn.y) == FAILURE ? new->ptn.y = 0 : 0;
  get_fvalues(tree, "coord", "z", &new->ptn.z) == FAILURE ? new->ptn.z = 0 : 0;
  get_fvalues(tree, "rot", "x", &new->rot.x) == FAILURE ? new->rot.x = 0 : 0;
  get_fvalues(tree, "rot", "y", &new->rot.y) == FAILURE ? new->rot.y = 0 : 0;
  get_fvalues(tree, "rot", "z", &new->rot.z) == FAILURE ? new->rot.z = 0 : 0;
  get_fvalue(tree, "rayon", rayon) == FAILURE ? (*rayon) = 10 : 0;
  new->data = (void *)(rayon);
  get_ivalue(tree, "material_id", &mat_id) == FAILURE ? 
    (new->mat = NULL) : (new->mat = seek_mat(mat_id, mat));
  new->next = NULL;
  new->matrix = NULL;
  creat_matrice_for_obj(new);
  new->cal_color = cal_color_shere;
  new->cal_inter = call_inter_sphere;
  /*  */
  printf("sphere\n");
  printf("coord = (x : %f y : %f z : %f)\n", new->ptn.x, new->ptn.y, new->ptn.z);
  printf("rotation = (x : %f z : %f z : %f)\n", new->rot.x, new->rot.y, new->rot.z);
  printf("rayon = %f\nmaterial_id = %d\n\n", *rayon, mat_id);
  /*  */
  add_to_end(obj, new);
}

void		new_plane(t_obj **obj, t_mat *mat, struct s_xml *tree)
{
  t_obj		*new;
  int		mat_id;

  mat_id = 0;
  new = xmalloc(sizeof(t_obj));
  get_fvalues(tree, "coord", "x", &new->ptn.x) == FAILURE ? new->ptn.x = 0 : 0;
  get_fvalues(tree, "coord", "y", &new->ptn.y) == FAILURE ? new->ptn.y = 0 : 0;
  get_fvalues(tree, "coord", "z", &new->ptn.z) == FAILURE ? new->ptn.z = 0 : 0;
  get_fvalues(tree, "rot", "x", &new->rot.x) == FAILURE ? new->rot.x = 0 : 0;
  get_fvalues(tree, "rot", "y", &new->rot.y) == FAILURE ? new->rot.y = 0 : 0;
  get_fvalues(tree, "rot", "z", &new->rot.z) == FAILURE ? new->rot.z = 0 : 0;
  get_ivalue(tree, "material_id", &mat_id) == FAILURE ?
    (new->mat = NULL) : (new->mat = seek_mat(mat_id, mat));
  new->next = NULL;
  new->matrix = NULL;
  creat_matrice_for_obj(new);
  new->cal_color = cal_color_plan;
  new->cal_inter = call_inter_plane;
  /*  */
  printf("plan\n");
  printf("coord = (x : %f y : %f z : %f)\n", new->ptn.x, new->ptn.y, new->ptn.z);
  printf("rotation = (x : %f z : %f z : %f)\n", new->rot.x, new->rot.y, new->rot.z);
  printf("material_id = %d\n\n", mat_id);
  /*  */
  add_to_end(obj, new);
}

void		new_cylinder(t_obj **obj, t_mat *mat, struct s_xml *tree)
{ 
  int		mat_id;
  float		*angle;
  t_obj		*new;

  angle = xmalloc(sizeof(float));
  new = xmalloc(sizeof(t_obj));
  get_fvalues(tree, "coord", "x", &new->ptn.x) == FAILURE ? new->ptn.x = 0 : 0;
  get_fvalues(tree, "coord", "y", &new->ptn.y) == FAILURE ? new->ptn.y = 0 : 0;
  get_fvalues(tree, "coord", "z", &new->ptn.z) == FAILURE ? new->ptn.z = 0 : 0;
  get_fvalues(tree, "rot", "x", &new->rot.x) == FAILURE ? new->rot.x = 0 : 0;
  get_fvalues(tree, "rot", "y", &new->rot.y) == FAILURE ? new->rot.y = 0 : 0;
  get_fvalues(tree, "rot", "z", &new->rot.z) == FAILURE ? new->rot.z = 0 : 0;
  get_fvalue(tree, "angle", angle) == FAILURE ? (*angle) = 45 : 0;
  new->data = (void *)(angle);
  get_ivalue(tree, "material_id", &mat_id) == FAILURE ? 
    (new->mat = NULL) : (new->mat = seek_mat(mat_id, mat));
  new->next = NULL;
  new->matrix = NULL;
  creat_matrice_for_obj(new);
  new->cal_color = cal_color_cylinder;
  new->cal_inter = call_inter_cylinder;
  /*  */
  printf("cylinder\n");
  printf("coord = (x : %f y : %f z : %f)\n", new->ptn.x, new->ptn.y, new->ptn.z);
  printf("rotation = (x : %f z : %f z : %f)\n", new->rot.x, new->rot.y, new->rot.z);
  printf("rayon = %f\nmaterial_id = %d\n\n", *angle, mat_id);
  /*  */
  add_to_end(obj, new);
}
