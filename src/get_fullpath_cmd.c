/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fullpath_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:42:16 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/21 15:12:49 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*  exit if path not found  */
static	int	get_path_index(t_pdata *pdata)
{
	int	index;

	index = 0;
	while (pdata->envp[index])
	{
		if (!ft_strncmp(pdata->envp[index], "PATH=", PATH_PREFIX))
			return (index);
		index++;
	}
	exit(EXIT_FAILURE);
}

static void	free_char(char **str)
{
	if (str && (*str))
	{
		free(*str);
		*str = NULL;
	}
}

static char	*get_fullcmd_core(t_pdata *pdata, char **cmd, char **all_paths)
{
	int		path_index;
	char	*fullcmd;
	char	*temp;

	path_index = -1;
	while (all_paths[++path_index])
	{
		temp = ft_strjoin(all_paths[path_index], "/");
		fullcmd = ft_strjoin(temp, cmd[0]);
		free_char(&temp);
		if (!(fullcmd))
			exit(EXIT_FAILURE);
		if (!(access(fullcmd, X_OK)))
			return (fullcmd);
		free_char(&fullcmd);
	}
	safe_func(ft_putstr_fd("pipex: command not found: ", STDERR));
	printf("58\n");
	safe_func(ft_putendl_fd(cmd[0], STDERR));
	printf("60\n");
	return (NULL);
	// exit(NOCMD);
}

/*  return (NULL) if fail  */
char	*get_fullpath_cmd(t_pdata *pdata, char **cmd, int cmd_index)
{
	char	**all_paths;
	int		env_index;

	if (!cmd || !(*cmd))
		exit(EXIT_FAILURE);
	if (!access(cmd[0], X_OK))
		return (cmd[0]);
	env_index = get_path_index(pdata);
	all_paths = ft_split(&(pdata->envp[env_index][PATH_PREFIX]), ':');
	if (!all_paths)
		exit(EXIT_FAILURE);
	return (get_fullcmd_core(pdata, cmd, all_paths));
}
