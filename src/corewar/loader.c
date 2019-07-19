/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:31:59 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/18 23:22:50 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "corewar/corewar.h"
#include "corewar/process.h"


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
    ch_load_champ(vm, fd);
}