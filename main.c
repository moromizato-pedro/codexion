/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 20:24:29 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/07/30 21:39:42 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

int	main(int ac, char **av)
{
	int		required_arguments;
	t_args	args;

	required_arguments = 8;
	if (ac != required_arguments + 1)
	{
		printf("Error: Wrong syntax.\n");
		printf("Usage: make <number_of_coders> <time_to_burnout> "
			"<time_to_compile> <time_to_debug> "
			"<time_to_refactor> "
			"<number_of_compiles_required> "
			"<dongle_cooldown> <scheduler>\n");
		return (0);
	}
	if (!validate_args(av + 1))
	{
		printf("Error: Failed to validate parsed values\n");
		return (0);
	}
	args = parse_args(av + 1);
	args.id = 0;
	if (!create_hub(args))
		printf("Error: Failed to create hub\n");
	return (0);
}
