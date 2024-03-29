/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 02:39:18 by qpeng             #+#    #+#             */
/*   Updated: 2019/08/18 18:18:46 by qpeng            ###   ########.fr       */
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



/**
 *  init a process and insert it at the beginning of the 
 *  process list.
 * 
 *  pid started at -1, the byte code is ffff ffff.
 * 
 *  need to assign the pid to the first register of the 
 *  process, so that the champion can call live with 
 *  the right value indicating that the process/champion
 *  with this pid is alive.
 * 
 * @param {t_vm} vm - current vm structure
 * @param {void *} pc - current program counter
 * 
 */
void    p_init_process(t_vm *vm, void * pc, t_champ *champ)
{
    t_process           *process;
    static int32_t      pid = -1;

    process = malloc(sizeof(t_process));
    bzero_(process, sizeof(t_process));
    process->pc = pc;
    process->pid = pid;
    process->registers[1] = pid;
    process->champion = champ;
    pid++;
    if (vm->process_list)
        process->next = vm->process_list;
    vm->process_list = process;
    vm->nprocess++;
}

// t_process   *p_create_process()
// {
//     t_process           *process;
//     static int32_t      pid = -1;

//     process = malloc(sizeof(t_process));
//     bzero_(process, sizeof(t_process));
//     process->pid = pid;
//     process->registers[1] = pid;
//     return process;
// }

// void    p_spawn_process(t_champ *champion, t_process *process_list)
// {
//     t_process   *p;

//     FOR_EACH(champ, champion)
//     {
//         p = p_create_process();
//         p->pc = champ->pc;
//         LOG("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",  champ->id + 2, 
//         hdr.prog_size, champ->name, champ->comment);
//     }
// }

/**
 *  a sys call for lfork
 *  fork a process and append it to the process list
 *  the pc of the forked process will have its pc 
 *  at pc + (offset % IDX_MOD), if this is a long fork
 *  then the offset is not mod by IDX_MOD
 * 
 * @param {t_vm} vm - current vm structure
 * @param {t_process *} parent - the parent process that's copying from
 * @param {int32_t} offset - offset of the pc 
 * @param {t_bool} is_long - whather it's a fork or lfork
 */
void    p_fork_process(t_vm *vm, t_process *parent, int32_t offset, t_bool is_long)
{
    t_process           *process;

    process = malloc(sizeof(t_process));
    bzero_(process, sizeof(t_process));
    memcpy_(process->registers, parent->registers, sizeof(process->registers));
    process->pc =  parent->pc + (is_long ? offset : (offset % IDX_MOD));
    process->pid = parent->pid;
    process->champion = parent->champion;
    if (vm->process_list)
        process->next = vm->process_list;
    vm->process_list = process;
    vm->nprocess++;
}

/**
 *   advance the pc by offset, check if the 
 *  destination exceeds the size of the map, if yes 
 *  then the exceeded part will be added to the beginning of the 
 *  map
 * 
 * @param {t_vm} vm - current vm structure
 * @param {t_process *} parent - the parent process that's copying from
 * @param {int32_t} offset - offset of the pc 
 * @param {t_bool} is_long - whather it's a fork or lfork
 */
t_byte  *advance_pc(t_byte **cur, int32_t offset)
{
    t_byte          *end;
    off_t           diff;

    end = g_base + MEM_SIZE;
    if ((diff = ((*cur += offset) - end)) > 0)
        *cur = g_base + diff;
    //printf("jmp[%d] to: %p %x\n", offset, *cur, **cur);
    return (*cur);
}


void    decode_with_acb(t_byte **pc, t_arg *arg, t_op *op)
{
    t_byte         acb;
    uint8_t        i;

    i = ITERATOR;
    acb = *(advance_pc(pc, 1));             //printf("%x\n", acb);
    advance_pc(pc, 1);  
    while (INC(i) < op->argc)
    {
        arg[i].argv = *pc;
        arg[i].argvt = GET_ACB_TYPE(acb);
        if (arg[i].argvt == REGISTER_TYPE)
            advance_pc(pc, 1);
		else if (arg[i].argvt == DIRECT_TYPE)
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

void    fetch(t_instr *instr, t_byte **pc)
{
    instr->icode = **pc;
    if (INSTR_LOOK_UP[instr->icode].coding_byte)
        instr->acb = *(++*pc);
    else 
    {
        
    }

    
    
}

void    instruction_cycle(t_vm *vm, t_process *cp)
{
    t_instr     instr;

    val_p = 0;
    fetch(&instr, &cp->pc);


   

    t_op                *op;
    static t_instr      i;
    
    i.instr = *cp->pc;
    cp->cpc = i.pc = cp->pc;
    op = &INSTR_LOOK_UP[i.instr - 1];
    i.argc = op->argc;

    if (op->coding_byte)
        decode_with_acb(&cp->pc, i.arg, op);
    else
    {
        advance_pc(&cp->pc, 1);
        i.arg[0].argv = cp->pc;
        advance_pc(&cp->pc, 4);
    }
    g_cur_process = cp;
    (instr_funptr[i.instr - 1])(vm, &i);
    print_mem(vm);
}


void    p_process_loop(t_vm   *vm)
{
    t_process       *curr_p;
    static uint32_t r_cycles[MAX_PLAYERS + 1];
    
    curr_p = vm->process_list;
    while (curr_p)
    {
        if (*(curr_p->pc) >= 0 && *(curr_p->pc) <= 16)
        {
            if (!r_cycles[curr_p->pid + 1])
                r_cycles[curr_p->pid + 1] = INSTR_LOOK_UP[*(curr_p->pc) - 1].cycles;
            r_cycles[curr_p->pid + 1]--;
            if (!r_cycles[curr_p->pid + 1])
            {
                instruction_cycle(vm, curr_p);
                r_cycles[curr_p->pid + 1] ^= r_cycles[curr_p->pid + 1];
            }
        }
        curr_p = curr_p->next;
    }
}

void    p_kill_process(t_vm *vm, int32_t id)
{
    t_process   *last;
    t_process   *cur;

    cur = vm->process_list;
    last = cur;
    if (cur->pid == id)
    {
        vm->process_list = cur->next;
        free(cur);
    }
    cur = cur->next;
    while (cur)
    {
        if (cur->pid == id)
        {
            last->next = cur->next;
            free(cur);
            break ;
        }
        else 
            cur = cur->next;
    }
}
// .name "zork"
// .comment "just a basic living prog"
		
// l2:	sti	r1,%:live,%0
// 	and	r1,%0,r1
// live:	live	%1
// 	zjmp	%:live