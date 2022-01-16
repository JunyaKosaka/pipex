# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 02:42:37 by jkosaka           #+#    #+#              #
#    Updated: 2022/01/17 03:02:44 by jkosaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ../pipex

HEADERFILE	= ../includes/pipex.h

SRCS		= main.c pipex.c

OBJS		= $(SRCS:%.c=%.o)

LIBUTIL		= ../utils/libutil.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror #-fsanitize=address -g3

$(NAME): $(OBJS)
	make -C ../utils
	${CC} ${CFLAGS} ${OBJS} ${LIBUTIL} -o ${NAME}

all: $(NAME)

%.o : %.c $(HEADERFILE)
	gcc $(FLAGS) -c $< -o $@

bonus : all

clean:
	make clean -C ../libft
	make clean -C ../utils
	$(RM) $(OBJS)

fclean: clean
	make fclean -C ../libft
	make fclean -C ../utils
	$(RM) $(NAME)

re: fclean all

test:
	./test.sh

INPUTFILE=small.txt
CMD1=cat
CMD2=head -n 4
CMD3=tail -n 2

my_test: ${NAME}
	./${NAME} $(INPUTFILE) $(CMD1) "$(CMD2)" "$(CMD3)" file1

original_test:
	< $(INPUTFILE) $(CMD1) | $(CMD2) | $(CMD3) > file2

# test: fclean retest

# heretest: ${NAME}
# 	./${NAME} here_doc aaa cat "head -n 1" file
# 	cat file

# here: fclean heretest

PHONY: fclean clean all re test retest
