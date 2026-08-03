/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 16:30:53 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/08/03 21:41:31 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	*work(void *coder_ptr)
{
	t_coder			*coder;
	time_t			start;
	time_t			stop;
	struct timespec	time;
	float			tpassed_nsec;

	get_monotonic_time(&time);
	start = time.tv_nsec;
	sleep(2);
	coder = (t_coder *)coder_ptr;
	printf("%d - %d\n", coder->id, coder->l_dongle->id);
	printf("%d - %d\n", coder->id, coder->r_dongle->id);
	get_monotonic_time(&time);
	stop = time.tv_nsec;
	tpassed_nsec = stop - start;
	printf("Start: %ld\nStop:  %ld\n", start, stop);
	printf("%.2fms has passed since the start of the work\n", tpassed_nsec / 1000000);
	return (NULL);
}

void	*compile(void)
{
	return (NULL);
}

void	*debug(void)
{
	return (NULL);
}

void	*refactor(void)
{
	return (NULL);
}
