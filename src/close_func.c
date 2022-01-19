/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:04:27 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/20 01:33:57 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*  safe close function  */
void	close_func(t_pdata *pdata, int filefd, int cmd_index)
{
	if (filefd != NOFILE && cmd_index == 0)
		safe_func(close(pdata->pipefd[cmd_index][PIPEIN]), pdata);
	else if (filefd != NOFILE)
		safe_func(close(pdata->pipefd[cmd_index - 1][PIPEOUT]), pdata);
	else
		safe_func(close(pdata->pipefd[cmd_index - 1][PIPEOUT]), pdata);
	if (filefd != NOFILE)
		safe_func(close(filefd), pdata);
	else
		safe_func(close(pdata->pipefd[cmd_index][PIPEOUT]), pdata);
}
