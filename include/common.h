/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 22:01:36 by qpeng             #+#    #+#             */
/*   Updated: 2019/08/16 11:59:04 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
// #include "../libft/includes/libft.h"

#define REVERSE_BIT reverseBits
#define PERROR perror_
#define ERROR(s) ({ printf(s); exit(1);})
#define false 0
#define true 1
#define ITERATOR -1
#define INC(num) (++num)
#define ONEBYTE 1

typedef uint8_t t_bool;
typedef uint8_t t_byte;
typedef int32_t t_word;

//lib	
void			perror_(const char *s);
void            *memcpy_(void *dst, const void *src, size_t n);
int             strlen_(char *str);
int             scmp_(char *s1, char *s2);

#endif