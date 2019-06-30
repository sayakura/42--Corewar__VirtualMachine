/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 02:39:18 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/29 23:46:59 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_instr_hdlr instr_funptr[] = {
    ft_live,
    ft_ld,
    ft_st,
    ft_add,
    ft_sub,
    ft_and, 
    ft_or,
    ft_xor,
    ft_zjmp,
    ft_ldi,
    ft_sti,
    ft_fork,
    ft_lld,
    ft_lldi,
    ft_lfork,
    ft_aff
};

t_byte  *advance_pc(t_byte **cur, off_t offset)
{
    t_byte          *end;
    off_t           diff;

    end = g_base + MEM_SIZE;
    if ((diff = ((*cur += offset) - end)) > 0)
        *cur = g_base + diff;
    return (*cur);
}

void    execute(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    (instr_funptr[cinstr->instr - 1])(vm, cp, cinstr);
    //printf("Running... %s\n", g_op_tab[instr - 1].name);
}

/*
** advance the program counter to the next instruction
** and decode it into argvt and argv
** pc = program counter / instruction pointer
** acb = argument's coding byte
*/

void    decode_without_acb(t_byte **pc, t_byte *argvt,\
                                t_byte **argv,  t_op *op)
{
    t_byte         acb;
    uint8_t        i;

    i = ITERATOR;
    advance_pc(pc, 1);
    while (INC(i) < op->argc)
    {
        argv[i] = *pc;
        if (op->argvt[i] & T_DIR)
            advance_pc(pc, DIR_SIZE);
        else if (op->argvt[i] & T_REG)
            advance_pc(pc, REG_SIZE);
        else if (op->argvt[i] & T_IND)
            advance_pc(pc, IND_SIZE);
    }
}

void    decode_with_acb(t_byte **pc, t_byte *argvt,\
                                t_byte **argv, t_op *op)
{
    t_byte         acb;
    uint8_t        i;

    i = ITERATOR;
    acb = *(advance_pc(pc, 1));             //printf("%x\n", acb);
    advance_pc(pc, 1);  
    while (INC(i) < op->argc)
    {
        argv[i] = *pc;
        argvt[i] = GET_ACB_TYPE(acb);
        if (argvt[i] == REGISTER_TYPE)
            advance_pc(pc, 1);
		else if (argvt[i] == DIRECT_TYPE)
		{
            if (op->truncate)
                advance_pc(pc, DIR_SIZE >> 1);
            else 
                advance_pc(pc, DIR_SIZE);
        }
		else
            advance_pc(pc, IND_SIZE);
        acb <<= 2;
    }
}

void    instruction_cycle(t_vm *vm, t_process *cp)
{
    t_op                *op;
    static t_instr      i;
    
    i.instr = *cp->pc;
    i.pc = cp->pc;
    op = &g_op_tab[i.instr - 1];
    i.argc = op->argc;
    if (op->coding_byte)
        decode_with_acb(&cp->pc, i.argvt, i.argv, op);
    else
        decode_without_acb(&cp->pc, i.argvt, i.argv, op);
    execute(vm, cp, &i);
}

void    process_loop(t_vm   *vm)
{
    t_process       *cp;
    static uint32_t r_cycles[MAX_PLAYERS + 1];
    
    cp = vm->process_list;
    while (cp)
    {
        if (*(cp->pc) && *(cp->pc) <= 16)
        {
            if (!r_cycles[cp->pid])
                r_cycles[cp->pid] = g_op_tab[*(cp->pc) - 1].cycles;
            r_cycles[cp->pid]--;
            if (!r_cycles[cp->pid])
            {
                printf("Pid: %d\n", cp->pid);
                printf("Cycle: %d\n", vm->corewar.cycle);
                instruction_cycle(vm, cp);
                printf("---------------\n");
                r_cycles[cp->pid] ^= r_cycles[cp->pid];
            }
        }
        cp = cp->next;
    }
}
// .name "zork"
// .comment "just a basic living prog"
		
// l2:	sti	r1,%:live,%0
// 	and	r1,%0,r1
// live:	live	%1
// 	zjmp	%:live