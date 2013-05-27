/*
** pars_main.c for pars_xml in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue Feb 19 22:22:10 2013 lucas mayol
** Last update Sat Apr 13 13:12:26 2013 lucas mayol
*/

#include <stdlib.h>
#include "../include/rtv1.h"
#include "../include/get_next_line.h"
#include "pars.h"

char		*my_take_data_b(t_rs *rs, t_noeud *lb, char *str, int fd)
{
  int		i;
  t_balist	bal;

  i = 0;
  lb->bal.data = my_take_word(str, &i);
  str = str + i;
  str = my_go_to_next(rs, str, fd);
  if ((i = what_balist(str, &bal)) == -1)
    my_error(rs, "ballist errors");
  if (my_strcmp(bal.name, lb->bal.name) == 0 || bal.bool != -1)
    my_error(rs, "no close balist");
  str = str + i;
  return (str);
}

char		*my_take_data_balist(t_rs *rs, int fd, t_noeud *lb, char *str)
{
  int		i;
  t_balist	bal;

  bal.name = NULL;
  str = my_go_to_next(rs, str, fd);
  if ((lb->branche1 = malloc(sizeof(t_noeud))) == NULL)
    my_error(rs, "malloc error");
  lb->branche1->pres = lb->bal.name;
  if ((i = what_balist(str, &bal)) == -1)
    my_error(rs, "ballist error");
  if (bal.bool == 1)
    str = my_pars_act(rs, fd, lb->branche1, str);
  return (str);
}

char	*ini_lb(t_noeud *lb, t_rs *rs, char *str, int fd)
{
  int	i;

  lb->type = 1;
  lb->branche1 = NULL;
  lb->branche2 = NULL;
  str = my_go_to_next(rs, str, fd);
  if ((i = what_balist(str, &lb->bal)) == -1)
    my_error(rs, "ballist errorrrr");
  str = str + i;
  str = my_go_to_next(rs, str, fd);
  i = epure_to_next(str);
  str = str + i;
  return (str);
}

char		*my_pars_act(t_rs *rs, int fd, t_noeud *lb, char *str)
{
  int		i;
  t_balist     	bal;

  str = ini_lb(lb, rs, str, fd);
  if (*str != '<')
    str = my_take_data_b(rs, lb, str, fd);
  else
    str = my_take_data_balist(rs, fd, lb, str);
  str = my_go_to_next(rs, str, fd);
  if ((i = what_balist(str, &bal)) == -1)
    my_error(rs, "ballist error");
  if (my_strcmp(lb->pres, bal.name) == 0)
    {
      if ((lb->branche2 = malloc(sizeof(t_noeud))) == NULL)
	my_error(rs, "malloc error");
      lb->branche2->pres = lb->pres;
      str = my_pars_act(rs, fd, lb->branche2, str);
    }
  else
    str = str + i;
  return (str);
}

void		pars_main_tree(t_rs *rs, int fd, t_noeud *n)
{
  int		i;
  char		*str;

  str = get_next_line(fd);
  rs->l = 1;
  n->type = 1;
  n->bal.name = "main";
  n->branche1 = NULL;
  n->branche2 = NULL;
  if ((n->branche1 = malloc(sizeof(t_noeud))) ==  NULL)
    my_error(rs, "malloc error");
  if ((i = what_balist(str, &n->bal)) == -1)
    my_error(rs, "ballist error");
  str = str + i;
  n->pres = n->bal.name;
  n->branche1->pres = n->bal.name;
  my_pars_act(rs, fd, n->branche1, str);
}
