/*
** new_triangle.c for raytracer in /home/mart_p//raytracer/new_elem
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Thu Jun  6 15:41:37 2013 louis martin-pierrat
** Last update Sun Jun  9 14:31:37 2013 karina martynava
*/
#include	"rt.h"

void		get_ptn(struct s_xml *tree, char *str, t_ptn *ptn)
{
  get_fvalues(tree, str, "x", &ptn->x) == FAILURE ? ptn->x = 0 : 0;
  get_fvalues(tree, str, "y", &ptn->y) == FAILURE ? ptn->y = 0 : 0;
  get_fvalues(tree, str, "z", &ptn->z) == FAILURE ? ptn->z = 0 : 0;
}

void		idontknowwhatisit(t_ptn *ptn1, t_ptn *ptn2)
{
  ptn1->x = ptn1->x - ptn2->x;
  ptn1->y = ptn1->y - ptn2->y;
  ptn1->z = ptn1->z - ptn2->z;
}

void		new_triangle(t_obj **obj, t_mat *mat, struct s_xml *tree, int i)
{
  int		mat_id;
  t_tri		*tri;
  t_obj		*new;

  tri = xmalloc(sizeof(t_tri));
  new = xmalloc(sizeof(t_obj));
  new->id = i;
  get_ptn(tree, "a1", &new->ptn);
  get_ptn(tree, "a2", &tri->a2);
  get_ptn(tree, "a3", &tri->a3);
  new->data = (void *)(tri);
  get_ivalue(tree, "material_id", &mat_id) == FAILURE ?
    (new->mat = NULL) : (new->mat = seek_mat(mat_id, mat));
  new->next = NULL;
  new->matrix = NULL;
  new->cal_color = call_color_triangle;
  new->cal_inter = call_inter_triangle;
  idontknowwhatisit(&tri->a2, &new->ptn);
  idontknowwhatisit(&tri->a3, &new->ptn);
  add_to_end(obj, new);
}
