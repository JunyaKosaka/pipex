# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/16 17:25:59 by jkosaka           #+#    #+#              #
#    Updated: 2022/01/21 20:14:02 by jkosaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

PIPEX_DIR := ./src

$(NAME) : empty
	make -C $(PIPEX_DIR)

all : $(NAME)

bonus : empty
	make bonus -C $(PIPEX_DIR)

clean :
	make clean -C $(PIPEX_DIR)

fclean :
	make fclean -C $(PIPEX_DIR)

re : fclean all

empty :

test:
	./test.sh

INPUTFILE=small.txt
CMD1=cat
CMD2=head -n 4
CMD3=tail -n 2

my_test: $(NAME)
	./$(NAME) $(INPUTFILE) $(CMD1) "$(CMD2)" "$(CMD3)" file1

original_test:
	< $(INPUTFILE) $(CMD1) | $(CMD2) | $(CMD3) > file2

here: $(NAME)
	./$(NAME) here_doc EOS cat "head -n 1" file
	cat file

# here: fclean heretest

.PHONY: all clean fclean re bonus empty
