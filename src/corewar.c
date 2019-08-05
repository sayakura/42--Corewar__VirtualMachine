/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:32:01 by qpeng             #+#    #+#             */
/*   Updated: 2019/08/04 15:50:36 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "vm.h"

t_byte	*g_base;

/**
 *  run corewar game
 * 
 *  @param {t_vm} vm - vm struct 
 */
void    cw_run(t_vm *vm)
{
    while (1)
    {
        ++vm->corewar.cycle;
        if (++vm->corewar.cycle == vm->corewar.dump_cycle)
            print_mem(vm);
        p_process_loop(vm);
        if (vm->corewar.cycle > vm->corewar.kill_cycle)
            ;//printf("start killing!\n");
        if (!vm->nprocess)
            ERROR("some one win!");
        if (vm->corewar.cycle > 1000)
            break ;
    }
}

/**
 *  read flags and if it's champion file 
 *  run loader to load it into corewar
 * 
 *  @param {t_vm} vm - vm struct 
 *  @param {int} ac - number of arguments
 *  @param {char **} av - argument vector
 */
void    cw_read_args(t_vm *vm, int ac, char **av)
{
    int     i;

    i = 1;
    while (i < ac)
    {
        loader(vm, av[i]);
        i++;
    }
}

/**
 *  clean up stage
 *  deallocates all the resouces back
 * 
 *  @param {t_vm} vm - vm struct 
 */
void    cw_cleanup(t_vm *vm)
{
    // t_process *tmp;
    
    // tmp = vm->process_list;
    // while (tmp)
    // {
    //     tmp = tmp->next;
    //     free(tmp);
    // }
}

/**
 *  init all the env
 *  set g_base as the beginning of memory 
 * 
 *  @param {t_vm} vm - vm struct 
 */
void    cw_env_init(t_vm *vm, int nplayers)
{
    bzero_(vm, sizeof(t_vm));
    vm->debug_mode = 1;
    vm->corewar.nplayers = nplayers;
    MAP_START = vm->memory;
    OWNER_START = vm->owner;
    memset_(OWNER_START, 7, MEM_SIZE);
    setbuf(stdout, NULL);
}

/**
 *  start the corewar game, set up (initialize all the envs)
 *  read all the args and run processes
 * 
 *  @param {int} ac - number of arguments
 *  @param {char **} av - argument vector
 */
void    cw_start(int ac, char **av)
{
    t_vm vm;
    
    if (ac < 2)
    {
        printf("usage\n");
        exit(EXIT_SUCCESS);
    }
    cw_env_init(&vm, ac - 1);
    cw_read_args(&vm, ac, av);
    cw_run(&vm);
    cw_cleanup(&vm);
}