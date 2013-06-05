/*
** send_xml.c for cluster in /home/mart_q//cluster/server/src
** 
** Made by thibault martinez
** Login   <mart_q@epitech.net>
** 
** Started on  Mon Jun  3 14:08:41 2013 thibault martinez
** Last update Wed Jun  5 20:00:42 2013 thibault martinez
*/

#include	"network.h"

void		send_xml(int fd, t_sock *sock)
{
  char		buf[512];
  int		file;
  ssize_t	ret;

  file = open(sock->av[3], O_RDONLY);
  while ((ret = read(file, buf, 512)) > 0)
    write(fd, buf, ret);
  close(file);
}