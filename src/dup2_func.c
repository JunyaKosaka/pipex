/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:04:27 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/20 01:34:21 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*  safe_dup2_func  */
void	dup2_func(t_pdata *pdata, int filefd, int cmd_index)
{
	if (filefd != NOFILE && cmd_index == 0)
	{
		safe_func(dup2(filefd, STDIN), pdata);
		safe_func(dup2(pdata->pipefd[cmd_index][PIPEOUT], STDOUT), pdata);
	}
	else if (filefd != NOFILE)
	{
		safe_func(dup2(pdata->pipefd[cmd_index - 1][PIPEIN], STDIN), pdata);
		safe_func(dup2(filefd, STDOUT), pdata);
	}
	else
	{
		safe_func(dup2(pdata->pipefd[cmd_index - 1][PIPEIN], STDIN), pdata);
		safe_func(dup2(pdata->pipefd[cmd_index][PIPEOUT], STDOUT), pdata);
	}
}
