/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 22:40:32 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/17 17:08:49 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

int	safe_func(int res, t_pdata *data)
{
	if (res == -1)
	{
		free_all(NULL, data, true);
		exit(EXIT_FAILURE);
	}
	return (res);
}
