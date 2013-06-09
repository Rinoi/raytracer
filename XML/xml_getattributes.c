/*
** xml_getattributes.c for xml_parseur in /home/mart_p//XML
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Sat Jun  1 19:35:07 2013 louis martin-pierrat
** Last update Sun Jun  9 16:40:59 2013 lucas mayol
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	"xml_struct.h"
#include	"xml_define.h"
#include	"xml_macros.h"

int		xml_getattribute(const int fd, struct s_xml **tree)
{
  char		c;
  int		i;

  i = 0;
  (*tree)->attributes = xmalloc(sizeof(char) * STR_SIZE);
  while (xml_getspace(fd, &c) != FAILURE)
    {
      (*tree)->attributes[i] = 0;
      if (c == '"' && xml_getstr(fd, (*tree)->attributes, &i) == FAILURE)
	return (FAILURE);
      else if (c == '>')
	return (xml_getvalues(fd, tree));
      else if (c != '"')
	i < STR_SIZE ? (*tree)->attributes[i++] = c : 0;
    }
  return (FAILURE);
}
