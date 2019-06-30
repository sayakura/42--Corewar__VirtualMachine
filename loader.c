/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:31:59 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/30 15:10:49 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <math.h>

void    init_process(t_vm *vm, void * pc)
{
    t_process           *process;
    static int32_t      pid = -1;

    process = malloc(sizeof(t_process));
    bzero_(process, sizeof(t_process));
    process->pc = pc;
    process->pid = pid;
    process->registers[1] = pid;
    //process->state = CREATE;
    printf("initing... pid: %d\n", pid);
    pid++;
    if (vm->process_list)
        process->next = vm->process_list;
    vm->process_list = process;
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
    champ = &(vm->corewar.champions[index]);
	memcpy_(champ->name, hdr.prog_name, PROG_NAME_LENGTH);
	memcpy_(champ->comment, hdr.comment, COMMENT_LENGTH);
    champ->id = index - 1;
	pc = &vm->memory[(MEM_SIZE / vm->corewar.nplayers) * index];
    printf("program size: %d\n",  hdr.prog_size);
	if (read(fd, pc, hdr.prog_size) != hdr.prog_size)
		PERROR("read");
    init_process(vm, pc);
    index++;
    close(fd);
}

void    print_mem(t_vm *vm)
{
    int                 i;
    unsigned            siz;

    i = 0;
    siz = (unsigned)sqrt(MEM_SIZE);
    while (i < 100) // < MEM_SZIE
    {
        if (i % siz == 0)
        {
            if (i)
                printf("\n");
            printf("%#06x : ", i);
        }
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