/*
** kdtree.h for kdtree in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Fri May  3 14:45:56 2013 lucas mayol
** Last update Sat Jun  8 23:20:51 2013 lucas mayol
*/

#ifndef _KD_TREE_
# define _KD_TREE_

# define MAX_ITERATION 16

typedef struct	s_obj t_obj;

typedef struct  s_ptn
{
  float		x;
  float		y;
  float		z;
} t_ptn;

typedef struct  s_box
{
  t_ptn		origine;
  t_ptn		lenght;
} t_box;

typedef struct  s_plan
{
  t_ptn		ptn;
} t_plan;

typedef struct		s_l_obj
{
  t_obj			*obj;
  struct s_l_obj	*next;
} t_l_obj;

typedef struct		s_kdtree
{
  t_ptn			ori;
  t_ptn			max;
  t_plan		plan;
  t_l_obj		*obj;
  int			pr;
  struct s_kdtree	*t_l;
  struct s_kdtree	*t_r;
  struct s_kdtree	*t_p;
} t_kdtree;

void		ini_f_tree(t_kdtree *tree);
void		creat_plan_for_tree(t_kdtree *tree);
t_kdtree	*creat_tree(t_obj *obj);
void		my_put_obj_in_tree(t_l_obj **list, t_obj *obj);
int		where_obj_is_in_plan(t_plan *plan, t_box *box);
int		creat_tree_rec(t_kdtree *tree, int b);
void		boxin_triangle(t_obj *obj);

#endif
