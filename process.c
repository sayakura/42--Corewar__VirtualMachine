/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 02:39:18 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/21 10:25:38 by qpeng            ###   ########.fr       */
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

t_byte    *addr(t_byte *cur, off_t offset)
{
    t_byte *end;
    off_t   diff;

    end = g_base + MEM_SIZE;
    if ((diff = ((cur += offset) - end)) > 0)
        return (g_base + diff);
    else
        return (cur);
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




void    execute(t_byte instr, t_arg_type *argvt, t_byte **argv, uint8_t *carry)
{
    (instr_funptr[instr])(argvt, argv, carry);
    printf("running... %d\n", instr);
}

/*
** advance the program counter to the next instruction
** and decode it into argvt and argv
** pc = program counter / instruction pointer
** acb = argument's coding byte
*/

void    fetch_decode(t_byte **pc, t_arg_type *argvt, t_byte **argv)
{
    t_byte         bcode;
    t_byte         acb;
    uint8_t        i;

    i = ITERATOR;
    bcode = **pc;
    acb = *(*pc = addr(*pc , 1));
    printf("acb: %x \n", acb);
    *pc = addr(*pc , 1);
    while (INC(i) < g_op_tab[bcode - 1].argc)
    {
        if ((acb & 0b11000000) == REGISTER_TYPE)
        {
            printf("advanced %d [%x]\n", T_REG, **pc);
            *pc = addr(*pc, T_REG);
            argvt[i] = T_REG;
        }
		else if ((acb & 0b11000000) == DIRECT_TYPE)
		{
            printf("advanced %d [%x]\n", DIR_SIZE, **pc);
            *pc = addr(*pc, T_DIR);
            argvt[i] = T_DIR;
        }
		else
		{
            printf("advanced %d [%x]\n", T_IND, **pc);
            *pc = addr(*pc, T_IND);
            argvt[i] = T_IND;
        }
        acb <<= 2;
    }
}

void    instruction_cycle(t_byte   **pc)
{
    t_byte              instr;
    static t_arg_type   argvt[MAX_ARGS_NUMBER];
    static t_byte       *argv[MAX_ARGS_NUMBER];
    static t_bool       carry;
    
    instr = **pc;
    fetch_decode(pc, argvt, argv);
    execute(instr, argvt, argv, &carry);
}

void    process_loop(t_vm   *vm)
{
    t_process *cp;
    static uint32_t r_cycles[MAX_PLAYERS + 1];
    
    cp = vm->process_list;
    while (cp)
    {
        if (!r_cycles[cp->pid])
            r_cycles[cp->pid] = g_op_tab[*(cp->pc) - 1].cycles;
        r_cycles[cp->pid]--;
        if (!r_cycles[cp->pid])
        {
            instruction_cycle(&cp->pc);
            r_cycles[cp->pid] = 0;
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
