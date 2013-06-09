/*
** server.c for rt in /home/mart_q//raytracer/network
** 
** Made by thibault martinez
** Login   <mart_q@epitech.net>
** 
** Started on  Wed Jun  5 19:43:56 2013 thibault martinez
** Last update Sat Jun  8 17:11:10 2013 thibault martinez
*/

#include	"rt.h"
#include	"network.h"

static int		socket_init(t_sock *sock)
{
  if ((sock->socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    f_error(strerror(errno));
  memset(&sock->si_server, 0, sizeof(struct sockaddr_in));
  sock->si_server.sin_family = AF_INET;
  sock->si_server.sin_port = htons(atoi(sock->av[2]));
  sock->si_server.sin_addr.s_addr = INADDR_ANY;
  if (bind(sock->socket_fd, (const struct sockaddr *)(&sock->si_server),
           sizeof(struct sockaddr_in)) == -1)
    f_error(strerror(errno));
  if (listen(sock->socket_fd, BACKLOG) == -1)
    f_error(strerror(errno));
  return (sock->socket_fd);
}

void                    close_all_fd(t_sock *sock)
{
  int                   i;

  i = 0;
  while (i < sock->dtablesize)
    {
      if (i != sock->socket_fd
          && i != STDIN_FILENO
          && i != STDOUT_FILENO
          && i != STDERR_FILENO)
        close(i);
      i = i + 1;
    }
}

#include <errno.h>

int                     handler(t_rs *rs, int fd)
{
  /* static char		*buf = NULL; */
  static int		ret = 0;
  static int		c = 1;
  int			tmp;

  /* printf("receiving...\n"); */
  /* if (buf == NULL) */
  /*   buf = malloc(sizeof(char) * rs->wind.sampled.x * rs->wind.sampled.y * (rs->wind.sampled.bpp / 8)); */
  tmp = read(fd, rs->wind.sampled.img + ret, rs->wind.sampled.x * rs->wind.sampled.y * (rs->wind.sampled.bpp / 8));
  /* printf("%s\n", strerror(errno)); */
  ret += tmp;
  /* printf("RETURN : %d\n", tmp); */
  if (ret == rs->wind.sampled.x * rs->wind.sampled.y * (rs->wind.sampled.bpp / 8))
    {
      printf("Receiving image [%d]\n", c++);
      my_expose(rs);
      /* close(fd); */
      /* FD_CLR(fd, read_fds); */
      ret = 0;
    }
  else
    {
      /* if (write(STDOUT_FILENO, buf, rs->wind.sampled.x * rs->wind.sampled.y * (rs->wind.sampled.bpp / 8)) == -1); */
      /* printf("loooooooool\n"); */
      /* rs->wind.sampled.img = strdup(buf); */
      /* my_expose(rs); */
    }
  return (EXIT_SUCCESS);
}

int                     fd_manager(t_rs *rs, t_sock *sock)
{
  int                   i;
  int                   new_fd;

  sock->c_read_fds = sock->read_fds;
  if (select(sock->dtablesize, &sock->c_read_fds, NULL, NULL, NULL) == -1)
    f_error(strerror(errno));
  if (FD_ISSET(sock->socket_fd, &sock->c_read_fds))
    {
      if ((new_fd = accept(sock->socket_fd, (struct sockaddr *)(&sock->si_client),
			   &sock->socket_size)) == -1)
	f_error(strerror(errno));
      printf("New connexion from [%s] on slot [%d]\n", inet_ntoa(sock->si_client.sin_addr), new_fd);
      FD_SET(new_fd, &sock->read_fds);
      send_xml(new_fd, sock);
    }
  i = -1;
  while (++i < sock->dtablesize)
    if (i != sock->socket_fd && FD_ISSET(i, &sock->c_read_fds))
      handler(rs, i);
  return (EXIT_SUCCESS);
}

int		rt_server(t_rs *rs, int argc, char **argv)
{
  t_sock                sock;

  signal(SIGPIPE, server_handler);
  if (argc != 4)
    f_error("Usage : ./rt --server PORT file.xml");
  rs->client = 0;
  if (init_rs(rs, xml_parsing(argv[3])) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  rt_main_mlx(rs);
  sock.socket_size = sizeof(struct sockaddr_in);
  sock.dtablesize = getdtablesize();
  sock.av = argv;
  if ((sock.socket_fd = socket_init(&sock)) == -1)
    return (EXIT_FAILURE);
  /* close_all_fd(&sock); */
  FD_ZERO(&sock.read_fds);
  FD_SET(sock.socket_fd, &sock.read_fds);
  while (1)
    fd_manager(rs, &sock);
  if (close(sock.socket_fd) == -1)
    f_error(strerror(errno));
}
