/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 20:01:05 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/12 20:58:03 by qpeng            ###   ########.fr       */
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

void    read_m(void *fd, void *buff, unsigned int size)
{
    mem_oper(READ, (t_byte *)buff, (t_byte *)fd, size);
    rev_bytes(buff, size);
}

void    write_m(void *fd, void *buff, unsigned int size)
{
    mem_oper(WRITE, (t_byte *)fd, (t_byte *)buff, size);
    rev_bytes(fd, size);
}


void    read_arg(t_arg *arg, int32_t *buff, t_bool addressing, t_bool far)
{
    int32_t     tmp;

    *buff = 0;
    tmp = 0;
    if (arg->argvt == INDIRECT_TYPE)
    {
        read_m(arg->argv, &tmp, 2);
        *buff = tmp;
        if (addressing)
            read_m(REL(PC, (far ? tmp : tmp % IDX_MOD)), buff, 4);
    }
    else if (arg->argvt == DIRECT_TYPE)
        read_m(arg->argv, buff, INSTR[*PC - 1].truncate ? 2 : 4);
    else
    {
        read_m(arg->argv, buff, 1);
        if (addressing)
            *buff = CP->registers[*buff];
    }
}

// void    read_from_mem(t_byte *where, void *buff, uint8_t howmany,\
//                                             t_endianess endianess)
// {
//     mem_oper(READ, buff, where, howmany);
//     if (endianess == BIG_E)
//         rev_bytes(buff, howmany);
// }

// void    write_to_mem(t_byte *to, void *buff, uint8_t howmany, 
//                                             t_endianess endianess)
// {
//     mem_oper(WRITE, to, buff, howmany);
//     if (endianess == BIG_E)
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
    // if (endianess == BIG_E)
    //     rev_bytes(buff, tmp);