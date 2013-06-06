/*
** client.c for rt in /home/mart_q//raytracer/network
** 
** Made by thibault martinez
** Login   <mart_q@epitech.net>
** 
** Started on  Wed Jun  5 19:55:17 2013 thibault martinez
** Last update Thu Jun  6 18:34:16 2013 thibault martinez
*/

#include	"rt.h"
#include	"network.h"

static int	socket_init(t_sock *sock)
{
  if ((sock->socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    f_error(strerror(errno));
  memset(&sock->si_client, 0, sizeof(struct sockaddr_in));
  sock->si_client.sin_family = AF_INET;
  sock->si_client.sin_port = htons(atoi(sock->av[2]));
  if (inet_aton(sock->av[3], &sock->si_client.sin_addr) == 0)
    f_error("Bad ipv4 format");
  if (connect(sock->socket_fd, (const struct sockaddr *)(&sock->si_client), sock->socket_size) == -1)
    f_error(strerror(errno));
  return (EXIT_SUCCESS);
}

int		rt_client(t_rs *rs, int argc, char **argv)
{
  t_sock	sock;
  int		i;

  if (argc != 4)
    f_error("Usage : ./rt --client PORT IP");
  rs->client = 1;
  sock.av = argv;
  i = 1;
  sock.socket_size = (sizeof(struct sockaddr_in));
  if (socket_init(&sock) == -1)
    return (EXIT_FAILURE);
  receive_xml(&sock);
  init_rs(rs, xml_parsing("tmp.xml"));
  rt_main_mlx(rs);
  send_rayon_main(rs);
  printf("Sending image [%d] to [%s]\n", i++, sock.av[3]);
  while (write(sock.socket_fd, rs->wind.sampled.img, rs->wind.sampled.x * rs->wind.sampled.y * (rs->wind.sampled.bpp / 8)) != -1)
    {
      send_rayon_main(rs);
      printf("Sending image [%d] to [%s]\n", i++, sock.av[3]);
    }
  return (EXIT_SUCCESS);
}
