/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 17:39:01 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/08/28 17:44:04 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	protected_log(t_hub *hub, const char *format, ...)
{
	va_list	args;

	pthread_mutex_lock(&hub->log_mut);
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	pthread_mutex_unlock(&hub->log_mut);
}
