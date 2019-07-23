# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 18:31:08 by qpeng             #+#    #+#              #
#    Updated: 2019/07/22 09:15:26 by qpeng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = helper.test.c \
		test.c\
		
TEST_SRC = helper.c
FILES = $(addprefix src/, $(SRC))
TEST_FILES = $(addprefix ../src/, $(TEST_SRC))
CUNIT_PATH=/nfs/2018/q/qpeng/.brew/Cellar/cunit/2.1-3/include
TEST_FILES_PATH=../include

test:
	gcc $$(pkg-config --cflags --libs cunit) -I$(CUNIT_PATH) -I$(TEST_FILES_PATH) $(FILES) $(TEST_FILES) 
all: test

