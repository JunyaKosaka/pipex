/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:35:35 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/17 20:16:05 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	get_here_doc(t_pdata *pdata, char *limiter)
{
	size_t	len;
	char	*temp;
	char	*new_document;

	pdata->total_doc = ft_strdup("");
	if (!pdata->total_doc)
		exit(error_handler());
	len = ft_strlen(limiter);
	limiter[len] = '\n';
	len++;
	temp = get_next_line(0);
	while (ft_strncmp(temp, limiter, len))
	{
		new_document = ft_strjoin(pdata->total_doc, temp);
		if (!new_document)
		{
			free_one(&temp);
			exit(free_all(NULL, pdata, true));
		}
		free(pdata->total_doc);
		free(temp);
		pdata->total_doc = new_document;
		temp = get_next_line(0);
	}
	free(temp);
}

static void	init_pdata(t_pdata *pdata, int argc, char **argv, char **envp)
{
	size_t	process_cnt;

	pdata->argc = argc;
	pdata->envp = envp;
	pdata->has_heredoc = false;
	pdata->total_doc = NULL;
	pdata->cmd_fullpath = NULL;
	pdata->argv = argv;
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		if (argc < MIN_ARGC + 1)
			exit(error_handler());
		pdata->has_heredoc = true;
		get_here_doc(pdata, argv[2]);
	}
	process_cnt = argc - 3 - pdata->has_heredoc;
	pdata->process_cnt = process_cnt;
	pdata->cmd_fullpath = (char **)malloc(sizeof(char *) * (process_cnt + 1));
	if (!pdata->cmd_fullpath)
		exit(free_all(NULL, pdata, true));
	pdata->cmd_fullpath[process_cnt] = NULL;
	pdata->cmd = (char ***)malloc(sizeof(char *) * (process_cnt + 1));
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
	size_t	pipe_index;

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
	// system("leaks -q pipex");
	exit(error_status);
}
