# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/16 23:19:51 by qpeng             #+#    #+#              #
#    Updated: 2019/07/02 17:34:42 by qpeng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


all:
	gcc -g -fsanitize=address *.c 