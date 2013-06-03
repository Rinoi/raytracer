/*
** xml_getendtag.c for xml_parsing in /home/mart_p//XML
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Mon Jun  3 18:46:13 2013 louis martin-pierrat
** Last update Mon Jun  3 18:58:49 2013 louis martin-pierrat
*/
#include	<stdlib.h>

#include	"xml_struct.h"
#include	"xml_define.h"
#include	"xml_macros.h"

static int	m_strcmp(char *str, char *str2)
{
  int		i;

  i = 0;
  while (str[i] == str2[i] && str[i] != '\0')
    i++;
  return ((str[i] == str2[i] && str[i] == '\0') ? 0 : 1);
}

int		xml_getendtag(const int fd, struct s_xml **tree)
{
  char		*name;
  char		c;
  int		i;

  i = 0;
  if (tree == NULL)
    return (FAILURE);
  name = xmalloc(sizeof(char) * STR_SIZE);
  while (xml_getchar(fd, &c) != FAILURE)
    {
      name[i] = 0;
      if (c == '>' && m_strcmp((*tree)->name, name) != 0)
	return (FAILURE);
      else if (c == '>')
	{
	  (*tree)->parent != NULL ? (*tree) = (*tree)->parent : 0;
	  return (SUCCESS);
	}
      i < STR_SIZE ? name[i++] = c : 0;
    }
  return (FAILURE);
}
