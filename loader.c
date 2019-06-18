/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:31:59 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/17 23:18:09 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// read .cor from command line, parse the info and load it into the memory
// void    init_process(t_vm *vm)
// {
//     t_process           *process;

//     process = fork_process();
//     // add this process to the process_list 
//     process->registers[0] = 0;
//     // set ownership
// }

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
	pc = &vm->memory[(MEM_SIZE / vm->nplayers) * index];
	if (read(fd, pc, hdr.prog_size) != hdr.prog_size)
		PERROR("read");
	close(fd);
}


void    loader(t_vm *vm, char *filename)
{
    int fd;

    if ((fd = open(filename, O_RDONLY)) == -1)
            PERROR("open"); 
    load_champ(vm, fd);
}