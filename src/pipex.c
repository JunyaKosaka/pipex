/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:35:35 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/20 03:59:35 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	get_heredoc(t_pdata *pdata, char *limiter)
{
	size_t	len;
	char	*temp;
	char	*new_document;

	pdata->total_doc = ft_strdup("");
	if (!pdata->total_doc)
		exit(error_handler());
	len = ft_strlen(limiter);
	limiter[len] = '\n';
	temp = get_next_line(STDIN);
	while (ft_strncmp(temp, limiter, len + 1))
	{
		new_document = ft_strjoin(pdata->total_doc, temp);
		if (!new_document)
		{
			free_one(&temp);
			exit(free_all(NULL, pdata, true));
		}
		free_one(&(pdata->total_doc));
		free_one(&temp);
		pdata->total_doc = new_document;
		temp = get_next_line(STDIN);
	}
	free_one(&temp);
}

/*  initialize process data  */
static void	init_pdata(t_pdata *pdata, int argc, char **argv, char **envp)
{
	int	process_cnt;

	pdata->argc = argc;
	pdata->envp = envp;
	pdata->has_heredoc = false;
	pdata->total_doc = NULL;
	pdata->fullpath_cmd = NULL;
	pdata->argv = argv;
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		if (argc < MIN_ARGC + 1)
			exit(error_handler());
		pdata->has_heredoc = true;
		get_heredoc(pdata, argv[2]);
	}
	process_cnt = argc - 3 - pdata->has_heredoc;
	pdata->process_cnt = process_cnt;
	pdata->fullpath_cmd = (char **)malloc(sizeof(char *) * (process_cnt + 1));
	if (!pdata->fullpath_cmd)
		exit(free_all(NULL, pdata, true));
	pdata->fullpath_cmd[process_cnt] = NULL;
	pdata->cmd = (char ***)malloc(sizeof(char **) * (process_cnt + 1));
	if (!pdata->cmd)
		exit(free_all(NULL, pdata, true));
	pdata->cmd[process_cnt] = NULL;
}

static void	init_info(t_info *info, t_pdata *pdata, int argc, bool has_heredoc)
{
	info->lead_cmd_index = 2 + has_heredoc;
	info->pid = (pid_t *)malloc(sizeof(pid_t) * pdata->process_cnt);
	if (!info->pid)
		exit(free_all(info, pdata, true));
}

static void	create_pipe(t_info *info, t_pdata *pdata)
{
	int	pipe_index;

	pdata->pipefd = (int **)malloc(sizeof(int *) * (pdata->process_cnt));
	if (!pdata->pipefd)
		exit(free_all(info, pdata, true));
	pdata->pipefd[pdata->process_cnt - 1] = NULL;
	pipe_index = 0;
	while (pipe_index < pdata->process_cnt - 1)
	{
		pdata->pipefd[pipe_index] = (int *)malloc(sizeof(int) * 2);
		if (!pdata->pipefd[pipe_index])
			exit(free_all(info, pdata, true));
		if (pipe(pdata->pipefd[pipe_index]) < 0)
			exit(free_all(info, pdata, true));
		pipe_index++;
	}
}

void	pipex(int argc, char **argv, char **envp)
{
	t_info		info;
	t_pdata		pdata;
	int			error_status;

	init_pdata(&pdata, argc, argv, envp);
	init_info(&info, &pdata, argc, pdata.has_heredoc);
	create_pipe(&info, &pdata);
	error_status = exec_processes(&info, &pdata);
	free_all(&info, &pdata, false);
	exit(error_status);
}
