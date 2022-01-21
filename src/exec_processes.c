/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:41:48 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/21 10:39:22 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*   set file and command   */
static void	set_elements(t_info *info, t_pdata *pdata, int cmd_index)
{
	pdata->file = NULL;
	if (!cmd_index && !(pdata->has_heredoc))
		pdata->file = pdata->argv[1];
	else if (cmd_index == pdata->process_cnt - 1)
		pdata->file = pdata->argv[pdata->argc - 1];
	// pdata->cmd[cmd_index] = \
	// 	ft_split(pdata->argv[info->lead_cmd_index + cmd_index], ' ');
	// if (!(pdata->cmd[cmd_index]))
	// 	exit(free_all(info, pdata, true));
	// convert_to_fullpath_cmd(pdata, cmd_index);
}

static int	wait_all_process(t_info *info, t_pdata *pdata)
{
	int	cmd_index;
	int	wstatus;

	cmd_index = 0;
	while (cmd_index < pdata->process_cnt)
	{
		safe_func(waitpid(info->pid[cmd_index], &wstatus, WUNTRACED), pdata);
		cmd_index++;
	}
	return (wstatus);
}

static void	create_pipe(t_pdata *pdata, int cmd_index)
{
	pdata->pipefd[cmd_index] = (int *)malloc(sizeof(int) * 2);
	if (!pdata->pipefd[cmd_index])
		exit(EXIT_FAILURE);
	if (pipe(pdata->pipefd[cmd_index]) < 0)
		exit(EXIT_FAILURE);
}

/*   execute processes  */
int	exec_processes(t_info *info, t_pdata *pdata)
{
	int	wstatus;
	int	cmd_index;

	cmd_index = 0;
	while (cmd_index < pdata->process_cnt)
	{
		set_elements(info, pdata, cmd_index);
		if (cmd_index < pdata->process_cnt - 1)
			create_pipe(pdata, cmd_index);
		info->pid[cmd_index] = fork();
		if (info->pid[cmd_index] == -1)
			exit(free_all(info, pdata, true));
		else if (info->pid[cmd_index] == 0)
			exec_child(pdata, cmd_index);
		else if (cmd_index)
		{
			safe_func(close(pdata->pipefd[cmd_index - 1][PIPEIN]), pdata);
			safe_func(close(pdata->pipefd[cmd_index - 1][PIPEOUT]), pdata);
		}
		cmd_index++;
	}
	pdata->fullpath_cmd[cmd_index] = NULL;
	wstatus = wait_all_process(info, pdata);
	return (WEXITSTATUS(wstatus));
}
