/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 20:01:05 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/29 23:24:00 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// # define WRITE_TO_MEM(a, b, c, d) 

// t_byte  *advance_pc(t_byte **cur, off_t offset)
// {
//     t_byte          *end;
//     off_t           diff;

//     end = g_base + MEM_SIZE;
//     if ((diff = ((*cur += offset) - end)) > 0)
//         *cur = g_base + diff;
//     return (*cur);
// }

/*
** read data(copy) from arena into buffer and make sure it 
** read circularly.  
*/

void    mem_oper(t_mem_op op, t_byte *dst, t_byte *src, uint8_t cnt)
{
    t_byte      *end;

    end = g_base + MEM_SIZE;
    while (cnt--)
    {
        if (op == READ)
            src =  src + 1 > end ? g_base : src;
        else 
            dst = dst + 1 > end ? g_base : dst;
        *dst++ = *src++;
    }
}

// void    read_from_mem(t_byte *where, void *buff, uint8_t howmany,\
//                                             t_endianess endianess)
// {
//     mem_oper(READ, buff, where, howmany);
//     if (endianess == E_BIG_ENDIAN)
//         rev_bytes(buff, howmany);
// }

// void    write_to_mem(t_byte *to, void *buff, uint8_t howmany, 
//                                             t_endianess endianess)
// {
//     mem_oper(WRITE, to, buff, howmany);
//     if (endianess == E_BIG_ENDIAN)
//         rev_bytes(to, howmany);
// }

  // t_byte      *ptr;
    // t_byte      *end;
    // uint8_t     tmp;
    
    // tmp = howmany;
    // ptr = (t_byte *)buff;
    // end = g_base + MEM_SIZE;
    // while (howmany--)
    // {
    //     if (where + 1 > end)
    //         where = g_base;
    //     *ptr++ = *where++;
    // }
    // if (endianess == E_BIG_ENDIAN)
    //     rev_bytes(buff, tmp);