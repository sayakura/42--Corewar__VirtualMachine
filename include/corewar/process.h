/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 20:30:24 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/22 09:41:53 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
#define PROCESS_H
#include "define.h"

# define PC g_cur_process->cpc
# define CP g_cur_process
# define INSTR g_op_tab
# define REG(i) g_cur_process->registers[i]

extern t_process *g_cur_process;

#endif