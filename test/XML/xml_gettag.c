/*
** xml_gettag.c for xml_parseur in /home/mart_p//XML
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Mon Jun  3 17:13:06 2013 louis martin-pierrat
** Last update Mon Jun  3 19:00:01 2013 louis martin-pierrat
*/
#include	<stdlib.h>

#include	"xml_struct.h"
#include	"xml_define.h"
#include	"xml_macros.h"

struct s_xml	*new_parent(struct s_xml **tree, struct s_xml *parent,
			   struct s_xml *prev)
{
  (*tree) = xmalloc(sizeof(struct s_xml));
  (*tree)->name = xmalloc(sizeof(char) * STR_SIZE);
  (*tree)->attributes = NULL;
  (*tree)->value = NULL;
  (*tree)->parent = parent;
  (*tree)->child = NULL;
  (*tree)->prev = prev;
  (*tree)->next = NULL;
  return (*tree);
}

struct s_xml	*new_child(struct s_xml **parent)
{
  struct s_xml	*child;

  child = (*parent)->child;
  if (child == NULL)
    return (new_parent(&(*parent)->child, (*parent), NULL));
  while (child != NULL && child->next != NULL)
    child = child->next;
  child->next = new_parent(&child->next, (*parent), child);
  return (child->next);
}

int		xml_gettag(const int fd, struct s_xml **tree, char c)
{
  int		i;

  i = 0;
  *tree = (*tree) == NULL ? new_parent(tree, NULL, NULL) : new_child(tree);
  (*tree)->name[i++] = c;
  while (xml_getchar(fd, &c) != FAILURE && c != '<')
    {
      (*tree)->name[i] = 0;
      if (c == ' ')
	return (xml_getattribute(fd, tree));
      else if (c == '>')
	return (xml_getvalues(fd, tree));
      i < STR_SIZE ? (*tree)->name[i++] = c : 0;
    }
  return (FAILURE);
}
