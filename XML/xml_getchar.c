/*
** xml_getchar.c for xml_parsing in /home/mart_p//XML
** 
** Made by louis martin-pierrat
** Login   <mart_p@epitech.net>
** 
** Started on  Fri May 31 17:47:41 2013 louis martin-pierrat
** Last update Sun Jun  9 18:04:08 2013 karina martynava
*/
#include	<unistd.h>
#include	"xml_macros.h"

static int	reset_static(char buffer[BUFFER_SIZE], int *read, int *ret)
{
  int		i;

  i = -1;
  while (++i < BUFFER_SIZE)
    buffer[i] = '\0';
  *read = 0;
  *ret = 0;
  return (FAILURE);
}

int		xml_getchar(const int fd, char *c)
{
  static char	buffer[BUFFER_SIZE];
  static int	nbr_read = 0;
  static int	nbr_ret = 0;

  if (fd == -1)
    return (reset_static(buffer, &nbr_read, &nbr_ret));
  if (nbr_read == nbr_ret)
    {
      nbr_read = read(fd, &buffer, BUFFER_SIZE);
      nbr_ret = 0;
    }
  if (nbr_read == -1 || nbr_read == 0)
    return (FAILURE);
  *c = buffer[nbr_ret++];
  return (SUCCESS);
}
