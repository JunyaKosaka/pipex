/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:04:27 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/17 20:01:29 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_func(t_pdata *pdata, int filefd, int cmd_index)
{
	if (filefd != NOFILE && cmd_index == 0)
		close(pdata->pipefd[cmd_index][PIPEIN]);
	else if (filefd != NOFILE)
		close(pdata->pipefd[cmd_index - 1][PIPEOUT]);
	else
		close(pdata->pipefd[cmd_index - 1][PIPEOUT]);
	if (filefd != NOFILE)
		close(filefd);
	else
		close(pdata->pipefd[cmd_index][PIPEOUT]);
}
