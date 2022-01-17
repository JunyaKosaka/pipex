/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_full_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:49:01 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/17 17:08:11 by jkosaka          ###   ########.fr       */
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

/*  convert command relative path to full path  */
void	convert_to_cmd_fullpath(t_pdata *pdata, int cmd_index)
{
	char	**all_paths;
	int		env_index;
	int		path_index;

	if (!access(pdata->cmd[cmd_index][0], X_OK))
	{
		pdata->cmd_full_path[cmd_index] = ft_strdup(pdata->cmd[cmd_index][0]);
		return ;
	}
	env_index = get_path_index(pdata);
	if (env_index == -1)
		exit(EXIT_FAILURE);
	all_paths = ft_split(&(pdata->envp[env_index][PATH_PREFIX]), ':');
	if (!all_paths)
		exit(free_all(NULL, pdata, true));
	path_index = 0;
	while (all_paths[path_index])
	{
		char *temp;
		temp = ft_strjoin(all_paths[path_index], "/");
		pdata->cmd_full_path[cmd_index] = ft_strjoin(temp, pdata->cmd[cmd_index][0]);
		free(temp);
		if (!pdata->cmd_full_path[cmd_index])
		{
			free_2d_arr((void **)all_paths);
			exit(free_all(NULL, pdata, true));
		}
		if (!access(pdata->cmd_full_path[cmd_index], X_OK))
		{
			free_2d_arr((void **)all_paths);
			return ;
		}
		free(pdata->cmd_full_path[cmd_index]);
		pdata->cmd_full_path[cmd_index] = NULL;
		path_index++;
	}
	pdata->cmd_full_path[cmd_index] = ft_strdup("");
	free_2d_arr((void **)all_paths);
	ft_putstr_fd("pipex: command not found: ", STDERR);
	ft_putendl_fd(pdata->cmd[cmd_index][0], STDERR);
	//execveで127設定
}
