# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/17 02:47:05 by jkosaka           #+#    #+#              #
#    Updated: 2022/01/21 20:13:22 by jkosaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libutil.a

HEADERFILE := ../includes/utils.h

SRCS := error_handler.c get_next_line.c get_next_line_utils.c \
	free.c safe_func.c \

OBJS := $(SRCS:%.c=%.o)

FLAGS := -Wall -Wextra -Werror

$(NAME) : $(OBJS)
	make $(FLAGS) -C ../libft
	cp ../libft/libft.a $(NAME)
	ar rc $@ $^

all	: $(NAME)

%.o : %.c $(HEADERFILE)
	gcc $(FLAGS) -c $< -o $@

clean :
	make clean -C ../libft
	$(RM) -f $(OBJS)

fclean : clean
	make fclean -C ../libft
	$(RM) -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
