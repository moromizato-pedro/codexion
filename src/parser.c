/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 20:25:06 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/07/30 20:25:08 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

char	*parse_scheduler(char *arg, char *name)
{
	if (strcmp("fifo", arg) == 0 || strcmp("edf", arg) == 0)
		return (arg);
	printf("Parsing error: \'%s\' = %s, must be 'fifo' or 'edf'.\n", name, arg);
	return ("");
}

int	parse_pos_int(char *arg, char *name)
{
	if (atoi(arg) > 0)
		return (atoi(arg));
	printf("Parsing error: \'%s\' = %s, value must be positive.\n", name, arg);
	return (0);
}

int	validate_args(char **av)
{
	int		errors;
	char	*sch;

	errors = 0;
	errors += !parse_pos_int(av[0], "Number of Coders");
	errors += !parse_pos_int(av[1], "Time to Burnout");
	errors += !parse_pos_int(av[2], "Time to Compile");
	errors += !parse_pos_int(av[3], "Time to Debug");
	errors += !parse_pos_int(av[4], "Time to Refactor");
	errors += !parse_pos_int(av[5], "Num. of Compiles Req.");
	errors += !parse_pos_int(av[6], "Dongle cooldown");
	sch = parse_scheduler(av[7], "Scheduler");
	if (strcmp(sch, "fifo") != 0 && strcmp(sch, "edf") != 0)
		errors += 1;
	if (!errors)
		return (1);
	printf("Error: Failed to parse, exiting program.\n");
	return (0);
}

t_args	parse_args(char **av)
{
	t_args	args;

	args.n_coders = parse_pos_int(av[0], "Number of Coders");
	args.t_burnout = parse_pos_int(av[1], "Time to Burnout");
	args.t_compile = parse_pos_int(av[2], "Time to Compile");
	args.t_debug = parse_pos_int(av[3], "Time to Debug");
	args.t_refactor = parse_pos_int(av[4], "Time to Refactor");
	args.n_compiles_req = parse_pos_int(av[5], "Num. of Compiles Req.");
	args.dongle_cooldown = parse_pos_int(av[6], "Dongle cooldown");
	args.scheduler = parse_scheduler(av[7], "Scheduler");
	return (args);
}
