/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:32:01 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/17 00:34:27 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "vm.h"
#include <stdio.h>

void    read_args(t_vm *vm, int ac, char **av)
{
    int     i;
    int     fd;

    i = 1;
    while (i < ac)
    {
        loader(vm, av[i]);
        i++;
    }
}

int     main(int ac, char **av)
{
    t_vm vm;
    
    if (ac < 2)
        printf("ac \n");
    printf("testing\n");
    read_args(&vm, ac, av);
    return (0);
}