/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:20:54 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/29 18:12:39 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
#define HANDLER_H

#include "vm.h"

typedef struct s_vm t_vm;
typedef struct s_process t_process;
typedef struct s_instr t_instr;

t_bool    ft_live(t_vm *, t_process *, t_instr *);
t_bool    ft_ld(t_vm *, t_process *, t_instr *);
t_bool    ft_st(t_vm *, t_process *, t_instr *);
t_bool    ft_add(t_vm *, t_process *, t_instr *);
t_bool    ft_sub(t_vm *, t_process *, t_instr *);
t_bool    ft_and(t_vm *, t_process *, t_instr *);
t_bool    ft_or(t_vm *, t_process *, t_instr *);
t_bool    ft_xor(t_vm *, t_process *, t_instr *);
t_bool    ft_zjmp(t_vm *, t_process *, t_instr *);
t_bool    ft_ldi(t_vm *, t_process *, t_instr *);
t_bool    ft_sti(t_vm *, t_process *, t_instr *);
t_bool    ft_fork(t_vm *, t_process *, t_instr *);
t_bool    ft_lld(t_vm *, t_process *, t_instr *);
t_bool    ft_lldi(t_vm *, t_process *, t_instr *);
t_bool    ft_lfork(t_vm *, t_process *, t_instr *);
t_bool    ft_aff(t_vm *, t_process *, t_instr *);

#endif