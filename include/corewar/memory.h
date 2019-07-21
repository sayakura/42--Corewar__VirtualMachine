/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 20:30:21 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/19 23:11:29 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
#define MEMORY_H

#include "corewar/process.h"

# define MAP_START g_base
# define MAP_END g_base + MEM_SIZE
#define FOR_EACH(item, array) typeof(*(array)) *start = array;\
                            typeof(*(array)) *end = (start + (sizeof(array) / sizeof*(array)) + 1);\
                            typeof(*(array)) *item;\
                            while ((item = start) && start++ != end )
# define READ_FROM_MEM(a, b, c, d) mem_oper(READ, (t_byte *)b, a, c); if (d) h_rev_bytes(b, c);
# define WRITE_TO_MEM(a, b, c, d) if(d == LITTLE_E)h_rev_bytes(a, c); mem_oper(WRITE, (t_byte *)a, (t_byte *)b, c); ;
# define READ_(i, b, c)  READ_FROM_MEM(i, b, c, BIG_E);
# define WRITE_(i, b, c)  WRITE_TO_MEM(i, b, c, LITTLE_E);
# define MEM_POX(a) mem_pos(a)
# define REL(pc, offset) MEM_POX(pc + (offset % IDX_MOD))
# define ABS(pc, offset)  MEM_POX(pc + offset)

extern uint8_t	*g_base;
typedef enum e_mem_op
{
	READ,
	WRITE
}			t_mem_op;

typedef enum e_endianess
{
	LITTLE_E,
	BIG_E
}			t_endianess;

t_byte      *mem_pos(t_byte *pos);
void        mem_oper(t_mem_op op, t_byte *dst, t_byte *src, uint8_t cnt);
void        read_arg(t_arg *arg, int32_t *buff, t_bool addressing, t_bool far);

#endif 
