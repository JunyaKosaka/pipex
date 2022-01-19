/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 00:07:23 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/20 02:49:15 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*  return -1 if fail  */
ssize_t	ft_putendl_fd(char *s, int fd)
{
	ssize_t	bytes;
	ssize_t	bytes2;

	bytes = ft_putstr_fd(s, fd);
	if (bytes == -1)
		return (bytes);
	bytes2 = write(fd, "\n", fd);
	if (bytes2 == -1)
		return (bytes2);
	return (bytes + bytes2);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	s[10][30] = {"012345", "a b c", ""};
// 	int		i = -1;

// 	while (++i < 3)
// 		ft_putendl_fd(s[i], 1);
// 	printf("Done\n");
// }
