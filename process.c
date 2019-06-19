/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 02:39:18 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/19 06:57:34 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


uint8_t    *addr(uint8_t *cur, off_t offset)
{
    uint8_t *end;
    off_t   diff;

    end = g_base + MEM_SIZE;
    if ((diff = ((cur += offset) - end)) > 0)
        return (g_base + diff);
    else
        return (cur);
}

void    exec_task(t_task *task)
{


    
}

/*
** advance the program counter to the next instruction
** meanwhile, load current instruction to current task
** t = current task
** pc = program counter / instruction pointer
** cb = argument's coding byte
*/

// t->coding_byte = g_op_tab[t->opcode].coding_byte;
// t->direct = g_op_tab[t->opcode].direct;

bool    load_pc(t_vm *vm, t_process *cp)
{
    uint8_t     i;
    uint8_t     acb;
    uint8_t     *pc;
    t_task      *t;

    i = 0;
    t = &cp->cur_task;
    t->opcode = *cp->pc;
    t->cycle_left = g_op_tab[t->opcode].cycles;
    pc = cp->pc;
    acb = g_op_tab[t->opcode].cb ? *(pc = addr(pc, 1)) : 0;
    while (i < g_op_tab[t->opcode].argc)
    {
        if (acb & 0xc0 == 0b00)
            return false;
        else if (acb & 0xc0 == 0x40)
            t->argv[i] = *(pc = addr(pc, T_REG));
		else if (acb & 0xc0 == 0x80)
			t->argv[i] = *(pc = addr(pc, T_DIR));
		else
			t->argv[i] = *(pc = addr(pc, T_IND));
        acb <<= 2;
        i++;
    }
    cp->pc = pc;
    return true;
}

void    run_process(t_vm *vm)
{
    t_process *cp;

    cp = vm->process_list;
    while (cp)
    {
       cp->cur_task.cycle_left--;
       if (cp->cur_task.cycle_left <= 0)
       {
            exec_task(&cp->cur_task);
            if (load_pc(vm, cp))
                ; // run 
       }
       cp = cp->next;
    }
}