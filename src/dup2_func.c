/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:04:27 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/17 16:47:53 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	dup2_func(t_pdata *pdata, int filefd, int cmd_index)
{
	if (filefd != NOFILE && cmd_index == 0)
	{
		dup2(filefd, STDIN);
		dup2(pdata->pipefd[cmd_index][PIPEOUT], STDOUT);
	}
	else if (filefd != NOFILE)
	{
		dup2(pdata->pipefd[cmd_index - 1][PIPEIN], STDIN);
		dup2(filefd, STDOUT);
	}
	else
	{
		dup2(pdata->pipefd[cmd_index - 1][PIPEIN], STDIN);
		dup2(pdata->pipefd[cmd_index][PIPEOUT], STDOUT);
	}
}
