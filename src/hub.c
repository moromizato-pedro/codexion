/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 20:34:53 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/07/30 21:19:27 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	create_hub(t_args args)
{
	t_hub	hub;

	hub.th = malloc(sizeof(pthread_t) * args.n_coders);
	hub.mut = malloc(sizeof(pthread_mutex_t) * (args.n_coders));
	if (!hub.mut || !hub.th)
	{
		hub_clear(hub);
		return (0);
	}
	if (!create_n_threads(hub, args))
	{
		hub_clear(hub);
		printf("Error: Failed to create threads\n");
		return (0);
	}
	if (!join_n_threads(hub, args.n_coders))
	{
		hub_clear(hub);
		printf("Error: Failed to join the threads\n");
		return (0);
	}
	pthread_clear(hub, args.n_coders);
	hub_clear(hub);
	return (1);
}

int	create_n_threads(t_hub hub, t_args args)
{
	int	i;

	i = -1;
	while (++i < args.n_coders)
	{
		pthread_mutex_init(&hub.mut[i], NULL);
		if (!create_thread(hub, args, i))
		{
			printf("ERROR: Failed creating thread at iteration '%d'\n", i);
			pthread_clear(hub, i);
			return (0);
		}
	}
	return (1);
}

int	join_n_threads(t_hub hub, int n_coders)
{
	int	i;

	i = -1;
	while (++i < n_coders)
	{
		if (pthread_join(hub.th[i], NULL) != 0)
		{
			pthread_clear(hub, n_coders);
			return (0);
		}
	}
	return (1);
}

void	*hub_clear(t_hub hub)
{
	if (hub.th)
		free(hub.th);
	if (hub.mut)
		free(hub.mut);
	return (NULL);
}
