/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 20:30:21 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/22 08:58:31 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
#define MEMORY_H
#include "define.h"

t_byte      *mem_pos(t_byte *pos);
void        mem_oper(t_mem_op op, t_byte *dst, t_byte *src, uint8_t cnt);
void        read_arg(t_arg *arg, int32_t *buff, t_bool addressing, t_bool far);

#endif 
