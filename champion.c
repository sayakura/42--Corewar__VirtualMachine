/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:02:14 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/29 22:23:51 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ *search_champion(t_vm *vm, int32_t id)
{
    FOR_EACH(champ, vm->corewar.champions)
    {
        if (champ->id == id)
            return champ;
    }
    // int8_t  i;

    // i = ITERATOR;
    // printf("-> %d\n", vm->nprocess);
    // while (++i < vm->nprocess)
    // {
    //     if (vm->corewar.champions[i].id == id)
    //         return (&vm->corewar.champions[i]);
    // }
    return (NULL);
}

