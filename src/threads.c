/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 20:24:19 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/11/09 18:49:35 by pedrohe3         ###   ########.fr       */
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
	int	coders_missing;
	int	should_continue;
	double	passed;

	hub = (t_hub *)hub_ptr;
	compiles_req = hub->args->n_compiles_req;
	protected_log(hub, "Start monitoring...\n");
	while (1)
	{
		pthread_mutex_lock(&hub->status_mut);
		should_continue = (hub->status == CONFIGURING);
		pthread_mutex_unlock(&hub->status_mut);
		if (should_continue)
			break ;
		usleep(500);
		continue ;
	}
	protected_log(hub, "Monitor start working\n");
	pthread_mutex_lock(&hub->status_mut);
	hub->status = WORKING;
	pthread_mutex_unlock(&hub->status_mut);
	while (1)
	{
		pthread_mutex_lock(&hub->status_mut);
		should_continue = (hub->status == WORKING);
		pthread_mutex_unlock(&hub->status_mut);
		if (!should_continue)
			break ;
		coders_missing = hub->args->n_coders;
		i = -1;
		while (++i < hub->args->n_coders)
		{
			passed = now() - hub->coders[i].last_compile_start;
			if (passed > hub->args->t_burnout)
			{
				protected_log(hub, "%.0f %d burned out\n", now() - hub->clock_start, hub->coders[i].id);
				protected_log(hub, "		Coder[%d]: (passed)%.0f > %d(t_burnout)? %d\n", i, passed, hub->args->t_burnout, passed > hub->args->t_burnout);
				protected_log(hub, "		%.0f\n		%.0f\n", now(), hub->coders[i].last_compile_start);
				pthread_mutex_lock(&hub->status_mut);
				hub->status = BURNED_OUT;
				pthread_mutex_unlock(&hub->status_mut);
			}
			if (hub->compile_count[i] >= compiles_req)
				coders_missing -= 1;
		}
		//printf("		Coders missing: %d\n", coders_missing);
		if (coders_missing == 0)
		{
			pthread_mutex_lock(&hub->status_mut);
			hub->status = WORK_DONE;
			pthread_mutex_unlock(&hub->status_mut);
			protected_log(hub, "All coders achieved at least %d compiles!\n", compiles_req);
		}
		usleep(500);
	}
	protected_log(hub, "End of monitoring...\n");
	return (NULL);
}
