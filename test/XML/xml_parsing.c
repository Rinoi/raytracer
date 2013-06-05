/*
** xml_parsing.c for xml_parseur in /home/mart_p//XML
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Mon Jun  3 18:45:45 2013 louis martin-pierrat
** Last update Mon Jun  3 19:03:14 2013 louis martin-pierrat
*/
#include	<unistd.h>
#include	<fcntl.h>
#include	<stdlib.h>

#include	"xml_struct.h"
#include	"xml_define.h"
#include	"xml_macros.h"

struct s_xml    *m_ret(const int fd, struct s_xml *ptr)
{
  if (fd != -1)
    close(fd);
  xml_getchar(-1, NULL);
  return (ptr);
}

static int	xopen(char *path, int flags)
{
  int		fd;

  if ((fd = open(path, flags)) == -1)
    {
      write(ERR, "Open failed\n", 12);
      exit(EXIT_FAILURE);
    }
  return (fd);
}

struct s_xml	*xml_parsing(char *path)
{
  struct s_xml	*tree;
  char		c;
  int		fd;

  tree = NULL;
  fd = xopen(path, O_RDONLY);
  while (xml_getspace(fd, &c) == SUCCESS)
    if (xml_select(fd, &tree, c) != SUCCESS)
      {
	write(ERR, "fichier xml invalide\n", 21);
	return (m_ret(fd, NULL));
      }
  return (m_ret(fd, tree));
}
