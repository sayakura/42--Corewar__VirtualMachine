/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:32:06 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/18 03:14:33 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
#define VM_H

#include <unistd.h>
#include "common.h"
#include "op.h"

enum e_process_state
{
	CREATE,
	RUNNING,
	WAITING,
	TERMINATED
};

typedef struct		s_op
{
	char			*name;
	int				argc;
	t_arg_type		argv[MAX_ARGS_NUMBER];
	char			opcode;
	uint32_t		cycles;
	char			*des;
	bool			coding_byte;
	bool			direct;
}					t_op;

typedef struct		s_hdr
{
	uint32_t		magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	uint32_t		prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_hdr;

typedef struct      	s_process
{
    int32_t         	registers[REG_NUMBER];
    int             	state;
    void            	*pc;
    uint8_t         	pid;
    int8_t          	carry : 1;
	struct s_process	*next;
}                   	t_process;

typedef struct      s_instr
{
    


}                   t_instr;


typedef struct      s_champ
{
	int8_t			id;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
}                   t_champ;

typedef struct      s_cw
{
	uint32_t		cycle;
	t_champ			champions[MAX_PLAYERS];
	uint8_t			ownership[MEM_SIZE];
	uint32_t		dump_cycle;
	uint32_t 		kill_cycle;
}                   t_cw;

typedef struct      s_loader
{
}                   t_loader;

typedef struct      s_vm
{
	uint8_t			memory[MEM_SIZE];
    t_process       *process_list;
	uint8_t			nprocess;
    uint8_t         nplayers;
    t_cw            corewar;
}                   t_vm;

// parser
void			parse_champ_header(t_hdr *hdr, int fd);

// helper 
void    		rev_bytes(void *ptr, size_t n);
void			puthex(unsigned char c);

void    		print_mem(t_vm *vm);
void			bzero_(void *rsi, size_t rcx);
//loader
void    		loader(t_vm *vm, char *filename);

#endif