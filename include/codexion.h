/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedrohe3@student.42porto.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 18:23:24 by pedro             #+#    #+#             */
/*   Updated: 2026/08/07 19:09:31 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <time.h>

// Parser
typedef struct s_args // 8ints + 1ptr = 40bytes 
{
	int				n_coders;
	int				t_burnout;
	int				t_compile;
	int				t_debug;
	int				t_refactor;
	int				n_compiles_req;
	int				dongle_cooldown;
	char			*scheduler;
}	t_args;

int			parse_pos_int(char *arg, char *arg_name);
int			validate_args(char **av);
char		*parse_scheduler(char *arg, char *name);
t_args		parse_args(char **av);

// Hub
typedef struct s_dongle	t_dongle;
typedef struct s_coder	t_coder;

typedef struct s_hub // 2ptr = 16bytes
{
	int		status;
	int		*compile_count;
	double		clock_start;
	t_coder		*coders;
	t_dongle	*dongles;
	t_args		*args;
	pthread_t	monitor;
}	t_hub;

enum e_status
{
	WORKING,
	BURNED_OUT,
	WORK_DONE
};

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	mut;
}	t_dongle;

enum e_dongles
{
	LEFT,
	RIGHT
};

int			create_hub(t_args *args);
t_dongle	*setup_n_dongles(int n_dongles);
t_coder		*recruit_n_coders(t_hub *hub, t_args *args);
int			put_n_coders_to_work(t_hub *hub, int n_coders);
void		free_hub(t_hub *hub);

// Threads
typedef struct s_coder
{
	int			id;
	int			*status;
	int			*compile_count;
	double			last_compile_start;
	double			*clock_start;
	pthread_t	th;
	t_args		*args;
	t_dongle	*l_dongle;
	t_dongle	*r_dongle;
}	t_coder;

void		send_n_coders_home(t_coder *coders, int n);
void		clear_n_dongles(t_dongle *dongles, int n);
void		*monitor(void *hub_ptr);
void		*work(void *args_ptr);
void		*compile(t_coder *coder);
void		*debug(t_coder *coder);
void		*refactor(t_coder *coder);
void		recruit_supervisor(t_hub *hub);

// Time
double		now(void);

#endif
