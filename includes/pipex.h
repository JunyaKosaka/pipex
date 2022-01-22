/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:25:33 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/22 14:08:58 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./utils.h"

void	pipex(int argc, char **argv, char **envp);
int		exec_processes(t_info *info, t_pdata *pdata);
void	exec_child(t_pdata *pdata, const int cmd_index);
void	close_func(t_pdata *pdata, const int filefd, const int cmd_index);
void	dup2_func(t_pdata *pdata, const int filefd, const int cmd_index);
char	*get_fullpath_cmd(t_pdata *pdata, char **cmd);

#endif  // PIPEX_H
