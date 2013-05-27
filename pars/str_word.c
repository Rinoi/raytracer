/*
** str_word.c for str_word in /home/mayol_l//corewar/pars
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed Jan 30 16:54:13 2013 lucas mayol
** Last update Sat Feb  2 10:07:02 2013 lucas mayol
*/

int	my_str_word(char *str)
{
  int	i;
  int	w;

  i = w = 0;
  while (str[i] != '\0')
    {
      while (str[i] == ' ' || str[i] == '\t')
	i = i + 1;
      if (str[i] != '\0')
	w = w + 1;
      while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
	i = i + 1;
    }
  return (w);
}
