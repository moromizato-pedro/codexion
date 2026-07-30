/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 20:24:19 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/07/30 21:20:36 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	create_thread(t_hub hub, t_args args, int id)
{
	t_args	*args_cpy;

	args_cpy = malloc(sizeof(t_args));
	if (!args_cpy)
		return (0);
	*args_cpy = args;
	args_cpy->id = id;
	printf("Args.id = %d | n_coders = %d\n", args_cpy->id, args.n_coders);
	if (pthread_create(&hub.th[id], NULL, program, args_cpy) != 0)
	{
		perror("Failed to create thread");
		free(args_cpy);
		return (0);
	}
	return (1);
}

void	*program(void *args_ptr)
{
	t_args	*args;

	sleep(1);
	args = (t_args *)args_ptr;
	for (int i = 0; i < 2; i++)
	{
		printf("%d - %d\n", (*args).id, i);
	}
	free(args_ptr);
	return (NULL);
}

void	*pthread_clear(t_hub hub, int n_mutexes)
{
	int	i;

	i = -1;
	while (++i < n_mutexes)
	{
		pthread_mutex_destroy(&hub.mut[i]);
	}
	return (NULL);
}
