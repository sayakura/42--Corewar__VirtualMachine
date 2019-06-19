#include "vm.h"

void    parse_champ_header(t_hdr *hdr, int fd)
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
    rev_bytes(&hdr->magic, sizeof(hdr->magic));
	if (hdr->magic != COREWAR_EXEC_MAGIC)
	{
        printf("%x %x\n", hdr->magic, COREWAR_EXEC_MAGIC);
        ERROR("Invalid header\n");
    }
    rev_bytes(&hdr->prog_size, sizeof(hdr->prog_size));
	if (hdr->prog_size != siz - sizeof(t_hdr))
        ERROR("Invalid header\n");
	if (hdr->prog_size > CHAMP_MAX_SIZE)
	{
        printf("%d %d\n", hdr->prog_size, CHAMP_MAX_SIZE);
        ERROR("Champion too large\n");
    }
}