/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:04:27 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/21 14:23:03 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*  safe_dup2_func  */
void	dup2_func(t_pdata *pdata, int filefd, int cmd_index)
{
	if (filefd != NOFILE && cmd_index == 0)
	{
		safe_func(dup2(filefd, STDIN));
		safe_func(dup2(pdata->pipefd[cmd_index][PIPEOUT], STDOUT));
	}
	else if (filefd != NOFILE)
	{
		safe_func(dup2(pdata->pipefd[cmd_index - 1][PIPEIN], STDIN));
		safe_func(dup2(filefd, STDOUT));
	}
	else
	{
		safe_func(dup2(pdata->pipefd[cmd_index - 1][PIPEIN], STDIN));
		safe_func(dup2(pdata->pipefd[cmd_index][PIPEOUT], STDOUT));
	}
}
