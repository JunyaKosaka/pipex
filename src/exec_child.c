/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:02:25 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/21 15:10:54 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static bool	is_valid_file(t_pdata *data)
{
	return (access(data->argv[1], R_OK) == 0);
}

/*  return -1 if open func fails  */
static int	get_filefd(t_pdata *pdata, int cmd_index)
{
	int	fd;

	if (pdata->file && cmd_index == 0)
	{
		if (!is_valid_file(pdata))
		{
			perror(pdata->argv[1]);
			exit(EXIT_FAILURE);
		}
		fd = open(pdata->file, R_OK);
	}
	else if (pdata->file)
	{
		if (pdata->has_heredoc)
			fd = open(pdata->file, O_CREAT | O_APPEND | W_OK, 0644);
		else
			fd = open(pdata->file, O_CREAT | O_TRUNC | W_OK, 0644);
	}
	else
		fd = NOFILE;
	return (fd);
}

/*  execute first child process having heredoc  */
static void	exec_child_heredoc(t_pdata *pdata)
{
	size_t	total_len;

	total_len = ft_strlen(pdata->total_doc);
	safe_func(close(pdata->pipefd[0][PIPEIN]));
	safe_func(ft_putstr_fd(pdata->total_doc, pdata->pipefd[0][PIPEOUT]));
	safe_func(close(pdata->pipefd[0][PIPEOUT]));
	exit(EXIT_SUCCESS);
}

static char	**get_cmd(t_pdata *pdata, int cmd_index)
{
	int		cmd_arg_index;
	char	**cmd;

	cmd_arg_index = 2 + pdata->has_heredoc + cmd_index;
	cmd = ft_split(pdata->argv[cmd_arg_index], ' ');
	if (!cmd)
		exit(EXIT_FAILURE);
	return (cmd);
}

/*  execute child process  */
void	exec_child(t_pdata *pdata, int cmd_index)
{
	int		filefd;
	char	**cmd;
	char	*fullpath_cmd;
	
	if (pdata->has_heredoc && cmd_index == 0)
		exec_child_heredoc(pdata);
	filefd = get_filefd(pdata, cmd_index);
	if (filefd == -1)
	{
		perror(pdata->file);
		exit(EXIT_FAILURE);
	}
	cmd = get_cmd(pdata, cmd_index);
	fullpath_cmd = get_fullpath_cmd(pdata, cmd, cmd_index);
	if (!fullpath_cmd)
		exit(NOCMD);
	dup2_func(pdata, filefd, cmd_index);
	close_func(pdata, filefd, cmd_index);
	execve(fullpath_cmd, cmd, pdata->envp);
	exit(NOCMD);
}
