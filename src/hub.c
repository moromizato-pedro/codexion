/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 20:34:53 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/08/03 23:25:26 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	create_hub(t_args *args)
{
	t_hub	hub;

	hub.dongles = setup_n_dongles(args->n_coders);
	if (!hub.dongles)
	{
		free_hub(&hub);
		printf("Error: Failed to create and initialize dongles structure\n");
		return (0);
	}
	hub.coders = recruit_n_coders(&hub, args);
	if (!hub.coders)
	{
		clear_n_dongles(hub.dongles, args->n_coders);
		free_hub(&hub);
		printf("Error: Failed to create all threads\n");
		return (0);
	}
	clear_n_dongles(hub.dongles, args->n_coders);
	send_n_coders_home(hub.coders, args->n_coders);
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
		coders[i].id = i;
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
	return (coders);
}

void	free_hub(t_hub *hub)
{
	if (hub->coders)
		free(hub->coders);
	if (hub->dongles)
		free(hub->dongles);
	return ;
}
