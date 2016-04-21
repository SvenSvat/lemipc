/*
** move_champ.c for  in /home/berny_m/tech2/PSU_2015_lemipc
**
** Made by berny_m
** Login   <berny_m@epitech.net>
**
** Started on  Fri Mar 18 13:28:17 2016 berny_m
** Last update Sun Mar 27 17:42:26 2016 Adrien Blanquer
*/

#include <sys/sem.h>
#include <stdlib.h>
#include <sys/msg.h>

#include "lemipc.h"

int		lock(int sem_id)
{
  struct sembuf	occup;

  occup.sem_num = 0;
  occup.sem_flg = 0;
  occup.sem_op = -1;
  if (semop(sem_id, &occup, 1) == -1)
    {
      unlock(sem_id);
      exit(0);
    }
  return (0);
}

void		unlock(int sem_id)
{
  struct sembuf	occup;

  occup.sem_num = 0;
  occup.sem_flg = 0;
  occup.sem_op = 1;
  semop(sem_id, &occup, 1);
}

static int	is_one_available(struct s_case *tab, int pos)
{
  int		x;
  int		y;
  int		return_v;

  return_v = 0;
  x = get_x(pos);
  y = get_y(pos);
  if (y > 0)
    tab[pos - LENGTH].nteam == 0 ? return_v = 1 : 0;
  if (x > 0)
    tab[pos - 1].nteam == 0 ? return_v = 1 : 0;
  if (y < SIZE)
    tab[pos + LENGTH].nteam == 0 ? return_v = 1 : 0;
  if (x < SIZE)
    tab[pos + 1].nteam == 0 ?  return_v = 1 : 0;
  return (return_v);
}

static int	find_first_space_available(struct s_case *tab, int pos)
{
  int		x;
  int		y;
  int		dir;

  x = get_x(pos);
  y = get_y(pos);
  if (is_one_available(tab, pos) == 1)
    {
      dir = rand() % 4;
      if (dir == 0 && y > 0 && tab[pos - LENGTH].nteam == 0)
	return (pos - LENGTH);
      if (dir == 1 && x < SIZE && tab[pos + 1].nteam == 0)
	return (pos + 1);
      if (dir == 2 && y < SIZE && tab[pos + LENGTH].nteam == 0)
	return (pos + LENGTH);
      if (dir == 3 && x > 0 && tab[pos - 1].nteam == 0)
	return (pos - 1);
    }
  return (pos);
}

int		move_champ(struct s_case *tab, int from, int msg_id)
{
  int		team_save;
  int		to;
  int		ret;
  t_msg		my_msg;

  ret = msgrcv(msg_id, &my_msg, sizeof(t_msg), tab[from].nteam, IPC_NOWAIT);
  if (ret == -1 || my_msg.mtype == tab[from].nteam || my_msg.pos == from ||
      my_msg.pos < 0 || my_msg.pos > SIZE)
    to = find_nearest_enemy(tab, from, msg_id);
  else
    to = calcul_pos(from, get_dir(from, my_msg.pos));
  team_save = tab[from].nteam;
  if (tab[to].nteam == 0)
    {
      tab[from].nteam = 0;
      tab[to].nteam = team_save;
    }
  else
    {
      to = find_first_space_available(tab, from);
      tab[from].nteam = 0;
      tab[to].nteam = team_save;
    }
  return (to);
}
