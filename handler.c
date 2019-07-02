#include "handler.h"

void    ft_live(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    t_champ     *champ; printf("[live]\n");
    int32_t     id;

    read_m(cinstr->argv[0], &id, REG_SIZE);
                                                           printf("Champion id: %d\n", id);
    champ = search_champion(vm, id);                                                  printf("at cycle: %d\n", vm->corewar.cycle);
    if (!champ)
        return ;
    LOG("Player %d (%s) is said to be alive\n", champ->id + 2, champ->name);
    champ->lives++; 
    champ->last_live = vm->corewar.cycle;
}

void    ft_ld(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    int32_t     rdi;
    int32_t     rsi;

    read_arg(cinstr, 0, &rdi, false);
    read_arg(cinstr, 1, &rsi, false);
    //if (cinstr->argvt[rsi] == INDIRECT_TYPE)

    cp->registers[rsi] = rdi;
    printf("[ld] argv: [ %d | %d ]\n", rdi, rsi);
}

void    ft_st(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    int32_t     rdi;
    int32_t     rsi;

    read_arg(cinstr, 0, &rdi, false);
    read_arg(cinstr, 1, &rsi, false);
    if (cinstr->argvt[1] == INDIRECT_TYPE)
        write_m(REL(cinstr->pc, rsi), &cp->registers[rdi], REG_SIZE);    
    else
        write_m(&cp->registers[rsi], &cp->registers[rdi], REG_SIZE); 
    printf("[st] argv: [ %d | %d ]\n", rdi, rsi);
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
    int32_t     rdi;
    int32_t     rsi;
    int32_t     rcx;
    t_byte      *ptr;

    ptr = cinstr->pc;
    read_arg(cinstr, 0, &rdi, true);
    read_arg(cinstr, 1, &rsi, true);
    if (cinstr->argvt[1] == REGISTER_TYPE)
        ptr = REL(ptr,  cp->registers[rsi]);
    else if (cinstr->argvt[1] == INDIRECT_TYPE)
    {
        read_m(REL(ptr, rsi), &rsi, 4);
        ptr += rsi % IDX_MOD;
    }
    read_arg(cinstr, 2, &rcx, true);
    if (cinstr->argvt[2] == REGISTER_TYPE)
        ptr = REL(ptr,  cp->registers[rcx]);
    else
        ptr = REL(ptr, rcx);
    write_m(ptr, &cp->registers[rdi], 4);
    printf("[sti] argv: [ %d | %d | %d]\n", rdi, rsi, rcx);
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

