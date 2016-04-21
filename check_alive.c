/*
** check_alive.c for  in /home/berny_m/tech2/PSU_2015_lemipc
**
** Made by berny_m
** Login   <berny_m@epitech.net>
**
** Started on  Mon Mar 21 11:34:59 2016 berny_m
** Last update Sun Mar 27 17:56:19 2016 blanqu_a
*/

#include "lemipc.h"

static int	exist_another(int *around, int pos)
{
  int		i;

  i = 0;
  while (i < 8)
    {
      if (i != pos && around[i] == around[pos])
	return (1);
      i++;
    }
  return (0);
}

static int	check_double(int *around, int current_team)
{
  int		i;

  i = 0;
  while (i < 8)
    {
      if (around[i] != current_team && exist_another(around, i) == 1 &&
	  around[i] != 0)
	return (0);
      i++;
    }
  return (1);
}

int		check_alive(struct s_case *tab, int pos)
{
  int		around[8];
  int		i;

  around[0] = ((i = pos + 1) > SIZE) ? 0 : tab[i].nteam;
  around[1] = ((i = pos + WIDTH + 1) > SIZE) ? 0 : tab[i].nteam;
  around[2] = ((i = pos + WIDTH) > SIZE) ? 0 : tab[i].nteam;
  around[3] = ((i = pos + WIDTH - 1) > SIZE) ? 0 : tab[i].nteam;
  around[4] = ((i = pos - 1) < 0) ? 0 : tab[i].nteam;
  around[5] = ((i = pos - WIDTH - 1) < 0) ? 0 : tab[i].nteam;
  around[6] = ((i = pos - WIDTH) < 0) ? 0 : tab[i].nteam;
  around[7] = ((i = pos - WIDTH + 1) < 0) ? 0 : tab[i].nteam;
  if (check_double(around, tab[pos].nteam) == 0)
    {
      tab[pos].nteam = 0;
      return (0);
    }
  return (1);
}
