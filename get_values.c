/*
** get_values.c for xml in /home/mart_p//raytracer
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Mon Jun  3 23:29:41 2013 louis martin-pierrat
** Last update Tue Jun  4 19:10:54 2013 louis martin-pierrat
*/

#include	<stdlib.h>
#include	"xml.h"
#include	"xml_macros.h"

int		get_fvalue(struct s_xml *tree, char *name, float *value)
{
  struct s_xml	*tmp;

  tmp = tree->child;
  while (tmp != NULL && m_strcmp(tmp->name, name) != 0)
    tmp = tmp->next;
  if (tmp != NULL && tmp->value != NULL)
    *(value) = atof(tmp->value);
  return (tmp == NULL || tmp->value == NULL ? FAILURE : SUCCESS);
}

int		get_ivalue(struct s_xml *tree, char *name, int *value)
{
  struct s_xml	*tmp;

  tmp = tree->child;
  while (tmp != NULL && m_strcmp(tmp->name, name) != 0)
    tmp = tmp->next;
  if (tmp != NULL && tmp->value != NULL)
    *(value) = atoi(tmp->value);
  return (tmp == NULL || tmp->value == NULL ? FAILURE : SUCCESS);
}

int		get_fvalues(struct s_xml *tree, char *name, char *cname, float *value)
{
  struct s_xml	*child;
  struct s_xml	*tmp;

  tmp = tree->child;
  while (tmp != NULL && m_strcmp(tmp->name, name) != 0)
    tmp = tmp->next;
  child = (tmp != NULL) ? tmp->child : NULL;
  while (child != NULL && m_strcmp(child->name, cname) != 0)
    child = child->next;
  if (child != NULL && child->value != NULL)
    *(value) = atof(child->value);
  return (child == NULL || child->value == NULL ? FAILURE : SUCCESS);
}

int		get_ivalues(struct s_xml *tree, char *name, char *cname, int *value)
{
  struct s_xml	*child;
  struct s_xml	*tmp;

  tmp = tree->child;
  while (tmp != NULL && m_strcmp(tmp->name, name) != 0)
    tmp = tmp->next;
  child = (tmp != NULL) ? tmp->child : NULL;
  while (child != NULL && m_strcmp(child->name, cname) != 0)
    child = child->next;
  if (child != NULL && child->value != NULL)
    *(value) = atof(child->value);
  return (child == NULL || child->value == NULL ? FAILURE : SUCCESS);
}
