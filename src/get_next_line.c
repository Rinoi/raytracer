/*
** get_next_line.c for get_next_ligne in /home/mayol_l//get_next_line/bonus
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed Nov 21 20:06:24 2012 lucas mayol
** Last update Tue Feb 19 22:07:11 2013 lucas mayol
*/

#include <stdlib.h>
#include <unistd.h>
#include "../include/get_next_line.h"

char	*str_cat(char *str_u, t_list *list)
{
  int	cb_a;
  int	cb_b;
  char	*my_return;

  cb_a = 0;
  cb_b = 0;
  while (str_u[cb_a] != '\0')
    cb_a = cb_a + 1;
  while (list->my_str[cb_b] != '\0')
    cb_b = cb_b + 1;
  my_return = malloc(sizeof(char) * (cb_a + cb_b + 1));
  my_return[cb_a + cb_b] = '\0';
  cb_a = 0;
  cb_b = 0;
  while (str_u[cb_a] != '\0')
    {
      my_return[cb_a] = str_u[cb_a];
      cb_a = cb_a + 1;
    }
  while (list->my_str[cb_b] != '\0')
    {
      my_return[cb_a + cb_b] = list->my_str[cb_b];
      cb_b = cb_b + 1;
    }
  return (my_return);
}

int		my_put_in_list(struct s_list **list, int where, const int fd)
{
  struct s_list	*elem;
  char		*buff;

  buff = malloc(sizeof(char) * (NB_READ + 1));
  elem = malloc(sizeof(*elem));
  if (elem == NULL)
    return (1);
  elem->error = read(fd, buff, NB_READ);
  if (elem->error == -1)
    return (1);
  buff[elem->error] = '\0';
  elem->buff = buff;
  elem->fd = fd;
  elem->buff = buff;
  elem->where = where;
  elem->next = *list;
  elem->my_str[0] = '\0';
  *list = elem;
  return (0);
}

t_list		*my_schek(struct s_list **list, const int fd)
{
  t_list	*tmp;

  if (*list == NULL)
    {
      my_put_in_list(list, 0, fd);
      tmp = *list;
      tmp->next = NULL;
      return (*list);
    }
  tmp = *list;
  while (tmp->fd != fd && tmp->next != NULL)
      tmp = tmp->next;
  if (tmp->fd != fd)
    {
      my_put_in_list(list, 0, fd);
      return (*list);
    }
  return (tmp);
}

void   	my_change_buff(t_list *elem, int *cb, char **str)
{
  if (elem->where == NB_READ)
    {
      elem->error = read(elem->fd, elem->buff, NB_READ);
      elem->buff[elem->error] = '\0';
      elem->where = 0;
      elem->my_str[*cb] = '\0';
      *str = str_cat(*str, elem);
      elem->my_str[0] = '\0';
      *cb = 0;
    }
}

char   		*get_next_line(const int fd)
{
  static t_list	*list = NULL;
  char	       	*str;
  t_list       	*elem;
  int		cb;

  str = "\0";
  cb = 0;
  elem = my_schek(&list, fd);
  if (elem->buff[elem->where] == '\n')
    str = "\n\0";
  while (elem->buff[elem->where] != '\n' && elem->buff[elem->where] != '\0')
    {
      elem->my_str[cb] = elem->buff[elem->where];
      cb = cb + 1;
      elem->where = elem->where + 1;
      my_change_buff(elem, &cb, &str);
    }
  elem->my_str[cb] = '\0';
  if (elem->buff[elem->where] == '\n')
    elem->where = elem->where + 1;
  my_change_buff(elem, &cb, &str);
  str = str_cat(str, elem);
  if (elem->error == -1 || str[0] == '\0')
    return (NULL);
  return (str);
}
