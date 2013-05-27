/*
** get_next_line.h for get_next_line in /home/mayol_l//get_next_line
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Mon Nov 19 13:50:42 2012 lucas mayol
** Last update Sun Nov 25 21:25:34 2012 lucas mayol
*/

#ifndef _MY_H_
#define _MY_H_

#define NB_READ 420

char	*get_next_line(const int fd);

typedef struct	s_list
{
  int		fd;
  char		*buff;
  int		where;
  char		my_str[NB_READ + 1];
  int		error;
  struct s_list	*next;
} t_list;

#endif
