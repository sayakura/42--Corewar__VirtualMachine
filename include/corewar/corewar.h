/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 20:30:16 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/22 08:58:51 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
#define COREWAR_H

#include "define.h"

extern t_op g_op_tab[17];

void    cw_start(int ac, char **av);
void    cw_env_init(t_vm *vm);
void    cw_cleanup(t_vm *vm);
void    cw_read_args(t_vm *vm, int ac, char **av);

void    cw_run(t_vm *vm);

t_champ	*ch_search_champion(t_vm *vm, int32_t id);
void	ch_parse_champ_header(t_hdr *hdr, int fd);
void    ch_load_champ(t_vm *vm, int fd);


#endif