/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 17:55:44 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/07/31 17:58:49 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	get_monotonic_time(struct timespec *tp)
{
	if (clock_gettime(CLOCK_MONOTONIC, tp) == -1)
	{
		perror("clock_gettime");
		exit(EXIT_FAILURE);
	}
	return (1);
}
