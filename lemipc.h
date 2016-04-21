/*
** lemipc.h for lemipc in /home/blanqu_a/rendu/PSU_2015_lemipc
**
** Made by Adrien Blanquer
** Login   <blanqu_a@epitech.net>
**
** Started on  Sun Mar 27 17:43:57 2016 Adrien Blanquer
** Last update Sun Mar 27 17:44:35 2016 Adrien Blanquer
*/

#ifndef LEMIPC_H__
# define LEMIPC_H__

# include <sys/types.h>
# include <sys/ipc.h>

/*
 * This is the structure that you must use to represent a champion
 * You can EXTEND it, but never change the base fields that are already
 * there. Failure to comply will result in a project failure.
 *
 * Your shared memory must be an array of this structure.
 * The size must be of width * height * sizeof(struct s_case)
 */

# define LENGTH 50 // x
# define WIDTH 50 // y
# define SIZE LENGTH * WIDTH
# define CREAT IPC_CREAT | SHM_R | SHM_W
# define GET SHM_R | SHM_W

struct  s_case
{
  /*
   * Position in the map
   */
  int   x;
  int   y;

  /*
   * Team number
   * A value of 0 means that the case is unnocupied
   */
  int   nteam;

  /* Add fields there */
};

/*
 * Note: We MIGHT add fields to the structure so don't use raw numbers for
 * your shm length, use the sizeof keyword
 */

typedef struct	s_ipcs
{
  key_t		key;
  int		sem_id;
  int		shm_id;
  int		msg_id;
}		t_ipcs;

typedef struct  s_msg
{
  int		mtype;
  char		mtext[1];
  int		pos;
}               t_msg;

int		get_x(int);
int		get_y(int);
int		move_champ(struct s_case *, int, int);
int		check_alive(struct s_case *, int);
int		creat_champion(struct s_case *, int, int);
int		find_nearest_enemy(struct s_case *, int, int);
int		calcul_pos(int, int);
int		get_dir(int, int);
int		lock(int);
void		unlock(int);
void		init_first_player(t_ipcs *, int);
void		continuous_aff(struct s_case *, int, int, int);
void		player_loop(struct s_case *, int, int, int);
t_ipcs		*init_ipcs(int, char **);
struct s_case	*creat_map(key_t, struct s_case *, int *);

#endif
