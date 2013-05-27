/*
** my_getnbr.c for my_getnbr.c in /home/mayol_l//fdf-2017-mayol_l
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sun Dec  9 21:25:39 2012 lucas mayol
** Last update Wed Jan  2 17:24:57 2013 lucas mayol
*/

int     my_getnbr(char *str)
{
  int   i;
  int   j;
  int   result;

  i = 0;
  j = 1;
  result = 0;
  while (str[i] == '-' || str[i] == '+')
    {
      if (str[i] == '-')
        j = j * -1;
      i = i + 1;
    }
  while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
    {
      result = result * 10 + (str[i] - '0');
      i++;
    }
  return (result * j);
}
