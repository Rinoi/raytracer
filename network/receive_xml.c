/*
** receive_xml.c for cluster in /home/mart_q//cluster/client/src
** 
** Made by thibault martinez
** Login   <mart_q@epitech.net>
** 
** Started on  Mon Jun  3 15:48:00 2013 thibault martinez
** Last update Wed Jun  5 22:57:06 2013 thibault martinez
*/

#include	"network.h"

int		receive_xml(t_sock *sock)
{
  char		buffer[512];
  int		ret;
  int		fd;
  int		pong;

  ret = 512;
  fd = open("tmp.xml", O_CREAT | O_WRONLY | O_TRUNC,
	    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  while (ret >= 512)
    {
      pong = 0;
      while (pong != ret)
	{
	  read(sock->socket_fd, &pong, sizeof(int));
	  ret = read(sock->socket_fd, buffer, 512);
	  write(sock->socket_fd, &ret, sizeof(int));
	}
      write(fd, buffer, ret);
    }
  close(fd);
  return (EXIT_SUCCESS);
}
