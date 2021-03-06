/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 22:40:32 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/21 14:49:05 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	free_2d_arr(void ***arr)
{
	int	i;

	if (!arr || !(*arr))
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free((*arr)[i]);
	(*arr)[i] = NULL;
	if (arr && *arr)
	{
		free(*arr);
		*arr = NULL;
	}
}

static void	free_info(t_info *info)
{
	if (!info)
		return ;
	if (info->pid)
	{
		free(info->pid);
		info->pid = NULL;
	}
}

static void	free_pdata(t_pdata *pdata)
{
	if (!pdata)
		return ;
	free_2d_arr((void ***)&(pdata->pipefd));
	free(pdata->total_doc);
	pdata->total_doc = NULL;
}

int	free_all(t_info *info, t_pdata *pdata, bool is_error)
{
	if (info)
		free_info(info);
	if (pdata)
		free_pdata(pdata);
	if (is_error)
		return (error_handler());
	return (0);
}
