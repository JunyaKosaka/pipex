/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:25:33 by jkosaka           #+#    #+#             */
/*   Updated: 2022/01/18 21:48:40 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./utils.h"

void	pipex(int argc, char **argv, char **envp);
int		exec_processes(t_info *info, t_pdata *pdata);
void	exec_child(t_pdata *pdata, int cmd_index);
void	close_func(t_pdata *pdata, int filefd, int cmd_index);
void	dup2_func(t_pdata *pdata, int filefd, int cmd_index);
void	convert_to_fullpath_cmd(t_pdata *pdata, int cmd_index);

#endif  // PIPEX_H
