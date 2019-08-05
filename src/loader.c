/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:31:59 by qpeng             #+#    #+#             */
/*   Updated: 2019/08/05 13:16:42 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vm.h"

int8_t     *g_ownerbase;

void    print_mem(t_vm *vm, t_gui *gui)
{
    int                 i;
    int                 x;
    int                 y;
    unsigned            siz;

    i = 0;
    x = -2;
    y = 1;
    siz = (unsigned)sqrt(MEM_SIZE);
    // while (i < vm->corewar.champions->prog_size) // < MEM_SZIE
    while (i < MEM_SIZE) // < MEM_SZIE
    {
        if (x == MAX_X - 3)
        {
            x = -2;
            y++;
        }
        if (i % siz == 0)
        {
            if (i)
                (void)i;
        }
        x += 3;
        // h_puthex(vm->memory[i], gui, x, y);
        if (i < vm->corewar.champions->prog_size)
        {
            init_pair(1, COLOR_GREEN, COLOR_BLACK);
            wattron(gui->win, COLOR_PAIR(1));
            mvwprintw(gui->win, y, x, "%02x", vm->memory[i]);
            wattroff(gui->win, COLOR_PAIR(1));
        }
        else
            mvwprintw(gui->win, y, x, "%02x", vm->memory[i]);

        i++;
    }
    // while (y != MAX_Y - 1)
    // {
    //    if (x == MAX_X - 3)
    //     {
    //         x = -2;
    //         y++;
    //     }
    //     else { 
    //     x += 3;
    //     mvwprintw(gui->win, y, x, "00 ");
    //     }
    // }
    //printf("\n");
}

void    loader(t_vm *vm, char *filename)
{
    int fd;

    if ((fd = open(filename, O_RDONLY)) == -1)
        PERROR("open"); 
    ch_load_champ(vm, fd);
}