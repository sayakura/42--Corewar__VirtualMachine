/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:31:59 by qpeng             #+#    #+#             */
/*   Updated: 2019/08/18 17:19:57 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vm.h"

int8_t     *g_ownerbase;

void    print_mem(t_vm *vm)
{
    int                 i;
    unsigned            siz;

    i = 0;
    siz = (unsigned)sqrt(MEM_SIZE);
    while (i < MEM_SIZE) // < MEM_SIZE
    {
        if (i % siz == 0)
        {
            if (i)
                printf("\n");
            printf("%#06x : ", i);
        }
        h_puthex(vm->memory[i]);
        printf(" ");
        i++;
    }
    printf("\nOWNER MAP: \n");
    i ^= i;
    while (i < MEM_SIZE) // < MEM_SIZE
    {
        if (i % siz == 0)
        {
            if (i)
                printf("\n");
            printf("%#06x : ", i);
        }
        if (vm->owner[i] != 7)
            printf("%02d", vm->owner[i]);
        else 
            printf("__");
        printf(" ");
        i++;
    }
    printf("\n");
}

void    dump_mem(t_vm *vm)
{
    int                 i;
    unsigned            siz;

    i = 0;
    siz = (unsigned)sqrt(MEM_SIZE);
    while (i < MEM_SIZE) // < MEM_SIZE
    {
        if (i % siz == 0)
        {
            if (i)
                printf("\n");
            printf("%#06x : ", i);
        }
        h_puthex(vm->memory[i]);
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