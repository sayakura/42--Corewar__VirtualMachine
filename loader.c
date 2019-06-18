/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:31:59 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/18 03:14:40 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <math.h>

void    init_process(t_vm *vm, void * pc, uint8_t index)
{
    t_process           *process;

    process = malloc(sizeof(t_process));
    bzero_(process, sizeof(t_process));
    process->pc = pc;
    process->pid = index;
    process->registers[0] = vm->nplayers;
    process->state = CREATE;
    if (vm->process_list == NULL)
        vm->process_list = process;
    else 
    {
        while (vm->process_list->next)
            vm->process_list = vm->process_list->next;
        vm->process_list->next = process;
    }
    vm->nprocess++;
}

// read .cor from command line, parse the info and load it into the memory
void    load_champ(t_vm *vm, int fd)
{
    t_hdr               hdr;
    t_champ             *champ;
    static uint8_t      index;
    void                *pc;

    parse_champ_header(&hdr, fd);
    champ = &(vm->corewar.champions[++index]);
	memcpy_(champ->name, hdr.prog_name, PROG_NAME_LENGTH);
	memcpy_(champ->comment, hdr.comment, COMMENT_LENGTH);
	pc = &vm->memory[(MEM_SIZE / vm->nplayers) * (index - 1)];
    printf("program size: %d\n",  hdr.prog_size);
	if (read(fd, pc, hdr.prog_size) != hdr.prog_size)
		PERROR("read");
    init_process(vm, pc, index);
	close(fd);
}

void    print_mem(t_vm *vm)
{
    int         i;
    unsigned    siz;

    i = 0;
    siz = (unsigned)sqrt(MEM_SIZE);
    while (i < MEM_SIZE)
    {
        if (i % siz == 0)
            printf("\n");
        puthex(vm->memory[i]);
        printf(" ");
        i++;
    }
    printf("\n");
}

void    loader(t_vm *vm, char *filename)
{
    int fd;

    if ((fd = open(filename, O_RDONLY)) == -1)
        PERROR("open"); 
    load_champ(vm, fd);
}