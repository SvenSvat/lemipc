/*
** main.c for  in /home/berny_m/tech2/PSU_2015_lemipc
**
** Made by berny_m
** Login   <berny_m@epitech.net>
**
** Started on  Fri Mar 18 13:40:32 2016 berny_m
** Last update Sun Mar 27 17:41:30 2016 Adrien Blanquer
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/shm.h>

#include "lemipc.h"

struct s_case	*creat_map(key_t key, struct s_case *map, int *sem_id)
{
  int		x;
  int		y;
  int		pos;

  x = 0;
  pos = 0;
  if ((*sem_id = semget(key, 1, IPC_CREAT | SHM_R | SHM_W)) == -1)
    return (NULL);
  semctl(*sem_id, 0, SETVAL, 1);
  while (x < WIDTH)
    {
      y = 0;
      while (y < LENGTH)
	{
	  map[pos].x = x;
	  map[pos].y = y;
	  map[pos].nteam = 0;
	  pos++;
	  y++;
	}
      x++;
    }
  return (map);
}

void		player_loop(struct s_case *addr, int pos, int sem_id, int msg_id)
{
  int		ret;

  ret = 1;
  while (ret)
    {
      lock(sem_id);
      pos = move_champ(addr, pos, msg_id);
      ret = check_alive(addr, pos);
      unlock(sem_id);
      usleep(100000);
    }
}

int		main(int argc, char **argv)
{
  int		pos;
  void		*addr;
  t_ipcs	*ipcs;

  if ((ipcs = init_ipcs(argc, argv)) == NULL)
    return (-1);
  if ((ipcs->shm_id =
       shmget(ipcs->key, (sizeof(struct s_case) * SIZE), GET)) == -1)
    {
      if ((ipcs->shm_id =
	   shmget(ipcs->key, (sizeof(struct s_case) * SIZE), CREAT)) != -1)
	init_first_player(ipcs, atoi(argv[2]));
    }
  else
    {
      ipcs->sem_id = semget(ipcs->key, 1, GET);
      ipcs->msg_id = msgget(ipcs->key, GET);
      if ((addr = shmat(ipcs->shm_id, NULL, GET)) != (void *)-1)
 	pos = creat_champion((struct s_case *)addr, atoi(argv[2]), ipcs->sem_id);
      player_loop((struct s_case *)addr, pos, ipcs->sem_id, ipcs->msg_id);
    }
  return (0);
}
