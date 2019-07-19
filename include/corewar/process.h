/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 20:30:24 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/18 22:03:50 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
#define PROCESS_H
#include "../common.h"
#include "corewar.h"
#include "op.h"

# define PC g_cur_process->cpc
# define CP g_cur_process
# define INSTR g_op_tab
# define REG(i) g_cur_process->registers[i]

typedef struct      	s_process
{
    t_word         		registers[REG_NUMBER + 1];
    t_byte            	*pc;
	t_byte 				*cpc;
    int32_t         	pid;
	t_champ				*champion;
	struct s_process	*next;
	t_bool				carry;
}                   	t_process;
extern t_process *g_cur_process;

#endif