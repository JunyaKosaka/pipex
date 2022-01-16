# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/16 17:25:59 by jkosaka           #+#    #+#              #
#    Updated: 2022/01/17 02:45:58 by jkosaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
PIPEX_DIR = ./src

$(NAME) : empty
	make -C $(PIPEX_DIR)

all : $(NAME)

bonus : all

clean :
	make clean -C $(PIPEX_DIR)

fclean :
	make fclean -C $(PIPEX_DIR)

re : fclean all

empty : 

.PHONY: all clean fclean re bonus empty