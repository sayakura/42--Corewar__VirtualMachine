/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:32:06 by qpeng             #+#    #+#             */
/*   Updated: 2019/06/17 00:19:10 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
#define VM_H

 #include <unistd.h>
#include "common.h"
#include "op.h"

#define MAGIC_NUM_R 0x83F300EA

typedef struct		s_hdr
{
	uint32_t		magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	uint32_t		prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_hdr;

typedef struct      s_process
{
    int32_t         registers[REG_NUMBER];
    int             state;
    void            *pc;
    uint8_t         pid;
    int8_t          carry : 1;
}                   t_process;

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
	t_champ			champions[MAX_PLAYERS];
    
}                   t_cw;

typedef struct      s_loader
{
}                   t_loader;

typedef struct      s_vm
{
	uint8_t			memory[MEM_SIZE];
	uint8_t			ownership[MEM_SIZE];
    t_process       *process_list;
    t_cw            corewar;
    uint8_t         nplayers;
    
}                   t_vm;

// parser
void			parse_champ_header(t_hdr *hdr, int fd);

// helper 
unsigned int	reverseBits(unsigned int num);

//loader
void    		loader(t_vm *vm, char *filename);

#endif