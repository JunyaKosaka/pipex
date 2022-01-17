/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 22:28:55 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/17 13:36:34 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include "../libft/libft.h"

# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <malloc/malloc.h> // delete

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define PIPEIN 0
# define PIPEOUT 1
# define NOFILE -2
# define FD_MAX 256
# define PATH_PREFIX 5
# define MIN_ARGC 5

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

/*   process data   */
typedef struct s_pdata
{
	size_t	process_cnt;
	int		**pipefd;
	int		argc;
	char	**envp;
	char	**cmd_full_path;
	char	***cmd;
	char	*file;
	char	*total_doc;
	char	**argv;
	bool	has_heredoc;
}	t_pdata;

/*   information   */
typedef struct	s_info
{   
	int		lead_cmd_index;
	pid_t	*pid;
}	t_info;

int		error_handler(void);
char	*get_next_line(int fd);
int		free_all(t_info *info, t_pdata *pdata, bool is_error);
void	free_2d_arr(void **arr);
void	*free_one(char **s);
void	*free_two(char **s1, char **s2);

#endif  // UTILS_H
