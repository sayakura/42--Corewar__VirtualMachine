/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:20:54 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/20 17:19:47 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
#define HANDLER_H

#include "vm.h"


t_bool    ft_live(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_ld(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_st(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_add(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_sub(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_and(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_or(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_xor(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_zjmp(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_ldi(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_sti(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_fork(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_lld(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_lldi(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_lfork(t_arg_type *, t_byte **, t_bool *);
t_bool    ft_aff(t_arg_type *, t_byte **, t_bool *);

#endif