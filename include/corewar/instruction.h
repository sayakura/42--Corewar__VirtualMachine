/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 20:30:18 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/22 08:58:46 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "define.h"

void    ft_live(t_vm *, t_instr *);
void    ft_ld(t_vm *, t_instr *);
void    ft_st(t_vm *, t_instr *);
void    ft_add(t_vm *, t_instr *);
void    ft_sub(t_vm *, t_instr *);
void    ft_and(t_vm *, t_instr *);
void    ft_or(t_vm *, t_instr *);
void    ft_xor(t_vm *, t_instr *);
void    ft_zjmp(t_vm *, t_instr *);
void    ft_ldi(t_vm *, t_instr *);
void    ft_sti(t_vm *, t_instr *);
void    ft_fork(t_vm *, t_instr *);
void    ft_lld(t_vm *, t_instr *);
void    ft_lldi(t_vm *, t_instr *);
void    ft_lfork(t_vm *, t_instr *);
void    ft_aff(t_vm *, t_instr *);
#endif