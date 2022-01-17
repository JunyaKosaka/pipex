/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:25:51 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/17 23:26:14 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

__attribute__((destructor))
void	destructor(void)
{
	int	status;

	status = system("leaks pipex &> leaksout");
	if (status)
	{
		write(2, "leak!!!\n", 8);
		system("cat leaksout >/dev/stderr");
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < MIN_ARGC)
		exit(error_handler());
	pipex(argc, argv, envp);
	return (0);
}
