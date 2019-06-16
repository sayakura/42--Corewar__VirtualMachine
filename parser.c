#include "vm.h"

void    parse_champ_header(t_hdr *hdr, int fd)
{
    off_t   siz;

    if (fd < 0)
        return ;
    if ((siz = lseek(fd, 0, SEEK_END)) == -1)
        PERROR("lseek");
    if (siz < sizeof(t_hdr))
        ERROR("Invalid header size");
    if (lseek(fd, 0, SEEK_SET) == -1)
        PERROR("lseek");
    if (read(fd, hdr, sizeof(t_hdr)) != sizeof(t_hdr))
        PERROR("read");
	if (hdr->magic != MAGIC_NUM_R)
		ERROR("Invalid header");
	if (hdr->prog_size != REVERSE_BIT(siz - sizeof(t_hdr)))
		ERROR("Invalid header");
	if (hdr->prog_size > REVERSE_BIT(CHAMP_MAX_SIZE))
		ERROR("Champion too large");
}