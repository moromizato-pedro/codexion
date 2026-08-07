/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 20:24:19 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/08/07 19:21:15 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	send_n_coders_home(t_coder *coders, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		pthread_join(coders[i].th, NULL);
}

void	clear_n_dongles(t_dongle *dongles, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		pthread_mutex_destroy(&dongles[i].mut);
}

void	*monitor(void *hub_ptr)
{
	t_hub	*hub;
	int	i;
	int	compiles_req;
	int	compiles_missing;
	double	start;
	double	passed;

	hub = (t_hub *)hub_ptr;
	compiles_req = hub->args->n_compiles_req;
	printf("Start monitoring...\n");
	while (hub->status == WORKING)
	{
		compiles_missing = 0;
		i = -1;
		while (++i < hub->args->n_coders)
		{
			start = now();
			passed = start - hub->coders[i].last_compile_start;
			if (passed > hub->args->t_burnout)
			{
				printf("%.0f %d burned out\n", start - hub->clock_start, hub->coders[i].id);
				printf("Coder[%d]: (passed)%.0f > %d(t_burnout)? %d\n", i, passed, hub->args->t_burnout, passed > hub->args->t_burnout);
				hub->status = BURNED_OUT;
			}
			if (hub->compile_count[i] < compiles_req)
				compiles_missing += 1;
		}
		if (compiles_missing == 0)
		{
			hub->status = WORK_DONE;
			printf("All threads achieved at least %d compiles!\n", compiles_req);
		}
		usleep(500);
		//printf("End of monitoring cycle...\n");
	}
	return (NULL);
}
