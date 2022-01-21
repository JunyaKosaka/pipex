/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 22:40:32 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/21 14:05:52 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

ssize_t	safe_func(ssize_t res)
{
	if (res == -1)
		exit(EXIT_FAILURE);
	return (res);
}
