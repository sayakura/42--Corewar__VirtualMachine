# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/16 23:19:51 by qpeng             #+#    #+#              #
#    Updated: 2019/08/02 12:33:24 by anjansse         ###   ########.fr        #
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
		corewar.c \
		graphic.c\

FILES = $(addprefix src/, $(SRC))

GRAPHIC_LIB = -lncurses

all:
	gcc -g -Iinclude $(GRAPHIC_LIB) -fsanitize=address $(FILES)

test:
	gcc -g -Iinclude -Wall -Werror -Wextra -fsanitize=address $(FILES) tests/libunity.a