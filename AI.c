/*
** AI.c for  in /home/berny_m/tech2/PSU_2015_lemipc
**
** Made by berny_m
** Login   <berny_m@epitech.net>
**
** Started on  Fri Mar 18 14:03:48 2016 berny_m
** Last update Sun Mar 27 17:39:02 2016 Adrien Blanquer
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <math.h>

#include "lemipc.h"

int		get_dir(int from, int to)
{
  int		y_i;
  int		x_i;
  int		y_save;
  int		x_save;

  y_i = get_y(from);
  x_i = get_x(from);
  y_save = get_y(to);
  x_save = get_x(to);
  if (y_i > y_save)
    return (1);
  if (y_i < y_save)
    return (3);
  if (x_i > x_save)
    return (2);
  else
    return (4);
}

static int	compare_dist(int from, int to)
{
  int		x;
  int		y;
  int		x_comp;
  int		y_comp;
  int		diff;

  diff = 0;
  x = get_x(from);
  y = get_y(from);
  x_comp = get_x(to);
  y_comp = get_y(to);
  diff = sqrt(pow(x_comp - x, 2) + pow(y_comp - y, 2));
  return (diff);
}

int		calcul_pos(int from, int dir)
{
  if (dir == 1)
    return (from - LENGTH);
  if (dir == 2)
    return (from - 1);
  if (dir == 3)
    return (from + LENGTH);
  else
    return (from + 1);
}

static void	send_msg(t_msg my_msg, struct s_case *tab, int save, int msg_id)
{
  my_msg.mtype = tab[save].nteam;
  my_msg.pos = save;
  my_msg.mtext[0] = 'a';
  my_msg.mtext[1] = 0;
  msgsnd(msg_id, &my_msg, sizeof(t_msg), my_msg.mtype | IPC_NOWAIT);
}

int		find_nearest_enemy(struct s_case *tab, int from, int msg_id)
{
  int		i;
  int		save;
  int		save_v;
  int		tmp;
  t_msg		my_msg;

  i = 0;
  save_v = 0;
  save = 0;
  while (i < SIZE)
    {
      if (tab[i].nteam != 0 && tab[i].nteam != tab[from].nteam)
	{
	  tmp = compare_dist(from, i);
	  if (save_v < tmp || save_v == 0)
	    {
	      save_v = tmp;
	      save = i;
	    }
	}
      i++;
    }
  send_msg(my_msg, tab, save, msg_id);
  return (calcul_pos(from, get_dir(from, save)));
}
