#include "handler.h"

void    ft_live(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    t_champ     *champ; printf("[live]\n");
    int32_t     id;

    read_m(cinstr->argv[0], &id, REG_SIZE);                                                       printf("Champion id: %d\n", id);
    champ = search_champion(vm, id);                                                  printf("at cycle: %d\n", vm->corewar.cycle);
    if (!champ)
        return ;
    LOG("Player %d (%s) is said to be alive\n", champ->id + 2, champ->name);
    champ->lives++; 
    champ->last_live = vm->corewar.cycle;
}

void    ft_ld(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    int8_t      i;                          printf("ld trigger!\n");

    i = ITERATOR;
    while (++i < cinstr->argc)
    {
    }
}

void    ft_st(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    int8_t      i; printf("[st]\n");
    int32_t     rdi;

    rdi = 0;
    read_m(cinstr->argv[0], &i, 1);
    if (cinstr->argvt[1] == INDIRECT_TYPE)
    {
        read_m(cinstr->argv[1], &rdi, IND_SIZE);                         printf("First arg (indirect): %d\n", rdi);
        write_m(REL(cinstr->pc, rdi), &cp->registers[i], REG_SIZE);
    }
    else
    {
        read_m(cinstr->argv[1], &rdi, 1);                                printf("First arg (register): %d\n", rdi);
        cp->registers[rdi] = cp->registers[i];
    }
}

void    ft_add(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("add trigger!\n");
}

void    ft_sub(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("sub trigger!\n");
}

void    ft_and(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("and trigger!\n");
}

void    ft_or(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("or trigger!\n");
}

void    ft_xor(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("xor trigger!\n");
}

void    ft_zjmp(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("zjmp trigger!\n");
}

void    ft_ldi(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("ldi trigger!\n");
}

void    ft_sti(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    int8_t      i;  printf("[sti]\n");
    t_byte      *ptr;
    int32_t     offset;

    offset = 0;
    read_m(cinstr->argv[0], &i, 1);
    if (cinstr->argvt[1] == INDIRECT_TYPE) // todo: change this
        read_m(cinstr->argv[1], &offset, 2);
    else if (cinstr->argvt[1] == DIRECT_TYPE)
        read_m(cinstr->argv[1], &offset, 2);
    else
    {
        read_m(cinstr->argv[1], &offset, 1);
        offset = cp->registers[offset];
    }
    ptr = REL(cinstr->pc, offset);
    if (cinstr->argvt[2] == DIRECT_TYPE)
        read_m(cinstr->argv[2], &offset, 2);
    else
    {
        read_m(cinstr->argv[2], &offset, 1);
        offset = cp->registers[offset];
    }
    write_m(REL(ptr, offset), &cp->registers[i], DIR_SIZE);
}

void    ft_fork(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("fork trigger!\n");
}

void    ft_lld(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("lld trigger!\n");
}

void    ft_lldi(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("lldi trigger!\n");
}

void    ft_lfork(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("lfork trigger!\n");
}

void    ft_aff(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("aff trigger!\n");
}

