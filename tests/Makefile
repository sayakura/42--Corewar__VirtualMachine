# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 18:31:08 by qpeng             #+#    #+#              #
#    Updated: 2019/07/17 20:10:39 by qpeng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = champion.c\
		handler.c\
		helper.c\
		lib.c\
		loader.c\
		memory.c\
		op.c\
		process.c
FILES = $(addprefix src/, $(SRC))

CUNIT_PATH=/nfs/2018/q/qpeng/.brew/Cellar/cunit/2.1-3/include

test:
	gcc $$(pkg-config --cflags --libs cunit) -I$(CUNIT_PATH) test.c $(FILES)
all: test

