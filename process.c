/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 02:39:18 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/18 03:28:12 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void    exec_op(void *pc)
{


    
}

void    run_process(t_vm *vm)
{
    t_process *cp;

    cp = vm->process_list;
    while (cp)
    {
        if (cp->state == CREATE)
        {
            
        }
        else
        {
            exec_op(cp->pc);
            
        }
        cp = cp->next;
    }
}