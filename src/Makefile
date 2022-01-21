# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 02:42:37 by jkosaka           #+#    #+#              #
#    Updated: 2022/01/21 20:12:40 by jkosaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ../pipex

HEADERFILE := ../includes/pipex.h

SRCS := pipex.c exec_processes.c exec_child.c \
	 close_func.c dup2_func.c get_fullpath_cmd.c \

OBJS := $(SRCS:%.c=%.o)

MAND := main.c

MAND_OBJS := $(MAND:%.c=%.o)

BONUS := main_bonus.c

BNS_OBJS := $(BONUS:%.c=%.o)

LIBUTIL := ../utils/libutil.a

CC := gcc

CFLAGS := -Wall -Wextra -Werror

ifdef WITH_BONUS
OBJS += $(BNS_OBJS)
else
OBJS += $(MAND_OBJS)
endif

$(NAME) : $(OBJS)
	make -C ../utils
	$(CC) $(CFLAGS) $(OBJS) $(LIBUTIL) -o $(NAME)

all : $(NAME)

%.o : %.c $(HEADERFILE)
	$(CC) $(FLAGS) -c $< -o $@

bonus :
	make WITH_BONUS=1

# $(OBJS) $(BNS_OBJS)
# 	make -C ../utils
# 	${CC} ${CFLAGS} ${OBJS} $(BNS_OBJS) ${LIBUTIL} -o ${NAME}

clean :
	make clean -C ../libft
	make clean -C ../utils
	$(RM) $(OBJS) $(MAND_OBJS) $(BNS_OBJS)

fclean : clean
	make fclean -C ../libft
	make fclean -C ../utils
	$(RM) $(NAME)

re : fclean all

empty :

PHONY: fclean clean all re test retest empty
