/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fullpath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:49:01 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/17 20:01:29 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

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
	return (-1);
}

static void	free_char(char **str)
{
	if (str && (*str))
	{
		free(*str);
		*str = NULL;
	}
}

static void	conv_fullpath_sub(t_pdata *pdata, int cmd_i, char ***all_paths)
{
	int		path_index;
	char	*temp;

	path_index = -1;
	while ((*all_paths)[++path_index])
	{
		temp = ft_strjoin((*all_paths)[path_index], "/");
		pdata->cmd_fullpath[cmd_i] = ft_strjoin(temp, pdata->cmd[cmd_i][0]);
		free_char(&temp);
		if (!(pdata->cmd_fullpath[cmd_i]))
		{
			free_2d_arr((void **)(*all_paths));
			exit(free_all(NULL, pdata, true));
		}
		if (!access(pdata->cmd_fullpath[cmd_i], X_OK))
		{
			free_2d_arr((void **)(*all_paths));
			return ;
		}
		free_char(&(pdata->cmd_fullpath[cmd_i]));
	}
	pdata->cmd_fullpath[cmd_i] = ft_strdup("");
	free_2d_arr((void **)(*all_paths));
	ft_putstr_fd("pipex: command not found: ", STDERR);
	ft_putendl_fd(pdata->cmd[cmd_i][0], STDERR);
}

/*   convert command relative path to full path  */
void	convert_to_cmd_fullpath(t_pdata *pdata, int cmd_index)
{
	char	**all_paths;
	int		env_index;

	if (!access(pdata->cmd[cmd_index][0], X_OK))
	{
		pdata->cmd_fullpath[cmd_index] = ft_strdup(pdata->cmd[cmd_index][0]);
		return ;
	}
	env_index = get_path_index(pdata);
	if (env_index == -1)
		exit(EXIT_FAILURE);
	all_paths = ft_split(&(pdata->envp[env_index][PATH_PREFIX]), ':');
	if (!all_paths)
		exit(free_all(NULL, pdata, true));
	conv_fullpath_sub(pdata, cmd_index, &all_paths);
}
