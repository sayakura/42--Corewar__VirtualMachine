/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:20:54 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/24 10:08:28 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
#define HANDLER_H

#include "vm.h"


t_bool    ft_live(t_byte *, t_byte **, t_bool *);
t_bool    ft_ld(t_byte *, t_byte **, t_bool *);
t_bool    ft_st(t_byte *, t_byte **, t_bool *);
t_bool    ft_add(t_byte *, t_byte **, t_bool *);
t_bool    ft_sub(t_byte *, t_byte **, t_bool *);
t_bool    ft_and(t_byte *, t_byte **, t_bool *);
t_bool    ft_or(t_byte *, t_byte **, t_bool *);
t_bool    ft_xor(t_byte *, t_byte **, t_bool *);
t_bool    ft_zjmp(t_byte *, t_byte **, t_bool *);
t_bool    ft_ldi(t_byte *, t_byte **, t_bool *);
t_bool    ft_sti(t_byte *, t_byte **, t_bool *);
t_bool    ft_fork(t_byte *, t_byte **, t_bool *);
t_bool    ft_lld(t_byte *, t_byte **, t_bool *);
t_bool    ft_lldi(t_byte *, t_byte **, t_bool *);
t_bool    ft_lfork(t_byte *, t_byte **, t_bool *);
t_bool    ft_aff(t_byte *, t_byte **, t_bool *);

#endif