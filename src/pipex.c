/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:35:35 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/21 14:51:11 by jkosaka          ###   ########.fr       */
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
}

static void	init_info(t_info *info, t_pdata *pdata, int argc, bool has_heredoc)
{
	info->lead_cmd_index = 2 + has_heredoc;
	info->pid = (pid_t *)malloc(sizeof(pid_t) * pdata->process_cnt);
	if (!info->pid)
		exit(free_all(info, pdata, true));
}

static void	prepare_pipe(t_info *info, t_pdata *pdata)
{
	int	pipe_index;

	pdata->pipefd = (int **)malloc(sizeof(int *) * (pdata->process_cnt));
	if (!pdata->pipefd)
		exit(free_all(info, pdata, true));
	pdata->pipefd[pdata->process_cnt - 1] = NULL;
}

void	pipex(int argc, char **argv, char **envp)
{
	t_info		info;
	t_pdata		pdata;
	int			error_status;

	init_pdata(&pdata, argc, argv, envp);
	init_info(&info, &pdata, argc, pdata.has_heredoc);
	prepare_pipe(&info, &pdata);
	error_status = exec_processes(&info, &pdata);
	free_all(&info, &pdata, false);
	// system("leaks pipex");
	exit(error_status);
}
