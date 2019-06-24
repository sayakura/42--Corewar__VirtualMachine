/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 02:39:18 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/24 10:09:41 by qpeng            ###   ########.fr       */
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

// t_byte    *addr(t_byte *cur, off_t offset)
// {
//     t_byte *end;
//     off_t   diff;

//     end = g_base + MEM_SIZE;
//     if ((diff = ((cur += offset) - end)) > 0)
//         return (g_base + diff);
//     else
//         return (cur);
// }

t_byte  *advance_pc(t_byte **cur, off_t offset)
{
    t_byte *end;
    off_t   diff;

    end = g_base + MEM_SIZE;
    if ((diff = ((*cur += offset) - end)) > 0)
        *cur = g_base + diff;
    return (*cur);
}

// t->coding_byte = g_op_tab[t->opcode].coding_byte;
// t->direct = g_op_tab[t->opcode].direct;


// t_bool    load_pc(t_byte *pc, t_task *t)
// {
//     t_byte     i;
//     t_byte     acb;

//     i = 0;
//     memcpy_(&t->op_info, &g_op_tab[*pc], sizeof(t_op));
//     if (!t->op_info.coding_byte)
//         return (load_pc_wo_cb(pc, t));
//     acb = *(pc = addr(pc, 1));
//     while (i < t->op_info.argc)
//     {
//         if (acb & 0xc0 == 0b00)
//             return false;
//         else if (acb & 0xc0 == 0x40)
//         {
//             memcpy_(&t->argv[i], addr(pc, REG_SIZE), REG_SIZE);
//             pc = addr(pc, REG_SIZE);
//         }
// 		else if (acb & 0xc0 == 0x80)
// 			t->argv[i] = *(pc = addr(pc, DIR_SIZE));
// 		else
// 			t->argv[i] = *(pc = addr(pc, IND_SIZE));
//         acb <<= 2;
//         i++;
//     }
//     return true;
// }


void    execute(t_byte instr, t_byte *argvt, t_byte **argv, uint8_t *carry)
{
    (instr_funptr[instr])(argvt, argv, carry);
    printf("running... %s\n", g_op_tab[instr - 1].name);
}

/*
** advance the program counter to the next instruction
** and decode it into argvt and argv
** pc = program counter / instruction pointer
** acb = argument's coding byte
*/

void    decode_without_acb(t_byte **pc, t_byte *argvt, t_byte **argv,  t_op *op)
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

void    decode_with_acb(t_byte **pc, t_byte *argvt, t_byte **argv, t_op *op)
{
    t_byte         acb;
    uint8_t        i;

    i = ITERATOR;
    acb = *(advance_pc(pc, 1));
    advance_pc(pc, 1);
    while (INC(i) < op->argc)
    {
        argv[i] = *pc;
        argvt[i] = GET_ACB_TYPE(acb);
        if (argvt[i] == REGISTER_TYPE)
            *pc = addr(*pc, 1);
		else if (argvt[i] == DIRECT_TYPE)
		{
            if (op->truncate)
                advance_pc(pc, DIR_SIZE >> 2);
            else 
                advance_pc(pc, DIR_SIZE);
        }
		else
            advance_pc(pc, IND_SIZE);
        acb <<= 2;
    }
}

void    instruction_cycle(t_byte   **pc)
{
    t_byte              instr;
    t_op                *op;
    static t_byte       argvt[MAX_ARGS_NUMBER];
    static t_byte       *argv[MAX_ARGS_NUMBER];
    static t_bool       carry;

    instr = **pc;
    op = &g_op_tab[instr - 1];
    if (op->coding_byte)
        decode_with_acb(pc, argvt, argv, op);
    else
        decode_without_acb(pc, argvt, argv, op);
    execute(instr, argvt, argv, &carry);
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
                printf("Cycle: %d\n", vm->corewar.cycle);
                instruction_cycle(&cp->pc);
                printf("------------------------------------------\n");
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
