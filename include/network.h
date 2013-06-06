/*
** server.h for cluster in /home/mart_q//cluster/server/include
** 
** Made by thibault martinez
** Login   <mart_q@epitech.net>
** 
** Started on  Fri May 31 12:33:32 2013 thibault martinez
** Last update Thu Jun  6 11:54:03 2013 thibault martinez
*/

#ifndef			_SERVER_H_
#define			_SERVER_H_

#include		<unistd.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<string.h>
#include		<errno.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<netinet/in.h>
#include		<arpa/inet.h>
#include		<netdb.h>
#include		<sys/stat.h>
#include		<fcntl.h>

#define			BACKLOG	10

typedef struct		s_sock
{
  int			socket_fd;
  socklen_t		socket_size;
  int			dtablesize;
  struct sockaddr_in	si_server;
  struct sockaddr_in	si_client;
  fd_set		read_fds;
  fd_set		c_read_fds;
  char			**av;
}			t_sock;

void			send_xml(int fd, t_sock *sock);
int			receive_xml(t_sock *sock);
void			f_error(char *);

#endif
