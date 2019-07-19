/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 20:30:16 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/19 15:53:52 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
#define COREWAR_H

#include <unistd.h>
#include "../common.h"
#include "instruction.h"
#include "op.h"

typedef struct s_process t_process;

typedef struct      s_champ
{
	int32_t			id;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	uint32_t		lives;
	uint32_t 		last_live;
	t_byte			*pc;
}                   t_champ;

typedef struct      s_cw
{
	uint32_t		cycle;
	t_champ			champions[MAX_PLAYERS];
	uint8_t			ownership[MEM_SIZE];
    uint8_t         nplayers;
	uint32_t		dump_cycle;
	uint32_t 		kill_cycle;
}                   t_cw;

typedef struct      s_vm
{
	uint8_t			memory[MEM_SIZE];
    t_process       *process_list;
	uint8_t			nprocess;
    t_cw            corewar;
	t_bool 			debug_mode;
}                   t_vm;

typedef struct      s_champ
{
	int32_t			id;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	uint32_t		lives;
	uint32_t 		last_live;
}                   t_champ;

typedef struct		s_hdr
{
	uint32_t		magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	uint32_t		prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_hdr;

extern t_op g_op_tab[17];

void    cw_init(int ac, char **av);
void    cw_env_init(t_vm *vm);
void    cw_cleanup(t_vm *vm);
void    cw_read_args(t_vm *vm, int ac, char **av);
void    cw_start(t_vm *vm);

t_champ	*ch_search_champion(t_vm *vm, int32_t id);
void	ch_parse_champ_header(t_hdr *hdr, int fd);
void    ch_load_champ(t_vm *vm, int fd);


#endif