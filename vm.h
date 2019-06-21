/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:32:06 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/20 17:30:53 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
#define VM_H

#include <unistd.h>
#include "common.h"
#include "op.h"
#include "handler.h"

#define ITERATOR -1
#define INC(num) (++num)
#define EDI_TYPE (acb) (acb & 0b11000000)
#define ESI_TYPE (acb) (acb & 0b00110000)
#define ECX_TYPE (acb) (acb & 0b00001100)
#define REGISTER_TYPE 0b01000000
#define DIRECT_TYPE 0b10000000

typedef t_bool(*t_instr_hdlr)(t_arg_type *, t_byte **, t_bool *);

enum e_process_state
{
	CREATE,
	RUNNING,
	WAITING,
	TERMINATED
};

// typedef struct 		s_cpu
// {
// 	t_arg_type   argvt[MAX_ARGS_NUMBER];
//     uint8_t      *argv[MAX_ARGS_NUMBER];
// }					t_cpu;

typedef struct		s_op
{
	char			*name;
	int				argc;
	t_arg_type		argvt[MAX_ARGS_NUMBER];
	char			opcode;
	uint32_t		cycles;
	char			*des;
	t_bool			coding_byte;
	t_bool			direct;
}					t_op;


typedef struct		s_hdr
{
	uint32_t		magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	uint32_t		prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_hdr;

typedef struct 		s_task
{
	t_op			op_info;
	uint64_t		argv[MAX_ARGS_NUMBER];
}					t_task;

typedef struct      	s_process
{
    t_word         		registers[REG_NUMBER];
    int             	state;
    t_byte            	*pc;
	t_byte				*ip;
    uint8_t         	pid;
    int8_t          	carry : 1;
	t_task				cur_task;
	uint16_t			remaining_cycle;
	struct s_process	*next;
}                   	t_process;


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

extern t_op g_op_tab[17];
extern uint8_t	*g_base;
// parser
void			parse_champ_header(t_hdr *hdr, int fd);

// helper 
void    		rev_bytes(void *ptr, size_t n);
void			puthex(unsigned char c);

void    		print_mem(t_vm *vm);
void			bzero_(void *rsi, size_t rcx);
//loader
void    		loader(t_vm *vm, char *filename);

//process
void    		process_loop(t_vm   *vm);

#endif