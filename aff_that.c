/*
** aff_that.c for  in /home/berny_m/tech2/PSU_2015_lemipc
**
** Made by berny_m
** Login   <berny_m@epitech.net>
**
** Started on  Thu Mar 17 17:24:13 2016 berny_m
** Last update Sun Mar 27 17:40:12 2016 Adrien Blanquer
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>

#include "lemipc.h"

static int	is_tab_one_team(struct s_case *map)
{
  int		x;
  int		save_team;

  x = 1;
  save_team = map[0].nteam;
  while (x < SIZE)
    {
      if (map[x].nteam != 0 && save_team == 0)
	save_team = map[x].nteam;
      else if (map[x].nteam != 0 && save_team != map[x].nteam &&
	       save_team != 0)
	return (0);
      x++;
    }
  return (1);
}

static int	nbr_alive(struct s_case *map)
{
  int		nb;
  int		x;

  nb = 0;
  x = 0;
  while (x < SIZE)
    {
      if (map[x].nteam != 0)
	nb++;
      x++;
    }
  return (nb);
}

static void	print_board()
{
  int		i;

  i = 0;
  printf("+");
  while (i < WIDTH)
    {
      printf("-");
      i++;
    }
  printf("+\n");
}

static void	display_map(struct s_case *map)
{
  int		pos;

  pos = 0;
  system("clear");
  print_board();
  printf("|");
  while (pos < SIZE)
    {
      if (map[pos].nteam > 0)
	printf("%d", map[pos].nteam);
      else
	printf(" ");
      pos++;
      if (pos % WIDTH == 0)
	printf("|\n|");
    }
  print_board();
  printf("nbr alive  = %i\n", nbr_alive(map));
}

void		continuous_aff(struct s_case *map, int shm_id,
			       int sem_id, int msg_id)
{
  int		i;

  i = 0;
  while (is_tab_one_team(map) == 1)
    usleep(1);
  while (is_tab_one_team(map) != 1)
    {
      lock(sem_id);
      display_map(map);
      usleep(100000);
      unlock(sem_id);
    }
  usleep(100000);
  unlock(sem_id);
  display_map(map);
  while (i < SIZE && map[i].nteam == 0)
    i++;
  printf("TEAM %i WON THEY ARE GOOD GUYS YEAH !\n", map[i].nteam);
  semctl(sem_id, 1, IPC_RMID);
  shmctl(shm_id, IPC_RMID, NULL);
  msgctl(msg_id, IPC_RMID, NULL);
}
