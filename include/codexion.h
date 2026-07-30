/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedrohe3@student.42porto.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 18:23:24 by pedro             #+#    #+#             */
/*   Updated: 2026/07/30 21:24:11 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>

// Parser
typedef struct s_args // 8ints + 1ptr = 40bytes 
{
	int		n_coders;
	int		t_burnout;
	int		t_compile;
	int		t_debug;
	int		t_refactor;
	int		n_compiles_req;
	int		dongle_cooldown;
	int		id;
	char	*scheduler;
}	t_args;

int		parse_pos_int(char *arg, char *arg_name);
int		validate_args(char **av);
char	*parse_scheduler(char *arg, char *name);
t_args	parse_args(char **av);

// Hub
typedef struct s_hub // 2ptr = 16bytes
{
	pthread_t		*th;
	pthread_mutex_t	*mut;
}	t_hub;

int		create_hub(t_args args);
int		create_n_threads(t_hub hub, t_args args);
int		join_n_threads(t_hub hub, int n_coders);
void	*hub_clear(t_hub hub);

// Threads
int		create_thread(t_hub hub, t_args args, int id);
void	*program(void *args_ptr);
void	*pthread_clear(t_hub hub, int n_threads);

#endif
