/*
** new_env.c for raytracer in /home/mart_p//raytracer
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Sat Jun  8 20:19:57 2013 louis martin-pierrat
** Last update Sat Jun  8 21:03:11 2013 louis martin-pierrat
*/
#include	"rt.h"

void		set_env(t_env *env, struct s_xml *tree)
{
  get_ivalue(tree, "antialliasing", &env->antia) == FAIL ? env->antia = 2 : 0;
  get_ivalue(tree, "black_and_white", &env->b_and_w) == FAIL ? \
    env->b_and_w = 0 : 0;
  get_ivalue(tree, "sepia", &env->sepia) == FAIL ? env->sepia = 0 : 0;
  get_ivalue(tree, "negatif", &env->negative) == FAIL ? env->negative = 0 : 0;
  get_ivalue(tree, "pattern", &env->pattern) == FAIL ? env->pattern = 2 : 0;
  get_fvalue(tree, "exposition", &env->expo) == FAIL
    || env->expo >= 0 ? env->expo = -2 : 0;
  get_ivalue(tree, "complexity", &env->complexity) == FAIL
    || env->complexity <= 0 ? env->complexity = 50 : 0;
  get_fvalue(tree, "dispersion", &env->disper) == FAIL ? env->disper = 2 : 0;
  get_fvalue(tree, "focus", &env->focus) == FAIL || env->focus <= 0 ?
    env->focus = 50 : 0;
  get_ivalue(tree, "stereoscopie", &env->stereo) == FAIL ? env->stereo = 0 :0;
}
