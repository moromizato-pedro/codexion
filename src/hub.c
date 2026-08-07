/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 20:34:53 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/08/07 19:19:39 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	create_hub(t_args *args)
{
	t_hub	hub;

	hub.args = args;
	hub.status = WORKING;
	hub.compile_count = malloc(sizeof(int) * args->n_coders);
	memset(hub.compile_count, 0, sizeof(int) * args->n_coders);
	hub.dongles = setup_n_dongles(args->n_coders);
	if (!hub.dongles)
	{
		free_hub(&hub);
		printf("Error: Failed to create and initialize dongles structure\n");
		return (0);
	}
	hub.clock_start = now();
	hub.coders = recruit_n_coders(&hub, args);
	if (!hub.coders)
	{
		clear_n_dongles(hub.dongles, args->n_coders);
		free_hub(&hub);
		printf("Error: Failed to create all threads\n");
		return (0);
	}
	recruit_supervisor(&hub);
	send_n_coders_home(hub.coders, args->n_coders);
	pthread_join(hub.monitor, NULL);
	clear_n_dongles(hub.dongles, args->n_coders);
	free_hub(&hub);
	return (1);
}

t_dongle	*setup_n_dongles(int n_dongles)
{
	int			i;
	t_dongle	*dongles;

	dongles = malloc(sizeof(t_dongle) * n_dongles);
	if (!dongles)
		return (NULL);
	i = -1;
	while (++i < n_dongles)
	{
		dongles[i].id = i;
		pthread_mutex_init(&dongles[i].mut, NULL);
	}
	return (dongles);
}

t_coder	*recruit_n_coders(t_hub *hub, t_args *args)
{
	int		i;
	t_coder	*coders;

	coders = malloc(sizeof(t_coder) * args->n_coders);
	if (!coders)
		return (0);
	i = -1;
	while (++i < args->n_coders)
	{
		coders[i].id = i + 1;
		coders[i].status = &hub->status;
		coders[i].compile_count = hub->compile_count;
		coders[i].last_compile_start = now();
		coders[i].clock_start = &hub->clock_start;
		coders[i].args = args;
		coders[i].l_dongle = &hub->dongles[i];
		if (i == args->n_coders - 1)
			coders[i].r_dongle = &hub->dongles[0];
		else
			coders[i].r_dongle = &hub->dongles[i + 1];
		if (pthread_create(&coders[i].th, NULL, work, (void *)&coders[i]) != 0)
		{
			printf("ERROR: Failed creating thread at iteration '%d'\n", i);
			send_n_coders_home(coders, i + 1);
			free(coders);
			return (NULL);
		}
	}
	printf("All coders created\n");
	return (coders);
}

void	free_hub(t_hub *hub)
{
	if (hub->compile_count)
		free(hub->compile_count);
	if (hub->coders)
		free(hub->coders);
	if (hub->dongles)
		free(hub->dongles);
	return ;
}

void	recruit_supervisor(t_hub *hub)
{
	if (pthread_create(&hub->monitor, NULL, monitor, (void *)hub) != 0)
	{
		printf("ERROR: Failed creating monitoring thread\n");
		return ;
	}
}
