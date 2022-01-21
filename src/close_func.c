/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:04:27 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/21 14:25:09 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*  safe close function  */
void	close_func(t_pdata *pdata, int filefd, int cmd_index)
{
	if (filefd != NOFILE && cmd_index == 0)
		safe_func(close(pdata->pipefd[cmd_index][PIPEIN]));
	else if (filefd != NOFILE)
		safe_func(close(pdata->pipefd[cmd_index - 1][PIPEOUT]));
	else
		safe_func(close(pdata->pipefd[cmd_index - 1][PIPEOUT]));
	if (filefd != NOFILE)
		safe_func(close(filefd));
	else
		safe_func(close(pdata->pipefd[cmd_index][PIPEOUT]));
}
