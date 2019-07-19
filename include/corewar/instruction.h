/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 20:30:18 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/18 23:28:21 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "memory.h"
#include "corewar.h"
#include "../common.h"
#include "op.h"

# define REGISTER_TYPE 0b01000000
# define DIRECT_TYPE 0b10000000
# define INDIRECT_TYPE 0b11000000
# define GET_ACB_TYPE(acb) (acb & 0b11000000)
# define LOG printf
# define LEA(reg, mem) read_arg(mem, &reg, false, false);
# define LLEA(reg, mem) read_arg(mem, &reg, false, true);
# define LD(reg, mem) read_arg(mem, &reg, true, false);
# define LLD(reg, mem) read_arg(mem, &reg, true, true);
# define EDI g_cur_process->registers[1]
# define ESI g_cur_process->registers[2]
# define ECX g_cur_process->registers[3]
# define ADD(reg1, reg2) reg1 += reg2
# define SUB(reg1, reg2) reg1 -= reg2
# define AND(reg1, reg2) reg1 &= reg2
# define OR(reg1, reg2) reg1 |= reg2
# define XOR(reg1, reg2) reg1 ^= reg2
# define MOV(r1, r2) WRITE_(&r1, &r2, 4);

typedef	struct 		s_arg
{
	t_byte			*argv;
	t_byte			argvt;
}					t_arg;

typedef struct 		s_instr
{
	t_byte 			*pc;
	t_byte			instr;
	t_byte 			argc;
	t_byte			*argv[MAX_ARGS_NUMBER];
	t_byte			argvt[MAX_ARGS_NUMBER];
	t_arg			arg[MAX_ARGS_NUMBER];
	t_process		*context;
}					t_instr;

typedef struct		s_op
{
	char			*name;
	int				argc;
	t_arg_type		argvt[MAX_ARGS_NUMBER];
	char			opcode;
	uint32_t		cycles;
	char			*des;
	t_bool			coding_byte;
	t_bool			truncate;
}					t_op;

typedef void(*t_instr_hdlr)(t_vm *, t_instr *);

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