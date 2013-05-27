/*
** my_strcmp.c for my_strcmp in /home/mayol_l//corewar/pars
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat Feb  9 10:14:08 2013 lucas mayol
** Last update Sat Feb  9 10:17:01 2013 lucas mayol
*/

int	my_strcmp(char *str, char *cmp)
{
  int	i;

  i = 0;
  while (str[i] == cmp[i] && str[i] != '\0' && cmp[i] != '\0')
    i = i + 1;
  if (str[i] == '\0' && cmp[i] == '\0')
    return (1);
  return (0);
}
