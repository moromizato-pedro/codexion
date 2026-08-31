/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 16:30:53 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/08/31 19:04:23 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	*work(void *coder_ptr)
{
	t_coder			*coder;
	double			start;
	double			stop;
	double			tpassed_msec;
	int			should_continue;

	coder = (t_coder *)coder_ptr;
	while (1)
	{
		pthread_mutex_lock(&coder->hub->status_mut);
		should_continue = (coder->hub->status != WAITING);
		pthread_mutex_unlock(&coder->hub->status_mut);
		if (should_continue)
			break ;
		usleep(500);
		continue ;
	}
	printf("Starting coder %d work\n", coder->id);
	while (1)
	{
		pthread_mutex_lock(&coder->hub->status_mut);
		should_continue = (coder->hub->status == WORKING);
		pthread_mutex_unlock(&coder->hub->status_mut);
		if (!should_continue)
			break ;
		start = now();
		if (compile(coder))
		{
			stop = now();
			tpassed_msec = stop - start;
			//printf("%d Start: %.2f | Stop:  %.2f\n", coder->id, start, stop);
			protected_log(coder->hub, "%.0f %d %.0fms has passed since the start of the work\n", now() - *coder->clock_start, coder->id, tpassed_msec/* / 1000000*/);
		}
		usleep(500);
	}
	printf("Coder %d stopped working\n", coder->id);
	return (NULL);
}

int	compile(t_coder *coder)
{
	double			start;
	double			stop;
	double			tpassed_msec;
	
	//printf("Start: 		%.0f\n", start);
	//printf("Clock_start:	%.0f\n", *coder->clock_start);
	if (!try_lock_dongles(coder))
		return (0);
	protected_log(coder->hub, "%.0f %d is compiling\n", now() - *coder->clock_start, coder->id);
	start = now();
	coder->last_compile_start = start;
	usleep(coder->args->t_compile * 1000);
	stop = now();
	tpassed_msec = stop - start;
	//printf("%d Start: %.2f | Stop:  %.2f\n", coder->id, start, stop);
	protected_log(coder->hub, "%.0f %d %.0fms has passed since the start of compiling\n", now() - *coder->clock_start, coder->id, tpassed_msec);
	coder->compile_count[coder->id - 1] += 1;
	pthread_mutex_unlock(&coder->l_dongle->mut);
	pthread_mutex_unlock(&coder->r_dongle->mut);
	debug(coder);
	return (1);
}

void	*debug(t_coder *coder)
{
	double			start;
	double			stop;
	double			tpassed_msec;
	
	start = now();
	protected_log(coder->hub, "%.0f %d is debugging\n", now() - *coder->clock_start, coder->id);
	usleep(coder->args->t_debug * 1000);
	stop = now();
	tpassed_msec = stop - start;
	//printf("%d Start: %.2f | Stop:  %.2f\n", coder->id, start, stop);
	protected_log(coder->hub, "%.0f %d %.0fms has passed since the start of debugging\n", now() - *coder->clock_start, coder->id, tpassed_msec);
	refactor(coder);
	return (NULL);
}

void	*refactor(t_coder *coder)
{
	double			start;
	double			stop;
	double			tpassed_msec;
	
	start = now();
	protected_log(coder->hub, "%.0f %d is refactoring\n", now() - *coder->clock_start, coder->id);
	usleep(coder->args->t_refactor * 1000);
	stop = now();
	tpassed_msec = stop - start;
	//printf("%d Start: %.2f | Stop:  %.2f\n", coder->id, start, stop);
	protected_log(coder->hub, "%.0f %d %.0fms has passed since the start of refactoring\n", now() - *coder->clock_start, coder->id, tpassed_msec);
	return (NULL);
}

int	try_lock_dongles(t_coder *coder)
{
	int	l_locked;
	int	r_locked;

	l_locked = 0;
	r_locked = 0;
	if (pthread_mutex_trylock(&coder->l_dongle->mut) == 0)
	{
		l_locked = 1;
		protected_log(coder->hub, "%.0f %d has taken a dongle (%d)\n", now() - *coder->clock_start, coder->id, coder->l_dongle->id);
	}
	if (pthread_mutex_trylock(&coder->r_dongle->mut) == 0)
	{
		r_locked = 1;
		protected_log(coder->hub, "%.0f %d has taken a dongle (%d)\n", now() - *coder->clock_start, coder->id, coder->r_dongle->id);
	}
	if (!l_locked || !r_locked)
	{
		if (l_locked)
			pthread_mutex_unlock(&coder->l_dongle->mut);
		if (r_locked)
			pthread_mutex_unlock(&coder->r_dongle->mut);
		return (0);
	}
	return (1);
}
