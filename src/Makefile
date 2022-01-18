# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 02:42:37 by jkosaka           #+#    #+#              #
#    Updated: 2022/01/18 21:49:09 by jkosaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ../pipex

HEADERFILE := ../includes/pipex.h

SRCS := main.c pipex.c exec_processes.c exec_child.c \
	 close_func.c dup2_func.c fullpath_cmd.c \

OBJS := $(SRCS:%.c=%.o)

LIBUTIL := ../utils/libutil.a

CC := gcc

CFLAGS := -Wall -Wextra -Werror #-fsanitize=address -g3

$(NAME) : $(OBJS)
	make -C ../utils
	${CC} ${CFLAGS} ${OBJS} ${LIBUTIL} -o ${NAME}

all : $(NAME)

%.o : %.c $(HEADERFILE)
	gcc $(FLAGS) -c $< -o $@

bonus : all

clean :
	make clean -C ../libft
	make clean -C ../utils
	$(RM) $(OBJS)

fclean : clean
	make fclean -C ../libft
	make fclean -C ../utils
	$(RM) $(NAME)

re: fclean all

PHONY: fclean clean all re test retest
