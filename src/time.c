/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 17:55:44 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/08/07 19:12:56 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

double	now(void)
{
	struct timespec	tp;
	double		seconds;
	double		nanosec;
	double		time_ms;

	if (clock_gettime(CLOCK_MONOTONIC, &tp) == -1)
	{
		perror("clock_gettime");
		exit(EXIT_FAILURE);
	}
	seconds = tp.tv_sec;
	nanosec = tp.tv_nsec;
	time_ms = seconds * 1000 + nanosec / 1000000;
	return (time_ms);
}
