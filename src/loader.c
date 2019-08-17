/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:31:59 by qpeng             #+#    #+#             */
/*   Updated: 2019/08/16 12:03:12 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vm.h"
# define RED "\x1b[91m"
# define BOLD "\x1b[1m"
# define RESET "\x1b[0m"

int8_t     *g_ownerbase;

static void    save_flag(t_vm *vm, char *filename)
{
    if (*filename == '\0')
        ERROR(RED BOLD"Error: flag invalid.\n"RESET);
    if (!scmp_(filename, "gui"))
        vm->flag |= FL_GUI;
}

void    print_mem(t_vm *vm, t_gui *gui)
{
    (void)vm;
    (void)gui;
    if (vm->flag &= FL_GUI)
    {
        int                 i;
        int                 x;
        int                 y;

        i = 0;
        x = -2;
        y = 1;
        int color[4] = {COLOR_YELLOW, COLOR_GREEN, COLOR_RED, COLOR_MAGENTA};
        while (i < MEM_SIZE)
        {
            if (x == MAX_X - 2)
            {
                x = -2;
                y++;
            }
            x += 3;
            if (vm->owner[i] != 7)
            {
                init_pair(vm->owner[i] + 2, color[vm->owner[i] + 1], COLOR_BLACK);
                wattron(gui->win, COLOR_PAIR(vm->owner[i] + 2));
                mvwprintw(gui->win, y, x, "%02x", vm->memory[i]);
                wattroff(gui->win, COLOR_PAIR(vm->owner[i] + 2));
            }
            i++;
        }
    }
}

void    loader(t_vm *vm, char *filename)
{
    int fd;

    if (*filename == '-')
    {
        save_flag(vm, &(filename[1]));
        return ;
    }
    if ((fd = open(filename, O_RDONLY)) == -1)
        PERROR("open"); 
    ch_load_champ(vm, fd);
}