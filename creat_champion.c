/*
** creat_champion.c for  in /home/berny_m/tech2/PSU_2015_lemipc
**
** Made by berny_m
** Login   <berny_m@epitech.net>
**
** Started on  Thu Mar 17 18:11:27 2016 berny_m
** Last update Sun Mar 27 17:59:49 2016 blanqu_a
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "lemipc.h"

int		get_y(int pos)
{
  int		i;

  i = 0;
  while (pos > LENGTH)
    {
      pos -= LENGTH;
      i++;
    }
  return (i);
}

int		get_x(int pos)
{
  while (pos > LENGTH)
    pos -= LENGTH;
   pos--;
  return (pos);
}

int		free_space(struct s_case *tab)
{
  int		i;

  i = 0;
  while (i < SIZE)
    {
      if (tab[i].nteam == 0)
	return (1);
      i++;
    }
  return (0);
}

int		creat_champion(struct s_case *tab, int team, int sem_id)
{
  int		pos;

  lock(sem_id);
  if (free_space(tab) == 0)
    {
      unlock(sem_id);
      exit(0);
    }
  pos = (rand() % (SIZE - 1));
  while (tab[pos].nteam != 0)
    pos = (rand() % (SIZE - 1));
  tab[pos].nteam = team;
  unlock(sem_id);
  return (pos);
}
