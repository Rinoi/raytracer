/*
** network_fails.c for network in /home/mart_q//raytracer/network
** 
** Made by thibault martinez
** Login   <mart_q@epitech.net>
** 
** Started on  Sat Jun  8 17:02:11 2013 thibault martinez
** Last update Sat Jun  8 17:14:00 2013 thibault martinez
*/

void	client_handler(__attribute__((unused))int sig)
{
  f_error("Server not found");
}

void	server_handler(__attribute__((unused))int sig)
{
}
