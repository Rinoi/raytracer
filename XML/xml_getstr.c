/*
** xml_getstr.c for xml_parseur in /home/mart_p//XML
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Mon Jun  3 18:44:37 2013 louis martin-pierrat
** Last update Mon Jun  3 19:02:50 2013 louis martin-pierrat
*/
#include	"xml_struct.h"
#include	"xml_define.h"
#include	"xml_macros.h"

int		xml_getspace(const int fd, char *c)
{
  while (xml_getchar(fd, c) != FAILURE)
    if (*c != ' ' && *c != '\t' && *c != '\n')
      return (SUCCESS);
  return (FAILURE);
}

int		xml_getstr(const int fd, char *str, int *i)
{
  char		c;

  while (xml_getchar(fd, &c) != FAILURE)
    {
      if (c == '"')
	return (SUCCESS);
      (*i) < STR_SIZE ? str[(*i)++] = c : 0;
    }
  return (FAILURE);
}
