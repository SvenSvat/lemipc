/*
** init.c for lemipc in /home/blanqu_a/rendu/PSU_2015_lemipc
**
** Made by blanqu_a
** Login   <blanqu_a@epitech.net>
**
** Started on  Wed Mar 23 18:14:17 2016 blanqu_a
** Last update Sun Mar 27 17:43:17 2016 Adrien Blanquer
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>

#include "lemipc.h"

int		init_ftok(int argc, char **argv)
{
  key_t		key;

  if (argc != 3)
    {
      fprintf(stderr, "Usage: %s PATH NB_TEAM \n", argv[0]);
      return (-1);
    }
  if ((key = ftok(argv[1], 0)) == -1)
    {
      fprintf(stderr, "%s: bad path\n", argv[1]);
      return (-1);
    }
  return (key);
}

t_ipcs		*init_ipcs(int argc, char **argv)
{
  t_ipcs	*new;

  if ((new = malloc(sizeof(t_ipcs))) == NULL)
    return (NULL);
  new->sem_id = 0;
  new->shm_id = 0;
  new->msg_id = 0;
  if ((new->key = init_ftok(argc, argv)) == -1)
    return (NULL);
  return (new);
}

void		init_first_player(t_ipcs *ipcs, int nteam)
{
  void		*addr;
  int		pos;

  if ((addr = shmat(ipcs->shm_id, NULL, SHM_R | SHM_W)) != (void *)-1)
    {
      if ((ipcs->msg_id = msgget(ipcs->key, SHM_R | SHM_W)) == -1)
	ipcs->msg_id = msgget(ipcs->key, IPC_CREAT | SHM_R | SHM_W);
      addr = creat_map(ipcs->key, addr, &ipcs->sem_id);
      pos = creat_champion((struct s_case *)addr, nteam, ipcs->sem_id);
      if (fork() == 0)
	continuous_aff(addr, ipcs->shm_id, ipcs->sem_id, ipcs->msg_id);
      else
	player_loop((struct s_case *)addr, pos, ipcs->sem_id, ipcs->msg_id);
    }
}
