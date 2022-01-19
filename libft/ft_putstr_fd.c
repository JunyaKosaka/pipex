/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:11:40 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/20 01:22:10 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	write_fd(char **s, int fd, size_t len)
{
	ssize_t	bytes;

	bytes = write(fd, *s, len);
	*s += len;
	return (bytes);
}

/*  return -1 if fail  */
ssize_t	ft_putstr_fd(char *s, int fd)
{
	size_t	len;
	ssize_t	bytes;

	if (!s)
		return (0);
	len = ft_strlen(s);
	bytes = write_fd(&s, fd, len % INT_MAX);
	if (bytes == -1)
		return (-1);
	len /= INT_MAX;
	while (len--)
	{
		bytes = write_fd(&s, fd, INT_MAX);
		if (bytes == -1)
			return (-1);
	}
	return (bytes);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	s[10][30] = {"012345", "a b c", ""};
// 	int		i = -1;

// 	while (++i < 3)
// 	{
// 		ft_putstr_fd(s[i], 1);
// 		printf("\n");
// 	}
// 	printf("Done\n");
// }
