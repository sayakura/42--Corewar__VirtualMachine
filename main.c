/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:32:01 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/16 06:19:29 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "vm.h"


void    read_args(t_vm *vm, int ac, char **av)
{
    int     i;
    int     fd;

    i = 1;
    while (i < ac)
    {
        if ((fd = open(av[i], O_RDONLY)) == -1)
            ERROR(); 
        load_champ(&vm, fd);
        
    }


}

int     main(int ac, char **av)
{
    t_vm vm;
    
    if (ac <  2)
        usage();
    read_args(&vm, ac, av);
    loader(&vm);
    cpu();
    return (0);
}