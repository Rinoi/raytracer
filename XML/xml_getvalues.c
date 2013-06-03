/*
** xml_getvalues.c for xml_parseur in /home/mart_p//XML
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Mon Jun  3 18:45:11 2013 louis martin-pierrat
** Last update Mon Jun  3 19:06:24 2013 louis martin-pierrat
*/
#include	<stdlib.h>

#include	"xml_struct.h"
#include	"xml_define.h"
#include	"xml_macros.h"

int		xml_getvalues(const int fd, struct s_xml **tree)
{
  char		c;
  int		i;

  i = 0;
  (*tree)->value = xmalloc(sizeof(char) * STR_SIZE);
  while (xml_getspace(fd, &c) != FAILURE)
    {
      (*tree)->value[i] = 0;
      if (c == '"' && xml_getstr(fd, (*tree)->value, &i) == FAILURE)
	return (FAILURE);
      else if (c == '<')
	{
	  i == 0 ? free((*tree)->value) : 0;
	  i == 0 ? (*tree)->value = NULL : 0;
	  return (xml_select(fd, tree, c));
	}
      else if (c != '"')
	i < STR_SIZE ? (*tree)->value[i++] = c : 0;
    }
  return (FAILURE);
}
