/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 16:30:53 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/08/07 19:55:32 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	*work(void *coder_ptr)
{
	t_coder			*coder;
	double			start;
	double			stop;
	double			tpassed_msec;

	coder = (t_coder *)coder_ptr;
	while (*coder->status == WORKING)
	{
		start = now();
		compile(coder);
		stop = now();
		tpassed_msec = stop - start;
		//printf("%d Start: %.2f | Stop:  %.2f\n", coder->id, start, stop);
		printf("%.0fms has passed since the start of the work\n", tpassed_msec/* / 1000000*/);
	}
	return (NULL);
}

void	*compile(t_coder *coder)
{
	double			start;
	double			stop;
	double			tpassed_msec;
	
	start = now();
	coder->last_compile_start = start;
	printf("Start: 		%.0f\n", start);
	printf("Clock_start:	%.0f\n", *coder->clock_start);
	printf("%.0f %d has taken a dongle (%d)\n", start - *coder->clock_start, coder->id, coder->l_dongle->id);
	printf("%.0f %d has taken a dongle (%d)\n", now() - *coder->clock_start, coder->id, coder->r_dongle->id);
	printf("%.0f %d is compiling\n", start - *coder->clock_start, coder->id);
	usleep(coder->args->t_compile * 1000);
	stop = now();
	tpassed_msec = stop - start;
	//printf("%d Start: %.2f | Stop:  %.2f\n", coder->id, start, stop);
	printf("	%d %.0fms has passed since the start of compiling\n", coder->id, tpassed_msec);
	coder->compile_count[coder->id - 1] += 1;
	debug(coder);
	return (NULL);
}

void	*debug(t_coder *coder)
{
	double			start;
	double			stop;
	double			tpassed_msec;
	
	start = now();
	printf("%.0f %d is debugging\n", start - *coder->clock_start, coder->id);
	usleep(coder->args->t_debug * 1000);
	stop = now();
	tpassed_msec = stop - start;
	//printf("%d Start: %.2f | Stop:  %.2f\n", coder->id, start, stop);
	printf("	%d %.0fms has passed since the start of debugging\n", coder->id, tpassed_msec);
	refactor(coder);
	return (NULL);
}

void	*refactor(t_coder *coder)
{
	double			start;
	double			stop;
	double			tpassed_msec;
	
	start = now();
	printf("%.0f %d is refactoring\n", start - *coder->clock_start, coder->id);
	usleep(coder->args->t_refactor * 1000);
	stop = now();
	tpassed_msec = stop - start;
	//printf("%d Start: %.2f | Stop:  %.2f\n", coder->id, start, stop);
	printf("	%d %.0fms has passed since the start of refactoring\n", coder->id, tpassed_msec);
	return (NULL);
}
