# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/16 23:19:51 by qpeng             #+#    #+#              #
#    Updated: 2019/08/01 19:07:55 by qpeng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = champion.c\
		handler.c\
		helper.c\
		lib.c\
		loader.c\
		main.c\
		memory.c\
		op.c\
		process.c\
		corewar.c

FILES = $(addprefix src/, $(SRC))

all:
	gcc -g -Iinclude -fsanitize=address $(FILES)

test:
	gcc -g -Iinclude -Wall -Werror -Wextra -fsanitize=address FILES tests/libunity.a