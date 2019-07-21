/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:02:14 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/19 23:04:02 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar/corewar.h"

/**
 *  search through process list, find 
 *  the champion with the specific id and return 
 *  it 
 * 
 * @param {t_vm} vm - current vm structure
 * @param {int32_t} id - targeted champion's id
 */
t_champ *ch_search_champion(t_vm *vm, int32_t id)
{
    FOR_EACH(champ, vm->corewar.champions)
    {
        if (champ->id == id)
            return champ;
    }
    return (NULL);
}

/**
 *  parse the champion header into t_hdr
 *  the magic is in little endianess format
 * 
 * @param {t_hdr} hdr - current vm structure
 * @param {int} fd - file descriptor of the file where the
 *      champion is stored
 * 
 */
void    ch_parse_champ_header(t_hdr *hdr, int fd)
{
    off_t   siz;

    if (fd < 0)
        return ;
    if ((siz = lseek(fd, 0, SEEK_END)) == -1)
        PERROR("lseek");
    if ((size_t)siz < sizeof(t_hdr))
        ERROR("Invalid header size\n");
    if (lseek(fd, 0, SEEK_SET) == -1)
        PERROR("lseek");
    if (read(fd, hdr, sizeof(t_hdr)) != sizeof(t_hdr))
        PERROR("read");
    h_rev_bytes(&hdr->magic, sizeof(hdr->magic));
	if (hdr->magic != COREWAR_EXEC_MAGIC)
	{
        printf("%x %x\n", hdr->magic, COREWAR_EXEC_MAGIC);
        ERROR("Invalid header\n");
    }
    h_rev_bytes(&hdr->prog_size, sizeof(hdr->prog_size));
	if (hdr->prog_size != siz - sizeof(t_hdr))
        ERROR("Invalid header\n");
	if (hdr->prog_size > CHAMP_MAX_SIZE)
	{
        printf("%d %d\n", hdr->prog_size, CHAMP_MAX_SIZE);
        ERROR("Champion too large\n");
    }
}

/**
 *  read .cor from command line, parse the info and load it
 *  into the memory
 *  
 *  parse the header of the champion file into t_hdr
 *  copy the name of the champion and the comment into 
 *  t_champ and the t_champ goes into t_vm.champions
 *  the id of the champion will be the same as pid of
 *  the process, but when displaying to the terminal
 *  we need to +2 to the value (pid start at -1, but
 *  it's also the 1st process aka "player 1")
 * 
 *  the acutal byte codes of the champion will be copied 
 *  into the arena (vm.memory), and the corresponding
 *  process will be initialized, as you know, 
 *  a process is the instance of a champion that
 *  is being executed 
 * 
 * @param {t_vm} vm - current vm structure
 * @param {int} fd - file descriptor of the file where the
 *      champion is stored
 * 
 */
void    ch_load_champ(t_vm *vm, int fd)
{
    t_hdr               hdr;
    t_champ             *champ;
    static uint8_t      index;
    t_byte              *pc;

    ch_parse_champ_header(&hdr, fd);
    champ = &(vm->corewar.champions[index]);
	memcpy_(champ->name, hdr.prog_name, PROG_NAME_LENGTH);
	memcpy_(champ->comment, hdr.comment, COMMENT_LENGTH);
    champ->id = index - 1;
	pc = &vm->memory[(MEM_SIZE / vm->corewar.nplayers) * index];
	if (read(fd, pc, hdr.prog_size) != hdr.prog_size)
		PERROR("read");
    p_init_process(vm, pc);
    LOG("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",  champ->id + 2, 
        hdr.prog_size, champ->name, champ->comment);
    index++;
    close(fd);
}